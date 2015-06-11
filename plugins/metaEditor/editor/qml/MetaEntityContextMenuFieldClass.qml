import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 100; height: 30
	color: "transparent"
	Rectangle { 
		x: 0 * parent.width / 1
		y: 0 * parent.height / 1
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		color: "#ffffff"
		border.color: "#000000"
		border.width: 1
	} 
	Text { 
		x: 1 * parent.width / 20
		y: 0 * parent.height / 1
		color: "#00007f"
		text: "Context Menu Field"
		font.family: "Helvetica"
		font.pixelSize: 1 * parent.height / 3
		font.bold: false
		font.italic: false
		font.underline: false
	} 
} 
