import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.13
import FileIO 1.0
import RcpInfo 1.0
import "./"

Window {
    id: mainWnd
    visible: true
    width: 550
    height: 400
    title: qsTr("Read File")
    FileIO{
        id : myFile
        source: ":/res/my_file.txt"
        onError: console.log(msg)
    }

    RcpInfo{
        id : rcpInfo
        dInspRange: 1.1
        dStPos: 2.2
        dScanOffset: 3.3
        dFilter: 4.4
    }


    Component.onCompleted: {
        //console.log(myFile.read())
        textReadField.text = myFile.read()
    }

    Input{
        id : myInputPad
        onBtnEnterClicked: {
            var floatNumber = parseFloat(myInputPad.inputVal);
            if(floatNumber < myInputPad.dMinVal ||  myInputPad.dMaxVal < floatNumber)
            {
                floatNumber = NaN;
            }
            if(myInputPad.dataType === 0){
                //valStPos.text= floatNumber
                rcpInfo.dStPos =floatNumber
            }
            else if(myInputPad.dataType === 1){
                //valScanOffset.text= floatNumber
                rcpInfo.dScanOffset =floatNumber
            }
            else if(myInputPad.dataType === 2){
                //valInspRange.text= floatNumber
                rcpInfo.dInspRange =floatNumber
            }
            else if(myInputPad.dataType === 3){
                //valFilter.text= floatNumber
                rcpInfo.dFilter =floatNumber
            }
            myInputPad.closeInputPad()
        }
        onBtnCancelClicked: {
            myInputPad.closeInputPad()
        }
    }

    property alias valStPos: valStPos
    property variant win;  // you can hold this as a reference..

    MovedText{
        textMsg: "Melani~~"
        textColor: "#45d366"
        pixelSize: 25
    }

    Text {
        id: titleRetry
        x: 32
        y: 68
        color: "#515559"
        text: qsTr("Retry")
        font.bold: true
        font.family: "Arial"
        font.pixelSize: 20
    }

    Text {
        id: titleStPos
        x: 47
        y: 111
        color: "#515559"
        text: qsTr("St.Pos")
        font.bold: true
        font.family: "Arial"
        font.pixelSize: 18
    }

    Text {
        id: titleScanOffset
        x: 47
        y: 147
        color: "#515559"
        text: qsTr("ScanOffset")
        font.bold: true
        font.pixelSize: 18
        font.family: "Arial"
    }

    Text {
        id: titleInspRange
        x: 47
        y: 182
        color: "#515559"
        text: qsTr("InspRange")
        font.bold: true
        font.family: "Arial"
        font.pixelSize: 18
    }

    Text {
        id: titleFilter
        x: 47
        y: 218
        color: "#515559"
        text: qsTr("Filter")
        font.bold: true
        font.pixelSize: 18
        font.family: "Arial"
    }

    Image {
        id: image
        x: 304
        y: 59
        width: 227
        height: 193
        source: "res/melani.PNG"
        fillMode: Image.PreserveAspectFit
    }

    MouseArea {
        id: inputStPos
        x: 180
        y: 109
        width: 93
        height: 29

        Text {
            id: valStPos
            x: 180
            color: "#515559"
            text: Number(rcpInfo.dStPos).toFixed(3).toString()
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.bold: true
            font.pixelSize: 18
            font.family: "Arial"
        }
        onDoubleClicked : {
            myInputPad.openInputPad(0, 0.0, 18.5)
        }
    }

    MouseArea {
        id: inputScanOffset
        x: 180
        y: 147
        width: 93
        height: 29
        Text {
            id: valScanOffset
            x: 180
            y: 147
            color: "#515559"
            text: Number(rcpInfo.dScanOffset).toFixed(3).toString()
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
            font.family: "Arial"
            anchors.fill: parent
            font.bold: true
        }
        onDoubleClicked : {
            myInputPad.openInputPad(1, 0.0, 30.0)
        }
    }

    MouseArea {
        id: inputInspRange
        x: 180
        y: 182
        width: 93
        height: 29
        Text {
            id: valInspRange
            x: 180
            color: "#515559"
            text: Number(rcpInfo.dInspRange).toFixed(3).toString()
            anchors.rightMargin: 0
            anchors.bottomMargin: 1
            anchors.leftMargin: 0
            anchors.topMargin: -1
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
            font.family: "Arial"
            anchors.fill: parent
            font.bold: true
        }
        onDoubleClicked : {
            myInputPad.openInputPad(2, 150.0, 322.0)
        }
    }

    MouseArea {
        id: inputFilter
        x: 180
        y: 218
        width: 93
        height: 29
        Text {
            id: valFilter
            color: "#515559"
            text:  Number(rcpInfo.dFilter).toFixed(3).toString()
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 18
            horizontalAlignment: Text.AlignHCenter
            font.family: "Arial"
            font.bold: true
        }
        onDoubleClicked : {
            myInputPad.openInputPad(3, 0.0, 3.0)
        }
    }

    Button {
        id: btnWriteRcp
        x: 163
        y: 264
        text: qsTr("Write Rcp")
    }

    Connections {
        target: btnReadRcp
        onClicked: {
            rcpInfo.read();
        }
    }

    Connections {
        target: btnWriteRcp
        onClicked:  {
            rcpInfo.write();
        }
    }

    Flickable {
        id: flickable
        x: 47
        y: 323
        width: 477
        height: 68
        contentHeight: textReadField.implicitHeight // height 설정해주지 않으면 스크롤 되지 않는다.
        clip: true // clip 설정해주면 텍스트가 다른 컨트롤을 침범하지 않는다.
        Text {
            id: textReadField
            color: "#0964ba"
            text: qsTr("read data..")
            anchors.fill: parent
            font.pixelSize: 15
            font.family: "Arial"
            font.bold: true
            wrapMode: Text.WordWrap
        }
        ScrollBar.vertical: ScrollBar {
            active: flickable.moving //|| !flick.moving
        }
    }

    Button {
        id: btnReadRcp
        x: 54
        y: 264
        text: qsTr("Read Rcp")
    }

}

/*##^##
Designer {
    D{i:23;anchors_height:48;anchors_width:478;anchors_x:"-351";anchors_y:30}
}
##^##*/
