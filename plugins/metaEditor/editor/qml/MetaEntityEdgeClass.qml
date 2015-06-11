import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	property string ids: ""
	width: 100; height: 100
	color: "transparent"
	Line { 
		x1: 1 * parent.width / 10
		y1: 0 * parent.height / 1
		x2: 0 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 1 * parent.width / 10
		y1: 1 * parent.height / 1
		x2: 0 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 9 * parent.width / 10
		y1: 0 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 9 * parent.width / 10
		y1: 1 * parent.height / 1
		x2: 1 * parent.width / 1
		y2: 1 * parent.height / 2
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
	Line { 
		x1: 17 * parent.width / 20
		y1: 24 
		x2: 3 * parent.width / 20
		y2: 24 
		color: "#2f4f4f"
		style: "solid"
		width: 2
	} 
} 
