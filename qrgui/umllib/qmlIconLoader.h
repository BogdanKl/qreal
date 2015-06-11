#pragma once

#include <QtCore/QMap>
#include <QtGui/QIcon>

#include <qrkernel/ids.h>

class QDeclarativeEngine;

namespace qReal {

/// Caches qml-described icons.
class QmlIconLoader
{
public:
	/// Configures the only qml icon loader instance to use the given qml engine for rendering icons.
	static void setQmlEngine(QDeclarativeEngine * const engine);

	/// Returns a pixmap of element in specified qml-file
	static QIcon iconOf(QString const &qmlString, Id const &id);

	/// Returns a size of the pixmap of element in specified qml-file
	static QSize preferedSizeOf(QString const &qmlStringm, Id const &id);

private:
	static QmlIconLoader *instance();
	static QIcon loadPixmap(QString const &qmlString, Id const &id);

	QmlIconLoader();
	~QmlIconLoader();

	QDeclarativeEngine *mQmlEngine;
	QMap<QString, QIcon> mLoadedIcons;
	QMap<QString, QSize> mPreferedSizes;
};

}
