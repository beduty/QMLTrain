import QtQuick 2.12
import QtQuick.Window 2.12
import HelloItem 1.0

Window {
    id: mainWindow
    visible: true
    width: 640
    height: 480
    title: ""
    property real dp: Math.min(width, height)/400
    property real topbarHeight: Math.floor(50*dp)
    color: "#404040"

    Rectangle{
        id: topArea
        width: parent.width
        height: Math.floor(25*dp)
        color: "#404040"
        Text {
            id: textItem
            anchors.centerIn: parent
            font.pixelSize: 12*dp
            color: "#E0E0E0"
            text: mainWindow.title
            Behavior on text {
                SequentialAnimation {
                    NumberAnimation {
                        target: textItem
                        property: "anchors.verticalCenterOffset"
                        to: -20 * dp
                        duration: 500
                        easing.type: Easing.InOutQuad
                    }
                    PropertyAction {
                        target: textItem
                        property: "text"
                    }
                    NumberAnimation {
                        target: textItem
                        property: "anchors.verticalCenterOffset"
                        to: 0
                        duration: 500
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
        Component.onCompleted: {
            mainWindow.title = "Menu"
        }
    }
    Rectangle{
        id:topSecondArea
        anchors.top:topArea.bottom
        width: parent.width
        height: mainWindow.topbarHeight
        gradient: Gradient{
            GradientStop{position: 0.0; color: "#303030"}
            GradientStop{position: 0.4; color: "#101010"}
            GradientStop{position: 1.0; color: "#292929"}
        }
        Text {
            id: titleTextItem
            anchors.centerIn: parent
            font.pixelSize: 14*dp
            font.bold: true
            color: "#f0f0f0"
            text: qsTr("QNanoPainter Examples Gallery")
            visible: galleryLoader.source == ""
        }
    }

    ListModel{
        id: galleryModel
        ListElement{name: "QNanoPainter Features" ;path: "qnanopainter_features"}
        ListElement{name: "Mouse Event Boxes" ;path: "mouse_events"}
        ListElement{name: "Freehand Painting" ;path: "painting"}
    }
    ListView{
        id : listView
        anchors.top: topSecondArea.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        model: galleryModel
        orientation: ListView.Vertical
        maximumFlickVelocity: 10000
        highlightMoveDuration: 2500
        visible: opacity // 없어지는 것이 아니라, 사라지는 것이다!
        // ListView만 사라지므로, topArea와 topSecondArea는 그대로 배경에 남아있다.
        opacity: galleryLoader.source == ""
        Behavior on opacity {
            NumberAnimation {
                duration: 500
                easing.type: Easing.InOutQuad
            }
        }
        delegate: Item{
            width: listView.width
            height: 75*dp
            Text{
                id : delegateTextItem
                anchors.centerIn: parent
                font.pixelSize: 20*dp
                color: "#b0b0b0"
                text: model.name
                opacity: delegateMouseArea.pressed? 0.4:1.0
            }
            MouseArea{
                id: delegateMouseArea
                anchors.fill: parent
                onClicked: {
                    mainWindow.title = model.name;
                    galleryLoader.loadDemo(model.path);
                }
            }
            Image {
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 25*dp
                width: 20*dp
                height: 20*dp
                rotation: 180
                source: "back.png"
                opacity: delegateMouseArea.pressed ? 0.4 : 1.0
            }
            Rectangle{
                // ListView 아이템간 구분선이다.
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                width: parent.width*0.9
                height: Math.ceil(1*dp)
                color: "#606060"
            }
        }
    }

    Loader {
        // 덮어쓰는게 아니라, 그냥 Item만 올린다. 아래 배경이 있으면, 그대로 배경이 동일하다.
        // 사라지는 것만 빼면, 나머지는 그대로 남아있다.
        id: galleryLoader
        function loadDemo(path) {
            galleryLoader.source = path + "/main.qml";
        }
        function closeDemo() {
            mainWindow.title = "";
            galleryLoader.source = "";
        }
        // height가 계산된다.
        anchors.top: topArea.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        // galleryLoader.source 바뀌면 호출된다.
        // "opacity" 0->1로 스르륵~ 나타난다.
        Behavior on source {
            SequentialAnimation {
                NumberAnimation {
                    target: galleryLoader
                    property: "opacity"
                    to: 0
                    duration: galleryLoader.source == "" ? 0 : 500
                    easing.type: Easing.InOutQuad
                }
                PropertyAction {
                    target: galleryLoader
                    property: "source"
                }
                NumberAnimation {
                    target: galleryLoader
                    property: "opacity"
                    to: 1
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }

    Image {
        property real animationState: galleryLoader.source != ""
        // galleryLoader.source의 내용이 있고 없고에 따라서 0과 1로 바뀐다.
        // Behavior NumberAnimation으로 넣었기 때문에, 0->1 혹은 1->0으로 스무스하게 바뀐다.
        Behavior on animationState {
            NumberAnimation {
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }
        x: animationState * 5 * dp // 0~1로 바뀌면서 x가 (0) ~ (5*dp)로 애니메이션으로 바뀐다.
        anchors.verticalCenter: topSecondArea.verticalCenter
        width: 20 * dp
        height: 20 * dp
        source: "back.png"
        enabled: opacity // animationState가 0또는 1에 따라서 opacity가 결정된다.! enable false면, onClicked가 되지 않는다.
        opacity: backMouseArea.pressed ? 0.4 : 1.0 * animationState
        MouseArea {
            id: backMouseArea
            anchors.fill: parent
            anchors.margins: -15 * dp
            onClicked: {
                galleryLoader.closeDemo();
            }
        }
    }
}
