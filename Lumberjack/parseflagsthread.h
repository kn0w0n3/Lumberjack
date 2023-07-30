#ifndef PARSEFLAGSTHREAD_H
#define PARSEFLAGSTHREAD_H
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

class ParseFlagsThread : public QThread{
    Q_OBJECT

public:
    ParseFlagsThread(QThread *parent = 0);
    void run();

signals:
    //void archiveCreationStatus(QString);
    void liveBkupStatsDoneToQml(QString);
    void addLogFileToComboBox(QString);
    void flagCount(QString);
    void updateRefreshInProgress(bool);
    void flagParsingStatus2Qml(QString);
    void flagParsingDone(int);
    void clearEventLogs();

public slots:
      //void setBackupType();
    void setData(QString, QString, bool);

private:
    QStringList flagParseList;
    QStringList logsToCompareToFlags;
    QString bType = "";
    QString fileName = "";
    QString clearLogsSwitchStatus = "";
    int flagCounter = 0;
    bool refreshInProgress = false;
};

#endif // PARSEFLAGSTHREAD_H
