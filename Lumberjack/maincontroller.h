#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include <QWidget>
#include <QProcess>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QTextStream>
//#include <QByteArray>
#include <QDomDocument>
#include <QXmlStreamReader>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringList>
#include <QObject>

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:
    void securityEventCount2Qml(QString secEventCountX);
    void appEventCount2Qml(QString appEventCountX);
    void sysEventCount2Qml(QString sysEventCountX);
    void processingStatus2Qml(QString processingStatus);

public slots:
    void getSystemLogs();
    void getApplicationLogs();
    void getSecurityLogs();

    void processStdOutSecLogInfo();
    void processErrorSecLogInfo();
    void processStdOutAppLogInfo();
    void processErrorAppLogInfo();
    void processStdOutSysLogInfo();
    void processErrorSysLogInfo();

    void sendLogInfoToQml();

    void convertSecEvtxToXml();
    void convertSecEvtxToJson();
    void convertAppEvtxToXml();
    void convertAppEvtxToJson();
    void convertSysEvtxToXml();
    void convertSysEvtxToJson();

    void getSecDatafromXml();
    void getSecDataFromJson();

    void getAppDataFromJson();
    void getSysDataFromJson();

private:
    QProcess getWinLogs;

    QProcess getSystemLogsProcess;
    QProcess getApplicationLogsProcess;
    QProcess getSecurityLogsProcess;

    QProcess parseLogs;
    QProcess convertSecEvtxToXmlProcess;
    QProcess convertSecEvtxToJsonProcess;
    QProcess convertAppEvtxToXmlProcess;
    QProcess convertAppEvtxToJsonProcess;
    QProcess convertSysEvtxToXmlProcess;
    QProcess convertSysEvtxToJsonProcess;

    //Byte arrays for std out info
    QByteArray b_StdOutSecLogInfo;
    QByteArray b_StdErrSecLogInfo;

    QByteArray b_StdOutAppLogInfo;
    QByteArray b_StdErrAppLogInfo;

    QByteArray b_StdOutSysLogInfo;
    QByteArray b_StdErrSysLogInfo;


    //Strings for std out info
    QString s_StdOutSecLogInfo;
    QString s_StdErrSecLogInfo;

    QString s_StdOutAppLogInfo;
    QString s_StdErrAppLogInfo;

    QString s_StdOutSysLogInfo;
    QString s_StdErrSysLogInfo;



    QString LogInfoText;

    QString evtxType = "";

    QString jsonStringData;
    QStringList jsonObjects;

    int numOfSecEvents = 0;
    int numbOfAppEvents = 0;
    int numbOfSysEvents = 0;

};

#endif // MAINCONTROLLER_H
