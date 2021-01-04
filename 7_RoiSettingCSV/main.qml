import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.12
import CRoiInfoFile 1.0
import RoiItem 1.0
import QtQuick.Dialogs 1.1

Window {
    visible: true
    width: 1200
    height: 850
    title: qsTr("Roi Setting")
    property int nRoiCnt: readRoiInfo.roiList.length

    CRoiInfoFile{
        id : readRoiInfo
//        roiList: [
//            RoiItem{
//                idx: 1
//                roiX : 375; roiY : 375; roiW : 50; roiH : 50;roiA : 0;
//            }
//        ]
    }
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
            for(var i = 0; i < readRoiInfo.roiList.length; i++)
            {
                var curRoi = readRoiInfo.roiList[i]
                curRoi.idx = i+1
            }
        }
        Repeater{
            id : rois
            model: readRoiInfo.roiList
            delegate: Roi{
                index: idx
                x : roiX;     y : roiY
                width: roiW;  height:roiH
                rotation: roiA
                parentMinX : 0; parentMaxX : roiArea.width
                parentMinY : 0; parentMaxY : roiArea.height
                active:false
                onActivated: {
                    roiArea.activateRoi(index)
                    spinBoxRoiIdx.value = index
                    lstRoiInfo.currentIndex = readRoiInfo.roiList.length
                    lstRoiInfo.currentIndex = index-1
                }
                onXChanged: {roiX = x}
                onYChanged: {roiY = y}
                onWidthChanged: {roiW = width}
                onHeightChanged: {roiH = height}
                onRotationChanged: {roiA = rotation}
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
            var radius = 125
            if(idx > 13)
                radius = 230
            if(idx > 25)
                radius = 335
            var roiX= 375+radius*Math.cos((30*nRoiCnt*Math.PI/180))
            var roiY= 375+radius*Math.sin((30*nRoiCnt*Math.PI/180))
            readRoiInfo.addRoi(nRoiCnt,roiX,roiY,35,35,45);
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
            if(readRoiInfo.roiList.length !==0){
                readRoiInfo.removeRoi(nRoiCnt)
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
            readRoiInfo.removeRoi(selRoiIdx-1)
            roiArea.updateRoiIdx()
        }
    }

    Frame {
        id: frame
        x: 806
        y: 71
        width: 385
        height: 710
        ListView {
            id: lstRoiInfo
            anchors.fill: parent
            model:readRoiInfo.roiList
            focus: true
            delegate: Item{
                implicitWidth: lstRoiInfo.implicitWidth
                implicitHeight: textRow.implicitHeight
                RowLayout{
                    id : textRow
                    spacing: 15
                    Text {
                        text: model.idx
                        Layout.fillWidth: true
                        Layout.preferredWidth: 33
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 18
                        MouseArea{
                            anchors.fill: parent
                            onClicked: {
                                lstRoiInfo.currentIndex = readRoiInfo.roiList.length
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
                            var curRoi = readRoiInfo.roiList[index]
                            curRoi.roiX = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = readRoiInfo.roiList.length
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
                            var curRoi = readRoiInfo.roiList[index]
                            curRoi.roiY = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = readRoiInfo.roiList.length
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
                            var curRoi = readRoiInfo.roiList[index]
                            curRoi.roiW = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = readRoiInfo.roiList.length
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
                            var curRoi = readRoiInfo.roiList[index]
                            curRoi.roiH = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = readRoiInfo.roiList.length
                            lstRoiInfo.currentIndex = index
                            roiArea.activateRoi(index+1)
                            spinBoxRoiIdx.value = index+1
                        }
                    }
                    TextField {
                        text: model.roiA.toFixed(0)
                        Layout.fillWidth: true
                        Layout.preferredWidth: 50
                        horizontalAlignment: Text.AlignHCenter
                        font.family: "Arial"; font.pointSize: 14
                        onAccepted: {
                            var curRoi = readRoiInfo.roiList[index]
                            curRoi.roiAngle = Number(text)
                        }
                        onPressed: {
                            lstRoiInfo.currentIndex = readRoiInfo.roiList.length
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
        to : readRoiInfo.roiList.length
        value: 0
        onValueChanged: {
            roiArea.activateRoi(value)
        }
    }

    Button {
        id: btnSaveFile
        x: 806
        y: 787
        width: 385
        height: 38
        text: qsTr("Save Roi Info to File")
        onClicked: {
            readRoiInfo.save2File("text")
        }
    }
}
