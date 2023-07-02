#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){

    checkDirectories();
}

//Save system logs to evtx file
void MainController::getSystemLogs(){
    emit processingStatus2Qml("Processing data, please wait...");
    getSystemLogsProcess = new QProcess();
    QStringList args;

    args  << "Set-Location -Path " + docsFolder + "/Lumberjack/evtx/system/;" << "Remove-Item " + docsFolder + "/Lumberjack/evtx/system/system.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'system';"
          << "$log.BackupEventlog('" + docsFolder + "/Lumberjack/evtx/system/system.evtx')";
    connect(getSystemLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSysEvtxToJson(); });
    getSystemLogsProcess->start("powershell", args);
}

//Save application logs to evtx file
void MainController::getApplicationLogs(){
    emit processingStatus2Qml("Processing data, please wait...");
    getApplicationLogsProcess = new QProcess();
    QStringList args;

    args  << "Set-Location -Path " + docsFolder + "/Lumberjack/evtx/application/;" << "Remove-Item " + docsFolder + "/Lumberjack/evtx/application/application.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'application';"
          << "$log.BackupEventlog('" + docsFolder + "/Lumberjack/evtx/application/application.evtx')";
    connect(getApplicationLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertAppEvtxToJson();});
    getApplicationLogsProcess->start("powershell", args);
}

//Save secuity logs to evtx file
void MainController::getSecurityLogs(){
    emit processingStatus2Qml("Processing data, please wait...");
    getSecurityLogsProcess = new QProcess();
    QStringList args;

    args  << "Set-Location -Path " + docsFolder + "/Lumberjack/evtx/security/;" << "Remove-Item " + docsFolder + "/Lumberjack/evtx/security/security.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'security';"
          << "$log.BackupEventlog('" + docsFolder + "/Lumberjack/evtx/security/security.evtx')";
    connect(getSecurityLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSecEvtxToJson();});
    getSecurityLogsProcess->start("powershell", args);
}
/*
//Convert security evtx to XML
void MainController::convertSecEvtxToXml(){
    //qDebug() << "IN CONVERT SEC EVTX TO XML........";

    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f " + docsFolder + "/Lumberjack/evtx/security/security.evtx --xml " + docsFolder + "/Lumberjack/xml/security/ --xmlf security.xml";

    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    //connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertSecEvtxToXmlProcess.start("powershell", args);
}
*/

//https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-6.0.16-windows-x64-installer?cid=getdotnetcore
//App wouldn't run because it was missing the above microsoft requirement
//Convert security evtx to JSON
void MainController::convertSecEvtxToJson(){
    //qDebug() << "IN CONVERT SEC EVTX TO JSON........";
    getSecurityLogsProcess->terminate();
    emit processingStatus2Qml("Processing data, please wait...");
    convertSecEvtxToJsonProcess = new QProcess();

    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f "  + docsFolder + "/Lumberjack/evtx/security/security.evtx --fj --json " + docsFolder + "/Lumberjack/json/security/ --jsonf security.json";

    //convertSecEvtxToJsonProcess->connect(convertSecEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    //convertSecEvtxToJsonProcess->connect(convertSecEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    connect(convertSecEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDataFromJson();});
    convertSecEvtxToJsonProcess->start("powershell", args);
}

void MainController::convertAppEvtxToXml(){

}

void MainController::convertAppEvtxToJson(){
    //qDebug() << "IN CONVERT App EVTX TO JSON........";
    getApplicationLogsProcess->terminate();
    emit processingStatus2Qml("Processing data, please wait...");
    convertAppEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f "  + docsFolder + "/Lumberjack/evtx/application/application.evtx --json " + docsFolder+ "/Lumberjack/json/application/ --fj --jsonf application.json";

    //convertAppEvtxToJsonProcess->connect(convertAppEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutAppLogInfo);
    //convertAppEvtxToJsonProcess->connect(convertAppEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorAppLogInfo);
    connect(convertAppEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getAppDataFromJson();});
    convertAppEvtxToJsonProcess->start("powershell", args);
}

void MainController::convertSysEvtxToXml(){

}

void MainController::convertSysEvtxToJson(){
    getSystemLogsProcess->terminate();
    emit processingStatus2Qml("Processing data, please wait...");
    convertSysEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f "  + docsFolder + "/Lumberjack/evtx/system/system.evtx --json " + docsFolder + "/Lumberjack/json/system/ --fj --jsonf system.json";
    connect(convertSysEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSysDataFromJson();});
    convertSysEvtxToJsonProcess->start("powershell", args);
}

void MainController::getSecDatafromXml(){

}

