#ifndef HISTORYITEM
#define HISTORYITEM

#include <QString>

struct HistoryItem{
    int id;
    QString fileName;
    QString dateTime;
    double compressionRatio;
    double originalSize;
    double compressedSize;
    double executionTime;
    QString notes;
};

#endif // HISTORYITEM

