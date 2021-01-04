import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.13

Window {
    id : root
    visible: true
    width: 1667
    height: 900
    title: qsTr("DashBoard Animation")
    
    function calculatePosition(angle, radius){
        var a = angle* Math.PI / 180;
        var px =  radius * Math.cos(a);
        var py =  radius * Math.sin(a);
        return Qt.point(px,py);
    }

    Rectangle {
        id: rectRPM
        x: 6
        y: 134
        width: 600
        height: 600
        color: "#000000"
        radius: 300
        z: 0

        Text {
            id: titleRPM
            x: 255
            y: 333
            color: "#c8c0c0"
            text: qsTr("RPM\n[x1000]")
            horizontalAlignment: Text.AlignHCenter
            font.bold: true
            font.family: "Arial"
            wrapMode: Text.WordWrap
            font.pixelSize: 16
        }

        Repeater{
            model: ["0", "1","2","3","4","5","6"]
            Item {
                property point pt : root.calculatePosition((35*index+ 120), 230)
                x : pt.x+ rectRPM.width/2
                y : pt.y+ rectRPM.width/2
                Text{
                    anchors.centerIn: parent
                    text: modelData
                    color: "white"
                    font.pointSize: 20
                    antialiasing: true
                }
            }
        }

        Repeater{
            model: 7
            Item {
                property point pt : root.calculatePosition((35*index+ 120), 210)
                x : pt.x+ rectRPM.width/2
                y : pt.y+ rectRPM.width/2
                Rectangle{
                    anchors.centerIn: parent
                    width: 2
                    height: 4
                    color: "white"
                    rotation: (35*index+ 30)
                    antialiasing: true
                }
            }
        }

        Needle{
            id : rpmCenter
            colorCenter: "red"
            colorNeedle: "white"
            lengthNeedle: 250
            anchors.centerIn: parent
            rotation: 30
        }

//        Rectangle {
//            id: rpmCenter
//            x: 151
//            y: 172
//            width: 30
//            height: 30
//            color: "#ffffff"
//            radius: 15
//            anchors.horizontalCenter: parent.horizontalCenter
//            anchors.verticalCenter: parent.verticalCenter
//            z: 0
//            transformOrigin: Item.Center
//            rotation: 30

//            Rectangle {
//                id: rpmCenter2
//                x: 7
//                y: 7
//                width: 6
//                height: 250
//                color: "#ffffff"
//                radius: 8
//                anchors.verticalCenterOffset: 80
//                anchors.horizontalCenter: parent.horizontalCenter
//                transformOrigin: Item.Center
//                rotation: 0
//                anchors.verticalCenter: parent.verticalCenter
//                z: 0
//            }

//            Rectangle {
//                id: rpmCenter1
//                x: 0
//                y: 0
//                width: 16
//                height: 16
//                color: "#c31515"
//                radius: 8
//                anchors.horizontalCenter: parent.horizontalCenter
//                transformOrigin: Item.Top
//                rotation: 0
//                anchors.verticalCenter: parent.verticalCenter
//                z: 0
//            }
//        }




        Text {
            id: txtGear
            x: 324
            y: 267
            color: "#efe600"
            property int gearIdx: 1
            property var gears:["R","N", "1<sup>st</sup>", "2<sup>nd</sup>",
                "3<sup>rd</sup>","4<sup>th</sup>","5<sup>th</sup>"]
            text: gears[gearIdx]//qsTr("1<sup>st</sup>")
            font.bold: true
            font.family: "Arial"
            font.pixelSize: 35
            textFormat: Text.RichText // RichText여야 <sup>st</sup>사용가능!
        }
    }
    DelayButton {
        id: delayBtnRpm
        x: 49
        y: 756
        text: qsTr("Rpm")
        delay: 1000
        onProgressChanged: {
            rpmCenter.rotation =  210*progress + 30
        }
    }

    Rectangle {
        id: rectSpeed
        x: 530
        y: 14
        width: 800
        height: 800
        color: "#020202"
        radius: 400
        z: 3
        Repeater{
            model: ["0", "20","40","60","80","100","120","140","160","180","200","220"]
            Item {
                property point pt : root.calculatePosition((25*index+ 120), 310)
                x : pt.x+ rectSpeed.width/2
                y : pt.y+ rectSpeed.width/2
                Text{
                    anchors.centerIn: parent
                    text: modelData
                    color: "white"
                    font.pointSize: 20
                }
            }
        }
        Repeater{
            model: 12
            Item {
                property point pt : root.calculatePosition((25*index+ 120), 280)
                x : pt.x+ rectSpeed.width/2
                y : pt.y+ rectSpeed.width/2
                Rectangle{
                    anchors.centerIn: parent
                    width: 2
                    height: 8
                    color: "white"
                    rotation: (25*index+ 30)
                    antialiasing: true
                }
            }
        }


        Repeater{
            model: 60
            Item {
                property point pt : root.calculatePosition((5*index+ 120), 283)
                x : pt.x+ rectSpeed.width/2
                y : pt.y+ rectSpeed.width/2
                Rectangle{
                    anchors.centerIn: parent
                    width: 1
                    height: 4
                    color: "white"
                    rotation: (5*index+ 30)
                    antialiasing: true
                }
            }
        }


        Text {
            id: titleRPM1
            x: 351
            y: 425
            color: "#c8c0c0"
            text: qsTr("Speed\n[kph]")
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            font.family: "Arial"
            wrapMode: Text.WordWrap
            font.pixelSize: 18
        }

        Rectangle {
            id: speedCenter
            x: 324
            y: 402
            width: 30
            height: 30
            color: "#e3c561"
            radius: 15
            anchors.verticalCenter: parent.verticalCenter
            Behavior on rotation {
                SmoothedAnimation{ velocity: 50}
            }
            Rectangle {
                id: speedCenter1
                x: 7
                y: 7
                width: 6
                height: 300
                color: "#debb47"
                radius: 8
                anchors.verticalCenter: parent.verticalCenter
                anchors.verticalCenterOffset: 120
                z: 0
                transformOrigin: Item.Center
                rotation: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Rectangle {
                id: speedCenter2
                x: 0
                y: 0
                width: 16
                height: 16
                color: "#eae6e6"
                radius: 8
                anchors.verticalCenter: parent.verticalCenter
                z: 0
                transformOrigin: Item.Top
                rotation: 0
                anchors.horizontalCenter: parent.horizontalCenter
            }
            transformOrigin: Item.Center
            rotation: 30
            anchors.horizontalCenter: parent.horizontalCenter
        }

    }
    Slider {
        id: sliderSpeed
        x: 592
        y: 847
        width: 648
        height: 40
        value: 0.0
        from : 0
        to : 1
        onMoved: {
            speedCenter.rotation =  275*value + 30
        }
    }

    Rectangle {
        id: rectDist
        x: 1067
        y: 131
        width: 600
        height: 600
        color: "#000000"
        radius: 300
        z: 1

        Text {
            id: titleDist
            x: 263
            y: 223
            color: "#ffffff"
            text: qsTr("Distance ")
            font.bold: true
            font.family: "Arial"
            font.pixelSize: 30
        }

        Text {
            id: valDist
            x: 281
            y: 277
            width: 207
            height: 46
            color: "#ffffff"
            text: qsTr("100.000")
            horizontalAlignment: Text.AlignRight
            font.bold: true
            font.family: "Arial"
            font.pixelSize: 40
        }

        Text {
            id: element
            x: 507
            y: 287
            color: "#ffffff"
            text: qsTr("Km")
            font.family: "Arial"
            font.bold: true
            font.pixelSize: 25
        }
    }

    DelayButton {
        id: delayBtnSpeed
        x: 592
        y: 787
        text: qsTr("Speed")
        autoExclusive: true
        delay: 3000
        onProgressChanged: {
            speedCenter.rotation =  275*progress + 30
        }
    }

    SpinBox {
        id: spinRPM
        x: 49
        y: 809
        value: 1
        to: 6
        onValueModified: {
            txtGear.gearIdx = value
        }
    }

    Slider {
        id: sliderDistance
        x: 1238
        y: 774
        width: 402
        height: 40
        value: 100.00
        from : 0.00
        to : 10000.00
        onMoved: {
            valDist.text = Number(value).toFixed(3).toString()
        }
    }
}


