import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

Window {
    visible: true
    width: 800
    height: 800
    title: qsTr("QNanoPainter")
    property real dp: Math.min(width, height)/400
    property real topbarHeight: Math.floor(30*dp)
    color: "#404040"
    Item{
        width: parent.width
        height: topbarHeight
        Button{
            id : btnLoad
            x : Math.ceil(5*dp)
            height: parent.height-Math.ceil(5*dp)
            anchors.bottom: parent.bottom
            text: "MouseEvent"
            onClicked: {
                console.log("complete!")
                loader.loadDemo("mouseEvents")
            }
        }
        Rectangle{
            anchors.bottom: parent.bottom
            height: Math.ceil(1*dp)
            width: parent.width
            color: "#909090"
        }
    }
    Loader{
        id : loader
        function loadDemo(path){
            if(loader.source ===  path + "/mainView.qml"){}
            else{
                loader.source = path + "/mainView.qml";
            }
        }
        function closeDemo(){
            loader.source = "";
        }
        anchors.fill: parent
        anchors.topMargin: topbarHeight
    }
}
