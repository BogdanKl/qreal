#include "declarativeImage.h"

#include <QtCore/QFileInfo>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtCore/QDir>

using namespace qmlTypes;
using namespace qReal;

DeclarativeImage::DeclarativeImage(QDeclarativeItem *parent)
	: QDeclarativeItem(parent)
	, mX1(0)
	, mY1(0)
	, mX2(0)
	, mY2(0)
	, mSource("default.svg")
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeImage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QString const fileName = SettingsManager::value("pathToImages").toString() + "/"
			+ mSource;
	QRect rect(mX1, mY1, mX2 - mX1, mY2 - mY1);
	mImagesCache.drawImage(fileName, *painter, rect);
}

void DeclarativeImage::ImagesCache::drawImage(
		QString const &fileName
		, QPainter &painter
		, QRect const &rect)
{
	auto savePrerenderedSvg = [this, &rect, &fileName] (QSvgRenderer &renderer) {
		QTransform scale;
		scale.scale(mCurrentZoomFactor, mCurrentZoomFactor);
		auto scaledRect = scale.mapRect(rect);
		QPixmap pixmap(scaledRect.size());
		pixmap.fill(Qt::transparent);
		QPainter pixmapPainter(&pixmap);
		renderer.render(&pixmapPainter, scaledRect);
		mPrerenderedSvgs.insert(fileName, pixmap);
	};

	if (mFileNamePixmapMap.contains(fileName)) {
		painter.drawPixmap(rect, mFileNamePixmapMap.value(fileName));
	} else if (mFileNameSvgRendererMap.contains(fileName)) {
		if (!mPrerenderedSvgs.contains(fileName)) {
			savePrerenderedSvg(*mFileNameSvgRendererMap.value(fileName));
		}

		painter.drawPixmap(rect, mPrerenderedSvgs.value(fileName));
	} else {
		// Cache miss - finding best file to load and loading it.
		QString const actualFileName = fileName.startsWith("./")
				? QApplication::applicationDirPath() + "/" + fileName
				: fileName;

		QFileInfo const actualFile = selectBestImageFile(actualFileName);

		QByteArray const rawImage = loadPixmap(actualFile);
		if (actualFile.suffix() == "svg") {
			QSharedPointer<QSvgRenderer> renderer(new QSvgRenderer(rawImage));
			mFileNameSvgRendererMap.insert(fileName, renderer);
			renderer->render(&painter, rect);
			savePrerenderedSvg(*renderer);
		} else {
			QPixmap pixmap;
			pixmap.loadFromData(rawImage);
			mFileNamePixmapMap.insert(fileName, pixmap);
			painter.drawPixmap(rect, pixmap);
		}
	}
}

QFileInfo DeclarativeImage::ImagesCache::selectBestImageFile(QString const &filePath)
{
	QFileInfo const originalFileInfo(filePath);
	QFileInfo const svgVersion(originalFileInfo.path() + originalFileInfo.completeBaseName() + "svg");

	if (svgVersion.exists()) {
		return svgVersion;
	}

	QFileInfo const fileInfo(filePath);
	if (fileInfo.exists() && fileInfo.isFile()) {
		return fileInfo;
	}

	QDir dir(fileInfo.absolutePath());
	auto candidates = dir.entryInfoList({fileInfo.completeBaseName() + ".*"}, QDir::Files);
	if (!candidates.empty()) {
		return candidates.at(0);
	}

	if (fileInfo.completeBaseName() != "default") {
		return selectBestImageFile(fileInfo.absolutePath() + "/default.svg");
	}

	return QFileInfo(":/icons/default.svg");
}

QByteArray DeclarativeImage::ImagesCache::loadPixmap(QFileInfo const &fileInfo)
{
	QFile file(fileInfo.absoluteFilePath());
	if (!file.open(QIODevice::ReadOnly)) {
		return QByteArray();
	}

	return file.readAll();
}

int DeclarativeImage::x1() const
{
	return mX1;
}

int DeclarativeImage::y1() const
{
	return mY1;
}

int DeclarativeImage::x2() const
{
	return mX2;
}

int DeclarativeImage::y2() const
{
	return mY2;
}

QString DeclarativeImage::source() const
{
	return mSource;
}

void DeclarativeImage::setX1(int x1)
{
	if (mX1 != x1) {
		mX1 = x1;
		updateSize();
		emit x1Changed();
		update();
	}
}

void DeclarativeImage::setY1(int y1)
{
	if (mY1 != y1) {
		mY1 = y1;
		updateSize();
		emit y1Changed();
		update();
	}
}

void DeclarativeImage::setX2(int x2)
{
	if (mX2 != x2) {
		mX2 = x2;
		updateSize();
		emit x2Changed();
		update();
	}
}

void DeclarativeImage::setY2(int y2)
{
	if (mY2 != y2) {
		mY2 = y2;
		updateSize();
		emit y2Changed();
		update();
	}
}

void DeclarativeImage::setSource(QString source)
{
	if (mSource != source) {
		mSource = source;
		updateSize();
		emit sourceChanged();
		update();
	}
}

void DeclarativeImage::updateSize()
{
	setX1(mX1);
	setY1(mY1);
	setX2(mX2);
	setY2(mY2);
	setSource(mSource);
}
