import QtQuick 2.0
Rectangle{
    id : myRoi
    property int index : -1
    property int widthBorder : 2
    property bool active : true
    property int rulerSize: 10
    property int minimumWidth : 30
    property int minimumHeight : 30
    property int parentMinX
    property int parentMaxX
    property int parentMinY
    property int parentMaxY

    property int exX
    property int exY
    signal activated(int index)
    function getQuadrant(){
        if(myRoi.rotation<=90) return 1;
        else if(90 < myRoi.rotation && myRoi.rotation<=180) return 2;
        else if(180 < myRoi.rotation && myRoi.rotation<=270) return 3;
        else if(270 < myRoi.rotation && myRoi.rotation<=360) return 4;
    }
    function chkInnerCircle(){
        var radius = (parentMaxX - parentMinX)/2
        var centX = parentMinX + radius;
        var centY = parentMinY + radius;
        if(((x+width/2) - centX)*((x+width/2) - centX) + ((y+height/2) - centY)*((y+height/2)- centY) < radius*radius)
            return false;
        else
            return true;
    }

    antialiasing: true
    border {
        width: widthBorder
        color: active? "orange" : "steelblue"
    }
    color: active? "#35FF5733" : "#354682B4"

    onXChanged: {
        if((x+width) > parentMaxX)
            x = exX
        if(x < parentMinX)
            x = exX
        if(chkInnerCircle())
            x = exX
        exX = x
    }
    onYChanged: {
        if((y+height) > parentMaxY)
            y = exY
        if(y < parentMinY)
            y = exY
        if(chkInnerCircle())
            y = exY
        exY = y
    }

    MouseArea{
        anchors.fill: parent
        drag.target: myRoi
        hoverEnabled: true
        onWheel: {
            myRoi.rotation += wheel.angleDelta.y / 120 * 5;
            if (Math.abs(myRoi.rotation) < 4 || Math.abs(myRoi.rotation) > 360)
                myRoi.rotation = 0;
            if(myRoi.rotation<0)
                myRoi.rotation = 360 + myRoi.rotation;
        }
        onEntered: {
            activated(index)
        }
    }

    Rectangle{
        anchors.left: parent.left
        anchors.top : parent.top
        width: 20
        height: 18
        color: active? "orange" : "steelblue"
        Text {
            text: myRoi.index.toString()
            color: "white"
            font.pointSize: 11
            font.bold: true
            anchors.centerIn: parent
        }
    }

    Rectangle {
        width: rulerSize
        height: rulerSize
        radius: rulerSize/2
        color: active? "orange" : "steelblue"
        anchors.horizontalCenter: parent.left
        anchors.verticalCenter: parent.verticalCenter
        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.XAxis }
            onMouseXChanged: {
                if(drag.active){
                    if(getQuadrant() === 1 || getQuadrant() === 4){
                        myRoi.width = myRoi.width - mouseX*2
                        myRoi.x = myRoi.x + mouseX
                    }
                    else{
                        myRoi.width = myRoi.width + mouseX*2
                        if(mouseX > -10)
                            myRoi.x = myRoi.x - mouseX
                    }
                    if(myRoi.width < minimumWidth)
                        myRoi.width = minimumWidth
                }
            }
        }
    }

    Rectangle {
        width: rulerSize
        height: rulerSize
        radius: rulerSize/2
        color: active? "orange" : "steelblue"
        anchors.horizontalCenter: parent.right
        anchors.verticalCenter: parent.verticalCenter
        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.XAxis }
            onMouseXChanged: {
                if(drag.active){
                    if(getQuadrant() === 1 || getQuadrant() === 4){
                        myRoi.width = myRoi.width + mouseX*2
                        if(mouseX > -10)
                            myRoi.x = myRoi.x - mouseX
                    }
                    else{
                        myRoi.width = myRoi.width - mouseX*2
                        myRoi.x = myRoi.x + mouseX
                    }
                    if(myRoi.width < minimumWidth)
                        myRoi.width = minimumWidth
                }
            }
        }
    }

    Rectangle {
        width: rulerSize
        height: rulerSize
        radius: rulerSize/2
        x: parent.x / 2
        y: 0
        color: active? "orange" : "steelblue"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.top
        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    if(getQuadrant() === 1 || getQuadrant() === 4){
                        myRoi.height = myRoi.height - mouseY*2
                        myRoi.y = myRoi.y + mouseY
                    }
                    else{
                        myRoi.height = myRoi.height + mouseY*2
                        if(mouseY > -10)
                            myRoi.y = myRoi.y - mouseY
                    }
                    if(myRoi.height < minimumHeight)
                        myRoi.height = minimumHeight
                }
            }
        }
    }

    Rectangle {
        width: rulerSize
        height: rulerSize
        radius: rulerSize/2
        x: parent.x / 2
        y: parent.y
        color: active? "orange" : "steelblue"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.bottom
        MouseArea {
            anchors.fill: parent
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    if(getQuadrant() === 1 || getQuadrant() === 4){
                        myRoi.height = myRoi.height + mouseY*2
                        if(mouseY > -10)
                            myRoi.y = myRoi.y - mouseY
                    }
                    else{
                        myRoi.height = myRoi.height - mouseY*2
                        myRoi.y = myRoi.y + mouseY
                    }
                    if(myRoi.height < minimumHeight)
                        myRoi.height = minimumHeight
                }
            }
        }
    }
}
