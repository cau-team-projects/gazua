import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

ApplicationWindow {
  visible: true
  color: 'blue'
  width: 800
  height: 600

  ListView {
    model: userInfo
    anchors.fill: parent
    delegate: ItemDelegate {
      width: 300
      height: 100
      Rectangle {
        Label {
          text: model.display
          color: 'red'
        }
      }
    }
  }

  MouseArea {
    anchors.fill: parent
    onClicked: console.log(userInfo)
  }
}
