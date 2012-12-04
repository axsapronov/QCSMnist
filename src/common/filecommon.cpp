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
int getCountNumberTrain(int number)
{
    int res = 0;

    switch (number)
    {
    case 1:
        res = 1134;
        break;
    case 2:
        res = 1031;
        break;
    case 3:
        res = 1009;
        break;
    case 4:
        res = 981;
        break;
    case 5:
        res = 891;
        break;
    case 6:
        res = 957;
        break;
    case 7:
        res = 1027;
        break;
    case 8:
        res = 973;
        break;
    case 9:
        res = 1008;
        break;
    default:
        // 0
        res = 979;
        break;
    }
    return res;
}
//------------------------------------------------------------------------------
int getCountNumberTest(int number)
{
    int res = 0;

    switch (number)
    {
    case 1:
        res = 6741;
        break;
    case 2:
        res = 5957;
        break;
    case 3:
        res = 6130;
        break;
    case 4:
        res = 5841;
        break;
    case 5:
        res = 5420;
        break;
    case 6:
        res = 5917;
        break;
    case 7:
        res = 6264;
        break;
    case 8:
        res = 5850;
        break;
    case 9:
        res = 5948;
        break;
    default:
        // 0
        res = 5922;
        break;
    }
    return res;
}
//------------------------------------------------------------------------------
