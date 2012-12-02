#ifndef __FILECOMMON__H
#define __FILECOMMON__H



#include <QString>
#include <QDir>

#include <QDirIterator>
#include <QStringList>

#include <QDebug>

/**
 * @brief removeEmptyQStringFromQStringList
 * @param list
 * @return
 */
QStringList removeEmptyQStringFromQStringList(QStringList *list);
/**
 * @brief recursiveFind
 * @param directory
 * @return
 */
QStringList recursiveFind(QString directory);


// this prog
QStringList getListImages(const QString number, const QString path);
#endif // __FILECOMMON__H
