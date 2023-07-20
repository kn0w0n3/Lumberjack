#include "archivecreatorthread.h"

ArchiveCreatorThread::ArchiveCreatorThread(QThread *parent) : QThread(parent){
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);

}

void ArchiveCreatorThread::run(){
    qDebug() << "In Create Archive...........";
    QString currentDateTime = QDateTime::currentDateTime().toString("MM-dd-yyyy_h-mm-ss-ap");
    QFile secJsonFile(docsFolder + "/Lumberjack/json/security/security.json");
    QFile sysJsonFile(docsFolder + "/Lumberjack/json/system/system.json");
    QFile appJsonFile(docsFolder + "/Lumberjack/json/application/application.json");
    QFile archiveFile("C:/Lumberjack/audit/archived_reports/audit_" + currentDateTime + ".json");

    if(secJsonFile.open(QIODevice::ReadOnly)){
        qDebug() << "In Sec JSON file...........";
        QTextStream in(&secJsonFile);
        while (!in.atEnd()){
            combineAllreports = in.readAll().trimmed() + "\n";
            //qDebug() << "Combined reports is: " + combineAllreports;
        }
        secJsonFile.close();

        if(sysJsonFile.open(QIODevice::ReadOnly)){
            qDebug() << "In Sys JSON file...........";
            QTextStream in(&sysJsonFile);
            while (!in.atEnd()){
                combineAllreports += in.readAll().trimmed() + "\n";
            }
            sysJsonFile.close();
        }
        if(appJsonFile.open(QIODevice::ReadOnly)){
            qDebug() << "In App JSON file...........";
            QTextStream in(&appJsonFile);
            while (!in.atEnd()){
                combineAllreports += in.readAll().trimmed();
            }
            appJsonFile.close();
        }
    }
    if(archiveFile.open(QIODevice::WriteOnly | QIODevice::Append)){
        qDebug() << "In write archive file...........";
        QTextStream out(&archiveFile);
        out << combineAllreports;
        archiveFile.close();

        //parseFlags(currentDateTime, backupType);
    }
    else{
        //error
    }
    qDebug() << "Emitting archive creation status";
    emit archiveCreationStatus(currentDateTime);
}

