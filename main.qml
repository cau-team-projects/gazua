import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Controls 1.4

ApplicationWindow {
  visible: true
  color: "red"
  width: 800
  height: 600
  TreeView {
    height: parent.height
    width: parent.width
    TableViewColumn {
        //title: "test"
        //role: "testRole"
        title: "hi"
        role: "key"
        width: parent.width
    }
    //model: userInfo
    model: coinInfoModel
  }
}
