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
                text: qsTr("Scan")
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
                id: mainWinSaveBtn
                x: 590
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
                onClicked: {
                    mainController.liveSave()
                }
            }

            Button {
                id: mainWinClearBtn
                x: 837
                y: 401
                width: 100
                height: 25
                text: qsTr("Clear")
                layer.enabled: true
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                hoverEnabled: false
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    horizontalOffset: 2
                    verticalOffset: 2
                    transparentBorder: true
                    spread: 0
                }
                palette.buttonText: "#ffffff"
                onClicked: {

                }
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

    Connections {
        target: mainController

        onSecurityEventCount2Qml:{
            var receivedSecTxt = secEventCountX
            secEventCountTxt.text = receivedSecTxt;
            //console.log("SecSignal Detected")
        }
        onAppEventCount2Qml:{
            var receivedAppTxt = appEventCountX
            appEventCountTxt.text = receivedAppTxt;
            //console.log("App Signal Detected")
        }
        onSysEventCount2Qml:{
            var reveivedSysTxt = sysEventCountX
            sysEventCountTxt.text = reveivedSysTxt;
            //console.log("Sys Signal Detected")
        }
        onProcessingStatus2Qml:{
            summaryText.text = processingStatus;
        }
        onDataToLogViewer:{
            logViewerWinTxtArea.text += logData + "\n";
            //console.log("Log Data Signal Detected")
        }
        onPopulateFlagDataToQml:{
            //iFlagText.text = eventIdFlag
            //console.log("flag is: " + flagText.text)
            eventModel.append({"listEntry": " Event ID: " + eventIdFlag})
        }
        //Display the file path
        onFilePathToQml:{
            cew_SelectFileTxt.text = filePath
        }
        //Display the dir path
        onDirPathToQml:{
            cew_SelectDirTxt.text = dirPath
        }
        //Display the save to path
        onSaveToPathToQml:{
            cew_SaveToTxt.text = saveToPath
        }
        onFileConvertEvtxStatus:{
            cew_logTxtArea.text += curStatus + "\n"
        }
        onFileNameToQml:{
            cew_fileSaveAsNameTxt.text = fileName
        }

        //function onSecurityEventCount2Qml(secEventCountX) {
        //secEventCountTxt.text = 11;
        //console.log("Signal Detected")
        // }
        // function onSecurityEventCount2Qml() {
        // secEventCountTxt.text = secEventCountX
        //console.log("Signal javascript function Detected")
        // }
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
            x: 133
            y: 70
            width: 1075
            height: 490
            color: "#000000"
            border.color: "#ffffff"
        }

        ScrollView {
            id: scrollView
            x: 136
            y: 74
            width: 1068
            height: 480
            clip: true

            TextArea {
                id: logViewerWinTxtArea
                x: 0
                y: 0
                width: 1068
                height: 480
                color: "#ffffff"
                font.pointSize: 13
                placeholderText: qsTr("Text Area")
                background: Rectangle {color: "black"}
            }
        }

        ComboBox {
            id: control
            x: 133
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
            x: 133
            y: 578
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
        id: convertEvtxWin
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"

        Image {
            id: image
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit

            Text {
                id: bannerText
                x: 605
                y: 8
                width: 147
                height: 28
                color: "#ffffff"
                text: qsTr("EVTX Converter")
                font.pixelSize: 21
            }

            Button {
                id: evtxWinSelectFileBtn
                x: 170
                y: 447
                width: 120
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
                onClicked: {
                    mainController.ce_SelectFile()

                }
            }

            Rectangle {
                id: ecw_SelectFileRect
                x: 304
                y: 449
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                Text {
                    id: cew_SelectFileTxt
                    x: 2
                    y: 2
                    width: 834
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Button {
                id: ce_SaveToBtn
                x: 170
                y: 575
                width: 120
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
                onClicked: {
                    mainController.ce_SaveToPath()
                }
            }

            Rectangle {
                id: ecw_SaveToRect
                x: 304
                y: 575
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                Text {
                    id: cew_SaveToTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Rectangle {
                id: ecw_TxtDataRect
                x: 170
                y: 64
                width: 973
                height: 360
                color: "#000000"
                border.color: "#ffffff"

                ScrollView {
                    id: ecw_scrollview
                    x: 3
                    y: 3
                    width: 966
                    height: 353

                    TextArea {
                        id: cew_logTxtArea
                        x: -7
                        y: -3
                        width: 966
                        color: "#ffffff"
                        placeholderText: qsTr("Text Area")
                        background: Rectangle {color: "black"}
                    }
                }
            }

            Button {
                id: cew_selectDirBtn
                x: 170
                y: 492
                width: 120
                height: 25
                text: qsTr("Select Dir - Combine")
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    transparentBorder: true
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                }
                layer.enabled: true
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                hoverEnabled: false
                palette.buttonText: "#ffffff"
                onClicked: {
                    mainController.ce_SelectDir()
                }
            }

            Rectangle {
                id: ecw_SelectDirRect
                x: 304
                y: 492
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                Text {
                    id: cew_SelectDirTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Button {
                id: cew_StartBtn
                x: 453
                y: 676
                width: 125
                height: 27
                text: qsTr("Start")
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    transparentBorder: true
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                }
                layer.enabled: true
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                hoverEnabled: false
                palette.buttonText: "#ffffff"
                onClicked: {
                    if(control1.currentText === "Convert To"){
                        cew_logTxtArea.text += "Please select a conversion type..."+ "\n"
                        console.log("Please select a conversion type...")
                        return;
                    }
                    else if(cew_SelectFileTxt.text === "" && cew_SelectDirTxt.text === ""){
                        cew_logTxtArea.text += "Select a file or directory..."+ "\n"
                        console.log("Select file and select dir felds are empty...")
                        return;
                    }

                    else if(cew_SaveToTxt.text === ""){
                        cew_logTxtArea.text += "Select a location to save the converted files" + "\n"
                        console.log("Select a location to save the converted files...")
                        return;
                    }
                    else if(cew_fileSaveAsNameTxt.text === ""){
                        cew_logTxtArea.text += "Please enter a name for the file to be converted. Do not include the extension..." + "\n"
                        console.log("Please enter a name for the new file. Do not include the extension...")
                        return;
                    }

                    else if(cew_SelectFileTxt.text !== "" && cew_SelectDirTxt.text !== ""){
                        //This situation should not happen because one field is set to "" when the other is populated, but just in case...
                        console.log("Select file or dir not both...")
                        return;
                    }
                    else if(cew_SelectFileTxt.text !== "" && cew_SelectDirTxt.text === ""){
                        console.log("Select file has text and selct dir does not...")
                        if(cew_fileSaveAsNameTxt.text === ""){
                            console.log("Please enter a file name...")
                            return;
                        }
                        else{
                            mainController.fileConvertEvtx(control1.currentText, cew_SelectFileTxt.text, cew_SaveToTxt.text, cew_fileSaveAsNameTxt.text)
                            //console.log("SENDING DATA TO C++...")
                            //console.log("control.currentText " + control.currentText)
                            //console.log("cew_SelectFileTxt.text " + cew_SelectFileTxt.text)
                            //console.log("cew_SaveToTxt.text " + cew_SaveToTxt.text)
                            //console.log("cew_fileSaveAsNameTxt.text " + cew_fileSaveAsNameTxt.text)
                        }
                    }
                    else if(cew_SelectDirTxt.text !== "" && cew_SelectFileTxt.text === ""){
                        console.log("Select dir has text and selct file does not...")
                        if(cew_fileSaveAsNameTxt.text !== ""){
                            console.log("Error: File name must be blank for directory conversion. Files will be converted using original file names....")
                            return;
                        }
                        else{

                        }
                    }
                }
            }

            Rectangle {
                id: ecw_FIleNameRect
                x: 304
                y: 621
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"

                TextEdit {
                    id: cew_fileSaveAsNameTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 16
                }
            }

            Text {
                id: fileNameLabel
                x: 217
                y: 624
                color: "#ffffff"
                text: qsTr("File name:")
                font.pixelSize: 16
            }

            Button {
                id: cew_ClearBtn
                x: 849
                y: 676
                width: 125
                height: 27
                text: qsTr("Clear")
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    samples: 17
                    transparentBorder: true
                    horizontalOffset: 2
                    spread: 0
                    verticalOffset: 2
                }
                layer.enabled: true
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                hoverEnabled: false
                palette.buttonText: "#ffffff"
                onClicked: {
                    cew_logTxtArea.clear()
                    cew_SelectFileTxt.text = ""
                    cew_SelectDirTxt.text = ""
                    cew_SaveToTxt.text = ""
                    cew_fileSaveAsNameTxt.text = ""
                }
            }

            Rectangle {
                id: cew_selectDirSeparateRect
                x: 304
                y: 535
                width: 839
                height: 25
                color: "#000000"
                border.color: "#ffffff"
                Text {
                    id: selectDirSeparateTxt
                    x: 2
                    y: 2
                    width: 835
                    height: 21
                    color: "#ffffff"
                    text: qsTr("")
                    font.pixelSize: 15
                }
            }

            Button {
                id: cew_selectDirSeparateBtn
                x: 170
                y: 535
                width: 120
                height: 25
                text: qsTr("Select Dir - Separate")
                hoverEnabled: false
                layer.effect: DropShadow {
                    width: 100
                    visible: true
                    color: "#ffffff"
                    radius: 8
                    horizontalOffset: 2
                    transparentBorder: true
                    verticalOffset: 2
                    samples: 17
                    spread: 0
                }
                layer.enabled: true
                palette.buttonText: "#ffffff"
                background: Rectangle {
                    color: "#161e20"
                    radius: 50
                }
                onClicked: {

                }
            }
        }

        ComboBox {
            id: control1
            x: 170
            y: 38
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
            model: ["Convert To", "JSON", "Full JSON", "XML", "CSV"]
        }
    }


    Rectangle {
        id: flagsWin
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"

        Image {
            id: image4
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit

            Rectangle {
                id: rectangle4
                x: 419
                y: 72
                width: 777
                height: 346
                color: "#000000"
                border.color: "#ffffff"
            }
        }

        Text {
            id: text3
            x: 609
            y: 8
            width: 62
            height: 33
            color: "#ffffff"
            text: qsTr("Flags")
            font.pixelSize: 25
        }

        Rectangle {
            id: rectangle1
            x: 175
            y: 73
            width: 200
            height: 28
            color: "#000000"
            border.color: "#ffffff"

            TextInput {
                id: flagTxtInput
                x: 2
                y: 1
                width: 196
                height: 28
                color: "#ffffff"
                text: qsTr("")
                font.pixelSize: 17
            }
        }

        Rectangle {
            id: currentFlags
            x: 175
            y: 218
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
                clip: true

                model: ListModel {
                    id:eventModel
                    ListElement {
                        listEntry: ""
                    }
                }

                delegate: Rectangle{
                    id: flagLabelText
                    width: 196
                    height: 23
                    color: "#000000"
                    border.color: "#ffffff"
                    radius: 5
                    Text {
                        id: iFlagText
                        color: "#ffffff"
                        //text: _billName + "   |   " + _dueDate + "    |   " + _dateToNotify + "    |   " + _amountDue
                        text: listEntry
                        font.bold: false
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
                Component.onCompleted: {
                    eventModel.remove(0)
                    mainController.populateFlagData()

                }
            }
        }

        Text {
            id: text4
            x: 175
            y: 190
            width: 180
            height: 22
            color: "#ffffff"
            text: qsTr("Current Event ID Flags")
            font.pixelSize: 18
        }

        Text {
            id: text5
            x: 178
            y: 45
            width: 69
            height: 22
            color: "#ffffff"
            text: qsTr("Event ID")
            font.pixelSize: 18
        }

        Button {
            id: addFlagBtn
            x: 176
            y: 109
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

            onClicked: {
                mainController.saveFlagData(flagTxtInput.text)
                flagTxtInput.text = ""
            }
        }

        Button {
            id: deleteFlagBtn
            x: 175
            y: 424
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
        id: schedulerWin
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"
        border.color: "#000000"

        Image {
            id: image3
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit

            Text {
                id: bannerTxt
                x: 584
                y: 8
                width: 113
                height: 34
                color: "#ffffff"
                text: qsTr("Scheduler")
                font.pixelSize: 25
            }

            Text {
                id: text6
                x: 290
                y: 466
                width: 114
                height: 34
                color: "#ffffff"
                text: qsTr("Days to run: ")
                font.pixelSize: 20
            }

            Text {
                id: text7
                x: 290
                y: 526
                width: 114
                height: 27
                color: "#ffffff"
                text: qsTr("Time to run:")
                font.pixelSize: 21
            }

            Rectangle {
                id: sw_infoRect
                x: 290
                y: 101
                width: 701
                height: 345
                color: "#000000"
                border.color: "#ffffff"
            }

            Text {
                id: text8
                x: 290
                y: 79
                width: 95
                height: 16
                color: "#ffffff"
                text: qsTr("Current Schedule")
                font.pixelSize: 12
            }

            Text {
                id: text9
                x: 421
                y: 459
                color: "#ffffff"
                text: qsTr("S")
                font.pixelSize: 12
            }

            Text {
                id: text10
                x: 450
                y: 459
                color: "#ffffff"
                text: qsTr("M")
                font.pixelSize: 12
            }

            Text {
                id: text12
                x: 506
                y: 459
                color: "#ffffff"
                text: qsTr("W")
                font.pixelSize: 12
            }

            Text {
                id: text11
                x: 481
                y: 459
                color: "#ffffff"
                text: qsTr("T")
                font.pixelSize: 12
            }

            Text {
                id: text13
                x: 533
                y: 459
                color: "#ffffff"
                text: qsTr("T")
                font.pixelSize: 12
            }

            Text {
                id: text14
                x: 560
                y: 459
                color: "#ffffff"
                text: qsTr("F")
                font.pixelSize: 12
            }

            Text {
                id: text15
                x: 587
                y: 459
                color: "#ffffff"
                text: qsTr("S")
                font.pixelSize: 12
            }

            CheckBox {
                id: checkBox
                x: 418
                y: 477
            }

            CheckBox {
                id: checkBox1
                x: 449
                y: 477
            }

            CheckBox {
                id: checkBox2
                x: 478
                y: 477
            }

            CheckBox {
                id: checkBox3
                x: 505
                y: 477
            }

            CheckBox {
                id: checkBox4
                x: 530
                y: 477
            }

            CheckBox {
                id: checkBox5
                x: 555
                y: 477
            }

            CheckBox {
                id: checkBox6
                x: 584
                y: 477
                width: 31
                height: 12
                text: qsTr("")
            }
        }

        Button {
            id: sw_saveBtn
            x: 291
            y: 585
            width: 100
            height: 25
            text: qsTr("Save")
            layer.enabled: true
            hoverEnabled: false
            palette.buttonText: "#ffffff"
            background: Rectangle {
                color: "#161e20"
                radius: 50
            }
            layer.effect: DropShadow {
                width: 100
                visible: true
                color: "#ffffff"
                radius: 8
                verticalOffset: 2
                transparentBorder: true
                spread: 0
                samples: 17
                horizontalOffset: 2
            }
        }
    }



    Rectangle {
        id: settingsWin
        x: 0
        y: 0
        width: 1280
        height: 720
        visible: false
        color: "#000000"
        border.color: "#000000"
        Image {
            id: settingsWinBg
            x: 0
            y: 0
            width: 1280
            height: 720
            source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/bg.png"
            fillMode: Image.PreserveAspectFit
            Text {
                id: settingsWinBannerTxt
                x: 594
                y: 8
                width: 92
                height: 34
                color: "#ffffff"
                text: qsTr("Settings")
                font.pixelSize: 25
            }
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
        y: 433
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
                flagsWin.visible = false
                convertEvtxWin.visible = false
                settingsWin.visible = true
                schedulerWin.visible = false
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
                scheduleBtn.visible = true
                mouseAreaScheduleBtn.visible = true
                flagsBtn.visible = true
                flagsBtnMouseArea.visible = true
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
                scheduleBtn.visible = false
                mouseAreaScheduleBtn.visible = false
                flagsBtn.visible = false
                flagsBtnMouseArea.visible = false
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
                flagsWin.visible = false
                convertEvtxWin.visible = false
                flagsWin.visible = false
                settingsWin.visible = false
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
                convertEvtxWin.visible = false
                flagsWin.visible = false
                settingsWin.visible = false
                schedulerWin.visible = false
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
                flagsWin.visible = false
                convertEvtxWin.visible = true
                settingsWin.visible = false
                schedulerWin.visible = false
            }
        }
    }

    Image {
        id: flagsBtn
        x: 5
        y: 266
        width: 60
        height: 50
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/flagBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: flagsBtnMouseArea
            x: 0
            y: 0
            width: 60
            height: 50
            onClicked: {
                mainWin.visible = false
                logViewerWin.visible = false
                flagsWin.visible = true
                convertEvtxWin.visible = false
                settingsWin.visible = false
                schedulerWin.visible = false
            }
            onExited: {
                flagsBtn.width = 60
                flagsBtn.height = 50
            }
            onEntered: {
                flagsBtn.width = 63
                flagsBtn.height = 53
            }
            hoverEnabled: true
        }
    }

    Image {
        id: scheduleBtn
        x: 5
        y: 350
        width: 60
        height: 50
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/scheduleBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: mouseAreaScheduleBtn
            x: 0
            y: 0
            width: 60
            height: 50
            onClicked: {
                mainWin.visible = false
                logViewerWin.visible = false
                flagsWin.visible = false
                convertEvtxWin.visible = false
                settingsWin.visible = false
                schedulerWin.visible = true
            }
            onExited: {
                scheduleBtn.width = 60
                scheduleBtn.height = 50
            }
            onEntered: {
                scheduleBtn.width = 63
                scheduleBtn.height = 53
            }
            hoverEnabled: true
        }
    }


}
