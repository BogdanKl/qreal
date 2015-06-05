#include "shapeDiagramGenerator.h"

#include <QtCore/QDebug>

#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QPoint>
#include <QPolygon>

#include "../../../qrutils/outFile.h"


using namespace shapeDiagram;
using namespace qReal;
using utils::OutFile;


ShapeDiagramGenerator::ShapeDiagramGenerator(qrRepo::GraphicalRepoApi const &gapi, qrRepo::LogicalRepoApi const &api, qReal::ErrorReporterInterface &errorReporter)
	: mGApi(gapi)
	, mApi(api)
	, mErrorReporter(errorReporter)
{
}

ShapeDiagramGenerator::~ShapeDiagramGenerator()
{

}

void ShapeDiagramGenerator::generate()
{
	QString path;
	QString name;
	Id const repoId = Id::rootId();
	IdList const rootDiagrams = mApi.children(repoId);
	foreach (Id const typeElement, rootDiagrams) {
		if (mApi.hasProperty(typeElement, "name of the directory"))
		{
			path =  mApi.property(typeElement, "name of the directory").toString();
		}
		if (mApi.hasProperty(typeElement, "file name"))
		{
			name = mApi.property(typeElement, "file name").toString();
		}
	}

	if (path == "") {
		path = ".";
	}

	if (name == "") {
		name = "Test";
	}
	utils::OutFile out(path + "/" + name);

	foreach (Id const typeElement, rootDiagrams) {
		if (mGApi.isGraphicalElement(typeElement))
		{
			out() << generateCode(typeElement);
		}
	}
}

QList<QVariant> ShapeDiagramGenerator::generateExplosion(Id const &id)
{
	QString code =  generateCode(id);
	QList<QVariant> result;
	result << mParent.first << mParent.second << code;
	return result;
}

QString ShapeDiagramGenerator::generateCode(const Id &id)
{
	QPoint topleft;
	QPoint topright;
	QString result = "";
	qDebug() << !mGApi.children(id).isEmpty();
	if (!mGApi.children(id).isEmpty()){
		qReal::Id childId = mGApi.children(id).first();
		topleft.setX(mGApi.position(childId).toPoint().rx());
		topright.setX(mGApi.position(childId).toPoint().rx());
		topleft.setY(mGApi.position(childId).toPoint().ry());
		topright.setY(mGApi.position(childId).toPoint().ry());
	}
	foreach(Id const childId, mApi.children(id))
	{
		calculateSize(childId, topleft, topright);
	}
	qDebug() << topleft << topright;
	result += generateImport() + QString("\n");
	mParent = qMakePair(topright.rx() - topleft.rx(), topright.ry() - topleft.ry());
	result += generateBackground(mParent);
	foreach (Id const childId, mApi.children(id)) {
		result += generateElements(childId, mParent, topleft, "\t");
	}
	return (result + QString("}\n"));
}

QString ShapeDiagramGenerator::generateBackground(QPair<int, int> parent)
{
	QString result = "";
	result += QString("Rectangle { \n")
			+ QString("\twidth: %1 %2").arg(QString::number(parent.first)).arg(QString("\n"))
			+ QString("\theight: %1 %2").arg(QString::number(parent.second)).arg(QString("\n"))
			+ QString("\tcolor: ""\"transparent""\"\n");
	return result;
}

