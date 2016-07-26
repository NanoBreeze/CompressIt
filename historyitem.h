#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QStandardItem>
#include <QDateTime>

class HistoryItem : public QStandardItem
{
public:
    HistoryItem(const QString& fileName,
                const QString& fileType,
//                const QDateTime& dateTimeOfCompression,
                const double& compressionRatio);

    void setFileName(const QString&);
    QString getFileName() const;

    void setFileType(const QString&);
    QString getFileType() const;

    void setDateTimeOfCompression(const QDateTime&);
    QDateTime getDateTimeOfCompression() const;

    void setCompressionRatio(const double&);
    double getComrpessionRatio() const;

private:
    QString fileName;
    QString fileType;
    QDateTime dateTimeOfCompression;
    double compressionRatio;    //the ratio between compressed size and original size

};

#endif // HISTORYITEM_H
