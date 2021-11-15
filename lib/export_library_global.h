#ifndef EXPORT_LIBRARY_GLOBAL_H
#define EXPORT_LIBRARY_GLOBAL_H

// #include <QtCore/qglobal.h>

#if defined(EXPORT_LIBRARY)
#  define LIBRARY_EXPORT Q_DECL_EXPORT
#else
// #  define LIBRARY_EXPORT Q_DECL_IMPORT
#  define LIBRARY_EXPORT
#endif

#endif // EXPORT_LIBRARY_GLOBAL_H
