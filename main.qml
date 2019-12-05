import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

ApplicationWindow {
  visible: true
  color: "blue"
  width: 800
  height: 600

  ListView {
      width: 100; height: 100

      model: coinInfoModel
      delegate: Rectangle {
          height: 25
          width: 100
          color: "gray"
          Text { text: name }
      }
  }

  /*
  TreeView {
    id: view
    height: parent.height
    width: parent.width
    model: userInfo
    TableViewColumn {
      title: "test"
      width: view.width
    }
  }
  */
}
