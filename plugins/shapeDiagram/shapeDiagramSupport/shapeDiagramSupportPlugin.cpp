#include <QtCore/QProcess>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QDesktopWidget>

#include "../../../qrkernel/settingsManager.h"
#include "../../../qrmc/metaCompiler.h"


#include "shapeDiagramSupportPlugin.h"

//Q_EXPORT_PLUGIN2(shapeDiagramSupportPlugin, shapeDiagram::ShapeDiagramSupportPlugin);

using namespace shapeDiagram;
using namespace qReal;

ShapeDiagramSupportPlugin::ShapeDiagramSupportPlugin()
	:mGenerateQmlCode(NULL)
{
	//mAppTranslator.load(":/metaEditorSupport_" + QLocale().name());
	//QApplication::installTranslator(&mAppTranslator);
}

ShapeDiagramSupportPlugin::~ShapeDiagramSupportPlugin()
{
}

void ShapeDiagramSupportPlugin::init(PluginConfigurator const &configurator)
{
	mGraphicalRepoApi = &configurator.graphicalModelApi().mutableGraphicalRepoApi();
	mMainWindowInterface = &configurator.mainWindowInterpretersInterface();
	mLogicalRepoApi = &configurator.logicalModelApi().mutableLogicalRepoApi();
	mRepoControlApi = &configurator.repoControlInterface();
}

QList<ActionInfo> ShapeDiagramSupportPlugin::actions()
{
	mGenerateQmlCode.setText(tr("Generate Qml Code"));
	ActionInfo generateQmlCodeActionInfo(&mGenerateQmlCode, "generators", "tools");
	connect(&mGenerateQmlCode, SIGNAL(triggered()), this, SLOT(generateQmlSourceCode()));
	return QList<ActionInfo>() << generateQmlCodeActionInfo;
}

void ShapeDiagramSupportPlugin::generateQmlSourceCode()
{
	ShapeDiagramGenerator shapeGenerator(*mGraphicalRepoApi, *mLogicalRepoApi, *mMainWindowInterface->errorReporter());
	shapeGenerator.generate();
}
