import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    id : mainWindow
    property real dp: Math.min(width, height)/400
    property string title: ""
    property real topbarHeight: Math.floor(50*dp);
    visible: true
    width: 375
    height: 667
    color: "#404040"
    Rectangle{
        id : topArea
        width: parent.width
        height: Math.floor(25*dp);
        color: "#404040"
        Text {
            id: textItem
            anchors.centerIn: parent
            color: "#C0C0C0"
            text: mainWindow.title

            Behavior on text {
                // text가 변경되었을때, 수행되는 Animation을 정의한다.
                SequentialAnimation{
                    NumberAnimation{
                        target: textItem
                        property: "anchors.verticalCenterOffset"
                        to : -20 *dp
                        duration: 1000
                        easing.type: Easing.InOutQuad
                    }
                    PropertyAction{
                        target: textItem
                        property: "text"
                    }
                    NumberAnimation{
                        target: textItem
                        property: "anchors.verticalCenterOffset"
                        to : 0
                        duration: 1000
                        easing.type: Easing.InOutQuad
                    }
                }
            }
        }
    }
    Rectangle{
        id : topSecondArea
        anchors.top: topArea.bottom
        width: parent.width
        height: mainWindow.topbarHeight
        gradient: Gradient{
            GradientStop{position: 0.0; color: "#303030"}
            GradientStop{position: 0.4; color: "#101010"}
            GradientStop{position: 1.0; color: "#292929"}
        }
        Text{
            id : titleTextItem
            anchors.centerIn: parent
            font.bold: true
            font.pixelSize: 14*dp
            color: "#f0f0f0"
            text: "QNanoPainter Exaple Gallery"
            visible: galleryLoader.source == ""//
        }
    }
    ListModel{
        id : galleryModel
        ListElement{ name : "Features" ; path : "features"}
        ListElement{ name : "Event Boxes"; path : "" }
        ListElement{ name : "Drawing"; path : "" }
    }
    ListView{
        id : listView
        orientation: ListView.Vertical
        anchors.top: topSecondArea.bottom
        anchors.bottom: parent.bottom
        width: parent.width
        model: galleryModel
        opacity: galleryLoader.source == ""
        visible: opacity
        Behavior on opacity {
            // opacity가 변할때 Trigger되어 Animation 동작한다.
            // NumberAnimation으로 0->1 또는 1->0 으로 스무스하게 변한다.
            NumberAnimation{
                duration: 200
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
                opacity: 1
            }
            MouseArea{
                id : delegateMouseArea
                anchors.fill: parent
                onClicked: {
                    mainWindow.title =model.name
                    galleryLoader.loadDemo(model.path)
                }
            }
            Image{
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 25* dp
                width: 20*dp
                height: 20*dp
                rotation: 180
                source: "qrc:/back.png"
                opacity: 1
            }
            Rectangle{
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                width: parent.width*0.9
                height: Math.ceil(1*dp)
                color: "#606060"
            }
        }
    }
    Loader{
        id : galleryLoader
        function loadDemo(path){
            galleryLoader.source = path + "/mainView.qml"
        }
        function closeDemo(path){
            mainWindow.title = "";
            galleryLoader.source = "";
        }
        anchors.top:topArea.bottom
        anchors.bottom: parent.bottom
        width: parent.width

        Behavior on source {
            SequentialAnimation{
                NumberAnimation{
                    target: galleryLoader
                    property: "opacity"
                    to : 0
                    duration: galleryLoader.source == "" ? 0 : 500
                    easing.type : Easing.InOutQuad
                }
                PropertyAction{
                    target: galleryLoader
                    property: "source"
                }
                NumberAnimation{
                    target: galleryLoader
                    property: "opacity"
                    to : 1
                    duration: 500
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
    Image{
        property real animationState: galleryLoader.source != ""
        Behavior on animationState {
            NumberAnimation{
                duration: 200
                easing.type: Easing.InOutQuad
            }
        }

        anchors.verticalCenter: topSecondArea.verticalCenter
        width: 20*dp
        height: 20*dp
        x : animationState * 5 * dp
        source: "qrc:/back.png"
        opacity: backMouseArea.pressed ? 0.4 : 1.0*animationState
        enabled: opacity
        MouseArea{
            id : backMouseArea
            anchors.fill: parent
            anchors.margins: -15 * dp
            onClicked: {
                galleryLoader.closeDemo()
            }
        }
    }
}


















