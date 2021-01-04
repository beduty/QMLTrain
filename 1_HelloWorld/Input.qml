import QtQuick 2.0
import QtQuick.Window 2.13
import QtQuick.Controls 2.13

Item {
    x:0
    y:0
    width: 280
    height: 420

    signal btnEnterClicked()
    signal btnCancelClicked()
    property string inputVal;
    property int dataType;
    property color btnColor: "green"
    property double dMinVal : 0.001
    property double dMaxVal : 0.350

ApplicationWindow{
    width: 280
    height: 420
    id : inputPad

    Rectangle {
        id: rectangle
        x: 18
        y: 19
        width: 245
        height: 30
        color: "#ffffff"
        radius: 7
        clip: false
        Text {
            id: title
            color: "#3f3838"
            text: qsTr("KeyPad")
            anchors.fill: parent
            font.bold: true
            styleColor: "#fd7d7d"
            verticalAlignment: Text.AlignVCenter
            font.family: "Arial"
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 20
        }
        border.width: 2
        layer.smooth: false
        border.color: "#433c3c"
    }

    Button {
        id: btnOK
        x: 18
        y: 365
        width: 120
        text: qsTr("Enter")
        layer.format: ShaderEffectSource.RGBA
        flat: false
        highlighted: false
        checkable: false
    }

    Button {
        id: btnCancel
        x: 146
        y: 365
        width: 120
        height: 40
        text: qsTr("Cancel")
    }

    Connections {
        target: btnOK
        onClicked: {
            inputVal = textInput.text
            btnEnterClicked()
        }
    }

    Connections {
        target: btnCancel
        onClicked: {
            btnCancelClicked()
        }
    }


    Rectangle {
        id: rectangle1
        x: 18
        y: 62
        width: 160
        height: 41
        color: "#eeebeb"
        radius: 5

        TextEdit {
            id: textInput
            text: qsTr("0.000")
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent
            font.family: "Arial"
            readOnly: true
            textFormat: Text.PlainText
            font.pixelSize: 20
        }
    }
    ToolSeparator {
        id: toolSeparator
        x: 18
        y: 346
        width: 248
        height: 13
        orientation: Qt.Horizontal
    }
    Button {
        id: btnKey_1
        x: 18
        y: 119
        width: 50
        height: 50
        text: qsTr("1")
        highlighted: false
        font.bold: true
        font.pointSize: 20
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "1"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_2
        x: 75
        y: 117
        width: 50
        height: 50
        text: qsTr("2")
        font.bold: true
        font.pointSize: 20
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "2"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_3
        x: 132
        y: 117
        width: 50
        height: 50
        text: qsTr("3")
        font.bold: true
        font.pointSize: 20
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "3"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_4
        x: 18
        y: 174
        width: 50
        height: 50
        text: qsTr("4")
        font.bold: true
        font.pointSize: 20
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "4"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_5
        x: 75
        y: 174
        width: 50
        height: 50
        text: qsTr("5")
        font.bold: true
        font.family: "Arial"
        font.pointSize: 20
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "5"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_6
        x: 132
        y: 174
        width: 50
        height: 50
        text: qsTr("6")
        font.bold: true
        font.family: "Arial"
        font.pointSize: 20
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "6"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_7
        x: 18
        y: 230
        width: 50
        height: 50
        text: qsTr("7")
        font.bold: true
        font.pointSize: 20
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "7"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_8
        x: 75
        y: 230
        width: 50
        height: 50
        text: qsTr("8")
        font.bold: true
        font.family: "Arial"
        font.pointSize: 20
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "8"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_9
        x: 132
        y: 230
        width: 50
        height: 50
        text: qsTr("9")
        font.bold: true
        font.family: "Arial"
        font.pointSize: 20
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "9"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_0
        x: 18
        y: 287
        width: 50
        height: 50
        text: qsTr("0")
        font.bold: true
        font.family: "Arial"
        font.pointSize: 20
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "0"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_Comma
        x: 75
        y: 287
        width: 50
        height: 50
        text: qsTr(".")
        font.bold: true
        font.pointSize: 20
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "."
            textInput.text = text
        }
    }

    Button {
        id: btnKey_Dash
        x: 132
        y: 287
        width: 50
        height: 50
        text: qsTr("_")
        font.bold: true
        font.pointSize: 20
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text
            text += "_"
            textInput.text = text
        }
    }

    Button {
        id: btnKey_Back
        x: 188
        y: 117
        width: 78
        height: 50
        text: qsTr("Back")
        font.bold: true
        font.family: "Arial"
        font.pointSize: 18
        palette { button: btnColor }
        onClicked: {
            var text = textInput.text.slice(0, -1)
            textInput.text = text
        }
    }

    Button {
        id: btnKey_Clear
        x: 188
        y: 174
        width: 78
        height: 50
        text: qsTr("Clear")
        font.bold: true
        font.pointSize: 18
        font.family: "Arial"
        palette { button: btnColor }
        onClicked: {
            textInput.text = ""
        }
    }

    Text {
        id: element
        x: 189
        y: 66
        text: qsTr("Min :")
        font.pixelSize: 12
    }

    Text {
        id: element1
        x: 189
        y: 85
        text: qsTr("Max :")
        font.pixelSize: 12
    }

    Text {
        id: txtMinVal
        x: 226
        y: 66
        text: dMinVal
        font.pixelSize: 12
    }

    Text {
        id: txtMaxVal
        x: 226
        y: 85
        text: dMaxVal
        font.pixelSize: 12
    }
}

    function openInputPad(type, minVal, maxVal){
        dMinVal = minVal
        dMaxVal = maxVal
        dataType = (type);
        inputPad.show();
    }
    function closeInputPad (){
        inputPad.close();
    }
}



