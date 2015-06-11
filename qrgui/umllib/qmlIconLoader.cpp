#include "qmlIconLoader.h"

#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeItem>

#include <qrkernel/ids.h>

#include <qrutils/graphicsUtils/itemRenderer.h>

using namespace qReal;

QmlIconLoader::QmlIconLoader()
{
}

QmlIconLoader::~QmlIconLoader()
{
}

void QmlIconLoader::setQmlEngine(QDeclarativeEngine * const engine)
{
	instance()->mQmlEngine = engine;
}

QIcon QmlIconLoader::iconOf(QString const &qmlString, const Id &id)
{
	return loadPixmap(qmlString, id);
}

QSize QmlIconLoader::preferedSizeOf(QString const &qmlStringm, const Id &id)
{
	loadPixmap(qmlStringm, id);
	return instance()->mPreferedSizes[qmlStringm];
}

QmlIconLoader *QmlIconLoader::instance()
{
	static QmlIconLoader instance;
	return &instance;
}

QIcon QmlIconLoader::loadPixmap(QString const &qmlString, Id const &id)
{
	QDeclarativeComponent component(instance()->mQmlEngine);
	component.setData(qmlString.toLocal8Bit(), QUrl());
	QObject  *object = component.create();
	if (id.diagram() == "ShapeEditor") {
		object->setProperty("ids", id.type().toString());
	}
	QDeclarativeItem * const item = qobject_cast<QDeclarativeItem *>(object);
	QIcon const icon = graphicsUtils::ItemRenderer::renderRecursively(item
		, item->width(), item->height(), QColor(Qt::white));

	instance()->mLoadedIcons[qmlString] = icon;
	instance()->mPreferedSizes[qmlString] = QSize(item->width(), item->height());

	return instance()->mLoadedIcons[qmlString];
}
