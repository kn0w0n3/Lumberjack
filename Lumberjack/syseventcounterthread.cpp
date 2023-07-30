#include "syseventcounterthread.h"

SysEventCounterThread::SysEventCounterThread(QThread *parent) : QThread(parent){
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

void SysEventCounterThread::run(){
    QFile file(docsFolder + "/Lumberjack/json/system/system.json");
    if(!file.open(QIODevice::ReadOnly)){
        //qDebug() << "Sys file not open.......";
    }
    QTextStream in(&file);
    while (!in.atEnd()){
        sysJsonObjects << in.readLine();
    }
    file.close();
    foreach(const QString &logEntry, sysJsonObjects){
        numOfSysEvents++;
    }
    if(_saveType == "refresh"){
        emit sysEventNum2MainContrler(QString::number(numOfSysEvents));
    }
    numOfSysEvents = 0;
    sysJsonObjects.clear();
}

void SysEventCounterThread::setSaveType(QString saveType_){
    _saveType = saveType_;
}