//Parse JSON data and retrieve desired values
void MainController::getSecDataFromJson(){
    emit processingStatus2Qml("Processing data, please wait...");
    QFile file(docsFolder + "/Lumberjack/json/security/security.json");
    if(!file.open(QIODevice::ReadOnly)){
    //qDebug() << "Sec file not open.......";
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        secJsonObjects << in.readLine();
    }
    file.close();

    foreach(const QString &logEntry, secJsonObjects){
        numOfSecEvents++;
        QString numToString = QString::number(numOfSecEvents);
        //qDebug() << "The counter is: " + numToString;

        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
        result += "Event ID: " + eventId + "\n";
       // QJsonObject obdata = jsonObject.value("PayloadData4").toObject();
        //QString eventId = obdata["EventID"].toString();
        //qDebug()<< "Event ID is: " + eventId;
        //emit dataToLogViewer("Event ID: " + eventId);
        //QThread::msleep(500);
    }

    emit securityEventCount2Qml(QString::number(numOfSecEvents));
    numOfSecEvents = 0;  
    //emit dataToLogViewer(result);
    evtxProcessingDoneRelay(1);
    //emit processingStatus2Qml("Summary " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    convertSecEvtxToJsonProcess->terminate();
    secJsonObjects.clear();

    getApplicationLogs();
}

void MainController::getAppDataFromJson(){
    //qDebug() << "In get App data from JSON file.......";

    emit processingStatus2Qml("Processing data, please wait...");
    QFile file(docsFolder + "/Lumberjack/json/application/application.json");
    if(!file.open(QIODevice::ReadOnly)) {
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        //QString line = in.readLine();
        //qDebug() << "Data is: " + line;
        appJsonObjects << in.readLine();
    }
    file.close();

    foreach(const QString &logEntry, appJsonObjects){
        numbOfAppEvents++;

        //qDebug() << "The counter is: " + QString::number(numbOfAppEvents);

        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
    }

    //qDebug() << "Trying to emit";
    emit appEventCount2Qml(QString::number(numbOfAppEvents));
    numbOfAppEvents = 0;
    evtxProcessingDoneRelay(1);
    //emit processingStatus2Qml("Summary " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    convertAppEvtxToJsonProcess->terminate();
    appJsonObjects.clear();
    getSystemLogs();
}

void MainController::getSysDataFromJson(){

    //qDebug() << "In get Sys data from JSON file.......";
    emit processingStatus2Qml("Processing data, please wait...");
    QFile file(docsFolder + "/Lumberjack/json/system/system.json");
    if(!file.open(QIODevice::ReadOnly)){
        //error
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        sysJsonObjects << in.readLine();
    }
    file.close();

    foreach(const QString &logEntry, sysJsonObjects){
        numbOfSysEvents++;

        //qDebug() << "The counter is: " + QString::number(numbOfSysEvents);

        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
    }

    //qDebug() << "Trying to emit";
    emit sysEventCount2Qml(QString::number(numbOfSysEvents));
    numbOfSysEvents = 0;
    evtxProcessingDoneRelay(1);
    convertSysEvtxToJsonProcess->terminate();
    sysJsonObjects.clear();
}

//Get saved flag data to populate the current flag list in QML
void MainController::populateFlagData(){
    QFile file("C:/Lumberjack/flags/flags.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        //qDebug() << "Flag file not open";
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        QString temp = in.readLine();
        emit populateFlagDataToQml(temp);
    }
    file.close();
}

//Save flag data to file
void MainController::saveFlagData(QString flagData){
    QFile file("C:/Lumberjack/flags/flags.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream out(&file);
        out << flagData + "\n";
    }
    else{
        //error
    }
    file.close();
}

//Get file path for evtx file
void MainController::ce_SelectFile(){
    convertEvtxFileName = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select File"), "");
    QFileInfo fileInfo(convertEvtxFileName);
    convertEvtxFullFilePath = fileInfo.filePath().trimmed();

    emit filePathToQml(convertEvtxFullFilePath);
    emit dirPathToQml("");
}

//Get directory path for evtx files
void MainController::ce_SelectDir(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << "The Dir is: " + dir;
    emit dirPathToQml(dir);
    emit filePathToQml("");
}

//Get path where converted files will be stored
void MainController::ce_SaveToPath(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    //qDebug() << "The Save to path is: " + dir;
    emit saveToPathToQml(dir);
}

