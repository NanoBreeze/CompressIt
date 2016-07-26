#include "historyitem.h"

HistoryItem::HistoryItem(const QString& fileName,
const QString& fileType,
//const QDateTime& dateTimeOfCompression,
const double& compressionRatio)
{
    this->fileName = fileName;
    this->fileType = fileType;
    this->dateTimeOfCompression = dateTimeOfCompression;
    this->compressionRatio = compressionRatio;
}

