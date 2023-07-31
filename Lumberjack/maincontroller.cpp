#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    checkDirectories();
    getSecurityLogs("refresh", "updateFlags");
    refreshInProgress = true;
}

//Save system logs to evtx file
void MainController::getSystemLogs(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Retrieving system log data, please wait...");
        saveRefreshedTime(QDateTime::currentDateTime().toString("h:mm:ss ap"));
        saveRefreshedTimeWd(QDateTime::currentDateTime().toString("h:mm:ss ap dd.MM.yyyy"));
    }
    getSystemLogsProcess = new QProcess();
    QStringList args;
    args  << "Set-Location -Path C:/Lumberjack/evtx/system/;" << "Remove-Item C:/Lumberjack/evtx/system/system.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'system';"
          << "$log.BackupEventlog('""C:/Lumberjack/evtx/system/system.evtx')";
    connect(getSystemLogsProcess, &QProcess::finished, this, &MainController::convertSysEvtxToJson);
    getSystemLogsProcess->start("powershell", args);
}

//Save application logs to evtx file
void MainController::getApplicationLogs(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Retrieving application log data, please wait...");
    }
    getApplicationLogsProcess = new QProcess();
    QStringList args;
    args  << "Set-Location -Path C:/Lumberjack/evtx/application/;" << "Remove-Item C:/Lumberjack/evtx/application/application.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'application';"
          << "$log.BackupEventlog('""C:/Lumberjack/evtx/application/application.evtx')";
    connect(getApplicationLogsProcess, &QProcess::finished, this, &MainController::convertAppEvtxToJson);
    getApplicationLogsProcess->start("powershell", args);
}

//Save secuity logs to evtx file
void MainController::getSecurityLogs(QString sType, QString bType){
    saveType = sType;
    _backupType = bType;
    if(saveType == "refresh"){
        emit processingStatus2Qml("Retrieving security log data, please wait...");
    }
    getSecurityLogsProcess = new QProcess();
    QStringList args;
    args  << "Set-Location -Path C:/Lumberjack/evtx/security/;" << "Remove-Item C:/Lumberjack/evtx/security/security.evtx;" << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'security';"
          << "$log.BackupEventlog('""C:/Lumberjack/evtx/security/security.evtx')";
    connect(getSecurityLogsProcess, &QProcess::finished, this, &MainController::convertSecEvtxToJson);
    getSecurityLogsProcess->start("powershell", args);
}

//Convert security evtx to JSON
void MainController::convertSecEvtxToJson(){
    getSecurityLogsProcess->terminate();
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing security data, please wait...");
    }
    convertSecEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Lumberjack/evtx/security/security.evtx --fj --json C:/Lumberjack/json/security/ --jsonf security.json";
    connect(convertSecEvtxToJsonProcess, &QProcess::finished, this, &MainController::getSecDataFromJson);
    convertSecEvtxToJsonProcess->start("powershell", args);
}

//Convert application EVTX to JSON
void MainController::convertAppEvtxToJson(){
    getApplicationLogsProcess->terminate();
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing application data, please wait...");
    }
    convertAppEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Lumberjack/evtx/application/application.evtx --json C:/Lumberjack/json/application/ --fj --jsonf application.json";
    connect(convertAppEvtxToJsonProcess, &QProcess::finished, this, &MainController::getAppDataFromJson);
    convertAppEvtxToJsonProcess->start("powershell", args);
}

//Convert system EVTX to JSON
void MainController::convertSysEvtxToJson(){
    getSystemLogsProcess->terminate();
    if(saveType == "refresh"){
        emit processingStatus2Qml("Processing system data, please wait...");
    }
    convertSysEvtxToJsonProcess = new QProcess();
    QStringList args;
    args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Lumberjack/evtx/system/system.evtx --json C:/Lumberjack/json/system/ --fj --jsonf system.json";
    connect(convertSysEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, this, &MainController::getSysDataFromJson);
    convertSysEvtxToJsonProcess->start("powershell", args);
}

