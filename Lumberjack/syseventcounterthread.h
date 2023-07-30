#ifndef SYSEVENTCOUNTERTHREAD_H
#define SYSEVENTCOUNTERTHREAD_H

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


class SysEventCounterThread : public QThread{
    Q_OBJECT

public:
    SysEventCounterThread(QThread *parent = 0);
    void run();
    void setSaveType(QString);

signals:
    void sysEventNum2MainContrler(QString);

public slots:

private:
    int numOfSysEvents = 0;
    QStringList sysJsonObjects;
    QString _saveType = "";
    QString docsFolder = "";
};

#endif // SYSEVENTCOUNTERTHREAD_H
