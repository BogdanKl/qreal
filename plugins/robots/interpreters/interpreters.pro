TEMPLATE = subdirs

SUBDIRS = \
	interpreterCore \
	interpreterBase \
	nullKitInterpreter \
	nxtKitInterpreter \
	trikKitInterpreter \
	commonTwoDModel \

interpreterCore.depends = commonTwoDModel
nullKitInterpreter.depends = interpreterBase
nxtKitInterpreter.depends = commonTwoDModel
trikKitInterpreter.depends = commonTwoDModel
commonTwoDModel.depends = interpreterBase
