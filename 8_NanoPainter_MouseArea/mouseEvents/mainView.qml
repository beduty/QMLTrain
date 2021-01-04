import QtQuick 2.0
import MouseEventItem 1.0

Item {
    id : mainView
    property int margin: Math.min(width,height)*0.02
    MouseArea{
        id : mouseArea
        anchors.fill: parent
    }
    MouseEventItem{
        id:eventItem
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.topMargin: margin
        anchors.bottomMargin: margin
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - margin*2
        mouseHoverEventsEnabled: true
        mouseEventsEnabled: true
    }
}
