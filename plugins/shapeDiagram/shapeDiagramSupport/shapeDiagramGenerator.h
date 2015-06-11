#pragma once

#include <QtCore/QObject>
#include <QtXml/QDomElement>
#include <QtXml/QDomDocument>
#include <QtXml/QDomText>

#include <QPair>

#include "../../../qrkernel/ids.h"
#include "../../../qrutils/outFile.h"
#include "../../../qrrepo/logicalRepoApi.h"
#include "../../../qrrepo/graphicalRepoApi.h"
#include "../../../qrgui/toolPluginInterface/usedInterfaces/errorReporterInterface.h"
#include "shapeDiagram.h"
namespace shapeDiagram {

class SHAPE_DIAGRAM_GENERATOR_EXPORT ShapeDiagramGenerator : public QObject
{
	Q_OBJECT
public:
	ShapeDiagramGenerator(qrRepo::GraphicalRepoApi const &gapi, qrRepo::LogicalRepoApi const &api, qReal::ErrorReporterInterface &errorReporter);
	virtual ~ShapeDiagramGenerator();
	/// Starts generation process.
	void generate();
	QString generateExplosion(qReal::Id const &id);
private:
	void calculateSize(qReal::Id const &id, QPoint &topleft, QPoint &topright);

	QString generateCode(qReal::Id const &id);
	QString generateImport();
	QString generateBackground(QPair<int,int> parent);
	QString generateElements(qReal::Id const &id, QPair<int, int> parent, QPoint topleft, QString t);
	///methods for generating element code
	QString generateRectangle(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateEllipse(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateLine(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generatePort(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateArc(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateText(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateImage(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateCurve(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateButton(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateCheckBox(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateTextArea(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);
	QString generateLinePort(qReal::Id const &id, QPoint point, QPoint topleft, QPair<int, int> parent, QString t);

	int gcd(int a, int b);
	QString factor(int x, int y, QString parentsize);
private:

	qReal::Id const mRepoId;

	/// Logical repo API containing all information required by generator
	qrRepo::LogicalRepoApi const &mApi;
	/// Graphical repo API containing information
	qrRepo::GraphicalRepoApi const &mGApi;

	/// ErrorReporter object to which error and warning messages are put
	qReal::ErrorReporterInterface &mErrorReporter;

	QPair<int, int> mParent;
	QDomDocument mDocument;
	QDomElement mElement;
	QDomElement mLabels;
};

}
