#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    checkDirectories();
    getSecurityLogs("refresh", "");
}

//Save system logs to evtx file
void MainController::getSystemLogs(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
        qDebug() << "The refresh time being saved is: " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap");
        saveRefreshedTime(QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    }
    getSystemLogsProcess = new QProcess();
    QStringList args;
    args  << "Set-Location -Path " + docsFolder + "/Lumberjack/evtx/system/;" << "Remove-Item " + docsFolder + "/Lumberjack/evtx/system/system.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'system';"
          << "$log.BackupEventlog('" + docsFolder + "/Lumberjack/evtx/system/system.evtx')";
    connect(getSystemLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSysEvtxToJson(); });
    getSystemLogsProcess->start("powershell", args);
}

//Save application logs to evtx file
void MainController::getApplicationLogs(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
    getApplicationLogsProcess = new QProcess();
    QStringList args;
    args  << "Set-Location -Path " + docsFolder + "/Lumberjack/evtx/application/;" << "Remove-Item " + docsFolder + "/Lumberjack/evtx/application/application.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'application';"
          << "$log.BackupEventlog('" + docsFolder + "/Lumberjack/evtx/application/application.evtx')";
    connect(getApplicationLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertAppEvtxToJson();});
    getApplicationLogsProcess->start("powershell", args);
}

//Save secuity logs to evtx file
void MainController::getSecurityLogs(QString sType, QString bType){
    saveType = sType;
    _backupType = bType;
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
    getSecurityLogsProcess = new QProcess();
    QStringList args;
    args  << "Set-Location -Path " + docsFolder + "/Lumberjack/evtx/security/;" << "Remove-Item " + docsFolder + "/Lumberjack/evtx/security/security.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'security';"
          << "$log.BackupEventlog('" + docsFolder + "/Lumberjack/evtx/security/security.evtx')";
    connect(getSecurityLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSecEvtxToJson();});
    getSecurityLogsProcess->start("powershell", args);
}

//Convert security evtx to JSON
void MainController::convertSecEvtxToJson(){
    //qDebug() << "IN CONVERT SEC EVTX TO JSON........";
    getSecurityLogsProcess->terminate();
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
    convertSecEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f "  + docsFolder + "/Lumberjack/evtx/security/security.evtx --fj --json " + docsFolder + "/Lumberjack/json/security/ --jsonf security.json";
    connect(convertSecEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDataFromJson();});
    convertSecEvtxToJsonProcess->start("powershell", args);
}

//Convert application EVTX to JSON
void MainController::convertAppEvtxToJson(){
    //qDebug() << "IN CONVERT App EVTX TO JSON........";
    getApplicationLogsProcess->terminate();
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
    convertAppEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f "  + docsFolder + "/Lumberjack/evtx/application/application.evtx --json " + docsFolder+ "/Lumberjack/json/application/ --fj --jsonf application.json";
    connect(convertAppEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getAppDataFromJson();});
    convertAppEvtxToJsonProcess->start("powershell", args);
}

//Convert system EVTX to JSON
void MainController::convertSysEvtxToJson(){
    getSystemLogsProcess->terminate();
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
    convertSysEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f "  + docsFolder + "/Lumberjack/evtx/system/system.evtx --json " + docsFolder + "/Lumberjack/json/system/ --fj --jsonf system.json";
    connect(convertSysEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSysDataFromJson();});
    convertSysEvtxToJsonProcess->start("powershell", args);
}

//Parse JSON security data and retrieve desired values
void MainController::getSecDataFromJson(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
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
        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
        result += "Event ID: " + eventId + "\n";
    }
    if(saveType == "refresh"){
        emit securityEventCount2Qml(QString::number(numOfSecEvents));
    }
    numOfSecEvents = 0;  
    evtxProcessingDoneRelay(1);
    convertSecEvtxToJsonProcess->terminate();
    secJsonObjects.clear();
    getApplicationLogs();
}

