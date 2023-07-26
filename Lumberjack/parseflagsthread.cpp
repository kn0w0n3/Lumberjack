#include "parseflagsthread.h"

ParseFlagsThread::ParseFlagsThread(QThread *parent) : QThread(parent){

}

void ParseFlagsThread::run(){
    qDebug() << "In parse flags thread............................";
    emit flagParsingStatus2Qml("Parsing flag data, please wait...");
    QFile currentFlagsFile("C:/Lumberjack/flags/flags.txt");
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
        qDebug() << "Flag file not open...";
    }

    //Get JSON archive logs
    if (archiveFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Getting logs to compare.....";
        QTextStream in(&archiveFile);
        while (!in.atEnd()){
            logsToCompareToFlags << in.readLine().trimmed();
        }
        archiveFile.close();
    }else{
        qDebug() << "Archive file not open...";
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
                    //qDebug() << "Save type is: " + saveType;
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
        qDebug() << "Emitting addLogFileToComboBox";
        emit addLogFileToComboBox("audit_" + fileName + ".json");
    }
    if(bType != "updateFlags" && bType != "live"){
        qDebug() << "Clearing logs after scheduled backup.......";
        //TODO: Check clear backup logs switch status before clearing
        //clearEventLogs();
    }
    if(bType == "updateFlags"){
        refreshInProgress = false;
        emit updateRefreshInProgress(refreshInProgress);
        qDebug() << "Refresh in progress = false";
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
