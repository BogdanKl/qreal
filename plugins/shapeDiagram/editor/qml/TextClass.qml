import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 30; height: 19
	color: "transparent"
	Text { 
		x: 0 * parent.width / 1
		y: -15 * parent.height / 19
		color: "#000000"
		text: "text"
		font.family: "Sans Serif"
		font.pixelSize: 15 * parent.height / 19
		font.bold: false
		font.italic: false
		font.underline: false
	} 
} 
