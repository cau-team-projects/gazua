/*import QtQuick 2.12
import QtQuick.Controls 2.5

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Scroll")

    ScrollView {
        anchors.fill: parent

        ListView {
            width: parent.width
            model: 20
            delegate: ItemDelegate {
                text: "Item " + (index + 1)
                width: parent.width
            }
        }
    }
}
*/

import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQml.Models 2.1
import QtQuick.Controls 1.0
import "./gui-kms/stock"

Item {
    id: mainRect
    width: 1280
    height: 768
    visible: true
    focus: true

    Keys.onPressed: {
        if (event.key === Qt.Key_1) imageCube.state = 'coinsPrice';
        else if (event.key === Qt.Key_2) imageCube.state = 'userBalance';
        else if (event.key === Qt.Key_3) imageCube.state = 'order';
        else if (event.key === Qt.Key_4) imageCube.state = 'login';
        else if (event.key === Qt.Key_5) imageCube.state = 'image5';
        else if (event.key === Qt.Key_6) imageCube.state = 'image6';
    }

    //! [0]
    ImageCube {
        id: imageCube
        width: 512 * (parent.width / 1280)
        height: 512 * (parent.height / 768)
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        //! [0]
        angleOffset: -180 / 8.0
        backgroundColor: "#FCFCFC"


        onStateChanged: {
            if (imageCube.state == "coinsPrice") {
                page1Button.selected = true;
                page2Button.selected = false;
                page3Button.selected = false;
                page4Button.selected = false;
                page5Button.selected = false;
                page6Button.selected = false;
                info1.visible = true;
                info2.visible = false;
                info4.visible = false;
                info3.visible = false;
                info5.visible = false;
                info6.visible = false;
            } else if (imageCube.state == "userBalance") {
                page1Button.selected = false;
                page2Button.selected = true;
                page3Button.selected = false;
                page4Button.selected = false;
                page5Button.selected = false;
                page6Button.selected = false;
                info1.visible = false;
                info2.visible = true;
                info4.visible = false;
                info3.visible = false;
                info5.visible = false;
                info6.visible = false;
            } else if (imageCube.state == "order") {
                page1Button.selected = false;
                page2Button.selected = false;
                page3Button.selected = true;
                page4Button.selected = false;
                page5Button.selected = false;
                page6Button.selected = false;
                info1.visible = false;
                info2.visible = false;
                info3.visible = true;
                info4.visible = false;
                info5.visible = false;
                info6.visible = false;
            } else if (imageCube.state == "login") {
                page1Button.selected = false;
                page2Button.selected = false;
                page3Button.selected = false;
                page4Button.selected = true;
                page5Button.selected = false;
                page6Button.selected = false;
                info1.visible = false;
                info2.visible = false;
                info3.visible = false;
                info4.visible = true;
                info5.visible = false;
                info6.visible = false;
            } else if (imageCube.state == "image5") {
                page1Button.selected = false;
                page2Button.selected = false;
                page3Button.selected = false;
                page4Button.selected = false;
                page5Button.selected = true;
                page6Button.selected = false;
                info1.visible = false;
                info2.visible = false;
                info3.visible = false;
                info4.visible = false;
                info5.visible = true;
                info6.visible = false;
            } else if (imageCube.state == "image6") {
                page1Button.selected = false;
                page2Button.selected = false;
                page3Button.selected = false;
                page4Button.selected = false;
                page5Button.selected = false;
                page6Button.selected = true;
                info1.visible = false;
                info2.visible = false;
                info3.visible = false;
                info4.visible = false;
                info5.visible = false;
                info6.visible = true;
            }
        }
    }

    property alias currentIndex: info1.currentIndex
    ColumnLayout {
        anchors.fill: parent

        Rectangle {
            id: menuBar
            anchors.top: parent.top
            width: parent.width
            height: 52
            color: "#ffffff"
            RowLayout {
                spacing: 28

                Image {
                    id: qtLogo
                    //source: "qrc:/textures/qtlogosmall.png"
                    Layout.minimumWidth: 133
                    Layout.minimumHeight:52
                    Layout.preferredWidth: 133
                    Layout.preferredHeight: 52
                    Layout.maximumWidth: 133
                    Layout.maximumHeight: 52
                }

                Navibutton {
                    id: page1Button
                    text: "Coins Price"
                    stateTarget: imageCube
                    stateSelect: "coinsPrice"
                    Layout.minimumHeight:52
                    Layout.preferredHeight: 52
                    Layout.maximumHeight: 52
                }

                Navibutton {
                    id: page2Button
                    text: "My Balance"
                    stateTarget: imageCube
                    stateSelect: "userBalance"
                    Layout.minimumHeight:52
                    Layout.preferredHeight: 52
                    Layout.maximumHeight: 52
                }

                Navibutton {
                    id: page3Button
                    text: "Order"
                    stateTarget: imageCube
                    stateSelect: "order"
                    Layout.minimumHeight:52
                    Layout.preferredHeight: 52
                    Layout.maximumHeight: 52
                }

                Navibutton {
                    id: page4Button
                    text: "Login"
                    stateTarget: imageCube
                    stateSelect: "login"
                    Layout.minimumHeight:52
                    Layout.preferredHeight: 52
                    Layout.maximumHeight: 52
                }

                Navibutton {
                    id: page5Button
                    text: "---"
                    stateTarget: imageCube
                    stateSelect: "image5"
                    Layout.minimumHeight:52
                    Layout.preferredHeight: 52
                    Layout.maximumHeight: 52
                }

                Navibutton {
                    id: page6Button
                    text: "---"
                    stateTarget: imageCube
                    stateSelect: "image6"
                    Layout.minimumHeight:52
                    Layout.preferredHeight: 52
                    Layout.maximumHeight: 52
                }
            }
        }

        Rectangle {
            id: separator
            anchors.top: menuBar.bottom
            width: parent.width
            height: 4
            color: "#e6e6e6"
        }

        /*
        InfoSheet {
            id: info1
            width: parent.width
            anchors.top: separator.bottom
            anchors.left: parent.left
            visible: false
        }
        */


        ListView {
            id: info1
            width: parent.width
            anchors.top: separator.bottom
            anchors.left: parent.left
            visible: false
            Layout.fillHeight: true
            //Layout.fillWidth: true
            snapMode: ListView.SnapOneItem
            highlightRangeMode: ListView.StrictlyEnforceRange
            //highlightMoveDuration: 250
            focus: false
            orientation: ListView.Horizontal
            boundsBehavior: Flickable.StopAtBounds



            StockModel {
                id: stock
                stockId: listView.currentStockId
                stockName: listView.currentStockName
                onStockIdChanged: stock.updateStock();
                onDataReady: {
                    info1.currentIndex = -1
                    stockView.update()
                }
            }

            model: ObjectModel {
                StockListView {
                    id: listView
                    width: info1.width
                    height: info1.height
                }

                StockView {
                    id: stockView
                    width: info1.width
                    height: info1.height
                    stocklist: listView
                    stock: stock
                }
            }
        }


        InfoSheet {
            id: info2
            visible: false
            width: parent.width
            anchors.top: separator.bottom
            anchors.left: parent.left
            headingText1: "Write & Recycle "
            headingText2: "Internet of Things"
            text: "A key focus for us is to help you get your embedded device to market quickly. You<br>"+
                  "can write and recycle Qt application and device UI code to run on all your target<br>"+
                  "devices. You can take your applications everywhere: embedded, desktop and mobile<br>"+
                  "platforms. Qt lets you future-proof your “things” by making them platform<br>"+
                  "independent. Should you want diversity between platforms, like a responsive UI<br>"+
                  "design for different screen sizes, this is simple to implement with Qt, as well."

        }

        InfoSheet {
            id: info3
            visible: false
            width: parent.width
            anchors.top: separator.bottom
            anchors.left: parent.left

            headingText1: "Rapid Embedded "
            headingText2: "Prototyping & Deployment"

            text: "We don’t want you wasting hundreds of man hours just setting up your embedded<br>"+
                  "toolchains. Prototyping on a real device can start immediately upon installation with<br>"+
                  "our fully pre-configured software stack, Boot to Qt. We provide full embedded<br>"+
                  "tooling for direct device deployment, on-device debugging and profiling, and the<br>"+
                  "needed tools to customize your stack."
        }

        Rectangle{
            id: info4
            visible: false
            width: parent.width
            anchors.top: separator.bottom
            anchors.left: parent.left

            color: "#eee"
            property variant window

            function login() {
                label.text = "Please wait..."
                window.login(userNameField.text, passwordField.text)
                userNameField.enabled = false
                passwordField.enabled = false
                userNameField.opacity = 0
                passwordField.opacity = 0
            }

            GridLayout {
                width: parent.width / 2
                anchors.centerIn: parent
                opacity: 0

                columns: 1
                rowSpacing: 18

                Item {
                    width: 256
                    height: 256
                    anchors.horizontalCenter: parent.horizontalCenter
                    Image {
                        anchors.fill: parent
                        fillMode: Image.PreserveAspectFit
                        antialiasing: true
                        source: "logo.png"

                        RotationAnimation on rotation {
                            loops: Animation.Infinite
                            from: 0
                            to: 360
                            duration: 60000
                        }
                    }
                }

                Label { id: phantomLabel; visible: false }

                Label {
                    id: label
                    font.pixelSize: 3 * phantomLabel.font.pixelSize
                    text: "Login in KORBIT"
                    color: "#888"
                }

                TextField {
                    id: userNameField
                    Layout.fillWidth: true
                    placeholderText: "User name"
                }

                TextField {
                    id: passwordField
                    echoMode: TextInput.Password
                    Layout.fillWidth: true
                    placeholderText: "Password"
                    onAccepted: login()
                }

                NumberAnimation on opacity {
                    id: fadeIn
                    to: 1.0
                    duration: 3000
                }

                Component.onCompleted: fadeIn.start()
            }
        }


        InfoSheet {
            id: info5
            visible: false
            width: parent.width
            anchors.top: separator.bottom
            anchors.left: parent.left

            headingText1: "Cross-platform "
            headingText2: "is Our Specialty"
            text: "We make cross-platform application development easy. Target all the screens in your<br>"+
                  "end users’ lives. You only need to write and maintain one code base regardless of<br>"+
                  "what kind of and how many target platforms you might have and we’re talking about<br>"+
                  "all major operating systems here. No need for separate implementations for<br>"+
                  "different user devices. Qt makes your time-to-market faster, technology strategy<br>"+
                  "simpler and future-proof, consequently reducing costs."
        }

        InfoSheet {
            id: info6
            visible: false
            width: parent.width
            anchors.top: separator.bottom
            anchors.left: parent.left

            headingText1: "What’s in the Box "
            headingText2: "Everything You Need"
            text: "Qt combines functionality with productivity. You can amaze your users with stunning<br>"+
                  "UIs and native performance by developing your desktop and multiscreen<br>"+
                  "applications with Qt.<br>"+
                  "<ul>"+
                  "<li>C++ library classes – comprehensive, highly intuitive, and modularized</li>"+
                  "<li>Declarative programming technology – exquisite UI design with Qt Quick</li>"+
                  "<li>Tooling – productive and professional development with Qt Creator IDE</li>"+
                  "</ul><br>"+
                  "Qt saves you development time, adds efficiency and ultimately shortens your<br>"+
                  "time-to-market."
        }
    }
}
