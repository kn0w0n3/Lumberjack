#include "fileopsthread.h"

FileOpsThread::FileOpsThread(QThread *parent) : QThread(parent){
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

void FileOpsThread::run(){
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
        QString numToString = QString::number(numOfSecEvents);
        QByteArray tArray = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
        QJsonObject jsonObject = json_doc.object();
        QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
        QString eventId = obdata["EventID"].toString();
        result += "Event ID: " + eventId + "\n";
    }
    if(_saveType == "refresh"){
        emit secEventNum2MainContrler(QString::number(numOfSecEvents));
    }
    numOfSecEvents = 0;
    secJsonObjects.clear();
}

void FileOpsThread::setSaveType(QString saveType_){
    _saveType = saveType_;
}