//Convert a single EVTX file to a single JSON, CSV, or XML file
void MainController::fileConvertEvtx(QString convertType, QString fPah, QString savePath, QString iFileName ){
    if(convertType == "JSON"){
        //qDebug() << "IN CONVERT EVTX TO JSON........";
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == " Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + iFileName.trimmed() + ".xml";
        connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertSecEvtxToXmlProcess.start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + iFileName.trimmed() + ".csv";
        connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertSecEvtxToXmlProcess.start("powershell", args);
    }
    else{
        //error
    }
}

void MainController::updateEvtxConvertStatus(){
    emit fileConvertEvtxStatus("Conversion completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileNameToQml("");
    emit filePathToQml("");
    emit dirPathToQml("");
    emit saveToPathToQml("");
}

void MainController::checkDirectories(){
    //Get the Documents path and create the main Lumberjack directory
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QDir docsDir(docsFolder + "/Lumberjack");
    qDebug() << "The docs folder path is: " << docsDir;
    qDebug() << "The docs folder pis: " << docsFolder;

    //EVTX directories
    QDir evtxDir(docsFolder + "/Lumberjack/evtx");
    QDir evtxSysDir(docsFolder + "/Lumberjack/evtx/system");
    QDir evtxAppDir(docsFolder + "/Lumberjack/evtx/application");
    QDir evtxSecDir(docsFolder + "/Lumberjack/evtx/security");

    //JSON directories
    QDir jsonDir(docsFolder + "/Lumberjack/json");
    QDir jsonSysDir(docsFolder + "/Lumberjack/json/system");
    QDir jsonAppDir(docsFolder + "/Lumberjack/json/application");
    QDir jsonSecDir(docsFolder + "/Lumberjack/json/security");

    //XML directories
    /*
    QDir xmlDir(docsFolder + "/Lumberjack/xml");
    QDir xmlSysDir(docsFolder + "/Lumberjack/xml/system");
    QDir xmlAppDir(docsFolder + "/Lumberjack/xml/application");
    QDir xmlSecDir(docsFolder + "/Lumberjack/xml/security");

    //CSV directories
    QDir csvDir(docsFolder + "/Lumberjack/csv");
    QDir csvSysDir(docsFolder + "/Lumberjack/csv/system");
    QDir csvAppDir(docsFolder + "/Lumberjack/csv/application");
    QDir csvSecDir(docsFolder + "/Lumberjack/csv/security");
    QDir settingsDir(docsFolder + "/Lumberjack/settings");
    */

    //Check if directories exist. If not, create them
    if(!docsDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack");
    }
    if(!evtxDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/evtx");
    }
    if(!evtxSysDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/evtx/system");
    }
    if(!evtxAppDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/evtx/application");
    }
    if(!evtxSecDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/evtx/security");
    }
    if(!jsonDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/json");
    }
    if(!jsonSysDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/json/system");
    }
    if(!jsonAppDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/json/application");
    }
    if(!jsonSecDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/json/security");
    }
    /*
    if(!xmlDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/xml");
    }
    if(!xmlSysDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/xml/system");
    }
    if(!xmlAppDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/xml/application");
    }
    if(!xmlSecDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/xml/security");
    }
    if(!csvDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/csv");
    }
    if(!csvSysDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/csv/system");
    }
    if(!csvAppDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/csv/application");
    }
    if(!csvSecDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/csv/security");
    }

    if(!settingsDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack/settings");
    }
    */
    getSecurityLogs();
    //getApplicationLogs();
    //getSystemLogs();
}

//Send message to QML when EVTX files have been saved, converted, and parsed
void MainController::evtxProcessingDoneRelay(int n){
    processingCount += n;
    if(processingCount == 3){
        emit processingStatus2Qml("Summary " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        processingCount = 0;
    }
}

void MainController::updateCurrentLogSummary(){
    getSecurityLogs();

}

//Save the time for the backup to run
void MainController::saveSchedulerTimeData(QString t_Hour, QString t_Minute, QString t_Ampm){
    qDebug() << "In save scheduler data. The hour is" << t_Hour;
    QString hourFilename = "C:/Lumberjack/settings/timetorun/schedulerHour.txt";
    QString minuteFilename = "C:/Lumberjack/settings/timetorun/schedulerMinute.txt";
    QString ampmFilename = "C:/Lumberjack/settings/timetorun/schedulerAmpm.txt";

    QFile h_File(hourFilename);
    if (h_File.open(QIODevice::ReadWrite)) {
        QTextStream stream(&h_File);
        stream << t_Hour;
        h_File.close();
        //emit saveScheduleDataSaveStatus("Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    }
    QFile m_File(minuteFilename);
    if (m_File.open(QIODevice::ReadWrite)) {
        QTextStream stream(&m_File);
        stream << t_Minute;
        m_File.close();
        //emit saveScheduleDataSaveStatus("Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    }
    QFile ampm_File(ampmFilename);
    if (ampm_File.open(QIODevice::ReadWrite)) {
        QTextStream stream(&ampm_File);
        stream << t_Ampm;
        ampm_File.close();
        emit saveScheduleDataSaveStatus("Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    }
}

//Get the saved time date from files and send it to QML to diplay in the GUI
void MainController::populateSchedulerTimeData(){
    qDebug() << "In populate scheduler Time data";

    QFile h_File("C:/Lumberjack/settings/timetorun/schedulerHour.txt");
    QFile s_File("C:/Lumberjack/settings/timetorun/schedulerMinute.txt");
    QFile a_File("C:/Lumberjack/settings/timetorun/schedulerAmpm.txt");

    if(h_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&h_File);
        while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedHourTxtToQml(temp);
            h_File.close();
        }
    }

    if(s_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&s_File);
        while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            int tempNumFix = temp.toInt() + 1;
            QString newTempString = QString::number(tempNumFix);
            emit savedMinTxtToQml(newTempString);
            s_File.close();
        }
    }

    if(a_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&a_File);
        while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedAmpmTxtToQml(temp);
            a_File.close();
        }
    }
}

