import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

ApplicationWindow {
  visible: true
  color: "blue"
  width: 800
  height: 600

  TreeView {
    id: view
    height: parent.height
    width: parent.width
    model: coinTreeModel
    TableViewColumn {
      title: "test"
      width: view.width
    }
  }
}
