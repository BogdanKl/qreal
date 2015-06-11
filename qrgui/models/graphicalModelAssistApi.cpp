#include "graphicalModelAssistApi.h"

#include <QtCore/QUuid>

#include <qrkernel/exception/exception.h>

using namespace qReal;
using namespace models;
using namespace models::details;

GraphicalModelAssistApi::GraphicalModelAssistApi(
		GraphicalModel &graphicalModel
		, GraphicalPartModel &graphicalPartModel
		, EditorManagerInterface const &editorManagerInterface
		)
	: mGraphicalModel(graphicalModel)
	, mModelsAssistApi(graphicalModel, editorManagerInterface)
	, mGraphicalPartModel(graphicalPartModel)
{
	connect(&graphicalModel, SIGNAL(nameChanged(Id)), this, SIGNAL(nameChanged(Id)));
}

EditorManagerInterface const &GraphicalModelAssistApi::editorManagerInterface() const
{
	return mModelsAssistApi.editorManagerInterface();
}

qrRepo::GraphicalRepoApi const &GraphicalModelAssistApi::graphicalRepoApi() const
{
	return mGraphicalModel.api();
}

qrRepo::GraphicalRepoApi &GraphicalModelAssistApi::mutableGraphicalRepoApi() const
{
	return mGraphicalModel.mutableApi();
}

Id GraphicalModelAssistApi::logicalId(Id const &elem) const
{
	return mGraphicalModel.data(indexById(elem), roles::logicalIdRole).value<Id>();
}

IdList GraphicalModelAssistApi::graphicalIdsByLogicalId(Id const &logicalId) const
{
	IdList result;
	QList<QPersistentModelIndex> indexes = mGraphicalModel.indexesWithLogicalId(logicalId);
	foreach (QPersistentModelIndex const &index, indexes) {
		result.append(idByIndex(index));
	}

	return result;
}

Id GraphicalModelAssistApi::createElement(Id const &parent, Id const &type)
{
	Q_ASSERT(type.idSize() == 3);
	Q_ASSERT(parent.idSize() == 4);

	Id const newElementId(type, QUuid::createUuid().toString());
	QString const elementFriendlyName = mModelsAssistApi.editorManagerInterface().friendlyName(type);
	mGraphicalModel.addElementToModel(parent, newElementId, Id::rootId(), elementFriendlyName, QPointF(0, 0));
	return newElementId;
}

Id GraphicalModelAssistApi::createElement(Id const &parent, Id const &id
		, bool isFromLogicalModel, QString const &name
		, QPointF const &position, Id const &preferedLogicalId)
{
	return mModelsAssistApi.createElement(parent, id, preferedLogicalId, isFromLogicalModel, name, position);
}

Id GraphicalModelAssistApi::copyElement(Id const &source)
{
	return mGraphicalModel.mutableApi().copy(source);
}

IdList GraphicalModelAssistApi::children(Id const &element) const
{
	return mGraphicalModel.api().children(element);
}

void GraphicalModelAssistApi::changeParent(Id const &element, Id const &parent, QPointF const &position)
{
	mGraphicalModel.changeParent(mGraphicalModel.indexById(element), mGraphicalModel.indexById(parent), position);
}

void GraphicalModelAssistApi::copyProperties(Id const &dest, Id const &src)
{
	mGraphicalModel.mutableApi().copyProperties(dest, src);
}

QMap<QString, QVariant> GraphicalModelAssistApi::properties(Id const id)
{
	return mGraphicalModel.mutableApi().properties(id);
}

