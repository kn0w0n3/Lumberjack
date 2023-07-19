#ifndef FILEOPSTHREAD_H
#define FILEOPSTHREAD_H
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

class FileOpsThread : public QThread{
    Q_OBJECT

public:
    FileOpsThread(QThread *parent = 0);
    void run();
    void setSaveType(QString);

signals:
   // void thread_evtxProcessingDoneRelay(int);
    void secEventNum2MainContrler(QString);

public slots:

private:
    int numOfSecEvents = 0;
    QStringList secJsonObjects;
    QString result = "";
    QString _saveType = "";
    QString docsFolder = "";
};

#endif // FILEOPSTHREAD_H
