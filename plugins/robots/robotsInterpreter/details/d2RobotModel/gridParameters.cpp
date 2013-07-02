#include <QtWidgets/QHBoxLayout>
#include <QtCore/QString>

#include "gridParameters.h"
#include "../../../qrkernel/settingsManager.h"

GridParameters::GridParameters(QWidget *parent)
	: QFrame(parent)
{
	QHBoxLayout *layout = new QHBoxLayout(this);

	mShowGridCheckBox = new QCheckBox(this);
	QString const checkBoxTitle = tr("Show grid");
	mShowGridCheckBox->setText(checkBoxTitle);
	mShowGridCheckBox->setTristate(false);

	mCellSize = new QSlider(this);
	mCellSize->setOrientation(Qt::Horizontal);
	mCellSize->setMinimum(50);
	mCellSize->setMaximum(200);
	mCellSize->setTickInterval(10);
	mCellSize->setEnabled(false);

	layout->addWidget(mShowGridCheckBox);
	layout->addWidget(mCellSize);
	layout->setContentsMargins(5, 5, 5, 5);

	connect(mShowGridCheckBox, SIGNAL(toggled(bool)), mCellSize, SLOT(setEnabled(bool)));
	connect(mShowGridCheckBox, SIGNAL(toggled(bool)), this, SLOT(showGrid(bool)));
	connect(mCellSize, SIGNAL(valueChanged(int)), this, SLOT(setCellSize(int)));

	setLayout(layout);

	showGrid(qReal::SettingsManager::value("2dShowGrid").toBool());
	setCellSize(qReal::SettingsManager::value("2dGridCellSize").toInt());
}

GridParameters::~GridParameters()
{
}

void GridParameters::showGrid(bool isGridEnabled)
{
	qReal::SettingsManager::setValue("2dShowGrid", isGridEnabled);
	emit parametersChanged();
}

void GridParameters::setCellSize(int cellSizeValue)
{
	qReal::SettingsManager::setValue("2dGridCellSize", cellSizeValue);
	emit parametersChanged();
}
