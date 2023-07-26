#include "seceventcounterthread.h"

SecEventCounterThread::SecEventCounterThread(QThread *parent) : QThread(parent){
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

void SecEventCounterThread::run(){
    qDebug() << "In file ops thread run()........";
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
    }
    if(_saveType == "refresh"){
        emit secEventNum2MainContrler(QString::number(numOfSecEvents));
    }
    numOfSecEvents = 0;
    secJsonObjects.clear();
}

void SecEventCounterThread::setSaveType(QString saveType_){
    _saveType = saveType_;
}