//Parse JSON security data and retrieve desired values
void MainController::getSecDataFromJson(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Parsing security data, please wait...");
    }
    secEventCounterThread = new SecEventCounterThread();
    connect(secEventCounterThread, &SecEventCounterThread::finished, this, &MainController::getSecDataJsonStatus);
    connect(secEventCounterThread, &SecEventCounterThread::secEventNum2MainContrler, this, &MainController::setNumberOfSecEvents);
    secEventCounterThread->setSaveType(saveType);
    secEventCounterThread->start();
}

void MainController::getSecDataJsonStatus(){
    //qDebug() << "In get sec data jason status:";
    QThread::msleep(300);
    convertSecEvtxToJsonProcess->terminate();
    evtxProcessingDoneRelay(1);
    secEventCounterThread->terminate();
    getApplicationLogs();
}

//Parse JSON application data and retrieve desired values
void MainController::getAppDataFromJson(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Parsing application data, please wait...");
    }
    appEventCounterThread = new AppEventCounterThread();
    connect(appEventCounterThread, &AppEventCounterThread::finished, this, &MainController::getAppDataJsonStatus);
    connect(appEventCounterThread, &AppEventCounterThread::appEventNum2MainContrler, this, &MainController::setNumberOfAppEvents);
    appEventCounterThread->setSaveType(saveType);
    appEventCounterThread->start();
}

void MainController::getAppDataJsonStatus(){
    QThread::msleep(300);
    convertAppEvtxToJsonProcess->terminate();
    evtxProcessingDoneRelay(1);
    appEventCounterThread->terminate();
    getSystemLogs();
}

//Parse JSON system data and retrieve desired values
void MainController::getSysDataFromJson(){
    if(saveType == "refresh"){
        emit processingStatus2Qml("Parsing System data, please wait...");
    }
    sysEventCounterThread = new SysEventCounterThread();
    connect(sysEventCounterThread, &SysEventCounterThread::finished, this, &MainController::getSysDataJsonStatus);
    connect(sysEventCounterThread, &SysEventCounterThread::sysEventNum2MainContrler, this, &MainController::setNumberOfSysEvents);
    sysEventCounterThread->setSaveType(saveType);
    sysEventCounterThread->start();
}

void MainController::getSysDataJsonStatus(){
    QThread::msleep(300);
    convertSysEvtxToJsonProcess->terminate();
    evtxProcessingDoneRelay(1);
    sysEventCounterThread->terminate();

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
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"),
                                                    "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit dirPathToQml(dir);
    emit filePathToQml("");
    emit dirPathSepToQml("");
}

