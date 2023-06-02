#include "maincontroller.h"

MainController::MainController(QWidget *parent) : QWidget(parent){
    //getLogInfo();
}

void MainController::getLogInfo(){
    QStringList args;
    args << "Get-WinEvent -ListLog *;";

    //getWinLogs = new QProcess();
    getWinLogs.connect(&getWinLogs, &QProcess::readyReadStandardOutput, this, &MainController::processStdOutLogInfo);
    getWinLogs.connect(&getWinLogs, &QProcess::readyReadStandardError, this, &MainController::processErrorLogInfo);
    connect(&getWinLogs, (void(QProcess::*)(int))&QProcess::finished, [=]{sendLogInfoToQml();});
    getWinLogs.start("powershell", args);
}

void MainController::processLogInfo(){

}

void MainController::processStdOutLogInfo(){
    b_StdOutLogInfo+= getWinLogs.readAllStandardOutput().trimmed();
    s_StdOutLogInfo = QString(b_StdOutLogInfo);
    qDebug() << "Std Info: " + s_StdOutLogInfo;
}

void MainController::processErrorLogInfo(){
    b_StdErrLogInfo += getWinLogs.readAllStandardError().trimmed();
    s_StdErrLogInfo = QString(b_StdErrLogInfo);
    qDebug() << "Error Info: " + s_StdErrLogInfo;
}

void MainController::sendLogInfoToQml(){
    qDebug() <<"Sending info to QML: " + s_StdOutLogInfo;
}
