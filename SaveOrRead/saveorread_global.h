#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SAVEORREAD_LIB)
#  define SAVEORREAD_EXPORT Q_DECL_EXPORT
# else
#  define SAVEORREAD_EXPORT Q_DECL_IMPORT
# endif
#else
# define SAVEORREAD_EXPORT
#endif
