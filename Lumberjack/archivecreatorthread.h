#ifndef ARCHIVECREATORTHREAD_H
#define ARCHIVECREATORTHREAD_H
#include <QThread>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringList>
#include <QStandardPaths>

class ArchiveCreatorThread : public QThread{
    Q_OBJECT

public:
    ArchiveCreatorThread(QThread *parent = 0);
    void run();

signals:
    void archiveCreationStatus(QString);

public slots:
    //void setBackupType();

private:
    QString docsFolder = "";
    QString combineAllreports = "";

};

#endif // ARCHIVECREATORTHREAD_H