//Parse JSON application data and retrieve desired values
void MainController::getAppDataFromJson(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
    QFile file(docsFolder + "/Lumberjack/json/application/application.json");
    if(!file.open(QIODevice::ReadOnly)) {
        //Error
    }
    QTextStream in(&file);
    while (!in.atEnd()){
        appJsonObjects << in.readLine();
    }
    file.close();
    foreach(const QString &logEntry, appJsonObjects){
        numbOfAppEvents++;
        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
    }
    if(saveType == "refresh"){
        emit appEventCount2Qml(QString::number(numbOfAppEvents));
    }
    numbOfAppEvents = 0;
    evtxProcessingDoneRelay(1);
    convertAppEvtxToJsonProcess->terminate();
    appJsonObjects.clear();
    getSystemLogs();
}

//Parse JSON system data and retrieve desired values
void MainController::getSysDataFromJson(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing data, please wait...");
    }
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
        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
    }
    if(saveType == "refresh"){
        emit sysEventCount2Qml(QString::number(numbOfSysEvents));
    }
    numbOfSysEvents = 0;
    evtxProcessingDoneRelay(1);
    convertSysEvtxToJsonProcess->terminate();
    sysJsonObjects.clear();

    if(saveType == "backup"){
        createArchive("live");
    }
    else if(saveType == "refresh"){
        createArchive("updateFlags");
    }
}

