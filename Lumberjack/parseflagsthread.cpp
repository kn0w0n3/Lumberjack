#include "parseflagsthread.h"

ParseFlagsThread::ParseFlagsThread(QThread *parent) : QThread(parent){

}

void ParseFlagsThread::run(){
    emit flagParsingStatus2Qml("Parsing flag data, please wait...");
    QFile currentFlagsFile("C:/Lumberjack/flags/flags.txt");
    QFile clearLogsStatusFile("C:/Lumberjack/settings/clearlogs/clearlogs.txt");
    QFile archiveFile("C:/Lumberjack/audit/archived_reports/audit_" + fileName + ".json");

    //Get the list of flags
    if (currentFlagsFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&currentFlagsFile);
        while(!in.atEnd()){
            flagParseList << in.readLine().trimmed();
        }
        currentFlagsFile.close();
    }
    else{
        //qDebug() << "Flag file not open...";
    }

    //Get JSON archive logs
    if (archiveFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&archiveFile);
        while (!in.atEnd()){
            logsToCompareToFlags << in.readLine().trimmed();
        }
        archiveFile.close();
    }else{
        //qDebug() << "Archive file not open...";
    }

    //compare the flags to event IDs from the archive logs
    foreach (const QString &logEntry, logsToCompareToFlags) {
        QByteArray tArray_G = logEntry.trimmed().toLocal8Bit();
        QJsonDocument json_doc_G = QJsonDocument::fromJson(tArray_G);
        QJsonObject jsonObject_G = json_doc_G.object();
        QJsonObject obdata_G = jsonObject_G.value("Event").toObject().value("System").toObject();
        QString eventId_G = obdata_G["EventID"].toString().trimmed();
        foreach (const QString &flag, flagParseList) {
            if(flag == eventId_G){
                if(bType == "updateFlags"){
                    flagCounter++;
                    emit flagCount(QString::number(flagCounter));

                }else{

                    if (archiveFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
                        QTextStream out(&archiveFile);
                        out << logEntry + "\n";
                    }
                }
                archiveFile.close();
            }
        }
    }
    if(bType != "updateFlags"){
        emit addLogFileToComboBox("audit_" + fileName + ".json");
    }
    if(bType != "updateFlags" && bType != "live"){

        //Get the clear logs switch saved status
        if (clearLogsStatusFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&currentFlagsFile);
            while(!in.atEnd()){
                clearLogsSwitchStatus = in.readLine().trimmed();
            }
            currentFlagsFile.close();
        }
        else{
            //error
        }

        //If clear logs switch is on: clear the event logs
        if(clearLogsSwitchStatus == "true"){
            emit clearEventLogs();
        }
    }
    if(bType == "updateFlags"){
        refreshInProgress = false;
        emit updateRefreshInProgress(refreshInProgress);
        archiveFile.remove();
    }
    if(bType == "live"){
        emit liveBkupStatsDoneToQml("Live backup completed @ " +  QDateTime::currentDateTime().toString("MM/dd/yyyy h:mm:ss ap"));
    }
    flagCounter = 0;
    emit flagParsingDone(1);
}

void ParseFlagsThread::setData(QString fName, QString backupType, bool _refreshStatus){
    fileName = fName;
    bType = backupType;
    refreshInProgress = _refreshStatus;
}