//Get path where converted files will be stored
void MainController::ce_SaveToPath(){
    QString dir = QFileDialog::getExistingDirectory(Q_NULLPTR, tr("Select Directory"),
                                                    "/home", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    emit saveToPathToQml(dir);
}

//Convert a single EVTX file to a single JSON, CSV, or XML file
void MainController::fileConvertEvtx(QString convertType, QString fPah, QString savePath, QString iFileName ){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " +
                                   QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToFullJsonProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(convertEvtxToJsonProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToJsonProcess->start("powershell", args);
    }
    else if(convertType == " Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " +
                                   QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToFullJsonProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";
        connect(convertEvtxToFullJsonProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToFullJsonProcess->start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToXmlProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + iFileName.trimmed() + ".xml";
        connect(convertEvtxToXmlProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToXmlProcess->start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToCsvProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + iFileName.trimmed() + ".csv";
        connect(convertEvtxToCsvProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToCsvProcess->start("powershell", args);
    }
    else{
        //error
    }
}

//Convert a directory of evtx files to a single json, xml, or csv. Note: Without using pointer for dynamic memory allocation, duplicate messages of conversion complete were being transmitted
void MainController::dirConvertEvtx(QString convertType, QString fPah, QString savePath){
    if(convertType == "JSON"){
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " +
                                   QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToJsonProcess = new QProcess();
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --json " +  savePath.trimmed();
        connect(convertEvtxToJsonProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToJsonProcess->start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " +
                                   QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToFullJsonProcess = new QProcess();
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf ";
        connect(convertEvtxToFullJsonProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToFullJsonProcess->start("powershell", args);
    }
    else if(convertType == "XML"){
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " +
                                   QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToXmlProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --xml " + savePath.trimmed();
        connect(convertEvtxToXmlProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToXmlProcess->start("powershell", args);
    }
    else if(convertType == "CSV"){
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " +
                                   QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        convertEvtxToCsvProcess = new QProcess();
        QStringList args;
        args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -d " + fPah.trimmed() +  " --csv " +  savePath.trimmed();       
        connect(convertEvtxToCsvProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
        convertEvtxToCsvProcess->start("powershell", args);
    }
    else{
        //error
    }
}

//Convert a directory of Evtx files to individual JSON, XML, or CSV files
void MainController::dirConvertEachEvtx(QString convertType, QString savePath){
    emit fileConvertEvtxStatus("EVTX file conversion process starting " +
                               QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
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
            connect(convertEachEvtxFileProcess, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
            convertEachEvtxFileProcess->start("powershell", args);
        }
        else if(convertType == "Full JSON"){
            QProcess *convertEachEvtxFileProcess2 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + curFileName + ".json";
            connect(convertEachEvtxFileProcess2, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
            convertEachEvtxFileProcess2->start("powershell", args);
        }
        else if(convertType == "XML"){
            QProcess *convertEachEvtxFileProcess3 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + curFileName + ".xml";
            connect(convertEachEvtxFileProcess3, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
            convertEachEvtxFileProcess3->start("powershell", args);
        }
        else if(convertType == "CSV"){
            convertEachEvtxFileProcess4 = new QProcess();
            QStringList args;
            args << "Set-Location -Path " + docsFolder + "/Lumberjack/EvtxeCmd/;"
                 << "./EvtxECmd.exe -f " + evtxFile.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + curFileName + ".csv";
            connect(convertEachEvtxFileProcess4, &QProcess::finished, this, &MainController::updateEvtxConvertStatus);
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

    if(!lumberjackDir.exists()){
        QDir().mkdir(docsFolder + "/Lumberjack");
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
    if(processingCount == 4){
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
        emit saveScheduleDataSaveStatus("Save completed @ " +
                                        QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
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
    emit saveScheduleDataSaveStatus("Shedule Days Save completed @ " +
                                    QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
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
     emit saveScheduleDataSaveStatus("Clear logs choice Save completed @ " +
                                     QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
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
    emit saveScheduleDataSaveStatus("Auto backup choice Save completed @ " +
                                     QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
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
            QString targetDir = "C:/Lumberjack/EvtxeCmd/";
            QStringList args;
            args << "Copy-Item -Path "  + targetDir +  " -Destination " + docsFolder + "/Lumberjack/EvtxeCmd/ -Recurse";
            moveEvtxeCmdToDocsProcess.start("powershell", args);
    }
    else{

    }
}

//Create an archive file containing the the date and time in the file name. Combine system, security, application, json files into one file.
void MainController::createArchive(QString backupType){
    _backupType = backupType;
    archiveCreatorThread = new ArchiveCreatorThread();
    connect(archiveCreatorThread, &ArchiveCreatorThread::archiveCreationStatus, this, &MainController::createArchiveStatus);
    archiveCreatorThread->start();
}

//BUG:Spaces in file names causes file to not be moved
//Move the selected audit log to the reviewed foler
void MainController::moveAuditLogToReviewedFolder(QString fileName){
    moveAuditLogToReviewedProcesss = new QProcess();
    QString fileToMove = "C:/Lumberjack/audit/archived_reports/" + fileName;
    QStringList args;
    args << "Move-Item -Path "  + fileToMove +  " -Destination C:/Lumberjack/audit/archived_reports/reviewed/" + fileName;
    //connect(moveAuditLogToReviewedProcesss,(void(QProcess::*)(int))&QProcess::finished, [=]{updateMovedLogsStatus();});
    connect(moveAuditLogToReviewedProcesss, &QProcess::finished, this, &MainController::updateMovedLogsStatus);
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
    getSecurityLogs("refresh", "updateFlags");
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
    QFile refreshSummaryFile("C:/Lumberjack/settings/refreshsummary/refreshsummary.txt"); 
    if(refreshSummaryFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&refreshSummaryFile);
            while (!in.atEnd()){

            QString temp = in.readAll().trimmed();
            emit savedRefreshDataToQml(temp);
            }
    }
    else{

    }
    refreshSummaryFile.close();
}

//Compare flags to event IDs in the archive log file. Add matches to the end of the file.
void MainController::parseFlags(QString fileName, QString bType){
    parseFlagsThread = new ParseFlagsThread();
    parseFlagsThread->setData(fileName, bType, refreshInProgress);
    connect(parseFlagsThread, &ParseFlagsThread::flagCount, this, &MainController::flagCount);
    connect(parseFlagsThread, &ParseFlagsThread::addLogFileToComboBox, this, &MainController::addLogFileToComboBox);
    connect(parseFlagsThread, &ParseFlagsThread::updateRefreshInProgress, this, &MainController::mc_UpdateRefreshInProgress);
    connect(parseFlagsThread, &ParseFlagsThread::liveBkupStatsDoneToQml, this, &MainController::updateLiveBackupStatus);
    connect(parseFlagsThread, &ParseFlagsThread::flagParsingStatus2Qml, this, &MainController::processingStatus2Qml);
    connect(parseFlagsThread, &ParseFlagsThread::flagParsingDone, this, &MainController::evtxProcessingDoneRelay);
    connect(parseFlagsThread, &ParseFlagsThread::clearEventLogs, this, &MainController::clearEventLogs);
    connect(parseFlagsThread, &ParseFlagsThread::finished, this, &MainController::terminateThread);
    parseFlagsThread->start();
}

//Add or remove program from run at start
void MainController::runOnStartRegEdit(QString switchState){
    if(switchState == "true"){
            QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings.setValue("Lumberjack.exe", QCoreApplication::applicationFilePath().replace('/', '\\'));
            settings.sync();
            //qDebug() << settings.status();
    }
    else if(switchState == "false"){
            QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
            settings.remove("Lumberjack.exe");
            settings.sync();
            //qDebug() << settings.status();
    }
}

//Save the time of refresh
void MainController::saveRefreshedTime(QString curTime){
    QFile lastRefreshTimeFile("C:/Lumberjack/settings/refreshsummary/lastrefreshtime.txt");
    if (lastRefreshTimeFile.open(QIODevice::WriteOnly)) {
            QTextStream stream(&lastRefreshTimeFile);
            stream << curTime;
    }
    lastRefreshTimeFile.close();
}

//Save the time and date of the current refresh in progress
void MainController::saveRefreshedTimeWd(QString curTimeWd){
    QFile lastRefreshTimeFileWd("C:/Lumberjack/settings/refreshsummary/lastrefreshtimewd.txt");
    if (lastRefreshTimeFileWd.open(QIODevice::WriteOnly)) {
            QTextStream stream(&lastRefreshTimeFileWd);
            stream << curTimeWd;
    }
    lastRefreshTimeFileWd.close();
}

//compare refresh time
void MainController::compareRefreshedTime(QString currentTime){
    QFile lastRefreshSummaryFile("C:/Lumberjack/settings/refreshsummary/lastrefreshtimewd.txt");
    if(lastRefreshSummaryFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&lastRefreshSummaryFile);
            while (!in.atEnd()){
                lastRefreshedTime_WD = in.readAll().trimmed();
            }            
    }
    lastRefreshSummaryFile.close();
    QString start = lastRefreshedTime_WD;
    QString end = currentTime;
    timeDiff = QString("%1").arg(QDateTime().fromString(start, "h:m:s ap dd.MM.yyyy").secsTo(QDateTime().fromString(end, "h:m:s ap dd.MM.yyyy")));

    QFile refreshIntervalFile("C:/Lumberjack/settings/refreshsummary/refreshsummary.txt");
    if(refreshIntervalFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&refreshIntervalFile);
            while (!in.atEnd()){
                refrshIntervalX = in.readAll().trimmed();
            }
    }
    refreshIntervalFile.close();

    if(refrshIntervalX == ""){

    }
    else if(refrshIntervalX == "0"){

    }
    else if(refrshIntervalX == "1"){

    }
    // 1 hour
    else if(refrshIntervalX == "2"
                && timeDiff.toInt() >= 3600
                && timeDiff.toInt() < 3720
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 2 hours
    else if(refrshIntervalX == "3"
                && timeDiff.toInt() >= 7200
                && timeDiff.toInt() < 7320
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 3 hours
    else if(refrshIntervalX == "4"
                && timeDiff.toInt() >= 10800
                && timeDiff.toInt() < 10920
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 4 hours
    else if(refrshIntervalX == "5"
                && timeDiff.toInt() >= 1440
                && timeDiff.toInt() < 1560
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 5 hours
    else if(refrshIntervalX == "6"
                && timeDiff.toInt() >= 18000
                && timeDiff.toInt() < 18120
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 6 hours
    else if(refrshIntervalX == "7"
                && timeDiff.toInt() >= 21600
                && timeDiff.toInt() < 21720
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 7 hours
    else if(refrshIntervalX == "8"
                && timeDiff.toInt() >= 25200
                && timeDiff.toInt() < 25320
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 8 hours
    else if(refrshIntervalX == "9"
                && timeDiff.toInt() >= 28800
                && timeDiff.toInt() < 28920
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 9 hours
    else if(refrshIntervalX == "10"
                && timeDiff.toInt() >= 32400
                && timeDiff.toInt() < 32520
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 10 hours
    else if(refrshIntervalX == "11"
                && timeDiff.toInt() >= 36000
                && timeDiff.toInt() < 36120
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 11 hours
    else if(refrshIntervalX == "12"
                && timeDiff.toInt() >= 39600
                && timeDiff.toInt() < 39720
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
    // 12 hours
    else if(refrshIntervalX == "13"
                && timeDiff.toInt() >= 43200
                && timeDiff.toInt() < 43320
                && refreshInProgress == false){
                refreshInProgress = true;
                updateCurrentLogSummary();
    }
}

void MainController::clearEventLogs(){
    clearLogsProcess = new QProcess();
    QStringList args;
    args  << "Clear-EventLog -LogName application, system, security";
    connect(clearLogsProcess, &QProcess::finished, this, &MainController::clearLogsStatus);
    clearLogsProcess->start("powershell", args);
}

void MainController::clearLogsStatus(){
    //TO DO: Send message to QML
    qDebug() << "Clear logs finished........";
}

//Send the number of security events to QML
void MainController::setNumberOfSecEvents(QString NOSE){
    emit securityEventCount2Qml(NOSE);
}

//Send the number of application events to QML
void MainController::setNumberOfAppEvents(QString NOAE){
    emit appEventCount2Qml(NOAE);
}

//Send the number of system events to QML
void MainController::setNumberOfSysEvents(QString NSE){
    emit sysEventCount2Qml(NSE);
}

//Parse flags after archive thread is done processing
void MainController::createArchiveStatus(QString timeFromArchive){
    parseFlags(timeFromArchive, _backupType);
    archiveCreatorThread->quit();
}

void MainController::mc_UpdateRefreshInProgress(bool refreshStatus){
    refreshInProgress = refreshStatus;
}

void MainController::updateLiveBackupStatus(){
    emit liveBkupStatsDoneToQml("Live backup completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

//Stop parse flags thread
void MainController::terminateThread(){
    parseFlagsThread->quit();
}


