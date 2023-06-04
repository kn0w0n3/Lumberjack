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

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:

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

};

#endif // MAINCONTROLLER_H
