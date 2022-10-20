#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PLAYVIDEO_LIB)
#  define PLAYVIDEO_EXPORT Q_DECL_EXPORT
# else
#  define PLAYVIDEO_EXPORT Q_DECL_IMPORT
# endif
#else
# define PLAYVIDEO_EXPORT
#endif
