import QtQuick 2.0
import FeaturesItem 1.0

Item {
    id : mainView2
    property int margin: Math.min(width, height) * 0.02
    property real animationSine: 1
    property real animationTime: 0
    property bool animatePainting: true


    TopBar{
        id : topBar
        currentIndex: listView.currentIndex
        itemCount: listView.count
    }
    ListView{
        id : listView
        anchors.top: topBar.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: margin
        anchors.bottomMargin: margin
        width: parent.width
        //anchors.horizontalCenter: mainView.horizontalCenter

        orientation: ListView.Horizontal
        highlightRangeMode: ListView.StrictlyEnforceRange
        model: 8
        delegate: FeaturesItem{
            width: listView.width
            height: listView.height
            galleryView: index
            animationSine: mainView2.animationSine
            animationTime: mainView2.animationTime
        }
    }

    SequentialAnimation on animationSine {
        running: true
        loops: Animation.Infinite
        NumberAnimation{
            from : 0
            to : 1
            duration:  1000
            easing.type: Easing.InOutSine
        }
        NumberAnimation{
            from : 1
            to : 0
            duration:  1000
            easing.type: Easing.InOutSine
        }
    }

    NumberAnimation on animationTime {
        id : animationTimeAnimation
        running: true
        from : 0
        to : 360
        duration: 1000*360
        loops: Animation.Infinite
    }
}







































