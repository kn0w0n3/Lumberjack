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
#include "tablemodel.h"


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
    void dirPathSepToQml(QString sepPath);
    void fileMoveStatusToQml(QString moveFileStatus);
    void flagsToRemove(QString i_flag);
    void flagsToAdd(QString i_AddFlag);
    void runOnStartSavedData(QString rosChoice);
    void refreshSummaryDavedData(QString rsChoice);


public slots:
    void getSystemLogs();
    void getApplicationLogs();
    void getSecurityLogs(QString);

    void convertSecEvtxToJson();
    void convertAppEvtxToJson();
    void convertSysEvtxToJson();

    void getSecDataFromJson();
    void getAppDataFromJson();
    void getSysDataFromJson();

    void populateFlagData();
    void saveFlagData(QString);
    void ce_SelectFile();
    void ce_SelectDir();
    void ce_SaveToPath();
    void fileConvertEvtx(QString, QString, QString, QString);
    void dirConvertEvtx(QString, QString, QString);
    void dirConvertEachEvtx(QString, QString);
    void selectDirConvertEachEvtx();
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
    void evtxCmdFolderExistsResponse();
    void createArchive();
    void moveAuditLogToReviewedFolder(QString);
    void updateMovedLogsStatus();
    void updateFlagList(QStringList, QStringList);
    void createBackup();
    void saveRunAtStartData(QString);
    void populateRunAtStartData();
    void saveRefreshSummaryData(QString);
    void populateRefreshSummaryData();

private:
    QProcess getWinLogs;
    QProcess *getSystemLogsProcess;
    QProcess *getApplicationLogsProcess;
    QProcess *getSecurityLogsProcess;
    QProcess convertSecEvtxToXmlProcess;
    QProcess *convertSecEvtxToJsonProcess;
    QProcess convertAppEvtxToXmlProcess;
    QProcess *convertAppEvtxToJsonProcess;
    QProcess convertSysEvtxToXmlProcess;
    QProcess *convertSysEvtxToJsonProcess;
    QProcess *convertEvtxToXmlProcess;
    QProcess *convertEvtxToJsonProcess;
    QProcess *convertEvtxToFullJsonProcess;
    QProcess *convertEvtxToCsvProcess;
    QProcess checkEvtxeCmdPathProcess;
    QProcess moveEvtxeCmdToDocsProcess;
    QProcess *moveAuditLogToReviewedProcesss;

    QProcess *convertEachEvtxFileProcess4;

    //Byte arrays
    QByteArray b_StdOutSecLogInfo;
    QByteArray b_StdErrSecLogInfo;
    QByteArray b_StdOutAppLogInfo;
    QByteArray b_StdErrAppLogInfo;
    QByteArray b_StdOutSysLogInfo;
    QByteArray b_StdErrSysLogInfo;
    QByteArray b_StdOutConvertInfo;
    QByteArray b_StdErrConvertInfo;

    //Strings
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
    QString convertEvtxFileName = "";
    QString convertEvtxFullFilePath = "";
    QString convertEvtxFilePathOnly = "";
    QString convertEvtxFileSize = "";
    QString docsFolder = "";
    QString result = "";

    //String lists
    QStringList secJsonObjects;
    QStringList appJsonObjects;
    QStringList sysJsonObjects;
    QStringList flagList;
    QStringList listOfLogs;
    QStringList listOfFilesToConvert;

    QString combineAllreports = "";
    QString saveType = "";

    TableModel *tableModel;

    int numOfSecEvents = 0;
    int numbOfAppEvents = 0;
    int numbOfSysEvents = 0;
    int processingCount = 0;   
};

#endif // MAINCONTROLLER_H
