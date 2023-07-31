#include "appeventcounterthread.h"

AppEventCounterThread::AppEventCounterThread(QThread *parent) : QThread(parent){
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

void AppEventCounterThread::run(){
    QFile file("C:/Lumberjack/json/application/application.json");
    if(!file.open(QIODevice::ReadOnly)){
        //qDebug() << "App file not open.......";
    }
    QTextStream in(&file);
    while (!in.atEnd()){
        appJsonObjects << in.readLine();
    }
    file.close();
    foreach(const QString &logEntry, appJsonObjects){
        numOfAppEvents++;
    }
    if(_saveType == "refresh"){
        emit appEventNum2MainContrler(QString::number(numOfAppEvents));
    }
    numOfAppEvents = 0;
    appJsonObjects.clear();
}

void AppEventCounterThread::setSaveType(QString saveType_){
    _saveType = saveType_;
}
