#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    //getSecurityLogs();
    //getApplicationLogs();
    //getSystemLogs();
    //getSecDatafromXml();
    //getSecDataFromJson();
    //convertSecEvtxToJson();
    //populateFlagData();

    //TODO:
   //Check if directories exist. If not, create them.
    //QDateTime::currentDateTime();
}

//Save system logs to evtx file
void MainController::getSystemLogs(){
    //qDebug() << "In get system logs........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;

    args  << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'system';"
          << "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/system/system.evtx')";

    getSystemLogsProcess.connect(&getSystemLogsProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSysLogInfo);
    getSystemLogsProcess.connect(&getSystemLogsProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSysLogInfo);
    connect(&getSystemLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSysEvtxToXml(); convertSysEvtxToJson();});
    getSystemLogsProcess.start("powershell", args);
}

//Save application logs to evtx file
void MainController::getApplicationLogs(){
    //qDebug() << "In get Application logs........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;

    args  << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'application';"
          << "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/application/application.evtx')";

    getApplicationLogsProcess.connect(&getApplicationLogsProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutAppLogInfo);
    getApplicationLogsProcess.connect(&getApplicationLogsProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorAppLogInfo);
    connect(&getApplicationLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertAppEvtxToXml(); convertAppEvtxToJson();});
    getApplicationLogsProcess.start("powershell", args);
}

//Save secuity logs to evtx file
void MainController::getSecurityLogs(){
    //qDebug() << "In get Security logs........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;

    args  << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'security';" <<
             "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx')";

    getSecurityLogsProcess.connect(&getSecurityLogsProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    getSecurityLogsProcess.connect(&getSecurityLogsProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    connect(&getSecurityLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSecEvtxToJson();});
    getSecurityLogsProcess.start("powershell", args);
}

//Convert security evtx to XML
void MainController::convertSecEvtxToXml(){
    //qDebug() << "IN CONVERT SEC EVTX TO XML........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx --xml C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/xml/security/ --xmlf security.xml";

    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    //connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertSecEvtxToXmlProcess.start("powershell", args);
}

//https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-6.0.16-windows-x64-installer?cid=getdotnetcore
//App wouldn't run because it was missing the above microsoft requirement
//Convert security evtx to JSON
void MainController::convertSecEvtxToJson(){
    //qDebug() << "IN CONVERT SEC EVTX TO JSON........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx --fj --json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/security/ --jsonf security.json";

    convertSecEvtxToJsonProcess.connect(&convertSecEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    convertSecEvtxToJsonProcess.connect(&convertSecEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    connect(&convertSecEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDataFromJson();});
    convertSecEvtxToJsonProcess.start("powershell", args);
}

void MainController::convertAppEvtxToXml(){

}

void MainController::convertAppEvtxToJson(){
    //qDebug() << "IN CONVERT App EVTX TO JSON........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/application/application.evtx --json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/application/ --fj --jsonf application.json";

    convertAppEvtxToJsonProcess.connect(&convertAppEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutAppLogInfo);
    convertAppEvtxToJsonProcess.connect(&convertAppEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorAppLogInfo);
    connect(&convertAppEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getAppDataFromJson();});
    convertAppEvtxToJsonProcess.start("powershell", args);
}

void MainController::convertSysEvtxToXml(){

}

void MainController::convertSysEvtxToJson(){
    //qDebug() << "IN CONVERT Sys EVTX TO JSON........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/system/system.evtx --json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/system/ --fj --jsonf system.json";

    convertSysEvtxToJsonProcess.connect(&convertSysEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSysLogInfo);
    convertSysEvtxToJsonProcess.connect(&convertSysEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSysLogInfo);
    connect(&convertSysEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSysDataFromJson();});
    convertSysEvtxToJsonProcess.start("powershell", args);
}

void MainController::getSecDatafromXml(){

}

