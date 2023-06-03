import QtQuick
//import QtQuick.Controls
import QtQuick.Controls 2.15

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Lumberjack")

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
            x: 239
            y: 157
            width: 802
            height: 285
            color: "#000000"
            border.color: "#ffffff"

            Text {
                id: errorLabel
                x: 19
                y: 63
                width: 66
                height: 38
                color: "#ffffff"
                text: qsTr("Error:")
                font.pixelSize: 25
            }

            Text {
                id: text2
                x: 0
                y: -33
                width: 104
                height: 38
                color: "#ffffff"
                text: qsTr("Summary")
                font.pixelSize: 25
            }

            Text {
                id: warningLabel
                x: 19
                y: 112
                width: 96
                height: 38
                color: "#ffffff"
                text: qsTr("Warning:")
                font.pixelSize: 25
            }

            Text {
                id: informationLabel
                x: 19
                y: 164
                width: 142
                height: 38
                color: "#ffffff"
                text: qsTr("Information:")
                font.pixelSize: 25
            }

            Text {
                id: auditSuccesslabel
                x: 18
                y: 216
                width: 162
                height: 38
                color: "#ffffff"
                text: qsTr("Audit Success:")
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
                text: qsTr("Last Hour")
                font.pixelSize: 25
                font.underline: true
            }

            Text {
                id: twentyfourHourlabedl
                x: 534
                y: 13
                width: 103
                height: 38
                color: "#1827f4"
                text: qsTr("24 Hours")
                font.pixelSize: 25
                font.underline: true
            }

            Text {
                id: sevenDayLabel
                x: 676
                y: 13
                width: 80
                height: 38
                color: "#1827f4"
                text: qsTr("7 Days")
                font.pixelSize: 25
                font.underline: true
            }

            Text {
                id: errorLabel1
                x: 382
                y: 63
                width: 110
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel2
                x: 534
                y: 63
                width: 103
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel3
                x: 676
                y: 63
                width: 118
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel4
                x: 382
                y: 112
                width: 110
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel5
                x: 382
                y: 164
                width: 110
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel6
                x: 382
                y: 216
                width: 110
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel7
                x: 534
                y: 112
                width: 103
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel8
                x: 534
                y: 164
                width: 103
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel9
                x: 534
                y: 216
                width: 103
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel10
                x: 676
                y: 112
                width: 118
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel11
                x: 676
                y: 164
                width: 118
                height: 38
                color: "#ffffff"
                text: qsTr("0")
                font.pixelSize: 25
            }

            Text {
                id: errorLabel12
                x: 676
                y: 216
                width: 118
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
