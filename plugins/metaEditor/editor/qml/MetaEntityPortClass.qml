import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 50; height: 50
	color: "transparent"
	Line { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 0 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 1 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 0 * parent.height / 1
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 1 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 1
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Ellipse { 
		x: 25 * parent.width / 50
		y: 25 * parent.height / 50
		width: 1 * parent.width / 1
		height: 1 * parent.height / 1
		color: "#ffffff"
		border.color: "#2f4f4f"
		border.style: "solid"
		border.width: 1
	} 
} 
