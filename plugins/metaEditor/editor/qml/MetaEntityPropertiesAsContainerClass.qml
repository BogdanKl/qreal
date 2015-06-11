import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 50; height: 50
	color: "transparent"
	Rectangle { 
		x: 20 * parent.width / 50
		y: 0 * parent.height / 1
		width: 3 * parent.width / 5
		height: 3 * parent.height / 5
		color: "transparent"
		border.color: "#2f4f4f"
		border.width: 1
	} 
	Rectangle { 
		x: 0 * parent.width / 1
		y: 20 * parent.height / 50
		width: 3 * parent.width / 5
		height: 3 * parent.height / 5
		color: "transparent"
		border.color: "#2f4f4f"
		border.width: 1
	} 
	Line { 
		x1: 7 * parent.width / 10
		y1: 1 * parent.height / 10
		x2: 7 * parent.width / 10
		y2: 1 * parent.height / 2
		color: "#2f4f4f"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 1 * parent.width / 2
		y1: 3 * parent.height / 10
		x2: 9 * parent.width / 10
		y2: 3 * parent.height / 10
		color: "#2f4f4f"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 1 * parent.width / 10
		y1: 7 * parent.height / 10
		x2: 1 * parent.width / 2
		y2: 7 * parent.height / 10
		color: "#2f4f4f"
		style: "solid"
		width: 1
	} 
} 