QVariant GraphicalModelAssistApi::getProperties(QString const ids, QString type)
{
	if (!ids.isEmpty()) {
		Id elemId = Id::loadFromString(ids);
		if (ids == elemId.type().toString())
		{
			if (elemId.element() == "Line") {
				if (type == "x1" || type == "y1") {
					return "0";
				} else if (type == "x2" || type == "y2") {
					return "100";
				} else if (type == "PenWidth") {
					return "1";
				} else if (type == "color") {
					return "black";
				} else if (type == "style") {
					return "Solid";
				} else {
					return "";
				}
			} else if (elemId.element() == "Rectangle") {
				if (type == "x" || type == "y") {
					return "0";
				} else if (type == "width" || type == "height") {
					return "100";
				} else if (type == "color") {
					return "white";
				} else if (type == "border.color"){
					return "black";
				} else if (type == "border.width") {
					return "1";
				} else {
					return "";
				}
			} else if (elemId.element() == "Ellipse") {
				if (type == "x" || type == "y") {
					return "50";
				} else if (type == "width" || type == "height") {
					return "100";
				} else if (type == "color") {
					return "white";
				} else {
					return "";
				}
			} else if (elemId.element() == "Curve") {
				if (type == "startx" || type == "starty") {
					return "0";
				} else if (type == "endx" || type == "endy") {
					return "100";
				} else if (type == "width") {
					return "1";
				} else if (type == "color") {
					return "black";
				} else if (type == "x") {
					return "70";
				} else if (type == "y") {
					return "40";
				} else {
					return "";
				}
			} else if (elemId.element() == "Image") {
				if (type == "x1" || type == "y1") {
					return "0";
				} else if (type == "x2" || type == "y2") {
					return "100";
				} else {
					return "";
				}
			} else if (elemId.element() == "Arc") {
				if (type == "x1" || type == "y1") {
					return "0";
				} else if (type == "x2" || type == "y2") {
					return "100";
				} else if (type == "PenWidth") {
					return "1";
				} else if (type == "color") {
					return "black";
				} else if (type == "style") {
					return "Solid";
				} else if (type == "startAngle"){
					return "0";
				} else  if (type == "spanAngle"){
					return "1440";
				} else {
					return "";
				}
			} else if (elemId.element() == "Button") {
				if (type == "height") {
					return "20";
				} else if (type == "width") {
					return "100";
				} else if (type == "buttonColor") {
					return "grey";
				} else if (type == "borderColor"){
					return "black";
				} else if (type == "textColor") {
					return "black";
				} else if (type == "text") {
					return "Button";
				} else {
					return "";
				}
			} else if (elemId.element() == "CheckBox") {
				if (type == "height") {
					return "20";
				} else if (type == "width") {
					return "100";
				} else if (type == "text") {
					return "check";
				}
			} else if (elemId.element() == "TextArea") {
				if (type == "height") {
					return "20";
				} else if (type == "width") {
					return "100";
				} else {
					return "";
				}
			} else if (elemId.element() == "Text") {
				if (type == "text") {
					return "test";
				} else if (elemId.element() == "font.pixelSize") {
					return "20";
				} else {
					return "";
				}
			} else if (elemId.element() == "PortLine") {
				if (type == "startx" || type == "starty"){
					return "6";
				} else if (type == "endx" || type == "endy") {
					return "44";
				} else {
					return "";
				}
			} else {
				return "";
			}
		}
		return mGraphicalModel.mutableApi().properties(Id::loadFromString(ids)).take(type).toString();
	} else {
		return "";
	}
}

void GraphicalModelAssistApi::setProperties(Id const &id, QMap<QString, QVariant> const &properties)
{
	mGraphicalModel.mutableApi().setProperties(id, properties);
}

void GraphicalModelAssistApi::stackBefore(const Id &element, const Id &sibling)
{
	mModelsAssistApi.stackBefore(element, sibling);
}

void GraphicalModelAssistApi::setConfiguration(Id const &elem, QPolygon const &newValue)
{
	mModelsAssistApi.setProperty(elem, QVariant(newValue), roles::configurationRole);
}

QPolygon GraphicalModelAssistApi::configuration(Id const &elem) const
{
	return mModelsAssistApi.property(elem, roles::configurationRole).value<QPolygon>();
}

void GraphicalModelAssistApi::setPosition(Id const &elem, QPointF const &newValue)
{
	mModelsAssistApi.setProperty(elem, QVariant(newValue), roles::positionRole);
}

QPointF GraphicalModelAssistApi::position(Id const &elem) const
{
	return mModelsAssistApi.property(elem, roles::positionRole).value<QPointF>();
}

void GraphicalModelAssistApi::setToPort(Id const &elem, qreal const &newValue)
{
	mModelsAssistApi.setProperty(elem, QVariant(newValue), roles::toPortRole);
}

qreal GraphicalModelAssistApi::toPort(Id const &elem) const
{
	return mModelsAssistApi.property(elem, roles::toPortRole).value<qreal>();
}

void GraphicalModelAssistApi::setFromPort(Id const &elem, qreal const &newValue)
{
	mModelsAssistApi.setProperty(elem, QVariant(newValue), roles::fromPortRole);
}

qreal GraphicalModelAssistApi::fromPort(Id const &elem) const
{
	return mModelsAssistApi.property(elem, roles::fromPortRole).value<qreal>();
}

void GraphicalModelAssistApi::setName(Id const &elem, QString const &newValue)
{
	mModelsAssistApi.setProperty(elem, QVariant(newValue), Qt::DisplayRole);
}

QString GraphicalModelAssistApi::name(Id const &elem) const
{
	return mModelsAssistApi.property(elem, Qt::DisplayRole).value<QString>();
}

void GraphicalModelAssistApi::setToolTip(Id const &elem, QString const &newValue)
{
	mModelsAssistApi.setProperty(elem, QVariant(newValue), Qt::ToolTipRole);
}

QString GraphicalModelAssistApi::toolTip(Id const &elem) const
{
	return mModelsAssistApi.property(elem, Qt::ToolTipRole).value<QString>();
}