void ShapeDiagramGenerator::calculateSize(const Id &id, QPoint &topleft, QPoint &topright)
{
	QPoint position = mGApi.position(id).toPoint();
	QPoint right;
	QString name = id.type().toString();
	qDebug() << topleft << topright << position;
	if (name == "qrm:/ShapeDiagram/ShapeEditor/Text") {
		right = mGApi.configuration(id).value<QPolygon>().at(2);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Line" || name == "qrm:/ShapeDiagram/ShapeEditor/Arc" || name == "qrm:/ShapeDiagram/ShapeEditor/Image") {
		right.setX(qMax(mApi.property(mGApi.logicalId(id), "x1").toInt(), mApi.property(mGApi.logicalId(id), "x2").toInt()));
		right.setY(qMax(mApi.property(mGApi.logicalId(id), "y1").toInt(), mApi.property(mGApi.logicalId(id), "y2").toInt()));
	} else  if (name == "qrm:/ShapeDiagram/ShapeEditor/Curve") {
		right.setX(qMax(qMax(mApi.property(mGApi.logicalId(id), "x").toInt(), mApi.property(mGApi.logicalId(id), "startx").toInt()), mApi.property(mGApi.logicalId(id), "endx").toInt()));
		right.setY(qMax(qMax(mApi.property(mGApi.logicalId(id), "y").toInt(), mApi.property(mGApi.logicalId(id), "starty").toInt()), mApi.property(mGApi.logicalId(id), "endy").toInt()));
	} else {
		right.setX(mApi.property(mGApi.logicalId(id), "width").toInt());
		right.setY(mApi.property(mGApi.logicalId(id), "height").toInt());
	}

	topleft.setX(qMin(topleft.rx(), position.rx()));
	topleft.setY(qMin(topleft.ry(), position.ry()));

	topright.setX(qMax(topright.rx(), position.rx() + right.x()));
	topright.setY(qMax(topright.ry(), position.ry() + right.y()));

	foreach(Id const childId, mGApi.children(id))
	{
		calculateSize(childId, topleft, topright);
	}
}

