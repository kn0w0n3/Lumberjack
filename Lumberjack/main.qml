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
    maximumWidth: 1280
    maximumHeight: 720
    minimumWidth: 1280
    minimumHeight: 720

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
        onSaveScheduleDataSaveStatus:{
            sw_ScrollViewTxtArea.text += shedulerSaveStatus + "\n"
        }
        onSavedHourTxtToQml:{
            control2.currentIndex = s_Hour
        }
        onSavedMinTxtToQml:{
            control3.currentIndex = s_Minute
        }
        onSavedAmpmTxtToQml:{
            if(s_Ampm === "am"){
                control4.currentIndex = 1
            }
            else if(s_Ampm === "pm"){
                control4.currentIndex = 2
            }
            else{
                control4.currentIndex = 0
            }
        }
        onSavedDaysDataToQml:{
            console.log("IN QML DYS DATA SLOT")
            if(dayX === "1"){
                checkBox_1.checkState = Qt.Checked
            }
            if(dayX === "2"){
                checkBox_2.checkState = Qt.Checked
            }
            if(dayX === "3"){
                checkBox_3.checkState = Qt.Checked
            }
            if(dayX === "4"){
                checkBox_4.checked = Qt.Checked
            }
            if(dayX === "5"){
                checkBox_5.checked = Qt.Checked
            }
            if(dayX === "6"){
                checkBox_6.checked = Qt.Checked
            }
            if(dayX === "7"){
                checkBox_7.checked = Qt.Checked
            }
        }
        onSavedClearLogDataToQML:{
            if(cl_CheckedStatus === "true"){
                //switch2.stateChanged(2)
                switch2.checked = true
                switch2.text = "<font color=\"white\">On</font>"
            }

        }
        onSavedAutoBackupDataToQML:{
            if(bu_CheckedStatus === "true"){
                switch1.checked = true
                switch1.text = "<font color=\"white\">On</font>"
            }
        }
        onArchivedLogEntryToQml:{
            model.append({text: logName})
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

    Timer {
        id: scheduleDateTimer
        interval: 1000
        repeat: true
        running: true
        property var locale: Qt.locale()
        property date currentDate: new Date()
        property string dateString
        onTriggered:{
            var curDayOfTheWeek  = currentDate.getDay().toString()
            //console.log("Current day of the week is: " + curDayOfTheWeek)
            //curDateTxt.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
        }
    }


    Timer {
        id: updateLogSummaryTimer
        interval: 1800000
        repeat: true
        running: true
        property var locale: Qt.locale()
        property date currentDate: new Date()
        property string dateString
        onTriggered:{
            mainController.updateCurrentLogSummary()
            //locale: Qt.locale("en_US");
            //QDateTime date = QDateTime::currentDateTime();
            //QString dateString = locale.toString(date);
            //console.log(date);
            //curDateTxt.text = currentDate.toLocaleDateString(locale, Locale.ShortFormat);
        }
    }

    Timer {
        id: schedulerTimer
        interval: 1000
        repeat: true
        running: true
        onTriggered:{
            var currentTime =  Qt.formatTime(new Date(),"hh:mm ap")
            var timeToCompare = control2.currentText + ":" + control3.currentText + " " + control4.currentText
            //console.log("Current time: " + currentTime)
            //console.log("Time to compare is: " + timeToCompare)
            if(currentTime === timeToCompare){
                console.log("THE TIME MATCHES............")
            }
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
                visible: false
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
                visible: false
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
                visible: false
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
            height: 273
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

        Image {
            id: homeTextImg
            x: 587
            y: 8
            width: 107
            height: 37
            visible: true

            //*******BUG*******
            //This will make the image display in the designer, but the image does not siplay during run time
            //source:"images/home-text.png"

            //This will make the image display during run time, but the image wn't display in designer
            source:"/images/home-text.png"
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: informationLabel1
            x: 361
            y: 371
            width: 68
            height: 38
            color: "#ffffff"
            text: qsTr("Flags:")
            font.pixelSize: 25
        }

        Text {
            id: sysEventCountTxt1
            x: 725
            y: 370
            width: 110
            height: 38
            color: "#ffffff"
            text: qsTr("0")
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
            //model: ["Available Logs", "Application", "System", "Security", "Custom"]
            model: ListModel{
                id: model
                ListElement {text: "Select Log"}
            }
            onAccepted: {
                if (find(editText) === -1)
                    model.append({text: editText})
            }

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
            Component.onCompleted: {
                //populate saved logs
                mainController.getArchivedLogsList()
            }
        }

        Text {
            id: text2
            x: 607
            y: 8
            width: 108
            height: 26
            visible: false
            color: "#ffffff"
            text: qsTr("Log Viewer")
            font.pixelSize: 21
        }

        Button {
            id: openLogBtn
            x: 133
            y: 578
            width: 135
            height: 25
            text: qsTr("View Log")
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

        Image {
            id: logViewTxtImg
            x: 584
            y: 8
            width: 174
            height: 46
            source: "/images/log-viewer-text.png"
            fillMode: Image.PreserveAspectFit
        }

        Button {
            id: markReviewedBtn
            x: 327
            y: 578
            width: 135
            height: 25
            text: qsTr("Mark as Reviewed")
            palette.buttonText: "#ffffff"
            layer.enabled: true
            hoverEnabled: false
            layer.effect: DropShadow {
                width: 100
                visible: true
                color: "#ffffff"
                radius: 8
                spread: 0
                transparentBorder: true
                horizontalOffset: 2
                verticalOffset: 2
                samples: 17
            }
            background: Rectangle {
                color: "#161e20"
                radius: 50
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
                visible: false
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

                    //else if(cew_SelectFileTxt.text !== "" && cew_SelectDirTxt.text !== ""){
                    //This situation should not happen because one field is set to "" when the other is populated, but just in case...
                    // console.log("Select file or dir not both...")
                    //return;
                    //}
                    else if(cew_SelectFileTxt.text !== "" && cew_SelectDirTxt.text === ""){
                        console.log("Select file has text and selct dir does not...")
                        if(cew_fileSaveAsNameTxt.text === ""){
                            cew_logTxtArea.text += "Please enter a file name...\n"
                            console.log("Please enter a file name...")
                            return;
                        }
                        else{
                            mainController.fileConvertEvtx(control1.currentText, cew_SelectFileTxt.text, cew_SaveToTxt.text, cew_fileSaveAsNameTxt.text)
                        }
                    }
                    else if(cew_SelectDirTxt.text !== "" && cew_SelectFileTxt.text === ""){
                        console.log("Select dir has text and selct file does not...")
                        if(cew_fileSaveAsNameTxt.text !== ""){
                            cew_logTxtArea.text += "Error: File name must be blank for directory conversion.\n"
                            //console.log("Error: File name must be blank for directory conversion. Files will be converted using original file names....")
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

        Image {
            id: image5
            x: 502
            y: 0
            width: 276
            height: 59
            source: "/images/evtx-converter-text.png"
            fillMode: Image.PreserveAspectFit
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

                ScrollView {
                    id: scrollView1
                    x: 3
                    y: 3
                    width: 771
                    height: 340

                    TextArea {
                        id: flagsWinTxtArea
                        color: "#ffffff"
                        anchors.fill: parent
                        placeholderText: qsTr("Text Area")
                        background: Rectangle {color: "black"}
                    }
                }
            }
        }

        Text {
            id: text3
            x: 609
            y: 8
            width: 62
            height: 33
            visible: false
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
                highlight: highlight
                highlightFollowsCurrentItem: false
                focus: true

                // highlightFollowsCurrentItem: true
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
                        text: listEntry
                        font.bold: false
                        anchors.verticalCenter: parent.verticalCenter
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                listView.currentIndex = index
                                if(flagLabelText.color.toString() === "#000000"){
                                    flagLabelText.color = "#ffffff"
                                    flagLabelText.border.color = "#000000"
                                    iFlagText.color = "#000000"
                                    console.log("Listview item clicked...")
                                }
                                else if(flagLabelText.color.toString() !== "#000000"){
                                    flagLabelText.color = "#000000"
                                    flagLabelText.border.color = "#ffffff"
                                    iFlagText.color = "#ffffff"
                                    console.log("Listview item clicked...")
                                }

                            }
                        }
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
                if(flagTxtInput.text === ""){
                    //console.log("Error: Enter an event ID")
                    flagsWinTxtArea.text += "Error: Enter an event ID \n"
                    return;
                }
                else if(flagTxtInput.text !== ""){
                    mainController.saveFlagData(flagTxtInput.text)
                    flagsWinTxtArea.text += "Flag successfully added.... \n"
                    flagTxtInput.text = "";
                }
                else{
                    flagsWinTxtArea.text += "An unknown error occurred. Try again..... \n"
                    return;
                }
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

        Image {
            id: image6
            x: 627
            y: 8
            width: 132
            height: 51
            source: "/images/flags-text.png"
            fillMode: Image.PreserveAspectFit
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
        Component.onCompleted: {
            mainController.populateSchedulerTimeData()
            mainController.populateShedulerDaysData()
            mainController.popSchdlerClrLogData()
            mainController.popSchdlerBkupData()
        }

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
                visible: false
                color: "#ffffff"
                text: qsTr("Scheduler")
                font.pixelSize: 25
            }

            Text {
                id: text6
                x: 292
                y: 445
                width: 112
                height: 34
                color: "#ffffff"
                text: qsTr("Days to run: ")
                font.pixelSize: 17
            }

            Text {
                id: text7
                x: 292
                y: 393
                width: 104
                height: 27
                color: "#ffffff"
                text: qsTr("Time to run:")
                font.pixelSize: 17
            }

            Rectangle {
                id: sw_infoRect
                x: 290
                y: 101
                width: 701
                height: 273
                color: "#000000"
                border.color: "#ffffff"

                ScrollView {
                    id: sw_ScrollVIew
                    x: 2
                    y: 2
                    width: 697
                    height: 269

                    TextArea {
                        id: sw_ScrollViewTxtArea
                        x: -7
                        y: -3
                        color: "#ffffff"
                        text: ""
                        font.pointSize: 11
                        placeholderText: qsTr("Text Area")
                        background: Rectangle {color: "black"}
                    }
                }
            }

            Text {
                id: text8
                x: 292
                y: 79
                width: 95
                height: 16
                color: "#ffffff"
                text: qsTr("Current Schedule")
                font.pixelSize: 12
            }

            Text {
                id: text9
                x: 423
                y: 438
                color: "#ffffff"
                text: qsTr("S")
                font.pixelSize: 12
            }

            Text {
                id: text10
                x: 452
                y: 438
                color: "#ffffff"
                text: qsTr("M")
                font.pixelSize: 12
            }

            Text {
                id: text12
                x: 508
                y: 438
                color: "#ffffff"
                text: qsTr("W")
                font.pixelSize: 12
            }

            Text {
                id: text11
                x: 483
                y: 438
                color: "#ffffff"
                text: qsTr("T")
                font.pixelSize: 12
            }

            Text {
                id: text13
                x: 535
                y: 438
                color: "#ffffff"
                text: qsTr("T")
                font.pixelSize: 12
            }

            Text {
                id: text14
                x: 562
                y: 438
                color: "#ffffff"
                text: qsTr("F")
                font.pixelSize: 12
            }

            Text {
                id: text15
                x: 589
                y: 438
                color: "#ffffff"
                text: qsTr("S")
                font.pixelSize: 12
            }

            CheckBox {
                id: checkBox_7
                x: 420
                y: 455
                height: 14
                text: qsTr("")
            }

            CheckBox {
                id: checkBox_1
                x: 452
                y: 455
                height: 14
                text: qsTr("")
            }

            CheckBox {
                id: checkBox_2
                x: 480
                y: 455
                width: 12
                height: 14
                text: qsTr("")
            }

            CheckBox {
                id: checkBox_3
                x: 508
                y: 455
                height: 14
                text: qsTr("")
            }

            CheckBox {
                id: checkBox_4
                x: 532
                y: 455
                height: 14
                text: qsTr("")
            }

            CheckBox {
                id: checkBox_5
                x: 559
                y: 455
                height: 14
                text: qsTr("")
            }

            CheckBox {
                id: checkBox_6
                x: 586
                y: 455
                height: 14
                text: qsTr("")
            }

            Switch {
                id: switch1
                x: 399
                y: 555
                visible: true
                text: "<font color=\"white\">Off</font>"
                onToggled: {
                    if(checked){
                        switch1.text= qsTr("<font color=\"white\">On</font>")
                    }
                    else{
                        switch1.text= qsTr("<font color=\"white\">Off</font>")
                    }
                }
            }

            Text {
                id: text16
                x: 292
                y: 498
                color: "#ffffff"
                text: qsTr("Clear Logs After Backup:")
                font.pixelSize: 17
            }

            Text {
                id: text17
                x: 294
                y: 555
                color: "#ffffff"
                text: qsTr("Auto Backup:")
                font.pixelSize: 17
            }
        }

        Button {
            id: sw_saveBtn
            x: 323
            y: 610
            width: 100
            height: 25
            visible: true
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
            onClicked: {
                sw_ScrollViewTxtArea.text += "Saving data....\n"
                var c_Hour = control2.currentText
                var cMinute = control3.currentText
                var dayNight = control4.currentText
                var daysList = []
                //var cb1_result = checkBox_1.checkState.toString()
                //var clearLogsSwitch = switch2.checked
                // var cb2_result = checkBox_2.checkState.toString()
                //var cb1_result = checkBox_1.checkState.toString()
                //console.log("The switch result is: " + clearLogsSwitch)


                if(checkBox_1.checkState.toString() === "2"){
                    console.log("IN CHECKBOX 1 IF STATEMENT")
                    daysList.push("1")
                    //mainController.saveSchedulerDayData("1")
                }
                if(checkBox_2.checkState.toString() === "2"){
                    daysList.push("2")
                    //mainController.saveSchedulerDayData("2")
                }
                if(checkBox_3.checkState.toString() === "2"){
                    daysList.push("3")
                    // mainController.saveSchedulerDayData("3")
                }
                if(checkBox_4.checkState.toString() === "2"){
                    daysList.push("4")
                    //mainController.saveSchedulerDayData("4")
                }
                if(checkBox_5.checkState.toString() === "2"){
                    daysList.push("5")
                    //mainController.saveSchedulerDayData("5")
                }
                if(checkBox_6.checkState.toString() === "2"){
                    daysList.push("6")
                    //mainController.saveSchedulerDayData("6")
                }
                if(checkBox_7.checkState.toString() === "2"){
                    daysList.push("7")
                    //mainController.saveSchedulerDayData("7")
                }

                if(switch2.checked){
                    mainController.saveSchdlerClrLogData("true")
                    console.log("The switch result is: " + switch2.checked)
                }

                if(switch1.checked){
                    mainController.saveSchdlerBkupData("true")
                    console.log("The switch result is: " + switch1.checked)
                }

                mainController.saveSchedulerTimeData(c_Hour, cMinute, dayNight)
                mainController.saveSchedulerDayData(daysList)
                console.log("The list is: " + daysList)
            }
        }

        Image {
            id: image7
            x: 542
            y: 8
            width: 196
            height: 37
            source: "/images/scheduler-text.png"
            fillMode: Image.PreserveAspectFit
        }

        ComboBox {
            id: control2
            x: 415
            y: 395
            width: 116
            height: 21
            visible: true
            background: Rectangle {
                color: "#000000"
                radius: 2
                border.color: control2.pressed ? "#ffffff" : "#ffffff"
                border.width: control2.visualFocus ? 2 : 1
                implicitWidth: 120
                implicitHeight: 40
            }
            popup: Popup {
                y: control2.height - 1
                width: control2.width
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#ffffff"
                }
                contentItem: ListView {
                    clip: true
                    model: control2.popup.visible ? control2.delegateModel : null
                    ScrollIndicator.vertical: ScrollIndicator {
                    }
                    currentIndex: control2.highlightedIndex
                    implicitHeight: contentHeight
                }
                padding: 1
                implicitHeight: contentItem.implicitHeight
            }
            contentItem: Text {
                color: control2.pressed ? "#000000" : "#ffffff"
                text: control2.displayText
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                font: control2.font
                leftPadding: 0
                rightPadding: control2.indicator.width + control2.spacing
            }
            model: ["Hour", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"]
            indicator: Canvas {
                x: control2.width - width - control2.rightPadding
                y: control2.topPadding + (control2.availableHeight - height) / 2
                width: 12
                height: 8
                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = control2.pressed ? "#ffffff" : "#ffffff";
                    context.fill();
                }
                Connections {
                    target: control2
                }
                contextType: "2d"
            }
            delegate: ItemDelegate {
                width: control2.width
                highlighted: control2.highlightedIndex === index
                contentItem: Text {
                    color: "#000000"
                    text: control2.textRole
                          ? (Array.isArray(control2.model) ? modelData[control2.textRole] : model[control2.textRole])
                          : modelData
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    font: control2.font
                }
            }
        }

        ComboBox {
            id: control3
            x: 559
            y: 395
            width: 116
            height: 21
            background: Rectangle {
                color: "#000000"
                radius: 2
                border.color: control3.pressed ? "#ffffff" : "#ffffff"
                border.width: control3.visualFocus ? 2 : 1
                implicitWidth: 120
                implicitHeight: 40
            }
            popup: Popup {
                y: control3.height - 1
                width: control3.width
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#ffffff"
                }
                contentItem: ListView {
                    clip: true
                    model: control3.popup.visible ? control3.delegateModel : null
                    ScrollIndicator.vertical: ScrollIndicator {
                    }
                    currentIndex: control3.highlightedIndex
                    implicitHeight: contentHeight
                }
                padding: 1
                implicitHeight: contentItem.implicitHeight
            }
            contentItem: Text {
                color: control3.pressed ? "#000000" : "#ffffff"
                text: control3.displayText
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                font: control3.font
                leftPadding: 0
                rightPadding: control3.indicator.width + control3.spacing
            }
            model: ["Minute", "00","01", "02", "03", "04", "05", "06", "07", "08", "09", "10",
                "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21",
                "22", "23", "24", "25", "26", "27", "28", "29", "30", "31", "32",
                "33", "34", "35", "36", "37", "38", "39", "40", "41", "42", "43",
                "44", "45", "46", "47", "48", "49", "50","51", "52", "53", " 54",
                "55", "56", "57", "58", "59"]
            indicator: Canvas {
                x: control3.width - width - control3.rightPadding
                y: control3.topPadding + (control3.availableHeight - height) / 2
                width: 12
                height: 8
                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = control3.pressed ? "#ffffff" : "#ffffff";
                    context.fill();
                }
                Connections {
                    target: control3
                }
                contextType: "2d"
            }
            delegate: ItemDelegate {
                width: control3.width
                highlighted: control3.highlightedIndex === index
                contentItem: Text {
                    color: "#000000"
                    text: control3.textRole
                          ? (Array.isArray(control3.model) ? modelData[control3.textRole] : model[control3.textRole])
                          : modelData
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    font: control3.font
                }
            }
        }

        ComboBox {
            id: control4
            x: 703
            y: 395
            width: 116
            height: 21
            background: Rectangle {
                color: "#000000"
                radius: 2
                border.color: control4.pressed ? "#ffffff" : "#ffffff"
                border.width: control4.visualFocus ? 2 : 1
                implicitWidth: 120
                implicitHeight: 40
            }
            popup: Popup {
                y: control4.height - 1
                width: control4.width
                background: Rectangle {
                    color: "#ffffff"
                    radius: 5
                    border.color: "#ffffff"
                }
                contentItem: ListView {
                    clip: true
                    model: control4.popup.visible ? control4.delegateModel : null
                    ScrollIndicator.vertical: ScrollIndicator {
                    }
                    currentIndex: control4.highlightedIndex
                    implicitHeight: contentHeight
                }
                padding: 1
                implicitHeight: contentItem.implicitHeight
            }
            contentItem: Text {
                color: control4.pressed ? "#000000" : "#ffffff"
                text: control4.displayText
                elide: Text.ElideRight
                verticalAlignment: Text.AlignVCenter
                font: control4.font
                leftPadding: 0
                rightPadding: control4.indicator.width + control4.spacing
            }
            model: ["am/pm", "am", "pm"]
            indicator: Canvas {
                x: control4.width - width - control4.rightPadding
                y: control4.topPadding + (control4.availableHeight - height) / 2
                width: 12
                height: 8
                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle = control4.pressed ? "#ffffff" : "#ffffff";
                    context.fill();
                }
                Connections {
                    target: control4
                }
                contextType: "2d"
            }
            delegate: ItemDelegate {
                width: control4.width
                highlighted: control4.highlightedIndex === index
                contentItem: Text {
                    color: "#000000"
                    text: control4.textRole
                          ? (Array.isArray(control4.model) ? modelData[control4.textRole] : model[control4.textRole])
                          : modelData
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                    font: control4.font
                }
            }
        }

        Switch {
            id: switch2
            x: 479
            y: 498
            text: "<font color=\"white\">Off</font>"
            onToggled: {
                if(checked){
                    switch2.text= qsTr("<font color=\"white\">On</font>")
                }
                else{
                    switch2.text= qsTr("<font color=\"white\">Off</font>")
                }
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
        width: 50
        height: 720
        opacity: 0.373
        color: "#515050"
    }

    Image {
        id: toolsBtn
        x: 5
        y: 315
        width: 40
        height: 40
        //source: "images/toolsBtn.png"
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/toolsBtn.png"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseAreaToolsBtn
            x: 0
            y: 0
            width: 40
            height: 40
            hoverEnabled: true
            onEntered: {
                toolsBtn.width = 43
                toolsBtn.height = 43
            }
            onExited: {
                toolsBtn.width = 40
                toolsBtn.height = 40
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
        x: 1
        y: 689
        width: 50
        height: 12
        visible: false
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/GopenMenuDots.png"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseAreaDotsBtn
            x: 0
            y: 0
            width: 50
            height: 12
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
        x: 4
        y: 662
        width: 40
        height: 40
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/GmenuClose.png"
        fillMode: Image.PreserveAspectFit

        MouseArea {
            id: mouseAreaMenuBtn
            width: 40
            height: 40
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
        x: 1204
        y: 28
        width: 74
        height: 20
        color: "#ffffff"
        text: qsTr("")
        font.pixelSize: 16
    }

    Text {
        id: logViewerTitleText
        x: 1127
        y: 682
        width: 147
        height: 29
        visible: true
        color: "#ffffff"
        text: qsTr("Secret City Labs")
        font.pixelSize: 21
    }

    Image {
        id: homeBtn
        x: 5
        y: 10
        width: 40
        height: 40
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
            width: 40
            height: 40
            hoverEnabled: true
            onEntered: {
                homeBtn.width = 43
                homeBtn.height = 43
            }
            onExited: {
                homeBtn.width = 40
                homeBtn.height = 40
            }
            onClicked: {
                mainWin.visible = true
                logViewerWin.visible = false
                flagsWin.visible = false
                convertEvtxWin.visible = false
                flagsWin.visible = false
                settingsWin.visible = false
                schedulerWin.visible = false
            }
        }
    }

    Image {
        id: viewLogBtn
        x: 5
        y: 73
        width: 40
        height: 40
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/searchBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: mouseAreaViewLogBtn
            x: 0
            y: 0
            width: 40
            height: 40
            onExited: {
                viewLogBtn.width = 43
                viewLogBtn.height = 43
            }
            hoverEnabled: true
            onEntered: {
                viewLogBtn.width = 40
                viewLogBtn.height = 40
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
        y: 134
        width: 40
        height: 40
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/convertBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: mouseAreaConvertEvtx
            x: 0
            y: 0
            width: 40
            height: 40
            onExited: {
                evtxConvertBtn.width = 43
                evtxConvertBtn.height = 43
            }
            hoverEnabled: true
            onEntered: {
                evtxConvertBtn.width = 40
                evtxConvertBtn.height = 40
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
        y: 194
        width: 40
        height: 40
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/flagBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: flagsBtnMouseArea
            x: 0
            y: 0
            width: 40
            height: 40
            onClicked: {
                mainWin.visible = false
                logViewerWin.visible = false
                flagsWin.visible = true
                convertEvtxWin.visible = false
                settingsWin.visible = false
                schedulerWin.visible = false
            }
            onExited: {
                flagsBtn.width = 43
                flagsBtn.height = 43
            }
            onEntered: {
                flagsBtn.width = 40
                flagsBtn.height = 40
            }
            hoverEnabled: true
        }
    }

    Image {
        id: scheduleBtn
        x: 5
        y: 255
        width: 40
        height: 40
        source: "file:C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/images/scheduleBtn.png"
        fillMode: Image.PreserveAspectFit
        MouseArea {
            id: mouseAreaScheduleBtn
            x: 0
            y: 0
            width: 40
            height: 40
            onClicked: {
                mainWin.visible = false
                logViewerWin.visible = false
                flagsWin.visible = false
                convertEvtxWin.visible = false
                settingsWin.visible = false
                schedulerWin.visible = true
            }
            onExited: {
                scheduleBtn.width = 43
                scheduleBtn.height = 43
            }
            onEntered: {
                scheduleBtn.width = 40
                scheduleBtn.height = 40
            }
            hoverEnabled: true
        }
    }
}
