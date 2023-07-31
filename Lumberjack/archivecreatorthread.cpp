#include "archivecreatorthread.h"

ArchiveCreatorThread::ArchiveCreatorThread(QThread *parent) : QThread(parent){
    docsFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
}

void ArchiveCreatorThread::run(){
    QString currentDateTime = QDateTime::currentDateTime().toString("MM-dd-yyyy_h-mm-ss-ap");
    QFile secJsonFile("C:/Lumberjack/json/security/security.json");
    QFile sysJsonFile("C:/Lumberjack/json/system/system.json");
    QFile appJsonFile("C:/Lumberjack/json/application/application.json");
    QFile archiveFile("C:/Lumberjack/audit/archived_reports/audit_" + currentDateTime + ".json");

    if(secJsonFile.open(QIODevice::ReadOnly)){
        QTextStream in(&secJsonFile);
        while (!in.atEnd()){
            combineAllreports = in.readAll().trimmed() + "\n";
        }
        secJsonFile.close();

        if(sysJsonFile.open(QIODevice::ReadOnly)){
            QTextStream in(&sysJsonFile);
            while (!in.atEnd()){
                combineAllreports += in.readAll().trimmed() + "\n";
            }
            sysJsonFile.close();
        }
        if(appJsonFile.open(QIODevice::ReadOnly)){
            QTextStream in(&appJsonFile);
            while (!in.atEnd()){
                combineAllreports += in.readAll().trimmed();
            }
            appJsonFile.close();
        }
    }
    if(archiveFile.open(QIODevice::WriteOnly | QIODevice::Append)){
        QTextStream out(&archiveFile);
        out << combineAllreports;
        archiveFile.close();
    }
    else{
        //error
    }
    emit archiveCreationStatus(currentDateTime);
}

