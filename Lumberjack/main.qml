import QtQuick
//import QtQuick.Controls
import QtQuick.Controls 2.15
import Qt5Compat.GraphicalEffects
import QtQml.Models 2.12

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
                x: 604
                y: 3
                width: 72
                height: 30
                color: "#ffffff"
                text: qsTr("Home")
                font.pixelSize: 25
            }

            Button {
                id: button
                x: 343
                y: 401
                width: 100
                height: 25
                text: qsTr("Start")
                hoverEnabled: false
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                layer.enabled: true
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                    transparentBorder: true
                    samples: 17
                }
                palette.buttonText: "#ffffff"
                onClicked: {
                    mainController.getSecurityLogs();
                    mainController.getApplicationLogs();
                    mainController.getSystemLogs();
                }
            }

            Button {
                id: button1
                x: 492
                y: 401
                width: 100
                height: 25
                text: qsTr("Save")
                hoverEnabled: false
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                layer.enabled: true
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                    transparentBorder: true
                    samples: 17
                }
                palette.buttonText: "#ffffff"
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

    }

    Rectangle {
        id: convertEvtxWin
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"

        Image {
            id: convertEvtxWinBg
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit
        }

        Image {
            id: image
            x: 0
            y: 0
            width: 1284
            height: 720
            source: "images/bg.png"
            fillMode: Image.PreserveAspectFit

            Text {
                id: text6
                x: 569
                y: 8
                width: 147
                height: 28
                color: "#ffffff"
                text: qsTr("EVTX Converter")
                font.pixelSize: 21
            }

            Button {
                id: button4
                x: 203
                y: 467
                width: 75
                height: 25
                text: qsTr("Select FIle")
                hoverEnabled: false
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                layer.enabled: true
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                    transparentBorder: true
                    samples: 17
                }
                palette.buttonText: "#ffffff"
            }

            Rectangle {
                id: rectangle2
                x: 292
                y: 469
                width: 200
                height: 25
                color: "#000000"
                border.color: "#ffffff"
            }

            Button {
                id: saveToBtn
                x: 834
                y: 467
                width: 75
                height: 25
                text: qsTr("Save To")
                hoverEnabled: false
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                layer.enabled: true
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                    transparentBorder: true
                    samples: 17
                }
                palette.buttonText: "#ffffff"
            }

            Rectangle {
                id: rectangle3
                x: 923
                y: 469
                width: 200
                height: 25
                color: "#000000"
                border.color: "#ffffff"
            }

            Rectangle {
                id: rectangle4
                x: 203
                y: 72
                width: 920
                height: 359
                color: "#000000"
                border.color: "#ffffff"

                ScrollView {
                    id: scrollView1
                    x: 8
                    y: 8
                    width: 904
                    height: 343
                }
            }
        }

        ComboBox {
            id: control1
            x: 584
            y: 470
            width: 116
            height: 21
            popup: Popup {
                y: control1.height - 1
                width: control1.width
                padding: 1
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#ffffff"
                }
                contentItem: ListView {
                    ScrollIndicator.vertical: ScrollIndicator {
                    }
                    currentIndex: control1.highlightedIndex
                    clip: true
                    model: control1.popup.visible ? control1.delegateModel : null
                    implicitHeight: contentHeight
                }
                implicitHeight: contentItem.implicitHeight
            }
            background: Rectangle {
                color: "#000000"
                radius: 2
                border.color: control1.pressed ? "#ffffff" : "#ffffff"
                border.width: control1.visualFocus ? 2 : 1
                implicitWidth: 120
                implicitHeight: 40
            }
            contentItem: Text {
                color: control1.pressed ? "#000000" : "#ffffff"
                text: control1.displayText
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                rightPadding: control1.indicator.width + control1.spacing
                font: control1.font
                leftPadding: 0
            }
            indicator: Canvas {
                x: control1.width - width - control1.rightPadding
                y: control1.topPadding + (control1.availableHeight - height) / 2
                width: 12
                height: 8
                Connections {
                    target: control1
                }
                contextType: "2d"
                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = control1.pressed ? "#ffffff" : "#ffffff";
                    context.fill();
                }
            }
            delegate: ItemDelegate {
                width: control1.width
                contentItem: Text {
                    color: "#000000"
                    text: control1.textRole
                          ? (Array.isArray(control1.model) ? modelData[control1.textRole] : model[control1.textRole])
                          : modelData
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    font: control1.font
                }
                highlighted: control1.highlightedIndex === index
            }
            model: ["Convert To", "JSON", "XML", "CSV"]
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

        Image {
            id: logViewWinBg
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit
        }

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
            id: control
            x: 82
            y: 43
            width: 116
            height: 21
            model: ["Filter", "Application", "System", "Security", "Custom"]

            delegate: ItemDelegate {
                width: control.width
                contentItem: Text {
                    text: control.textRole
                          ? (Array.isArray(control.model) ? modelData[control.textRole] : model[control.textRole])
                          : modelData
                    color: "#000000" //Change the text color of the model data in the drop down box.
                    font: control.font
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
                highlighted: control.highlightedIndex === index
            }

            indicator: Canvas {
                id: canvas
                x: control.width - width - control.rightPadding
                y: control.topPadding + (control.availableHeight - height) / 2
                width: 12
                height: 8
                contextType: "2d"

                Connections {
                    target: control
                    function onPressedChanged() { canvas.requestPaint(); }
                }

                //This will change the color of the triangle indicator.
                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = control.pressed ? "#ffffff" : "#ffffff";
                    context.fill();
                }
            }
            //The second color is the main color. The first item is what color the changes to once clicked.
            //This will change the text color of main text in the box.
            contentItem: Text {
                leftPadding: 0
                rightPadding: control.indicator.width + control.spacing

                text: control.displayText
                font: control.font
                color: control.pressed ? "#000000" : "#ffffff"
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            //This will change the main box background color, border color,  and the border color when pressed.
            //The second color is the main color. The first item is what color the changes to once clicked.
            background: Rectangle {
                implicitWidth: 120
                implicitHeight: 40
                color: "#000000"
                border.color: control.pressed ? "#ffffff" : "#ffffff"
                border.width: control.visualFocus ? 2 : 1
                radius: 2
            }

            popup: Popup {
                y: control.height - 1
                width: control.width
                implicitHeight: contentItem.implicitHeight
                padding: 1

                contentItem: ListView {
                    clip: true
                    implicitHeight: contentHeight
                    model: control.popup.visible ? control.delegateModel : null
                    currentIndex: control.highlightedIndex

                    ScrollIndicator.vertical: ScrollIndicator { }
                }

                //This will change the color of the drop down Rectangle
                background: Rectangle {
                    border.color: "#ffffff"
                    color: "#ffffff"
                    radius: 5
                }
            }
        }

        Text {
            id: text2
            x: 607
            y: 8
            width: 108
            height: 26
            color: "#ffffff"
            text: qsTr("Log Viewer")
            font.pixelSize: 21
        }

        Button {
            id: selectFileBtn
            x: 82
            y: 612
            width: 100
            height: 25
            text: qsTr("Select File")
            hoverEnabled: false
            background: Rectangle {
                color: "#161e20"
                radius: 50
            }
            layer.enabled: true
            layer.effect: DropShadow {
                width: 100
                visible: true
                color: "#ffffff"
                radius: 8
                horizontalOffset: 2
                spread: 0
                verticalOffset: 2
                transparentBorder: true
                samples: 17
            }
            palette.buttonText: "#ffffff"
        }

    }

    Rectangle {
        id: logViewerSettings
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"

        Image {
            id: image3
            x: 0
            y: 0
            width: 1282
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: text3
            x: 595
            y: 8
            width: 91
            height: 33
            color: "#ffffff"
            text: qsTr("Settings")
            font.pixelSize: 25
        }

        Rectangle {
            id: rectangle1
            x: 290
            y: 136
            width: 130
            height: 28
            color: "#000000"
            border.color: "#ffffff"

            TextInput {
                id: textInput
                x: 0
                y: 0
                width: 130
                height: 28
                text: qsTr("Text Input")
                font.pixelSize: 12
            }
        }

        Rectangle {
            id: currentFlags
            x: 762
            y: 106
            width: 200
            height: 200
            color: "#000000"
            border.color: "#ffffff"

            ListView {
                id: listView
                x: 2
                y: 2
                width: 196
                height: 195

                model: ListModel {
                    id:eventModel
                    ListElement {
                        listEntry: ""
                    }
                }
                delegate: Rectangle{
                    id: iremindLabelText
                    width: 196
                    height: 23
                    color: "#000000"
                    border.color: "#ffffff"
                    radius: 5
                    Text {
                        id:reminderText
                        //text: _billName + "   |   " + _dueDate + "    |   " + _dateToNotify + "    |   " + _amountDue
                        text: listEntry
                        font.bold: false
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }

        Text {
            id: text4
            x: 762
            y: 78
            width: 200
            height: 22
            color: "#ffffff"
            text: qsTr("Current Event ID Flags")
            font.pixelSize: 18
        }

        Text {
            id: text5
            x: 290
            y: 108
            width: 93
            height: 22
            color: "#ffffff"
            text: qsTr("Event ID")
            font.pixelSize: 18
        }

        Button {
            id: button2
            x: 196
            y: 136
            width: 74
            height: 28
            text: qsTr("Add")
            hoverEnabled: false
            background: Rectangle {
                color: "#161e20"
                radius: 50
            }
            layer.enabled: true
            layer.effect: DropShadow {
                width: 100
                visible: true
                color: "#ffffff"
                radius: 8
                horizontalOffset: 2
                spread: 0
                verticalOffset: 2
                transparentBorder: true
                samples: 17
            }
            palette.buttonText: "#ffffff"
        }

        Button {
            id: button3
            x: 762
            y: 324
            width: 75
            height: 24
            text: qsTr("Delete")
            hoverEnabled: false
            background: Rectangle {
                color: "#161e20"
                radius: 50
            }
            layer.enabled: true
            layer.effect: DropShadow {
                width: 100
                visible: true
                color: "#ffffff"
                radius: 8
                horizontalOffset: 2
                spread: 0
                verticalOffset: 2
                transparentBorder: true
                samples: 17
            }
            palette.buttonText: "#ffffff"
        }

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
            onClicked: {
                mainWin.visible = false
                logViewerWin.visible = false
                logViewerSettings.visible = true
                convertEvtxWin.visible  = false
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

    Text {
        id: curDateTxt
        x: 1200
        y: 8
        width: 74
        height: 20
        color: "#ffffff"
        text: qsTr("")
        font.pixelSize: 16
    }

    Text {
        id: clockText
        x: 1210
        y: 28
        width: 74
        height: 20
        color: "#ffffff"
        text: qsTr("")
        font.pixelSize: 16
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
                logViewerSettings.visible = false
                convertEvtxWin.visible  = false
            }
        }
    }

    Image {
        id: viewLogBtn
        x: 5
        y: 92
        width: 60
        height: 50
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/searchBtn.png"
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
                logViewerSettings.visible = false
                convertEvtxWin.visible  = false
            }
        }
    }

    Image {
        id: evtxConvertBtn
        x: 5
        y: 180
        width: 60
        height: 50
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/convertBtn.png"
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
            onClicked: {
                mainWin.visible = false
                logViewerWin.visible = false
                logViewerSettings.visible = false
                convertEvtxWin.visible  = true
            }
        }
    }

}
