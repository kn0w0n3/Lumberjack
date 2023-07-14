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
#include <QSettings>
#include <QCoreApplication>
//#include "tablemodel.h"


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
    void addLogFileToComboBox(QString logFileName);
    void liveBkupStatsDoneToQml(QString liveBackupStatus);
    void flagCount(QString _FlagCount);
    void settingsWinStatMesg(QString sw_StatMsg);
    void savedRefreshDataToQml(QString refreshData_);

public slots:
    void getSystemLogs();
    void getApplicationLogs();
    void getSecurityLogs(QString, QString);

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
    void createArchive(QString);
    void moveAuditLogToReviewedFolder(QString);
    void updateMovedLogsStatus();
    void updateFlagList(QStringList, QStringList);
    void createBackup(QString);

    void saveRunAtStartData(QString);
    void populateRunAtStartData();

    void saveRefreshSummaryData(QString);
    void populateRefreshSummaryData();

    void parseFlags(QString, QString);

    void runOnStartRegEdit();
    void saveRefreshedTime(QString);
    void getRefreshedTime();


private:
    //QProcess getWinLogs;
    QProcess *getSystemLogsProcess;
    QProcess *getApplicationLogsProcess;
    QProcess *getSecurityLogsProcess;
    QProcess *convertSecEvtxToJsonProcess;
    QProcess *convertAppEvtxToJsonProcess;
    QProcess *convertSysEvtxToJsonProcess;
    QProcess *convertEvtxToXmlProcess;
    QProcess *convertEvtxToJsonProcess;
    QProcess *convertEvtxToFullJsonProcess;
    QProcess *convertEvtxToCsvProcess;
    QProcess checkEvtxeCmdPathProcess;
    QProcess moveEvtxeCmdToDocsProcess;
    QProcess *moveAuditLogToReviewedProcesss;
    QProcess *convertEachEvtxFileProcess4;

    QString LogInfoText;
    QString evtxType = "";
    QString jsonStringData;
    QString convertEvtxFileName = "";
    QString convertEvtxFullFilePath = "";
    QString convertEvtxFilePathOnly = "";
    QString convertEvtxFileSize = "";
    QString docsFolder = "";
    QString result = "";
    QString combineAllreports = "";
    QString saveType = "";
    QString _backupType = "";

    //String lists
    QStringList secJsonObjects;
    QStringList appJsonObjects;
    QStringList sysJsonObjects;
    QStringList flagList;
    QStringList listOfLogs;
    QStringList listOfFilesToConvert;
    QStringList flagParseList;
    QStringList logsToCompareToFlags;

    QByteArray tArray_G;
    QJsonDocument json_doc_G;
    QJsonObject jsonObject_G;
    QJsonObject obdata_G;
    QJsonObject obdata2_G;
    QString eventId_G = obdata_G["EventID"].toString();
    //QString computerName = obdata["Computer"].toString();
    QString channel_G = obdata_G["Channel"].toString();
    //QString timeCreated = obdata2["@SystemTime"].toString();

    //TableModel *tableModel;

    int numOfSecEvents = 0;
    int numbOfAppEvents = 0;
    int numbOfSysEvents = 0;
    int processingCount = 0;
    int flagCounter = 0;
};

#endif // MAINCONTROLLER_H