//Get saved flag data to populate the current flag list in QML
void MainController::populateFlagData(){
    QFile file("C:/Lumberjack/flags/flags.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        //qDebug() << "Flag file not open";
    }
    QTextStream in(&file);
    while (!in.atEnd()){
        QString temp = in.readLine().trimmed();
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
    //add item to list in qml
    emit flagsToAdd(flagData);
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
    emit dirPathToQml(dir);
    emit filePathToQml("");
    emit dirPathSepToQml("");
}

//Get path where converted files will be stored
void MainController::ce_SaveToPath(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit saveToPathToQml(dir);
}

//Convert a single EVTX file to a single JSON, CSV, or XML file
void MainController::fileConvertEvtx(QString convertType, QString fPah, QString savePath, QString iFileName ){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToFullJsonProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess->start("powershell", args);
    }
    else if(convertType == " Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToFullJsonProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(convertEvtxToFullJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToFullJsonProcess->start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToXmlProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + iFileName.trimmed() + ".xml";
        connect(convertEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToXmlProcess->start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToCsvProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + iFileName.trimmed() + ".csv";
        connect(convertEvtxToCsvProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToCsvProcess->start("powershell", args);
    }
    else{
        //error
    }
}

//Convert a directory of evtx files to a single json, xml, or csv. Note: Without using pointer for dynamic memory allocation, duplicate messages of conversion complete were being transmitted
void MainController::dirConvertEvtx(QString convertType, QString fPah, QString savePath){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        qDebug() << "SAVE PATH IS: " + savePath;
        convertEvtxToJsonProcess = new QProcess();
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --json " +  savePath.trimmed();
        connect(convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess->start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToFullJsonProcess = new QProcess();
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf ";
        connect(convertEvtxToFullJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToFullJsonProcess->start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToXmlProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --xml " + savePath.trimmed();
        connect(convertEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToXmlProcess->start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToCsvProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --csv " +  savePath.trimmed();
        connect(convertEvtxToCsvProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToCsvProcess->start("powershell", args);
    }
    else{
        //error
    }
}

//Convert a directory of Evtx files to individual JSON, XML, or CSV files
void MainController::dirConvertEachEvtx(QString convertType, QString savePath){
    emit fileConvertEvtxStatus("EVTX file conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileConvertEvtxStatus("Please Wait....");

    foreach(const QString &evtxFile, listOfFilesToConvert){
        QFileInfo fileInfo(evtxFile);
        QString curFileName = fileInfo.fileName().trimmed();
        curFileName.replace(".evtx","");

        if(convertType == "JSON"){
            QProcess *convertEachEvtxFileProcess = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess->start("powershell", args);
        }
        else if(convertType == "Full JSON"){
            QProcess *convertEachEvtxFileProcess2 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess2, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess2->start("powershell", args);
        }
        else if(convertType == "XML"){
            QProcess *convertEachEvtxFileProcess3 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + curFileName + ".xml";
            connect(convertEachEvtxFileProcess3, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess3->start("powershell", args);
        }
        else if(convertType == "CSV"){
            convertEachEvtxFileProcess4 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + curFileName + ".csv";
            connect(convertEachEvtxFileProcess4, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
            convertEachEvtxFileProcess4->start("powershell", args);
        }
        else{
            //error
        }
    }
}

//Select a directory and store the path of each file to be converted to individual JSON, XML, or CSV files
void MainController::selectDirConvertEachEvtx(){
    listOfFilesToConvert.clear();
    QString path = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"), "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit dirPathSepToQml(path);
    emit dirPathToQml("");
    emit filePathToQml("");
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        listOfFilesToConvert << fileInfo.absoluteFilePath();
    }
}

//send completion message after EVTX converter completion
void MainController::updateEvtxConvertStatus(){
    emit fileConvertEvtxStatus("Conversion completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit fileNameToQml("");
    emit filePathToQml("");
    emit dirPathToQml("");
    emit dirPathSepToQml("");
    emit saveToPathToQml("");
}

//Check to see if directories exist. Create directories if needed.
void MainController::checkDirectories(){
    //Get the Documents path and create the main Lumberjack directory
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

    //Main Dir
    QDir lumberjackDir(docsFolder + "/Lumberjack");

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

    //Check if directories exist. If not, create them
    if(!lumberjackDir.exists()){
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

    //Check if the EvtxeCmd folder exists in the Documents\EvtxConverter folder
    QStringList args;
    args << "Test-Path -Path " + docsFolder + "/Lumberjack/EvtxeCmd;";
    checkEvtxeCmdPathProcess.connect(&checkEvtxeCmdPathProcess, &QProcess::readyReadStandardOutput, this, &MainController::evtxCmdFolderExistsResponse);
    checkEvtxeCmdPathProcess.start("powershell", args);
}

//Send message to QML when EVTX files have been saved, converted, and parsed
void MainController::evtxProcessingDoneRelay(int n){
    processingCount += n;
    if(processingCount == 3){
        emit processingStatus2Qml("Summary " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        processingCount = 0;
    }
}

//Save the time for the backup to run
void MainController::saveSchedulerTimeData(QString t_Hour, QString t_Minute, QString t_Ampm){
    QString hourFilename = "C:/Lumberjack/settings/timetorun/schedulerHour.txt";
    QString minuteFilename = "C:/Lumberjack/settings/timetorun/schedulerMinute.txt";
    QString ampmFilename = "C:/Lumberjack/settings/timetorun/schedulerAmpm.txt";

    QFile h_File(hourFilename);
    if (h_File.open(QIODevice::ReadWrite)) {
        QTextStream stream(&h_File);
        stream << t_Hour;
        h_File.close();
    }
    QFile m_File(minuteFilename);
    if (m_File.open(QIODevice::ReadWrite)) {
        QTextStream stream(&m_File);
        stream << t_Minute;
        m_File.close();
    }
    QFile ampm_File(ampmFilename);
    if (ampm_File.open(QIODevice::ReadWrite)) {
        QTextStream stream(&ampm_File);
        stream << t_Ampm;
        emit saveScheduleDataSaveStatus("Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    }
    ampm_File.close();
}

//Get the saved time date from files and send it to QML to diplay in the GUI
void MainController::populateSchedulerTimeData(){
    QFile h_File("C:/Lumberjack/settings/timetorun/schedulerHour.txt");
    QFile s_File("C:/Lumberjack/settings/timetorun/schedulerMinute.txt");
    QFile a_File("C:/Lumberjack/settings/timetorun/schedulerAmpm.txt");

    if(h_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&h_File);
        while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedHourTxtToQml(temp);
        }
        h_File.close();
    }

    if(s_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&s_File);
        while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            int tempNumFix = temp.toInt() + 1;
            QString newTempString = QString::number(tempNumFix);
            emit savedMinTxtToQml(newTempString);
        }
        s_File.close();
    }

    if(a_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&a_File);
        while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedAmpmTxtToQml(temp);
        }
    }
    a_File.close();
}

//Save the selected backup days
void MainController::saveSchedulerDayData(QStringList daysOfTheWeekList){
    QFile::remove("C:/Lumberjack/settings/daystorun/daystorun.txt");
    QFile dtr_File("C:/Lumberjack/settings/daystorun/daystorun.txt");
    foreach (const QString &dayOfTheWeek, daysOfTheWeekList) {
        if (dtr_File.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&dtr_File);
            stream << dayOfTheWeek + "\n";
        }
    }
    dtr_File.close();
    emit saveScheduleDataSaveStatus("Shedule Days Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

//Get the saved data from file and send to the QML GUI to be displayed
void MainController::populateShedulerDaysData(){
    QFile dtr_File("C:/Lumberjack/settings/daystorun/daystorun.txt");
    if(dtr_File.open(QIODevice::ReadOnly)) {
        QTextStream in(&dtr_File);
        while (!in.atEnd()){
            QString temp = in.readLine().trimmed();
            emit savedDaysDataToQml(temp);
        }
    }
    dtr_File.close();
}

//Save clear log data after backup choice to file
void MainController::saveSchdlerClrLogData(QString switchState){
     QFile clearLogsChoice_File("C:/Lumberjack/settings/clearlogs/clearlogs.txt");
     if (clearLogsChoice_File.open(QIODevice::WriteOnly)) {
        QTextStream stream(&clearLogsChoice_File);
        stream << switchState;
     }
     clearLogsChoice_File.close();
     emit saveScheduleDataSaveStatus("Clear logs choice Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

//Get the saved "clear log after backup" choice data from file and send to QML
void MainController::popSchdlerClrLogData(){
        QFile dtr_File("C:/Lumberjack/settings/clearlogs/clearlogs.txt");
        if(dtr_File.open(QIODevice::ReadOnly)) {
            QTextStream in(&dtr_File);
            while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedClearLogDataToQML(temp);
            }
        }
        dtr_File.close();
}

//Save autobackup choice to file
void MainController::saveSchdlerBkupData(QString bUpChoice){
    QFile backupChoice_File("C:/Lumberjack/settings/autobackup/autobackup.txt");
    if (backupChoice_File.open(QIODevice::WriteOnly)) {
            QTextStream stream(&backupChoice_File);
            stream << bUpChoice;
    }
    backupChoice_File.close();
    emit saveScheduleDataSaveStatus("Auto backup choice Save completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

//Get the saved autobackup choice data from file and send to QML
void MainController::popSchdlerBkupData(){
    QFile dtr_File("C:/Lumberjack/settings/autobackup/autobackup.txt");
    if(dtr_File.open(QIODevice::ReadOnly)) {
            QTextStream in(&dtr_File);
            while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit savedAutoBackupDataToQML(temp);

            }
    }
    dtr_File.close();
}

//Get the list of archived logs and send to QML
void MainController::getArchivedLogsList(){
    QString path ="C:/Lumberjack/audit/archived_reports/";
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Size | QDir::Reversed);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
            QFileInfo fileInfo = list.at(i);
            emit archivedLogEntryToQml(fileInfo.fileName());
    }
}

//Copy EvtxeCmd files to docs folder if not already there
void MainController::evtxCmdFolderExistsResponse(){
    QByteArray ba  = checkEvtxeCmdPathProcess.readAllStandardOutput().trimmed();
    QString response = QString(ba);
    if(response == "True"){
            return;
    }
    else if(response == "False"){
            qDebug() << "The folder does not exist. It needs to be copied and moved with powershell......";
            QString targetDir = "C:/Lumberjack/EvtxeCmd/";
            QStringList args;
            args << "Copy-Item -Path "  + targetDir +  " -Destination " + docsFolder + "/Lumberjack/EvtxeCmd/ -Recurse";
            moveEvtxeCmdToDocsProcess.start("powershell", args);
    }
    else{
            qDebug() << "The evtxecmd folder exist response was neither true nor false......";
    }
}

//Create an archive file containing the the date and time in the file name. Combine system, security, application, json files into one file.
void MainController::createArchive(QString backupType){
    qDebug() << "In Create Archive...........";
    QString currentDateTime = QDateTime::currentDateTime().toString("MM-dd-yyyy_h-mm-ss-ap");
    QFile secJsonFile(docsFolder + "/Lumberjack/json/security/security.json");
    QFile sysJsonFile(docsFolder + "/Lumberjack/json/system/system.json");
    QFile appJsonFile(docsFolder + "/Lumberjack/json/application/application.json");
    QFile archiveFile("C:/Lumberjack/audit/archived_reports/audit_" + currentDateTime + ".json");

    if(secJsonFile.open(QIODevice::ReadOnly)) {
            qDebug() << "In Sec JSON file...........";
            QTextStream in(&secJsonFile);
            while (!in.atEnd()){
            combineAllreports = in.readAll().trimmed() + "\n";
            //qDebug() << "Combined reports is: " + combineAllreports;
            }
            secJsonFile.close();

            if(sysJsonFile.open(QIODevice::ReadOnly)) {
            qDebug() << "In Sys JSON file...........";
            QTextStream in(&sysJsonFile);
            while (!in.atEnd()){
                combineAllreports += in.readAll().trimmed() + "\n";
            }
            sysJsonFile.close();
            }
            if(appJsonFile.open(QIODevice::ReadOnly)) {
            qDebug() << "In App JSON file...........";
            QTextStream in(&appJsonFile);
            while (!in.atEnd()){
                combineAllreports += in.readAll().trimmed();
            }
            appJsonFile.close();
            }
    }
    if(archiveFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
            qDebug() << "In write archive file...........";
            QTextStream out(&archiveFile);
            out << combineAllreports;
            archiveFile.close();
            parseFlags(currentDateTime, backupType);
    }
    else{
            //error
    }
}

//BUG:Spaces in file names causes file to not be moved
//Move the selected audid log to the reviewed foler
void MainController::moveAuditLogToReviewedFolder(QString fileName){
    moveAuditLogToReviewedProcesss = new QProcess();
    QString fileToMove = "C:/Lumberjack/audit/archived_reports/" + fileName;
    QStringList args;
    args << "Move-Item -Path "  + fileToMove +  " -Destination C:/Lumberjack/audit/archived_reports/reviewed/" + fileName;
    connect(moveAuditLogToReviewedProcesss,(void(QProcess::*)(int))&QProcess::finished, [=]{updateMovedLogsStatus();});
    moveAuditLogToReviewedProcesss->start("powershell", args);
}

//Send completion message to QML when after file move operation and kill the process
void MainController::updateMovedLogsStatus(){
    emit fileMoveStatusToQml("Audit log has been moved to the reviewed folder....");
    moveAuditLogToReviewedProcesss->kill();
    //Remove the item from the list in qml
}

//Overwrite the currentn flag list with the new list
void MainController::updateFlagList(QStringList newFlagList, QStringList removeFlagsList){
    QFile::remove("C:/Lumberjack/flags/flags.txt");
    QFile flagFile("C:/Lumberjack/flags/flags.txt");
    foreach (const QString &flagData, newFlagList) {
            if (flagFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream stream(&flagFile);
            stream << flagData + "\n";
            flagFile.close();
            }
    }
    foreach (const QString &removeFlagData, removeFlagsList) {
            emit flagsToRemove(removeFlagData);
    }
}

void MainController::updateCurrentLogSummary(){
    getSecurityLogs("refresh", "");
}

void MainController::createBackup(QString backupType){
    getSecurityLogs("backup", backupType);
}

//Save run at start data to file
void MainController::saveRunAtStartData(QString rasChoice){
    QFile runAtStartFile("C:/Lumberjack/settings/runonstart/runonstart.txt");
    if (runAtStartFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&runAtStartFile);
            stream << rasChoice;
    }
    runAtStartFile.close();
}

//Populate run at start choices in QML
void MainController::populateRunAtStartData(){
    qDebug() << "In populate run at start data";
    QFile runAtStartFile("C:/Lumberjack/settings/runonstart/runonstart.txt");
    if(runAtStartFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&runAtStartFile);
            while (!in.atEnd()){
            QString temp = in.readAll().trimmed();
            emit runOnStartSavedData(temp);
            }
    }
    runAtStartFile.close();
}

//Save the refresh summary data to file
void MainController::saveRefreshSummaryData(QString rsChoice){
    QFile refreshSummaryFile("C:/Lumberjack/settings/refreshsummary/refreshsummary.txt");
    if (refreshSummaryFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&refreshSummaryFile);
            stream << rsChoice;
    }
    refreshSummaryFile.close();
    QString currentDateTime = QDateTime::currentDateTime().toString("MM-dd-yyyy_h-mm-ss-ap");
    emit settingsWinStatMesg("Refresh data saved @ " + currentDateTime);
}

//Populate the refresh summary data in QML
void MainController::populateRefreshSummaryData(){
    qDebug() << "In populate resfresh data";
    QFile refreshSummaryFile("C:/Lumberjack/settings/refreshsummary/refreshsummary.txt"); 
    if(refreshSummaryFile.open(QIODevice::ReadOnly)) {
            qDebug() << "In populate resfresh data file open";
            QTextStream in(&refreshSummaryFile);
            while (!in.atEnd()){

            QString temp = in.readAll().trimmed();
            qDebug() << "The save refrsh data is: " + temp;
            qDebug() << "Emitting populate resfresh data";
            emit savedRefreshDataToQml(temp);
            }
    }
    else{
            qDebug() << "The file is not open";
    }
    refreshSummaryFile.close();
}

//Compare flags to event IDs in the archive log file. Add matches to the end of the file.
void MainController::parseFlags(QString fileName, QString bType){
    qDebug() << "In parse flags";
    QFile currentFlagsFile("C:/Lumberjack/flags/flags.txt");
    QFile archiveFile("C:/Lumberjack/audit/archived_reports/audit_" + fileName + ".json");

    //Get the list of flags
    if (currentFlagsFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&currentFlagsFile);
            while(!in.atEnd()){
                flagParseList << in.readLine().trimmed();
            }
            currentFlagsFile.close();
    }
    else{
            qDebug() << "Flag file not open...";
    }

    //Get JSON archive logs
    if (archiveFile.open(QIODevice::ReadOnly)) {
            qDebug() << "Getting logs to compare.....";
            QTextStream in(&archiveFile);
            while (!in.atEnd()){
                logsToCompareToFlags << in.readLine().trimmed();
            }
            archiveFile.close();
    }else{
            qDebug() << "Archive file not open...";
    }

    //compare the flags to event IDs from the archive logs
    foreach (const QString &logEntry, logsToCompareToFlags) {
            QByteArray tArray_G = logEntry.trimmed().toLocal8Bit();
            QJsonDocument json_doc_G = QJsonDocument::fromJson(tArray_G);
            QJsonObject jsonObject_G = json_doc_G.object();
            QJsonObject obdata_G = jsonObject_G.value("Event").toObject().value("System").toObject();
            QString eventId_G = obdata_G["EventID"].toString().trimmed();
            foreach (const QString &flag, flagParseList) {
                if(flag == eventId_G){
                if(bType == "updateFlags"){
                    //qDebug() << "Save type is: " + saveType;
                    flagCounter++;
                    emit flagCount(QString::number(flagCounter));

                }else{

                    if (archiveFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                        QTextStream out(&archiveFile);
                        out << logEntry + "\n";
                    }
                }
                archiveFile.close();
                }
            }
    }

    if(bType != "updateFlags"){
            qDebug() << "Emitting addLogFileToComboBox";
            emit addLogFileToComboBox("audit_" + fileName + ".json");
    }

    if(bType == "live"){
            emit liveBkupStatsDoneToQml("Live backup completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    }
    flagCounter = 0;
}

//Add program to startup
void MainController::runOnStartRegEdit(){
    qDebug() << "In regedit";
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    settings.setValue("Lumberjack.exe", QCoreApplication::applicationFilePath().replace('/', '\\'));
    settings.sync();
    qDebug() << settings.status();

    //or settings.remove("name");
}

void MainController::saveRefreshedTime(QString curTime){
    QFile lastRefreshTimeFile("C:/Lumberjack/settings/refreshsummary/lastrefreshtime.txt");
    if (lastRefreshTimeFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&lastRefreshTimeFile);
            stream << curTime;
    }
    lastRefreshTimeFile.close();
    //QString currentDateTime = QDateTime::currentDateTime().toString("MM-dd-yyyy_h-mm-ss-ap");
    //emit settingsWinStatMesg("Refresh data saved @ " + currentDateTime);

}

void MainController::getRefreshedTime(){

}

