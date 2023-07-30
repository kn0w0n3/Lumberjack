#ifndef APPEVENTCOUNTERTHREAD_H
#define APPEVENTCOUNTERTHREAD_H

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

class AppEventCounterThread : public QThread{
    Q_OBJECT

public:
    AppEventCounterThread(QThread *parent = 0);
    void run();
    void setSaveType(QString);

signals:
    void appEventNum2MainContrler(QString);

public slots:

private:
    int numOfAppEvents = 0;
    QStringList appJsonObjects;
    QString _saveType = "";
    QString docsFolder = "";
};

#endif // APPEVENTCOUNTERTHREAD_H