bool GraphicalModelAssistApi::isGraphicalId(Id const &id) const
{
	return indexById(id) != QModelIndex();
}

IdList GraphicalModelAssistApi::temporaryRemovedLinksFrom(Id const &elem) const
{
	return graphicalRepoApi().temporaryRemovedLinksAt(elem, "from");
}

IdList GraphicalModelAssistApi::temporaryRemovedLinksTo(Id const &elem) const
{
	return graphicalRepoApi().temporaryRemovedLinksAt(elem, "to");
}

IdList GraphicalModelAssistApi::temporaryRemovedLinksNone(Id const &elem) const
{
	return graphicalRepoApi().temporaryRemovedLinksAt(elem, QString());
}

void GraphicalModelAssistApi::removeTemporaryRemovedLinks(Id const &elem)
{
	mutableGraphicalRepoApi().removeTemporaryRemovedLinks(elem);
}

void GraphicalModelAssistApi::setTo(Id const &elem, Id const &newValue)
{
	mModelsAssistApi.setTo(elem, newValue);
}

Id GraphicalModelAssistApi::to(Id const &elem) const
{
	return mModelsAssistApi.to(elem);
}

void GraphicalModelAssistApi::setFrom(Id const &elem, Id const &newValue)
{
	mModelsAssistApi.setFrom(elem, newValue);
}

Id GraphicalModelAssistApi::from(Id const &elem) const
{
	return mModelsAssistApi.from(elem);
}

QModelIndex GraphicalModelAssistApi::indexById(Id const &id) const
{
	return mModelsAssistApi.indexById(id);
}

Id GraphicalModelAssistApi::idByIndex(QModelIndex const &index) const
{
	return mModelsAssistApi.idByIndex(index);
}

QPersistentModelIndex GraphicalModelAssistApi::rootIndex() const
{
	return mModelsAssistApi.rootIndex();
}

Id GraphicalModelAssistApi::rootId() const
{
	return mGraphicalModel.rootId();
}

bool GraphicalModelAssistApi::hasRootDiagrams() const
{
	return mModelsAssistApi.hasRootDiagrams();
}

int GraphicalModelAssistApi::childrenOfRootDiagram() const
{
	return mModelsAssistApi.childrenOfRootDiagram();
}

int GraphicalModelAssistApi::childrenOfDiagram(const Id &parent) const
{
	return mModelsAssistApi.childrenOfDiagram(parent);
}

void GraphicalModelAssistApi::removeElement(Id const &graphicalId)
{
	QPersistentModelIndex const index = indexById(graphicalId);
	if (graphicalRepoApi().exist(graphicalId) && index.isValid()) {
		mGraphicalModel.removeRow(index.row(), index.parent());
	}
}

bool GraphicalModelAssistApi::hasLabel(Id const &graphicalId, int index)
{
	return mGraphicalPartModel.findIndex(graphicalId, index).isValid();
}

void GraphicalModelAssistApi::createLabel(
		Id const &graphicalId
		, int index
		, QPointF const &position
		, QSizeF const &size
		)
{
	QModelIndex const modelIndex = mGraphicalPartModel.addGraphicalPart(graphicalId, index);
	mGraphicalPartModel.setData(modelIndex, position, GraphicalPartModel::positionRole);

	QPolygonF configuration;
	configuration.append(QPointF(size.width(), size.height()));
	mGraphicalPartModel.setData(modelIndex, configuration, GraphicalPartModel::configurationRole);
}

void GraphicalModelAssistApi::setLabelPosition(Id const &graphicalId, int index, QPointF const &position)
{
	QModelIndex const modelIndex = mGraphicalPartModel.findIndex(graphicalId, index);
	mGraphicalPartModel.setData(modelIndex, position, GraphicalPartModel::positionRole);
}

void GraphicalModelAssistApi::setLabelSize(Id const &graphicalId, int index, const QSizeF &size)
{
	QModelIndex const modelIndex = mGraphicalPartModel.findIndex(graphicalId, index);

	QPolygonF configuration;
	configuration.append(QPointF(size.width(), size.height()));
	mGraphicalPartModel.setData(modelIndex, configuration, GraphicalPartModel::configurationRole);
}

QPointF GraphicalModelAssistApi::labelPosition(Id const &graphicalId, int index) const
{
	QModelIndex const modelIndex = mGraphicalPartModel.findIndex(graphicalId, index);
	return modelIndex.data(GraphicalPartModel::positionRole).toPointF();
}

QSizeF GraphicalModelAssistApi::labelSize(Id const &graphicalId, int index) const
{
	QModelIndex const modelIndex = mGraphicalPartModel.findIndex(graphicalId, index);
	QPolygonF const configuration = modelIndex.data(GraphicalPartModel::configurationRole).value<QPolygonF>();
	return QSizeF(configuration.at(0).x(), configuration.at(0).y());
}