//Parse JSON data and retrieve desired values
void MainController::getSecDataFromJson(){
    //qDebug() << "In get SEC data from JSON file.......";

    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/security/security.json");
    if(!file.open(QIODevice::ReadOnly)){

    }

    QTextStream in(&file);
    while (!in.atEnd()){
        jsonObjects << in.readLine();
    }
    file.close();

    foreach(const QString &logEntry, jsonObjects){
        numOfSecEvents++;
        //QString numToString = QString::number(numOfSecEvents);
        //qDebug() << "The counter is: " + numToString;

        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QJsonObject obdata2 = jsonObject.value("Event").toObject().value("System").toObject().value("TimeCreated").toObject();
        eventId_ = obdata["EventID"].toString();

        //Temp fix formatting
        if(eventId_.length() < 5){
            int x = 5 - eventId_.length();

            while( x > 0){
                x--;
                eventId_.append("0");
            }
        }
        QString computerName = obdata["Computer"].toString();
        QString channel_ = obdata["Channel"].toString();
        QString timeCreated = obdata2["@SystemTime"].toString();
        result += "Event ID: " + eventId_+ "     |     Computer Name: " + computerName + "     |     Channel: " + channel_ + "     |     Time Created: " + timeCreated + "\n";
       // QJsonObject obdata = jsonObject.value("PayloadData4").toObject();
        //QString eventId = obdata["EventID"].toString();
        //qDebug()<< "Event ID is: " + eventId;
        //emit dataToLogViewer("Event ID: " + eventId);
        //QThread::msleep(500);
    }

    //Working JSON!!!
    /*
    foreach(const QString &logEntry, jsonObjects){
        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject().value("Provider").toObject();
        QString test = obdata["@Name"].toString();
        qDebug() << "Event id is:" + test;
    }
    */

    //qDebug() << "Trying to emit";

    emit securityEventCount2Qml(QString::number(numOfSecEvents));
    numOfSecEvents = 0;
    emit processingStatus2Qml("Summary " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    emit dataToLogViewer(result);
}

void MainController::getAppDataFromJson(){
    //qDebug() << "In get App data from JSON file.......";

    emit processingStatus2Qml("Processing data, please wait...");
    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/application/application.json");
    if(!file.open(QIODevice::ReadOnly)) {

    }

    QTextStream in(&file);
    while (!in.atEnd()){
        //QString line = in.readLine();
        //qDebug() << "Data is: " + line;
        jsonObjects << in.readLine();
    }
    file.close();

    foreach(const QString &logEntry, jsonObjects){
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
    emit processingStatus2Qml("Summary " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

void MainController::getSysDataFromJson(){
    //qDebug() << "In get Sys data from JSON file.......";
    emit processingStatus2Qml("Processing data, please wait...");
    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/system/system.json");
    if(!file.open(QIODevice::ReadOnly)){
        //error
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        jsonObjects << in.readLine();
    }
    file.close();

    foreach(const QString &logEntry, jsonObjects){
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
    numbOfAppEvents = 0;
    emit processingStatus2Qml("Summary " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
}

//Get asved flag data to populate the current flag list in QML
void MainController::populateFlagData(){
    //qDebug() << "In populate flag data.......";

    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/flags/flags.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        //qDebug() << "Flag file not open";
    }

    QTextStream in(&file);
    while (!in.atEnd()){
        //qDebug() << in.readLine();
        QString temp = in.readLine();
        //flagList << in.readLine();
        emit populateFlagDataToQml(temp);
        //QThread::msleep(300);

    }
    file.close();

    //foreach(const QString &flag, flagList){

        //emit populateFlagDataToQml(flag);
        //QThread::msleep(500);
    //}
    //qDebug() << "Done In populate flag data.......";
}

//Save flag data to file
void MainController::saveFlagData(QString flagData){
    //qDebug() << "In Save Flag Data";
    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/flags/flags.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append)) {
        QTextStream out(&file);
        out << flagData + "\n";
    }
    else{
        //error
    }
    file.close();
}

//Get file name and path for evtx file
void MainController::ce_SelectFile(){
    convertEvtxFileName = QFileDialog::getOpenFileName(Q_NULLPTR, tr("Select File"), "");
    QFileInfo fileInfo(convertEvtxFileName);
    convertEvtxFileName = fileInfo.fileName().trimmed();

    //emit dbFileNameToQml(convertEvtxFileName);
    convertEvtxFullFilePath  = fileInfo.filePath().trimmed();

    convertEvtxFilePathOnly = fileInfo.filePath().trimmed();
    convertEvtxFilePathOnly.replace(convertEvtxFileName, "");
    convertEvtxFileSize = QString::number(fileInfo.size());
    //testPath = dbFullFileP\ath;
    //testPath.replace(" ","\\");

    //qDebug() << "The selected file path is " << convertEvtxFullFilePath;
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

//Convert an extx file to json, xml, or csv
void MainController::fileConvertEvtx(QString convertType, QString fPah, QString savePath, QString iFileName ){
    if(convertType == "JSON"){
        //qDebug() << "IN CONVERT EVTX TO JSON........";
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";

        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        //qDebug() << "IN CONVERT EVTX TO  Full JSON........";
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";

        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);

    }
    else if(convertType == "XML"){
        //qDebug() << "IN CONVERT EVTX TO XML........";
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + iFileName.trimmed() + ".xml";

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
        connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertSecEvtxToXmlProcess.start("powershell", args);

    }
    else if(convertType == "CSV"){
        //qDebug() << "IN CONVERT EVTX TO CSV........";
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + iFileName.trimmed() + ".csv";

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
        connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertSecEvtxToXmlProcess.start("powershell", args);
    }
    else{
        //error
    }
}

//Convert a directory of evtx files to json, xml, or csv
void MainController::dirConvertEvtx(QString convertType, QString fPah, QString savePath){
    if(convertType == "JSON"){
        //qDebug() << "IN CONVERT EVTX TO JSON........";
        emit fileConvertEvtxStatus("EVTX to JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";

        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        convertEvtxToJsonProcess.connect(&convertEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);
    }
    else if(convertType == "Full JSON"){
        //qDebug() << "IN CONVERT EVTX TO  Full JSON........";
        emit fileConvertEvtxStatus("EVTX to FUll JSON conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");
        QStringList args;
        //Set a permanent location for deployment
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --fj --json " +  savePath.trimmed() + " --jsonf " + iFileName.trimmed() + ".json";

        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processConvertStdOutInfo);
        //convertEvtxToFullJsonProcess.connect(&convertEvtxToFullJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processConvertErrorInfo);
        connect(&convertEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertEvtxToJsonProcess.start("powershell", args);

    }
    else if(convertType == "XML"){
        //qDebug() << "IN CONVERT EVTX TO XML........";
        emit fileConvertEvtxStatus("EVTX to XML conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --xml " +  savePath.trimmed() + " --xmlf " + iFileName.trimmed() + ".xml";

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
        connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{updateEvtxConvertStatus();});
        convertSecEvtxToXmlProcess.start("powershell", args);

    }
    else if(convertType == "CSV"){
        //qDebug() << "IN CONVERT EVTX TO CSV........";
        emit fileConvertEvtxStatus("EVTX to CSV conversion process starting " + QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
        emit fileConvertEvtxStatus("Please Wait....");

        QStringList args;
        args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
             << "./EvtxECmd.exe -f " + fPah.trimmed() +  " --csv " +  savePath.trimmed() + " --csvf " + iFileName.trimmed() + ".csv";

        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
        //convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
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
    //Try to access the C drive program files folder. This is where the EvtxECmd.exe program will live as well.
    //Create a directory in mydocuments for output files. Get user name for path?
}

void MainController::processStdOutSecLogInfo(){
    b_StdOutSecLogInfo += getSecurityLogsProcess.readAllStandardOutput().trimmed();
    s_StdOutSecLogInfo = QString(b_StdOutSecLogInfo);
    //qDebug() << "Std out Sec Info: " + s_StdOutSecLogInfo;
}

void MainController::processErrorSecLogInfo(){
    b_StdErrSecLogInfo += getSecurityLogsProcess.readAllStandardError().trimmed();
    s_StdErrSecLogInfo = QString(b_StdErrSecLogInfo);
    //qDebug() << "Error Sec Info: " + s_StdErrSecLogInfo;
}

void MainController::processStdOutAppLogInfo(){
    b_StdOutAppLogInfo+= getApplicationLogsProcess.readAllStandardOutput().trimmed();
    s_StdOutAppLogInfo = QString(b_StdOutAppLogInfo);
    //qDebug() << "Std out App Info: " + s_StdOutAppLogInfo;
}

void MainController::processErrorAppLogInfo(){
    b_StdErrAppLogInfo += getApplicationLogsProcess.readAllStandardError().trimmed();
    s_StdErrAppLogInfo = QString(b_StdErrAppLogInfo);
    //qDebug() << "Error App Info: " + s_StdErrAppLogInfo;
}

void MainController::processStdOutSysLogInfo(){
    b_StdOutSysLogInfo+= getSystemLogsProcess.readAllStandardOutput().trimmed();
    s_StdOutSysLogInfo = QString(b_StdOutSysLogInfo);
    //qDebug() << "Std out Sys Info: " + s_StdOutSysLogInfo;
}

void MainController::processErrorSysLogInfo(){
    b_StdErrSysLogInfo += getSystemLogsProcess.readAllStandardError().trimmed();
    s_StdErrSysLogInfo = QString(b_StdErrSysLogInfo);
    //qDebug() << "Error Sys Info: " + s_StdErrSysLogInfo;
}

void MainController::processConvertStdOutInfo(){
    b_StdOutConvertInfo += convertEvtxToJsonProcess.readAllStandardOutput().trimmed();
    s_StdOutConvertInfo = QString(b_StdOutConvertInfo);
    //qDebug() << "Std out convert evtx Info: " + s_StdOutConvertInfo;
}

void MainController::processConvertErrorInfo(){
    b_StdErrConvertInfo += convertEvtxToJsonProcess.readAllStandardError().trimmed();
    s_StdErrConvertInfo = QString(b_StdErrConvertInfo);
    //qDebug() << "Error Convert Info: " + s_StdErrConvertInfo;
}

void MainController::sendLogInfoToQml(){
    //qDebug() <<"Sending info to QML: " + s_StdOutLogInfo;
}
