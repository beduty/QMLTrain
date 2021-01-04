import QtQuick 2.12
import FeatureItem 1.0

Item {
    id : featureView
    property int margin: Math.min(width, height) * 0.02
    property real animationSine: 1
    property real animationTime: 0
    width: parent.width

    TopBar{
        id : topBar
        currentIndex: listView.currentIndex
        itemCount: listView.count
    }

    ListView{
        id : listView
        anchors.top : topBar.bottom
        anchors.bottom: parent.bottom
        anchors.topMargin: margin
        anchors.bottomMargin: margin
        width: parent.width
        model: 8
        orientation: ListView.Horizontal
        highlightRangeMode: ListView.StrictlyEnforceRange
        delegate: FeatureItem{
            width: listView.width
            height: listView.height
            galleryView: model.index
            animationSine: featureView.animationSine
            animationTime: featureView.animationTime
        }
    }
    SequentialAnimation on animationSine {
        running: true
        loops : Animation.Infinite
        NumberAnimation{
            from: 0
            to : 1
            duration: 1000
            easing.type: Easing.InOutSine
        }
        NumberAnimation{
            from: 1
            to : 0
            duration: 1000
            easing.type: Easing.InOutSine
        }
    }

    NumberAnimation on animationTime {
        id : aniamtionTime
        running: true
        from : 0
        to : 360
        duration: 1000*360
        loops: Animation.Infinite
    }

}
