#include <QPoint>

#include "declarativeCurve.h"

using namespace qmlTypes;

DeclarativeCurve::DeclarativeCurve(QDeclarativeItem *parent)
	:DeclarativePen(parent)
	, mStartx(0)
	, mStarty(0)
	, mEndx(0)
	, mEndy(0)
	, mX(0)
	, mY(0)
	, mSizex(0)
	, mSizey(0)
	, mFill(Qt::white)
{
	// Important, otherwise the paint method is never called
	setFlag(QGraphicsItem::ItemHasNoContents, false);
}

void DeclarativeCurve::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	if (mFirstSizex == 0) {
		mFirstSizex = mSizex;
	}
	if (mFirstSizey == 0) {
		mFirstSizey = mSizey;
	}
	QPen pen(mColor, mWidth);
	if (mStyle == "solid") {
		pen.setStyle(Qt::SolidLine);
	} else if (mStyle == "dot") {
		pen.setStyle(Qt::DotLine);
	} else if (mStyle == "dash") {
		pen.setStyle(Qt::DashLine);
	} else if (mStyle == "dashdot") {
		pen.setStyle(Qt::DashDotLine);
	} else if (mStyle == "dashdotdot") {
		pen.setStyle(Qt::DashDotDotLine);
	} else if (mStyle == "none") {
		pen.setStyle(Qt::NoPen);
	}

	painter->setPen(pen);
	QPoint start;
	start.setX(mStartx);
	start.setY(mStarty);
	QPoint end;
	end.setX(mEndx);
	end.setY(mEndy);
	QPoint c1;
	c1.setX(mX);
	c1.setY(mY);
	QPainterPath path(start);
	path.quadTo(c1, end);
	painter->drawPath(path);
}

int DeclarativeCurve::startx() const
{
	return mStartx;
}

int DeclarativeCurve::starty() const
{
	return mStarty;
}

int DeclarativeCurve::endx() const
{
	return mEndx;
}

int DeclarativeCurve::endy() const
{
	return mEndy;
}

int DeclarativeCurve::x() const
{
	return mX;
}

int DeclarativeCurve::y() const
{
	return mY;
}

int DeclarativeCurve::sizex() const
{
	return mSizex;
}

int DeclarativeCurve::sizey() const
{
	return mSizey;
}

QColor DeclarativeCurve::fill() const
{
	return mFill;
}

void DeclarativeCurve::setStartx(int startx)
{
	if (mStartx != startx) {
		mStartx = startx;
		updateSize();
		emit startxChanged();
		update();
	}
}

void DeclarativeCurve::setStarty(int starty)
{
	if (mStarty != starty) {
		mStarty = starty;
		updateSize();
		emit startyChanged();
		update();
	}
}

void DeclarativeCurve::setEndx(int endx)
{
	if (mEndx != endx) {
		mEndx = endx;
		updateSize();
		emit endxChanged();
		update();
	}
}

void DeclarativeCurve::setEndy(int endy)
{
	if (mEndy != endy) {
		mEndy = endy;
		updateSize();
		emit endyChanged();
		update();
	}
}

void DeclarativeCurve::setX(int x)
{
	if (mX != x) {
		mX = x;
		updateSize();
		emit xChanged();
		update();
	}
}

void DeclarativeCurve::setY(int y)
{
	if (mY != y) {
		mY = y;
		updateSize();
		emit yChanged();
		update();
	}
}

void DeclarativeCurve::setSizex(int sizex)
{
	if (mSizex != sizex) {
		mSizex = sizex;
		updateSize();
		emit sizexChanged();
		update();
	}
}

void DeclarativeCurve::setSizey(int sizey)
{
	if (mSizey != sizey) {
		mSizey = sizey;
		updateSize();
		emit sizeyChanged();
		update();
	}
}

void DeclarativeCurve::setFill(QColor color)
{
	if (mFill != color) {
		mFill = color;
		updateSize();
		emit fillChanged();
		update();
	}
}

void DeclarativeCurve::updateSize()
{
	setStartx(mStartx);
	setStarty(mStarty);
	setEndx(mEndx);
	setEndy(mEndy);
	setX(mX);
	setY(mY);
	setSizex(mSizex);
	setSizey(mSizey);
	setFill(mFill);
}
