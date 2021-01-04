import QtQuick 2.0

Item {
    id : root
    anchors.centerIn: parent
    property color colorNeedle
    property color colorCenter
    property int  lengthNeedle

    Rectangle {
        id: center
        x: 151
        y: 172
        width: lengthNeedle/10
        height: width
        color: colorNeedle//"#00ffff"
        radius: width/2
        anchors.centerIn: parent
        Rectangle {
            id: needle
            x: 7
            y: 7
            width: 6
            height: lengthNeedle//250
            color: colorNeedle//"#00ffff"
            radius: 8
            anchors.centerIn: parent
            anchors.verticalCenterOffset: 80
        }
        Rectangle {
            id: centerPoint
            x: 0
            y: 0
            width: lengthNeedle/20//16
            height: width
            color: colorCenter//"#c31515"
            radius: width/2
            anchors.centerIn: parent
        }
    }
}
