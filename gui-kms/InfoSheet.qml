import QtQuick 2.0
import QtQuick.Layouts 1.1

Item {
    id: infoSheet
    anchors.topMargin: 59
    anchors.leftMargin: 48
    property alias headingText1: heading1.text
    property alias headingText2: heading2.text
    property alias text: description.text
    state: "hidden"

    states: [
        State {
            name: "hidden"
            when: !visible
            PropertyChanges { target: heading1; color: "#00000000"; }
            PropertyChanges { target: heading2; color: "#005caa15"; }
            PropertyChanges { target: description; color: "#00000000"; }
            PropertyChanges { target: infoSheet; visible: false; }
        },
        State {
            name: "visible"
            when: visible
            PropertyChanges { target: heading1; color: "#FF000000"; }
            PropertyChanges { target: heading2; color: "#FF5caa15"; }
            PropertyChanges { target: description; color: "#FF000000"; }
            PropertyChanges { target: infoSheet; visible: true; }
        }
    ]

    transitions: [
        Transition {
            from: "visible"
            to: "hidden"
            ColorAnimation {
                properties: "color"
                easing.type: Easing.InOutCubic
                duration: 300
            }
            PropertyAnimation {
                properties: "visible"
                duration: 300
            }
        },
        Transition {
            from: "hidden"
            to: "visible"
            ColorAnimation {
                properties: "color"
                easing.type: Easing.InOutCubic
                duration: 300
            }
        }
    ]

    ColumnLayout {
        Text {
            id: heading1
            text: ""
            font.family: "Helvetica"
            font.pointSize: 36
            font.weight: Font.Light
            color: "black"

            Text {
                id: heading2
                anchors.top: heading1.top
                anchors.left: heading1.right
                text: ""
                font.family: "Helvetica"
                font.pointSize: 36
                font.weight: Font.Light
                color: "#5caa15"
            }
        }

        Item {
            id: layoutHelper
            Layout.minimumHeight: 37
            Layout.preferredHeight: 37
            Layout.maximumHeight: 37
        }

        Text {
            id: description
            text: ""
            width: (infoSheet.width - infoSheet.anchors.leftMargin) * 0.3
            font.family: "Helvetica"
            font.pointSize: 16
            font.weight: Font.Light
        }
    }
}