//Save the selected backup days
void MainController::saveSchedulerDayData(QStringList daysOfTheWeekList){
    qDebug() << "In saveSchedulerDayData......";
    QFile::remove("C:/Lumberjack/settings/daystorun/daystorun.txt");
    QFile dtr_File("C:/Lumberjack/settings/daystorun/daystorun.txt");

    foreach (const QString &dayOfTheWeek, daysOfTheWeekList) {
        if (dtr_File.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&dtr_File);
            stream << dayOfTheWeek + "\n";
            dtr_File.close();
        }
    }
    emit saveScheduleDataSaveStatus("Shedule Days Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

//Get the saved data from file and send to the QML GUI to be displayed
void MainController::populateShedulerDaysData(){
    qDebug() << "IN POPULATE DAYS DATA......";
    QFile dtr_File("C:/Lumberjack/settings/daystorun/daystorun.txt");
    if(dtr_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&dtr_File);
        while (!in.atEnd()){
            QString temp = in.readLine().trimmed();
            emit savedDaysDataToQml(temp);
            dtr_File.close();
        }
    }
}

void MainController::saveSchdlerClrLogData(QString switchState){
    qDebug() << "In saveSchdlerClrLogData......";
    //QFile::remove("C:/Lumberjack/settings/daystorun/daystorun.txt");
    QFile clearLogsChoice_File("C:/Lumberjack/settings/clearlogs/clearlogs.txt");


        if (clearLogsChoice_File.open(QIODevice::WriteOnly)) {
            QTextStream stream(&clearLogsChoice_File);
            stream << switchState;
            clearLogsChoice_File.close();
        }

    emit saveScheduleDataSaveStatus("Clear logs choice Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));

}

void MainController::popSchdlerClrLogData(){
    qDebug() << "In POLULATE CLEAR LOGS SAVED DATA......";
    QFile dtr_File("C:/Lumberjack/settings/clearlogs/clearlogs.txt");
    if(dtr_File.open(QIODevice::ReadOnly)) {
            QTextStream in(&dtr_File);
            while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedClearLogDataToQML(temp);
            dtr_File.close();
            }
    }
}

void MainController::saveSchdlerBkupData(QString bUpChoice){
    qDebug() << "In saveSchdlerClrLogData......";
    //QFile::remove("C:/Lumberjack/settings/daystorun/daystorun.txt");
    QFile backupChoice_File("C:/Lumberjack/settings/autobackup/autobackup.txt");

    if (backupChoice_File.open(QIODevice::WriteOnly)) {
            QTextStream stream(&backupChoice_File);
            stream << bUpChoice;
            backupChoice_File.close();
    }

    emit saveScheduleDataSaveStatus("Auto backup choice Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));

}

void MainController::popSchdlerBkupData(){
    qDebug() << "In POLULATE BACKUP SAVED DATA......";
    QFile dtr_File("C:/Lumberjack/settings/autobackup/autobackup.txt");
    if(dtr_File.open(QIODevice::ReadOnly)) {
            QTextStream in(&dtr_File);
            while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedAutoBackupDataToQML(temp);
            dtr_File.close();
            }
    }
}

void MainController::getArchivedLogsList(){
    qDebug() << "In get archived logs......";
    //listOfLogs.clear();
    QString path ="C:/Lumberjack/audit/archived_reports/";
    //emit dirPathSepToQml(path);
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);

            emit archivedLogEntryToQml(fileInfo.fileName());
    }
}
