#pragma once

#include "../../../qrgui/toolPluginInterface/toolPluginInterface.h"
#include "../../../qrgui/toolPluginInterface/pluginConfigurator.h"


#include "shapeDiagramGenerator.h"

namespace shapeDiagram {

/** Entry point for generator plugin, through this class QReal GUI loads and
	runs a plugin. It provides a list of actions that user can do with a plugin
	(basically there is only "generate" action), and GUI customization object.
*/
class ShapeDiagramSupportPlugin : public QObject, public qReal::ToolPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(qReal::ToolPluginInterface)
	Q_PLUGIN_METADATA(IID "shapeDiagram.ShapeDiagramSupportPlugin")

public:
	ShapeDiagramSupportPlugin();
	virtual ~ShapeDiagramSupportPlugin();

	virtual void init(qReal::PluginConfigurator const &configurator);
	virtual QList<qReal::ActionInfo> actions();
	//virtual QPair<QString, PreferencesPage *> preferencesPage();

private slots:
	/// Slot that calls generator
	void generateQmlSourceCode();

private:
	/// Action that starts generation of .xml file with metamodel for qrxc
	QAction mGenerateQmlCode;

	/// Interface of MainWindow, used, for example, to reinit models when finished parsing
	qReal::gui::MainWindowInterpretersInterface *mMainWindowInterface;  // Does not have ownership

	/// API of logical part of a repository, mutable to allow parser build model
	qrRepo::LogicalRepoApi *mLogicalRepoApi;  // Does not have ownership

	qrRepo::GraphicalRepoApi *mGraphicalRepoApi;

	/// Control API of a repository, used for requests such as current save file name
	qrRepo::RepoControlInterface *mRepoControlApi;  // Does not have ownership
};

}

