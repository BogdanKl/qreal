import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 30; height: 30
	color: "transparent"
	Ellipse { 
		x: 15 * parent.width / 30
		y: 15 * parent.height / 30
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		color: "#ffffff"
		border.color: "#000000"
		border.style: "dot"
		border.width: 1
	} 
	Ellipse { 
		x: 15 * parent.width / 30
		y: 15 * parent.height / 30
		width: 2 * parent.width / 3
		height: 2 * parent.height / 3
		color: "#000000"
		border.color: "#0000f0"
		border.style: "solid"
		border.width: 1
	} 
	Text { 
		x: 3 * parent.width / 10
		y: 1 * parent.height / 6
		color: "#ffffff"
		text: "M"
		font.family: "Helvetica"
		font.pixelSize: 1 * parent.height / 2
		font.bold: false
		font.italic: false
		font.underline: false
	} 
} 
