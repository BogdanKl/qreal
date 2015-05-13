import QtQuick 1.0
import CustomComponents 1.0
Item {
   id: checkbox
   signal clicked
   property string text
   property bool state: true
   width: 100
   height: 20
   Rectangle {
       anchors.fill: checkbox
       Rectangle {
           id: checkwindow
           anchors.verticalCenter: parent.verticalCenter
           x: 0
           y: 0
           width: checkbox.width / 12
           height: 3 * checkbox.height / 5
           color: "white"
           border.width: 1
           border.color: "grey"
           Ellipse {
               x: parent.width / 2
               y: parent.height / 2
               width: parent.width
               height: parent.height
               color: checkbox.state ? "black" : "white"
               visible: checkbox.state
           }
       }

       Text {
           x: checkbox.width / 12 + 2
           y: 0
           color: "#000000"
           text: checkbox.text
           horizontalAlignment: Text.AlignHCenter
           verticalAlignment: Text.AlignVCenter
           font.pointSize: checkbox.height / 2

       }
       MouseArea {
           id: mouseArea
           anchors.fill: parent
           onClicked: {
               console.debug(checkbox.state)
               checkbox.state = checkbox.state ? false : true
           }
       }
   }
}