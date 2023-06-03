#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    //getLogInfo();
    getSecDatafromXml();
}

void MainController::getLogInfo(){
    qDebug() << "1 IN GET LOG INFO........";
    QStringList args;
    //args << "Get-WinEvent -ListLog *;";

            //Save system logs to evtx file
    args  << "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'system';" <<
            "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/system.evtx');" <<

            //Save application logs to evtx file
            "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'application';" <<
            "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/application.evtx');" <<

            //Save setup logs to evtx file - Not working currently
            //"$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'setup';" <<
            //"$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/setup.evtx');" <<

            //Save secuity logs to evtx file
            "$log = Get-WmiObject -Class Win32_NTEventlogFile | Where-Object LogfileName -EQ 'security';" <<
            "$log.BackupEventlog('C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/security.evtx');";

    //getWinLogs = new QProcess();
    getWinLogs.connect(&getWinLogs, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutLogInfo);
    getWinLogs.connect(&getWinLogs, &QProcess::readyReadStandardError, this, &MainController::processErrorLogInfo);
    connect(&getWinLogs, (void(QProcess::*)(int))&QProcess::finished, [=]{convertEvtxToXml();});
    getWinLogs.start("powershell", args);
    //convertEvtxToXml();
}

void MainController::processLogInfo(){

}

void MainController::processStdOutLogInfo(){
    b_StdOutLogInfo+= getWinLogs.readAllStandardOutput().trimmed();
    s_StdOutLogInfo = QString(b_StdOutLogInfo);
    //qDebug() << "Std Info: " + s_StdOutLogInfo;

    QString filename = "C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/logdata.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        //qDebug() << "Writing data to file.........";
        stream << s_StdOutLogInfo;
    }
    //qDebug() << "Finished writing data to file.........";
}

void MainController::processErrorLogInfo(){
    b_StdErrLogInfo += getWinLogs.readAllStandardError().trimmed();
    s_StdErrLogInfo = QString(b_StdErrLogInfo);
    qDebug() << "Error Info: " + s_StdErrLogInfo;
}

void MainController::sendLogInfoToQml(){
    //qDebug() <<"Sending info to QML: " + s_StdOutLogInfo;
}

void MainController::convertEvtxToXml(){
    qDebug() << "2 IN CONVERT EVTX TO XML........";
    QStringList args;
    //args << "Get-WinEvent -ListLog *;";

    //Save system logs to evtx file
    args  << "get-winevent -Path C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/security.evtx -oldest | convertto-xml -as Stream -depth 10 > C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/security.xml;";

    //getWinLogs = new QProcess();
    parseLogs.connect(&parseLogs, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutLogInfo);
   parseLogs.connect(&parseLogs, &QProcess::readyReadStandardError, this, &MainController::processErrorLogInfo);
    connect(&parseLogs, (void(QProcess::*)(int))&QProcess::finished, [=]{getSecDatafromXml();});
    parseLogs.start("powershell", args);
}

void MainController::getSecDatafromXml(){
    /*
    qDebug() << "3 IN GET SEC DATA FROM XML........";
    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/security.xml");

    qDebug() << "Trying to open XML file........";
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file!";
        return;
    }

    QXmlStreamReader xmlReader(&file);
       qDebug() << "Trying to parse XML file........";
    while(!xmlReader.atEnd() && !xmlReader.hasError()){
        qDebug() << "IN WHILE LOOP........";
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        //if(token == QXmlStreamReader::StartDocument)
            //qDebug() << "In continue........";
            //continue;

        if(token == QXmlStreamReader::StartElement){
            qDebug() << "IN START ELEMENT........";
            if(xmlReader.name().toString() == "Object"){
                qDebug() << "WAS PROPERTY........";
                QString curValue = xmlReader.attributes().value("Id").toString();
                qDebug() << "curValue: " << curValue;
            }
        }
    }
*/

    QFile file("C:/Users/Voldem0rt/Documents/Qt_Projects/Lumberjack/security.xml");

    qDebug() << "Trying to open XML file........";
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file!";
        return;
    }

    QXmlStreamReader xml(&file);
    while (!xml.atEnd() && !xml.hasError())
    {
        xml.readNext();
        if (xml.isStartElement())
        {
            QString name = xml.name().toString();
            if (name == "Object" || name == "Property" ||
                name == "Id" || name == "Type")
            {
                qDebug() << "element name: '" << name  << "'"
                     << ", text: '" << xml.readElementText()
                     << "'" ;
            }
        }
    }

    if (xml.hasError()){
       qDebug() << "XML ERROR IS........" + xml.errorString();
    }

    else if (xml.atEnd()){
        qDebug() << "XML END........Reached end, done";
    }

    /*
    QByteArray xmlText;
    //Get your xml into xmlText(you can use QString instead og QByteArray)
    QDomDocument doc;
    doc.setContent(xmlText);
    QDomNodeList list=doc.elementsByTagName("string");
    QString helloWorld=list.at(0).toElement().text();
    */
}
