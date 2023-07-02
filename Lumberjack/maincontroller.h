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
#include <QThread>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QDate>
#include <QStandardPaths>

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:
    void securityEventCount2Qml(QString secEventCountX);
    void appEventCount2Qml(QString appEventCountX);
    void sysEventCount2Qml(QString sysEventCountX);
    void processingStatus2Qml(QString processingStatus);
    void dataToLogViewer(QString logData);
    void populateFlagDataToQml(QString eventIdFlag);

    //File info
    void fileNameToQml(QString fileName);
    void filePathToQml(QString filePath);
    void dirPathToQml(QString dirPath);
    void saveToPathToQml(QString saveToPath);

    void fileConvertEvtxStatus(QString curStatus);

    void saveScheduleDataSaveStatus(QString shedulerSaveStatus);

    void savedHourTxtToQml(QString s_Hour);
    void savedMinTxtToQml(QString s_Minute);
    void savedAmpmTxtToQml(QString s_Ampm);

    void savedDaysDataToQml(QString dayX);

    void savedClearLogDataToQML(QString cl_CheckedStatus);
    void savedAutoBackupDataToQML(QString bu_CheckedStatus);

    void archivedLogEntryToQml(QString logName);

public slots:
    void getSystemLogs();
    void getApplicationLogs();
    void getSecurityLogs();

    //void processStdOutSecLogInfo();
    //void processErrorSecLogInfo();
    //void processStdOutAppLogInfo();
    //void processErrorAppLogInfo();
    //void processStdOutSysLogInfo();
    //void processErrorSysLogInfo();

    //void processConvertStdOutInfo();
   // void processConvertErrorInfo();

    //void sendLogInfoToQml();

    //void convertSecEvtxToXml();
    void convertSecEvtxToJson();
    void convertAppEvtxToXml();
    void convertAppEvtxToJson();
    void convertSysEvtxToXml();
    void convertSysEvtxToJson();

    void getSecDatafromXml();
    void getSecDataFromJson();

    void getAppDataFromJson();
    void getSysDataFromJson();

    void populateFlagData();
    void saveFlagData(QString);

    void ce_SelectFile();
    void ce_SelectDir();
    void ce_SaveToPath();
    void fileConvertEvtx(QString, QString, QString, QString);
    void updateEvtxConvertStatus();
    void checkDirectories();
    void evtxProcessingDoneRelay(int);

    void updateCurrentLogSummary();

    void saveSchedulerTimeData(QString, QString, QString);
    void populateSchedulerTimeData();
    void saveSchedulerDayData(QStringList);
    void populateShedulerDaysData();

    void saveSchdlerClrLogData(QString);
    void popSchdlerClrLogData();

    void saveSchdlerBkupData(QString);
    void popSchdlerBkupData();

    void getArchivedLogsList();

private:
    QProcess getWinLogs;

    QProcess *getSystemLogsProcess;
    QProcess *getApplicationLogsProcess;
    QProcess *getSecurityLogsProcess;

    //QProcess parseLogs;
    QProcess convertSecEvtxToXmlProcess;
    QProcess *convertSecEvtxToJsonProcess;
    QProcess convertAppEvtxToXmlProcess;
    QProcess *convertAppEvtxToJsonProcess;
    QProcess convertSysEvtxToXmlProcess;
    QProcess *convertSysEvtxToJsonProcess;

    QProcess convertEvtxToXmlProcess;
    QProcess convertEvtxToJsonProcess;
    QProcess convertEvtxToFullJsonProcess;


    //Byte arrays for std out info
    QByteArray b_StdOutSecLogInfo;
    QByteArray b_StdErrSecLogInfo;

    QByteArray b_StdOutAppLogInfo;
    QByteArray b_StdErrAppLogInfo;

    QByteArray b_StdOutSysLogInfo;
    QByteArray b_StdErrSysLogInfo;

    QByteArray b_StdOutConvertInfo;
    QByteArray b_StdErrConvertInfo;

    //Strings for std out info
    QString s_StdOutSecLogInfo;
    QString s_StdErrSecLogInfo;

    QString s_StdOutAppLogInfo;
    QString s_StdErrAppLogInfo;

    QString s_StdOutSysLogInfo;
    QString s_StdErrSysLogInfo;

    QString s_StdOutConvertInfo;
    QString s_StdErrConvertInfo;



    QString LogInfoText;

    QString evtxType = "";

    QString jsonStringData;
    QStringList secJsonObjects;
    QStringList appJsonObjects;
    QStringList sysJsonObjects;

    int numOfSecEvents = 0;
    int numbOfAppEvents = 0;
    int numbOfSysEvents = 0;

    QString result = "";

    QStringList flagList;

    QString convertEvtxFileName = "";
    QString convertEvtxFullFilePath = "";
    QString convertEvtxFilePathOnly = "";
    QString convertEvtxFileSize = "";

    QString docsFolder = "";

    int processingCount = 0;

    QStringList listOfLogs();
};

#endif // MAINCONTROLLER_H
