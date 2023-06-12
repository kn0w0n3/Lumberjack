import QtQuick
//import QtQuick.Controls
import QtQuick.Controls 2.15

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Lumberjack")

    Timer {
        id: clockTimer
        interval: 1000
        repeat: true
        running: true
        onTriggered:{
            clockText.text =  Qt.formatTime(new Date(),"hh:mm:ss")
        }
    }

    Timer {
        id: dateTimer
        interval: 1000
        repeat: true
        running: true
        property var locale: Qt.locale()
        property date currentDate: new Date()
        property string dateString
        onTriggered:{
            curDateTxt.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
        }
    }

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
        onProcessingStatus2Qml:{

            summaryText.text = processingStatus;

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

            Image {
                id: image1
                x: 1094
                y: 681
                width: 40
                height: 31
                visible: false
                source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/eagle.png"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: clockText
                x: 1211
                y: 28
                width: 74
                height: 20
                color: "#ffffff"
                text: qsTr("")
                font.pixelSize: 16
            }

            Text {
                id: curDateTxt
                x: 1208
                y: 8
                width: 74
                height: 20
                color: "#ffffff"
                text: qsTr("")
                font.pixelSize: 16
            }

            Image {
                id: image2
                x: 1157
                y: 692
                width: 119
                height: 28
                visible: false
                source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/logo2.png"
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: text1
                x: 550
                y: 8
                width: 180
                height: 48
                color: "#ffffff"
                text: qsTr("Main Menu")
                font.pixelSize: 35
            }

            Button {
                id: button
                x: 343
                y: 401
                width: 63
                height: 23
                text: qsTr("Start")
                onClicked: {
                    mainController.getSecurityLogs();
                    mainController.getApplicationLogs();
                    mainController.getSystemLogs();
                }
            }

            Button {
                id: button1
                x: 441
                y: 401
                width: 63
                height: 23
                text: qsTr("Save")
            }
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
                id: summaryText
                x: 0
                y: -22
                width: 206
                height: 23
                color: "#ffffff"
                text: qsTr("Summary")
                font.pixelSize: 16
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
                width: 202
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
            x: 1143
            y: 676
            width: 129
            height: 36
            visible: true
            color: "#ffffff"
            text: qsTr("Lumberjack")
            font.pixelSize: 25
        }

    }

    Rectangle {
        id: logViewerWin
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"

        Rectangle {
            id: rectangle
            x: 82
            y: 70
            width: 1158
            height: 520
            color: "#000000"
            border.color: "#ffffff"
        }

        ScrollView {
            id: scrollView
            x: 82
            y: 70
            width: 1158
            height: 509
        }

        TextArea {
            id: textArea
            x: 85
            y: 73
            width: 1151
            height: 513
            placeholderText: qsTr("Text Area")
            background: Rectangle {color: "black"}
        }

        ComboBox {
            id: comboBox
            x: 82
            y: 37
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
        y: 265
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
        id: dotsBtn
        x: -2
        y: 696
        width: 72
        height: 15
        visible: false
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/GopenMenuDots.png"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseAreaDotsBtn
            x: 0
            y: 0
            width: 72
            height: 15
            onClicked: {
                sidePanelRect.visible = true
                toolsBtn.visible = true
                homeBtn.visible = true
                mouseAreaHomeBtn.visible = true
                mouseAreaToolsBtn.visible = true
                dotsBtn.visible = false
                mouseAreaDotsBtn.visible =  false
                menuBtn.visible = true
                mouseAreaMenuBtn.visible = true
                viewLogBtn.visible = true
                mouseAreaViewLogBtn.visible = true
                evtxConvertBtn.visible = true
                mouseAreaConvertEvtx.visible = true
            }
        }
    }

    Image {
        id: menuBtn
        x: 8
        y: 662
        width: 50
        height: 50
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/GmenuClose.png"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseAreaMenuBtn
            width: 50
            height: 50
            onClicked: {
                sidePanelRect.visible = false
                toolsBtn.visible = false
                homeBtn.visible = false
                mouseAreaHomeBtn.visible = false
                mouseAreaToolsBtn.visible = false
                menuBtn.visible = false
                mouseAreaMenuBtn.visible = false
                viewLogBtn.visible = false
                mouseAreaViewLogBtn.visible = false
                evtxConvertBtn.visible = false
                mouseAreaConvertEvtx.visible = false
                dotsBtn.visible = true
                mouseAreaDotsBtn.visible =  true

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
            onClicked: {
                mainWin.visible = true
                logViewerWin.visible = false
            }
        }
    }

    Image {
        id: viewLogBtn
        x: 5
        y: 92
        width: 60
        height: 50
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/helpBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: mouseAreaViewLogBtn
            x: 0
            y: 0
            width: 60
            height: 50
            onExited: {
                viewLogBtn.width = 60
                viewLogBtn.height = 50
            }
            hoverEnabled: true
            onEntered: {
                viewLogBtn.width = 63
                viewLogBtn.height = 53
            }
            onClicked: {
                mainWin.visible = false
                logViewerWin.visible = true
            }
        }
    }

    Image {
        id: evtxConvertBtn
        x: 5
        y: 180
        width: 60
        height: 50
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/helpBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: mouseAreaConvertEvtx
            x: 0
            y: 0
            width: 60
            height: 50
            onExited: {
                evtxConvertBtn.width = 60
                evtxConvertBtn.height = 50
            }
            hoverEnabled: true
            onEntered: {
                evtxConvertBtn.width = 63
                evtxConvertBtn.height = 53
            }
        }
    }



}
