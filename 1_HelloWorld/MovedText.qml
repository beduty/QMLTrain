import QtQuick 2.14

Item {
    property string textMsg
    property color textColor
    property int pixelSize

    Text {
        id: title
        width: 176
        height: 36
        //color: "#45d366"
        color: textColor
        //text: qsTr("Hello World~")
        text: qsTr(textMsg)
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.top: parent.top
        anchors.topMargin: 20
        font.bold: true
        font.family: "Arial"
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: pixelSize
    }
    SequentialAnimation
    {
        running : true
        loops : Animation.Infinite
        XAnimator{
            target: title
            to : 120
            from: 0
            duration: 3000
        }
        XAnimator{
            target: title
            to : 0
            from: 120
            duration: 3000
        }
    }
}
