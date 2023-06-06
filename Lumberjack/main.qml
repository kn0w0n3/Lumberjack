import QtQuick
//import QtQuick.Controls
import QtQuick.Controls 2.15

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Lumberjack")

    //Main Controller Connections
    Connections {
        target: mainController

       onSecurityEventCount2Qml:{
           var receivedSecTxt = secEventCountX
            secEventCountTxt.text = receivedSecTxt;
             console.log("SecSignal Detected")

        }
      // function onSecurityEventCount2Qml() {
                  // secEventCountTxt.text = secEventCountX
                   //console.log("Signal javascript function Detected")
                  // }

       onAppEventCount2Qml:{
           var receivedAppTxt = appEventCountX
            appEventCountTxt.text = receivedAppTxt;
             console.log("App Signal Detected")

        }
       onSysEventCount2Qml:{
           var reveivedSysTxt = sysEventCountX
            sysEventCountTxt.text = reveivedSysTxt;
             console.log("Sys Signal Detected")

        }
        //function onSecurityEventCount2Qml(secEventCountX) {
            //secEventCountTxt.text = 11;
            //console.log("Signal Detected")
           // }
    }



    Rectangle {
        id: mainWin
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: true
        color: "#000000"



        Image {
            id: mainWinBgImg
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            id: summaryRect
            x: 342
            y: 157
            width: 597
            height: 225
            color: "#000000"
            border.color: "#ffffff"


            Text {
                id: errorLabel
                x: 19
                y: 63
                width: 131
                height: 38
                color: "#ffffff"
                text: qsTr("Application:")
                font.pixelSize: 25
            }

            Text {
                id: text2
                x: 0
                y: -33
                width: 90
                height: 38
                color: "#ffffff"
                text: qsTr("Summary")
                font.pixelSize: 21
            }

            Text {
                id: warningLabel
                x: 19
                y: 112
                width: 96
                height: 38
                color: "#ffffff"
                text: qsTr("Security:")
                font.pixelSize: 25
            }

            Text {
                id: informationLabel
                x: 19
                y: 164
                width: 142
                height: 38
                color: "#ffffff"
                text: qsTr("System:")
                font.pixelSize: 25
            }

            Text {
                id: eventTypeLabel
                x: 16
                y: 13
                width: 123
                height: 38
                color: "#1827f4"
                text: qsTr("Event Type")
                font.pixelSize: 25
                font.underline: true
            }

            Text {
                id: lastHourLabel
                x: 382
                y: 13
                width: 110
                height: 38
                color: "#1827f4"
                text: qsTr("Number of Events")
                font.pixelSize: 25
                font.underline: true
            }

            Text {
                id: appEventCountTxt
                x: 382
                y: 63
                width: 110
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: secEventCountTxt
                x: 382
                y: 112
                width: 110
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: sysEventCountTxt
                x: 382
                y: 164
                width: 110
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }
        }
        Text {
            id: logViewerTitleText
            x: 1162
            y: 680
            width: 110
            height: 32
            color: "#ffffff"
            text: qsTr("Lumberjack")
            font.pixelSize: 21
        }

        Image {
            id: image
            x: 8
            y: 662
            width: 50
            height: 50
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/GmenuClose.png"
            fillMode: Image.PreserveAspectFit
        }

    }

    Rectangle {
        id: logViewer
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"

        Rectangle {
            id: rectangle
            x: 290
            y: 78
            width: 953
            height: 515
            color: "#000000"
            border.color: "#ffffff"
        }

        Rectangle {
            id: rectangle1
            x: 110
            y: 78
            width: 147
            height: 193
            color: "#000000"
            border.color: "#ffffff"
        }

        ScrollView {
            id: scrollView
            x: 292
            y: 81
            width: 948
            height: 509
        }

        TextArea {
            id: textArea
            x: 292
            y: 81
            width: 948
            height: 509
            placeholderText: qsTr("Text Area")
            background: Rectangle {color: "black"}
        }
    }

    Rectangle {
        id: lowViewerSettings
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"
    }

    Rectangle {
        id: sidePanelRect
        x: 0
        y: 0
        width: 70
        height: 720
        opacity: 0.373
        color: "#515050"

    }

    Image {
        id: toolsBtn
        x: 5
        y: 82
        width: 60
        height: 50
        //source: "images/toolsBtn.png"
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/toolsBtn.png"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseAreaToolsBtn
            x: 0
            y: 0
            width: 60
            height: 50
            hoverEnabled: true
            onEntered: {
                toolsBtn.width = 63
                toolsBtn.height = 53
            }
            onExited: {
                toolsBtn.width = 60
                toolsBtn.height = 50
            }
        }

    }

    Image {
        id: homeBtn
        x: 5
        y: 8
        width: 60
        height: 50
        visible: true
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/homeBtnImg.png"
        clip: false
        //source: "qrc:/images/homeBtnImg.png"
        z: 0
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseAreaHomeBtn
            x: 0
            y: 0
            width: 60
            height: 50
            hoverEnabled: true
            onEntered: {
                homeBtn.width = 63
                homeBtn.height = 53
            }
            onExited: {
                homeBtn.width = 60
                homeBtn.height = 50
            }
        }
    }

}
