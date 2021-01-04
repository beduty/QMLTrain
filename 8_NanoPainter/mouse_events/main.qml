import QtQuick 2.12
import EventItem 1.0

Item {
    id: mainView
    property int margin: Math.min(width, height)*0.02
    MouseArea{
        id: mouseArea
        anchors.fill: parent //eventItem
    }
    Item {
        id: topArea
        width: parent.width
        height: mainWindow.topbarHeight
        Row{
            id: buttonArea
            anchors.centerIn: parent
            width: parent.width*0.75
            height: parent.height*0.6
            spacing: margin*3/2
            ToggleButton {
                id: enableMouseToggle
                width: parent.width / 3 - margin
                text: "Enable mouse"
                toggled: true
            }
            ToggleButton{
                id : enableHoverToggle
                width : parent.width/3 - margin
                text : "Enable hover"
                toggled: true
                onToggledChanged:{
                    //eventItem.update();
                }
            }
            ToggleButton{
                width : parent.width/3 - margin
                text : "Random"
                isToggle: false
                onClicked:{
                    eventItem.generateRandomItems();
                }
            }
        }
    }
    EventItem{
        id:eventItem
        anchors.top: topArea.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: margin
        anchors.bottomMargin: margin
        width: parent.width-margin*2
        anchors.horizontalCenter: parent.horizontalCenter
        mouseEventsEnabled: true
        mouseHoverEventsEnabled: true
    }
}


















