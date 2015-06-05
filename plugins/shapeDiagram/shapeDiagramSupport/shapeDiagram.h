#pragma once

#include <QtCore/qglobal.h>

#ifndef SHAPE_DIAGRAM_GENERATOR_EXPORT
#  if defined(SHAPE_DIAGRAM_GENERATOR_LIBRARY)
#    define SHAPE_DIAGRAM_GENERATOR_EXPORT Q_DECL_EXPORT
#  else
#    define SHAPE_DIAGRAM_GENERATOR_EXPORT Q_DECL_IMPORT
#  endif
#endif
