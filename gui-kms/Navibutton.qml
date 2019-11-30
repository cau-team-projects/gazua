import QtQuick 2.0
import QtQuick.Layouts 1.1

Text {
    id: menubarItem
    text: ""
    font.family: "Helvetica"
    font.pointSize: 20
    font.weight: Font.Light
    color: "#404244"
    Layout.alignment: Qt.AlignHCenter
    state: "default"
    verticalAlignment: Text.AlignVCenter
    property bool selected: false
    property string stateSelect: ""
    property Item stateTarget

    states: [
        State {
            name: "default"
            when: !menubarItem.selected
            PropertyChanges { target: menubarItem; color: "#404244"; }
            PropertyChanges { target: selectedHighlight; height: 0; }
        },
        State {
            name: "mouseover"
            PropertyChanges { target: menubarItem; color: "#5caa15"; }
            PropertyChanges { target: selectedHighlight; height: 4; }
        },
        State {
            name: "selected"
            when: menubarItem.selected
            PropertyChanges { target: menubarItem; color: "#5caa15"; }
            PropertyChanges { target: selectedHighlight; height: 4; }
        }
    ]

    onStateChanged: {
        if (state == "selected") {
            menubarItem.stateTarget.state = menubarItem.stateSelect;
        }
    }

    transitions: [
        Transition {
            from: "*"
            to: "*"
            ColorAnimation {
                properties: "color"
                easing.type: Easing.InOutCubic
                duration: 250
            }
        }
    ]

    Rectangle {
        id: selectedHighlight
        color: "#7cc54d"
        width: parent.width
        anchors.bottom: parent.bottom
        height: 0

        Behavior on height {

                    NumberAnimation {
                        easing.type: Easing.InOutCubic
                        duration: 250
                    }
                }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true

        onPressed: {
            menubarItem.state = "mouseover";
        }

        onReleased: {
            if (menubarItem.state == "mouseover") {
                menubarItem.selected = true;
            }
        }

        onEntered: {
            menubarItem.state = "mouseover";
        }

        onExited: {
            if (menubarItem.selected) {
                menubarItem.state = "selected";
            } else {
                menubarItem.state = "default";
            }
        }
    }
}

