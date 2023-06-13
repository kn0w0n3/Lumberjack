#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    //getSecurityLogs();
    //getApplicationLogs();
    //getSystemLogs();
    //getSecDatafromXml();
    //getSecDataFromJson();
    //convertSecEvtxToJson();
}

//Save system logs to evtx file
void MainController::getSystemLogs(){
    qDebug() << "In get system logs........";
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
    qDebug() << "In get Application logs........";
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
    qDebug() << "In get Security logs........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;

    args  << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'security';" <<
             "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx')";

    getSecurityLogsProcess.connect(&getSecurityLogsProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    getSecurityLogsProcess.connect(&getSecurityLogsProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    connect(&getSecurityLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSecEvtxToJson();});
    getSecurityLogsProcess.start("powershell", args);
}



void MainController::convertSecEvtxToXml(){
    qDebug() << "IN CONVERT SEC EVTX TO XML........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx --xml C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/xml/security/ --jsonf security.xml";

    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    //connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertSecEvtxToXmlProcess.start("powershell", args);
}

//https://dotnet.microsoft.com/en-us/download/dotnet/thank-you/runtime-6.0.16-windows-x64-installer?cid=getdotnetcore
//App wouldn't run because it was missing the above microsoft requirement
void MainController::convertSecEvtxToJson(){
    qDebug() << "IN CONVERT SEC EVTX TO JSON........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx --json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/security/ --fj --jsonf security.json";

    convertSecEvtxToJsonProcess.connect(&convertSecEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    convertSecEvtxToJsonProcess.connect(&convertSecEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    connect(&convertSecEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDataFromJson();});
    convertSecEvtxToJsonProcess.start("powershell", args);
}

void MainController::convertAppEvtxToXml(){

}

void MainController::convertAppEvtxToJson(){
    qDebug() << "IN CONVERT App EVTX TO JSON........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/application/application.evtx --json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/application/ --jsonf application.json";

    convertAppEvtxToJsonProcess.connect(&convertAppEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutAppLogInfo);
    convertAppEvtxToJsonProcess.connect(&convertAppEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorAppLogInfo);
    connect(&convertAppEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getAppDataFromJson();});
    convertAppEvtxToJsonProcess.start("powershell", args);
}

void MainController::convertSysEvtxToXml(){

}

void MainController::convertSysEvtxToJson(){
    qDebug() << "IN CONVERT Sys EVTX TO JSON........";
    emit processingStatus2Qml("Processing data, please wait...");
    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/EvtxeCmd/;"
         << "./EvtxECmd.exe -f C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/system/system.evtx --json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/system/ --jsonf system.json";

    convertSysEvtxToJsonProcess.connect(&convertSysEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSysLogInfo);
    convertSysEvtxToJsonProcess.connect(&convertSysEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSysLogInfo);
    connect(&convertSysEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSysDataFromJson();});
    convertSysEvtxToJsonProcess.start("powershell", args);
}

void MainController::getSecDatafromXml(){

}

void MainController::getSecDataFromJson(){
    qDebug() << "In get SEC data from JSON file.......";

    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/security/security.json");
    if(!file.open(QIODevice::ReadOnly)) {

    }

    QTextStream in(&file);
    while (!in.atEnd()){
        jsonObjects << in.readLine();
    }
    file.close();

    foreach(const QString &logEntry, jsonObjects){
        numOfSecEvents++;
        QString numToString = QString::number(numOfSecEvents);
        //qDebug() << "The counter is: " + numToString;

        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
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

    qDebug() << "Trying to emit";
    emit securityEventCount2Qml(QString::number(numOfSecEvents));
    numOfSecEvents = 0;
    emit processingStatus2Qml("Summary");
}

void MainController::getAppDataFromJson(){
    qDebug() << "In get App data from JSON file.......";

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

    qDebug() << "Trying to emit";
    emit appEventCount2Qml(QString::number(numbOfAppEvents));
    numbOfAppEvents = 0;
}

void MainController::getSysDataFromJson(){
    qDebug() << "In get Sys data from JSON file.......";
    emit processingStatus2Qml("Processing data, please wait...");
    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/system/system.json");
    if(!file.open(QIODevice::ReadOnly)) {

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

    qDebug() << "Trying to emit";
    emit sysEventCount2Qml(QString::number(numbOfSysEvents));
    numbOfAppEvents = 0;
}

void MainController::processStdOutSecLogInfo(){
    b_StdOutSecLogInfo+= getSecurityLogsProcess.readAllStandardOutput().trimmed();
    s_StdOutSecLogInfo = QString(b_StdOutSecLogInfo);
    qDebug() << "Std out Sec Info: " + s_StdOutSecLogInfo;
}

void MainController::processErrorSecLogInfo(){
    b_StdErrSecLogInfo += getSecurityLogsProcess.readAllStandardError().trimmed();
    s_StdErrSecLogInfo = QString(b_StdErrSecLogInfo);
    qDebug() << "Error Sec Info: " + s_StdErrSecLogInfo;
}

void MainController::processStdOutAppLogInfo(){
    b_StdOutAppLogInfo+= getApplicationLogsProcess.readAllStandardOutput().trimmed();
    s_StdOutAppLogInfo = QString(b_StdOutAppLogInfo);
    qDebug() << "Std out App Info: " + s_StdOutAppLogInfo;
}

void MainController::processErrorAppLogInfo(){
    b_StdErrAppLogInfo += getApplicationLogsProcess.readAllStandardError().trimmed();
    s_StdErrAppLogInfo = QString(b_StdErrAppLogInfo);
    qDebug() << "Error App Info: " + s_StdErrAppLogInfo;
}

void MainController::processStdOutSysLogInfo(){
    b_StdOutSysLogInfo+= getSystemLogsProcess.readAllStandardOutput().trimmed();
    s_StdOutSysLogInfo = QString(b_StdOutSysLogInfo);
    qDebug() << "Std out Sys Info: " + s_StdOutSysLogInfo;
}

void MainController::processErrorSysLogInfo(){
    b_StdErrSysLogInfo += getSystemLogsProcess.readAllStandardError().trimmed();
    s_StdErrSysLogInfo = QString(b_StdErrSysLogInfo);
    qDebug() << "Error Sys Info: " + s_StdErrSysLogInfo;
}


void MainController::sendLogInfoToQml(){
    //qDebug() <<"Sending info to QML: " + s_StdOutLogInfo;
}