QString ShapeDiagramGenerator::generateElements(const Id &id, QPair<int, int> parent, QPoint topleft, QString t)
{
	QString result = "";
	QPoint position = mGApi.position(id).toPoint();
	QString name = id.type().toString();
	qReal::Id logicId = mGApi.logicalId(id);
	if (name == "qrm:/ShapeDiagram/ShapeEditor/Rectangle") {
		result += generateRectangle(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Ellipse") {
		result += generateEllipse(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Line") {
		result += generateLine(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Curve") {
		result += generateCurve(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Image") {
		result += generateImage(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Arc") {
		result += generateArc(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Text") {
		result += generateText(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/TextArea") {
		result += generateTextArea(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Port") {
		result += generatePort(logicId, position, topleft, parent, t);
	} else if ( name == "qrm:/ShapeDiagram/ShapeEditor/PortLine") {
		result += generateLinePort(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/Button") {
		result += generateButton(logicId, position, topleft, parent, t);
	} else if (name == "qrm:/ShapeDiagram/ShapeEditor/CheckBox") {
		result += generateCheckBox(logicId, position, topleft, parent, t);
	}
	foreach(Id const childId, mGApi.children(id))
	{
		result += generateElements(childId, parent, topleft, t + "\t");
	}

	if (name != "qrm:/ShapeDiagram/ShapeEditor/ShapeDiagramNode" && name != "qrm:/MetaEditor/MetaEditor/ShapeDiagramNode")
	{
		result += QString("%1%2").arg(t).arg(QString("}\n"));
	}
	return result;
}

QString ShapeDiagramGenerator::generateImport()
{
	QString result = "";
	result += QString("%1%2%3").arg("import QtQuick 1.0 \n")
			.arg(QString("import CustomComponents 1.0 \n"))
			.arg(QString("import ""\"qrc:/qmlType/Control/""\" \n"));
	return result;
}

QString ShapeDiagramGenerator::generateRectangle(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QString result = "";
	QPoint coordinate(point.rx() - topleft.rx() + mApi.property(id, "x").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y").toInt());
	result += QString("%1%2").arg(t).arg(QString("Rectangle { \n"))
			+ QString("%1\tx: %2\n").arg(t).arg(factor(coordinate.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(coordinate.ry(), parent.second, "height"))
			+ QString("%1\twidth: %2\n").arg(t).arg(factor(mApi.property(id, "width").toInt(), parent.first, "width"))
			+ QString("%1\theight: %2\n").arg(t).arg(factor(mApi.property(id, "height").toInt(), parent.second, "height"))
			+ QString("%1\tcolor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "color").toString())
			+ QString("%1\tborder.color: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "border.color").toString())
			+ QString("%1\tborder.width: %2\n").arg(t).arg(mApi.property(id, "border.width").toString());
	return result;
}

QString ShapeDiagramGenerator::generatePort(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	Q_UNUSED(id);
	QString result = "";
	QPoint coordinate(point.rx() - topleft.rx() + 3, point.ry() - topleft.ry() + 3);
	result += t + QString("Ellipse { \n")
			+ QString("%1\tx: %2\n").arg(t).arg(factor(coordinate.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(coordinate.ry(), parent.second, "height"))
			+ t + QString("\twidth: 6 \n")
			+ t + QString("\theight: 6 \n")
			+ t + QString("\tcolor: ""\"black""\"\n");
	return result;
}

QString ShapeDiagramGenerator::generateEllipse(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QString result = "";
	QPoint coordinate(point.rx() - topleft.rx() + mApi.property(id, "x").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y").toInt());
	result += t + QString("Ellipse { \n")
			+ QString("%1\tx: %2\n").arg(t).arg(factor(coordinate.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(coordinate.ry(), parent.second, "height"))
			+ QString("%1\twidth: %2\n").arg(t).arg(factor(mApi.property(id, "width").toInt(), parent.first, "width"))
			+ QString("%1\theight: %2\n").arg(t).arg(factor(mApi.property(id, "height").toInt(), parent.second, "height"))
			+ QString("%1\tcolor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "color").toString())
			+ QString("%1\tborder.color: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "border.color").toString())
			+ QString("%1\tborder.width: %2\n").arg(t).arg(mApi.property(id, "border.width").toString())
			+ QString("%1\tborder.style: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "border.style").toString());
	return result;
}

QString ShapeDiagramGenerator::generateLine(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QPoint point_1(point.rx() - topleft.rx() + mApi.property(id, "x1").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y1").toInt());
	QPoint point_2(point.rx() - topleft.rx() + mApi.property(id, "x2").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y2").toInt());
	QString result = t + QString("Line { \n");
	result += QString("%1\tx1: %2\n").arg(t).arg(factor(point_1.rx(), parent.first, "width"))
			+ QString("%1\ty1: %2\n").arg(t).arg(factor(point_1.ry(), parent.second, "height"))
			+ QString("%1\tx2: %2\n").arg(t).arg(factor(point_2.rx(), parent.first, "width"))
			+ QString("%1\ty2: %2\n").arg(t).arg(factor(point_2.ry(), parent.second, "height"))
			+ QString("%1\tcolor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "color").toString())
			+ QString("%1\twidth: %2\n").arg(t).arg(mApi.property(id, "PenWidth").toString())
			+ QString("%1\tstyle: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "style").toString());
	return result;
}

QString ShapeDiagramGenerator::generateArc(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QPoint point_1(point.rx() - topleft.rx() + mApi.property(id, "x1").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y1").toInt());
	QPoint point_2(point.rx() - topleft.rx() + mApi.property(id, "x2").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y2").toInt());
	QString result = t + QString("Arc { \n");
	result += QString("%1\tx1: %2\n").arg(t).arg(factor(point_1.rx(), parent.first, "width"))
			+ QString("%1\ty1: %2\n").arg(t).arg(factor(point_1.ry(), parent.second, "height"))
			+ QString("%1\tx2: %2\n").arg(t).arg(factor(point_2.rx(), parent.first, "width"))
			+ QString("%1\ty2: %2\n").arg(t).arg(factor(point_2.ry(), parent.second, "height"))
			+ QString("%1\tcolor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "color").toString())
			+ QString("%1\twidth: %2\n").arg(t).arg(mApi.property(id, "PenWidth").toString())
			+ QString("%1\tstyle: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "style").toString())
			+ QString("%1\tstartAngle: %2\n").arg(t).arg(mApi.property(id, "startAngle").toString())
			+ QString("%1\tspanAngle: %2\n").arg(t).arg(mApi.property(id, "spanAngle").toString());
	return result;
}

QString ShapeDiagramGenerator::generateText(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QPoint coordinate(point.rx() - topleft.rx() + mApi.property(id, "x").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y").toInt());
	QString result =  t + QString("Text { \n");
	result += QString("%1\tx: %2\n").arg(t).arg(factor(coordinate.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(coordinate.ry(), parent.second, "height"))
			+ QString("%1\ttext: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "text").toString())
			+ QString("%1\tcolor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "color").toString())
			+ QString("%1\tfont.family: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "font.family").toString())
			+ QString("%1\tfont.bold: %2\n").arg(t).arg(mApi.property(id, "font.bold").toString())
			+ QString("%1\tfont.italic: %2\n").arg(t).arg(mApi.property(id, "font.italic").toString())
			+ QString("%1\tfont.underline: %2\n").arg(t).arg(mApi.property(id, "font.underline").toString())
			+ QString("%1\tfont.pixelSize: %2\n").arg(t).arg(factor(mApi.property(id, "font.pixelSize").toInt(), parent.second, "height"));
	return result;
}

QString ShapeDiagramGenerator::generateImage(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QPoint point_1(point.rx() - topleft.rx() + mApi.property(id, "x1").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y1").toInt());
	QPoint point_2(point.rx() - topleft.rx() + mApi.property(id, "x2").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y2").toInt());
	QString result = t + QString("Picture { \n");
	result += QString("%1\tx1: %2\n").arg(t).arg(factor(point_1.rx(), parent.first, "width"))
			+ QString("%1\ty1: %2\n").arg(t).arg(factor(point_1.ry(), parent.second, "height"))
			+ QString("%1\tx2: %2\n").arg(t).arg(factor(point_2.rx(), parent.first, "width"))
			+ QString("%1\ty2: %2\n").arg(t).arg(factor(point_2.ry(), parent.second, "height"))
			+ QString("%1\tsource: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "source").toString());
	return result;
}

QString ShapeDiagramGenerator::generateCurve(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QPoint point_start(point.rx() - topleft.rx() + mApi.property(id, "startx").toInt(), point.ry() - topleft.ry() + mApi.property(id, "starty").toInt());
	QPoint point_end(point.rx() - topleft.rx() + mApi.property(id, "endx").toInt(), point.ry() - topleft.ry() + mApi.property(id, "endy").toInt());
	QPoint point_xy(point.rx() - topleft.rx() + mApi.property(id, "x").toInt(), point.ry() - topleft.ry() + mApi.property(id, "y").toInt());
	QString result = t + QString("Curve { \n");
	result += QString("%1\tstartx: %2\n").arg(t).arg(factor(point_start.rx(), parent.first, "width"))
			+ QString("%1\tstarty: %2\n").arg(t).arg(factor(point_start.ry(), parent.second, "height"))
			+ QString("%1\tendx: %2\n").arg(t).arg(factor(point_end.rx(), parent.first, "width"))
			+ QString("%1\tendy: %2\n").arg(t).arg(factor(point_end.ry(), parent.second, "height"))
			+ QString("%1\tx: %2\n").arg(t).arg(factor(point_xy.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(point_xy.ry(), parent.second, "height"))
			+ QString("%1\tcolor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "color").toString())
			+ QString("%1\tfill: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "fill").toString())
			+ QString("%1\tstyle: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "style").toString());
	return result;
}

QString ShapeDiagramGenerator::generateButton(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QString result = t + QString("Button { \n");
	result += QString("%1\tx: %2\n").arg(t).arg(factor(point.rx() - topleft.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(point.ry() - topleft.ry(), parent.second, "height"))
			+ QString("%1\tbuttonWidth: %2\n").arg(t).arg(factor(mApi.property(id, "width").toInt(), parent.first, "width"))
			+ QString("%1\tbuttonHeight: %2\n").arg(t).arg(factor(mApi.property(id, "height").toInt(), parent.second, "height"))
			+ QString("%1\tlabel: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "text").toString())
			+ QString("%1\ttextColor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "textColor").toString())
			+ QString("%1\tbuttonColor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "buttonColor").toString())
			+ QString("%1\tborderColor: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "borderColor").toString());
	return result;
 }

QString ShapeDiagramGenerator::generateCheckBox(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QString result = t + QString("CheckBox { \n");
	result += QString("%1\tx: %2\n").arg(t).arg(factor(point.rx() - topleft.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(point.ry() - topleft.ry(), parent.second, "height"))
			+ QString("%1\twidth: %2\n").arg(t).arg(factor(mApi.property(id, "width").toInt(), parent.first, "width"))
			+ QString("%1\theight: %2\n").arg(t).arg(factor(mApi.property(id, "height").toInt(), parent.second, "height"))
			+ QString("%1\ttext: ""\"%2""\"\n").arg(t).arg(mApi.property(id, "text").toString());
	return result;
}

QString ShapeDiagramGenerator::generateTextArea(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QString result = t + QString("TextArea { \n");
	result += QString("%1\tx: %2\n").arg(t).arg(factor(point.rx() - topleft.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(point.ry() - topleft.ry(), parent.second, "height"))
			+ QString("%1\twidth: %2\n").arg(t).arg(factor(mApi.property(id, "width").toInt(), parent.first, "width"))
			+ QString("%1\theight: %2\n").arg(t).arg(factor(mApi.property(id, "height").toInt(), parent.second, "height"));
	return result;
}

QString ShapeDiagramGenerator::generateLinePort(const Id &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t)
{
	QPoint point_start(point.rx() - topleft.rx() + mApi.property(id, "startx").toInt(), point.ry() - topleft.ry() + mApi.property(id, "starty").toInt());
	QPoint point_end(point.rx() - topleft.rx() + mApi.property(id, "endx").toInt(), point.ry() - topleft.ry() + mApi.property(id, "endy").toInt());
	QString result = t + QString("Ellipse { \n");
	result += QString("%1\tx: %2\n").arg(t).arg(factor(point_start.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(point_start.ry(), parent.second, "height"))
			+ t + QString("\twidth: 6 \n")
			+ t + QString("\theight: 6 \n")
			+ t + QString("\tcolor: ""\"black""\"\n")
			+ t + QString("} \n")
			+ t + QString("Ellipse { \n")
			+ QString("%1\tx: %2\n").arg(t).arg(factor(point_end.rx(), parent.first, "width"))
			+ QString("%1\ty: %2\n").arg(t).arg(factor(point_end.ry(), parent.second, "height"))
			+ t + QString("\twidth: 6 \n")
			+ t + QString("\theight: 6 \n")
			+ t + QString("\tcolor: ""\"black""\"\n")
			+ t + QString("} \n")
			+ t + QString("Line { \n")
			+ t + QString("%1\tx1: %2\n").arg(t).arg(factor(point_start.rx(), parent.first, "width"))
			+ t + QString("%1\ty1: %2\n").arg(t).arg(factor(point_start.ry(), parent.second, "height"))
			+ t + QString("%1\tx2: %2\n").arg(t).arg(factor(point_end.rx(), parent.first, "width"))
			+ t + QString("%1\ty2: %2\n").arg(t).arg(factor(point_end.ry(), parent.second, "height"))
			+ t + QString("\tcolor: ""\"black""\"\n")
			+ t + QString("\tstyle: ""\"solid""\"\n")
			+ t + QString("\twidth: 1\n");
	return result;
}

QString ShapeDiagramGenerator::factor(int x, int y, QString parentsize)
{
	if (x == 0) {
		return QString::number(0);
	}
	if (x == y) {
		return QString(" parent.%1").arg(parentsize);
	}
	int nod = gcd(x, y);
	if (x == nod) {
		return QString(" parent.%1 / %2").arg(parentsize).arg(QString::number(y / nod));
	}
	return QString("%1 * parent.%2 / %3").arg(QString::number(x / nod)).arg(parentsize).arg(QString::number(y / nod));
}

int ShapeDiagramGenerator::gcd(int a, int b)
{
	int c;
	while (b) {
		c = a % b;
		a = b;
		b = c;
	}
	return abs(a);
}
