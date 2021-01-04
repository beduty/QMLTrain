import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12

Window {
    visible: true
    width: 1200
    height: 850
    title: qsTr("Roi Setting")
    property int nRoiCnt: 1

    Rectangle{
        id : roiArea
        width: 800
        height: 800
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color: "aliceblue"
        Text {
            id: name
            text: qsTr("Roi Setting Board")
            anchors.centerIn: parent
        }
        Rectangle{
            anchors.fill: parent
            radius: width/2 - 3
            border.color: "gray"
            border.width: 2
            opacity: 0.5
        }

        function activateRoi(index){
            for(var i = 0; i < rois.count; i++)
            {
                var curRoi = rois.itemAt(i);
                if(curRoi.index === index) {
                    curRoi.z = 1
                    curRoi.active = true
                }
                else{
                    curRoi.z = 0
                    curRoi.active = false
                }
            }
        }
        function updateRoiIdx(){
            for(var i = 0; i < roiModel.count; i++)
            {
                var curRoi = roiModel.get(i)
                curRoi.roiIndex = i+1
            }
        }

        ListModel{
            id : roiModel
            ListElement{ roiIndex : 1; roiX : 375; roiY : 375; roiW : 50; roiH : 50; roiAngle : 0}
        }

        Repeater{
            id : rois
            model: roiModel
            delegate: Roi{
                index: roiIndex
                x : roiX
                y : roiY
                width: roiW
                height:roiH
                rotation: roiAngle
                parentMinX : 0
                parentMaxX : roiArea.width
                parentMinY : 0
                parentMaxY : roiArea.height
                active:false
                onActivated: {
                    roiArea.activateRoi(index)
                    spinBoxRoiIdx.value = index
                    lstRoiInfo.currentIndex = roiModel.count
                    lstRoiInfo.currentIndex = index-1
                }
                onXChanged: {roiX = x}
                onYChanged: {roiY = y}
                onWidthChanged: {roiW = width}
                onHeightChanged: {roiH = height}
                onRotationChanged: {roiAngle = rotation}
            }
        }
    }

    Button {
        id: btnRoiAdd
        x: 806
        y: 25
        width: 80
        height: 40
        text: qsTr("Add")
        onClicked: {
            nRoiCnt++
            var idx = nRoiCnt
            var radius = 150
            if(idx > 13)
                radius = 300
            var roiX= 375+radius*Math.cos((30*nRoiCnt*Math.PI/180))
            var roiY= 375+radius*Math.sin((30*nRoiCnt*Math.PI/180))
            roiModel.append({ "roiIndex" : idx, "roiX" : roiX, "roiY" : roiY, "roiW" : 50, "roiH" : 50})
        }
    }

    Button {
        id: btnRoiRemoveLast
        x: 892
        y: 25
        width: 81
        height: 40
        text: qsTr("Remove")
        onClicked: {
            nRoiCnt--
            if(nRoiCnt<0)
                nRoiCnt = 0
            var idx = nRoiCnt
            if(roiModel.count !=0){
                roiModel.remove(nRoiCnt)
            }
        }
    }

    Button {
        id: btnRoiRemoveSel
        x: 1110
        y: 25
        width: 81
        height: 40
        text: qsTr("Remove")
        onClicked: {
            nRoiCnt--
            if(nRoiCnt<0)
                nRoiCnt = 0
            var selRoiIdx= spinBoxRoiIdx.value
            roiModel.remove(selRoiIdx-1)
            roiArea.updateRoiIdx()
        }
    }

    Frame {
        id: frame
        x: 806
        y: 71
        width: 385
        height: 754
        ListView {
            id: lstRoiInfo
            anchors.fill: parent
            model:roiModel
            focus: true
            delegate: Item{
                implicitWidth: lstRoiInfo.implicitWidth
                implicitHeight: textRow.implicitHeight
                RowLayout{
                    id : textRow
                    spacing: 15
                    Text {
                        text: model.roiIndex
                        Layout.fillWidth: true
                        Layout.preferredWidth: 33
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 18
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                lstRoiInfo.currentIndex = roiModel.count
                                lstRoiInfo.currentIndex = index
                                roiArea.activateRoi(index+1)
                                spinBoxRoiIdx.value = index+1
                            }
                        }
                    }
                    TextField{
                        text: model.roiX.toFixed(0)
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 14
                        onAccepted: {
                            var curRoi = roiModel.get(index)
                            curRoi.roiX = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = roiModel.count
                            lstRoiInfo.currentIndex = index
                            roiArea.activateRoi(index+1)
                            spinBoxRoiIdx.value = index+1
                        }
                    }
                    TextField {
                        text: model.roiY.toFixed(0)
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 14
                        onAccepted: {
                            var curRoi = roiModel.get(index)
                            curRoi.roiY = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = roiModel.count
                            lstRoiInfo.currentIndex = index
                            roiArea.activateRoi(index+1)
                            spinBoxRoiIdx.value = index+1
                        }
                    }
                    TextField {
                        text: model.roiW.toFixed(0)
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 14
                        onAccepted: {
                            var curRoi = roiModel.get(index)
                            curRoi.roiW = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = roiModel.count
                            lstRoiInfo.currentIndex = index
                            roiArea.activateRoi(index+1)
                            spinBoxRoiIdx.value = index+1
                        }
                    }
                    TextField {
                        text: model.roiH.toFixed(0)
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 14
                        onAccepted: {
                            var curRoi = roiModel.get(index)
                            curRoi.roiH = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = roiModel.count
                            lstRoiInfo.currentIndex = index
                            roiArea.activateRoi(index+1)
                            spinBoxRoiIdx.value = index+1
                        }
                    }
                    TextField {
                        text: model.roiAngle.toFixed(0)
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 14
                        onAccepted: {
                            var curRoi = roiModel.get(index)
                            curRoi.roiAngle = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = roiModel.count
                            lstRoiInfo.currentIndex = index
                            roiArea.activateRoi(index+1)
                            spinBoxRoiIdx.value = index+1
                        }
                    }
                }
            }
            highlight: Rectangle{
                width: lstRoiInfo.width
                color: "blue"
                opacity: 0.1
                radius: 14
                z : 3
            }
            highlightFollowsCurrentItem: true;
            highlightResizeVelocity: 0

            header: Item{
                implicitWidth: lstRoiInfo.implicitWidth
                implicitHeight: textRowHeader.implicitHeight+10
                RowLayout{
                    id : textRowHeader
                    spacing: 20
                    Text {
                        text: "Idx"
                        Layout.fillWidth: true
                        Layout.preferredWidth: 30
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 16
                    }
                    Repeater{
                        model: ["X", "Y", "W", "H", "A"]
                        delegate: Text {
                           text: modelData
                           Layout.fillWidth: true
                           Layout.preferredWidth: 45
                           horizontalAlignment: Text.AlignHCenter
                           font.family: "Arial"; font.pointSize: 14
                        }
                    }
                }
            }
        }
    }

    SpinBox {
        id: spinBoxRoiIdx
        x: 980
        y: 25
        width: 123
        height: 40
        from: 0
        to : roiModel.count
        value: 0
        onValueChanged: {
            roiArea.activateRoi(value)
        }
    }
}
