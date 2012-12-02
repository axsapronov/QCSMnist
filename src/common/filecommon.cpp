#include "filecommon.h"

#include "debughelper.h"


//------------------------------------------------------------------------------
QStringList removeEmptyQStringFromQStringList(QStringList *list)
{
    QStringList listn;
    for(int i = 0; i < list->size(); i++)
    {
        if(!list->at(i).isEmpty()
                && list->at(i) != ""
                && list->at(i) != " ")
        {
            listn << list->at(i);
        }
    }
    //    myDebug() << listn;
    return listn;
}
//------------------------------------------------------------------------------
QStringList recursiveFind(QString directory)
{
    //// подумать, нужен ли чистый рекурсивный поиск
    //// если нет, то сюда вставить обработку getModuleFilesList
    QStringList list;
    QDirIterator iterator (directory, QDir::Files | QDir::NoSymLinks, QDirIterator::Subdirectories);
    while(iterator.hasNext())
    {
        iterator.next();
        list << iterator.fileInfo().absoluteFilePath();
    }
    return list;
}
//------------------------------------------------------------------------------
QStringList getListImages(const QString number, const QString path)
{
    QStringList list;
    QStringList listNumbers;
    list = recursiveFind(path);
//    myDebug() << path;

    for (int i = 0; i < list.size(); i++)
    {
        if (list.at(i).indexOf("/" + number + "_") >= 0)
        {
            listNumbers << list.at(i);
//            myDebug() << list.at(i);
        }
    }

    return listNumbers;
}
//------------------------------------------------------------------------------
