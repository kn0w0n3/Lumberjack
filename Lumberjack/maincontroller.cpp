#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    //getSecurityLogs();
    //getApplicationLogs();
    //getSystemLogs();
    //getSecDatafromXml();
    getSecDataFromJson();
}

//Save system logs to evtx file
void MainController::getSystemLogs(){
    qDebug() << "In get system logs........";
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
    QStringList args;

    args  << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'security';" <<
             "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx')";

    getSecurityLogsProcess.connect(&getSecurityLogsProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    getSecurityLogsProcess.connect(&getSecurityLogsProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    connect(&getSecurityLogsProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{convertSecEvtxToXml(); convertSecEvtxToJson();});
    getSecurityLogsProcess.start("powershell", args);
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

void MainController::convertSecEvtxToXml(){
    qDebug() << "IN CONVERT SEC EVTX TO XML........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/;"
         << "./evtx_dump-v0_8_1 C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx | Out-File -FilePath C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/xml/security/security.xml";

    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    convertSecEvtxToXmlProcess.connect(&convertSecEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    //connect(&convertSecEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertSecEvtxToXmlProcess.start("powershell", args);
}

void MainController::convertSecEvtxToJson(){
    qDebug() << "IN CONVERT SEC EVTX TO JSON........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/;"
         << "./evtx_dump-v0_8_1 -o json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/security/security.evtx | Out-File -FilePath C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/security/security.json";

    convertSecEvtxToJsonProcess.connect(&convertSecEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSecLogInfo);
    convertSecEvtxToJsonProcess.connect(&convertSecEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSecLogInfo);
    connect(&convertSecEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDataFromJson();});
    convertSecEvtxToJsonProcess.start("powershell", args);
}

void MainController::convertAppEvtxToXml(){
    qDebug() << "IN CONVERT App EVTX TO XML........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/;"
         << "./evtx_dump-v0_8_1 C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/application/application.evtx | Out-File -FilePath C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/xml/application/application.xml";

    convertAppEvtxToXmlProcess.connect(&convertAppEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutAppLogInfo);
    convertAppEvtxToXmlProcess.connect(&convertAppEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorAppLogInfo);
    //connect(&convertAppEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertAppEvtxToXmlProcess.start("powershell", args);

}

void MainController::convertAppEvtxToJson(){
    qDebug() << "IN CONVERT App EVTX TO JSON........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/;"
         << "./evtx_dump-v0_8_1 -o json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/application/application.evtx | Out-File -FilePath C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/application/application.json";

    convertAppEvtxToJsonProcess.connect(&convertAppEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutAppLogInfo);
    convertAppEvtxToJsonProcess.connect(&convertAppEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorAppLogInfo);
    //connect(&convertAppEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertAppEvtxToJsonProcess.start("powershell", args);
}

void MainController::convertSysEvtxToXml(){
    qDebug() << "IN CONVERT Sys EVTX TO XML........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/;"
         << "./evtx_dump-v0_8_1 C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/system/system.evtx | Out-File -FilePath C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/xml/system/system.xml";

    convertSysEvtxToXmlProcess.connect(&convertSysEvtxToXmlProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSysLogInfo);
    convertSysEvtxToXmlProcess.connect(&convertSysEvtxToXmlProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSysLogInfo);
    //connect(&convertSysEvtxToXmlProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertSysEvtxToXmlProcess.start("powershell", args);
}

void MainController::convertSysEvtxToJson(){
    qDebug() << "IN CONVERT Sys EVTX TO JSON........";

    QStringList args;
    args << "Set-Location -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/;"
         << "./evtx_dump-v0_8_1 -o json C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/evtx/system/system.evtx | Out-File -FilePath C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/system/system.json";

    convertSysEvtxToJsonProcess.connect(&convertSysEvtxToJsonProcess, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutSysLogInfo);
    convertSysEvtxToJsonProcess.connect(&convertSysEvtxToJsonProcess, &QProcess::readyReadStandardError, this, &MainController::processErrorSysLogInfo);
    //connect(&convertSysEvtxToJsonProcess, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    convertSysEvtxToJsonProcess.start("powershell", args);
}

void MainController::getSecDatafromXml(){
    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/xml/security/security.xml");

    qDebug() << "Trying to open XML file........";
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file!";
        return;
    }

    QXmlStreamReader xml(&file);
    //while (!xml.atEnd() && !xml.hasError())
    while (!xml.atEnd()){
        xml.readNext();
        //if (xml.isStartElement())
       // {
            QString name = xml.name().toString();
            if (name == "EventData"){

                QString data = xml.readElementText();
                //if(data.isEmpty() || data == "\n"){
                    //continue;
                    //xml.readNext();
                    //continue;
                    //xml.readNext();
                    //continue;
                //}
               // else{
                qDebug() << "element name: '" << name  << "'"
                     << ", text: '" << data
                     << "'" ;
                //}
            }
       // }
    }

    if (xml.hasError()){
       qDebug() << "XML ERROR IS........" + xml.errorString();
    }

    else if (xml.atEnd()){
        qDebug() << "XML END........Reached end, done";
    }
}

void MainController::getSecDataFromJson(){
    qDebug() << "In get SEC data from JSON file.......";

    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/json/security/security.json");
    if(!file.open(QIODevice::ReadOnly)) {

    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        jsonStringData = in.readAll();

    }
    file.close();

    QJsonDocument json_doc = QJsonDocument::fromJson(jsonStringData.toUtf8());
    QJsonObject jsonObject = json_doc.object();
     //QJsonArray array = json_doc.array();

     //foreach(const QJsonValue &v, array){
     //    QJsonObject obj = v.toObject();
    // }
    ///

    //Get the desired info from the JSON data.
    //QJsonObject obdata = jsonObject["Event"].toObject();
    //QString test = obdata.value("EventData").toObject().value("SubjectUserName").toString();
    QString test = jsonObject.value("Event").toObject().value("EventData").toObject().value("SubjectUserName").toString();
    qDebug() << "The json data is: " +  test;
    //rank = obdata["rank"].toString();
    //marketCapUsd = obdata["marketCapUsd"].toString();
    //availableSupply = obdata["supply"].toString();
    //maxSupply = obdata["maxSupply"].toString();
}
