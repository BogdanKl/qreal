import QtQuick 1.0 
import CustomComponents 1.0 
Rectangle { 
	width: 150; height: 130
	color: "transparent"
	Line { 
		x1: 0 
		y1: 0 
		x2: 100 
		y2: 0 
		color: "#000000"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 0 
		y1: 30 
		x2: 0 
		y2: 0 
		color: "#000000"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 100 
		y1: 30 
		x2: 100 
		y2: 0 
		color: "#000000"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 0 
		y1: 30 
		x2: 1 * parent.width / 1
		y2: 30 
		color: "#000000"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 0 
		y1: 30 
		x2: 0 * parent.width / 1
		y2: 64 * parent.height / 65
		color: "#000000"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 74 * parent.width / 75
		y1: 30 
		x2: 1 * parent.width / 1
		y2: 64 * parent.height / 65
		color: "#000000"
		style: "solid"
		width: 1
	} 
	Line { 
		x1: 0 * parent.width / 1
		y1: 64 * parent.height / 65
		x2: 1 * parent.width / 1
		y2: 64 * parent.height / 65
		color: "#000000"
		style: "solid"
		width: 1
	} 
} 