#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent){
    loadHeaderData();
}

int TableModel::rowCount(const QModelIndex &) const{
    return table.size();
}

int TableModel::columnCount(const QModelIndex &) const{
    return table.at(0).size(); //num of columns
}

QVariant TableModel::data(const QModelIndex &index, int role) const{
     qDebug() << "In data() tableModel.cpp: ";
     switch (role){
     case Qt::DisplayRole:
         return table.at(index.row()).at(index.column());
     default:
         break;
     }
     return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const{
    return {{Qt::DisplayRole, "display"}};
}

void TableModel::loadHeaderData(){
    rowCounter++;
    if(rowCounter == 1 && mainHeaderSet == false){
         mainHeaderSet = true;
         table.append({"Event ID", "Computer Name", "Channel", "Time Created"});
    }
    rowCounter = 0;
}

bool TableModel::removeRows(int position, int rows, const QModelIndex &parent){
    beginRemoveRows(QModelIndex(), position, position+rows-1);
    //remove rows from underlying data
    table.removeAt(position);
    endRemoveRows();
    return true;
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &parent){
    changeFileList.clear();
    qDebug() << "The selected file name is:" + selectedFile;
    //insert new rows to the underlying data
    QFile arachiveFile("C:/Lumberjack/audit/archived_reports/" + selectedFile);
    if(!arachiveFile.open(QIODevice::ReadOnly)){
      //error
    }
    QTextStream in(&arachiveFile);
    while (!in.atEnd()){
      changeFileList << in.readLine().trimmed();
    }
    arachiveFile.close();
          beginInsertRows(QModelIndex(), position, position+rows-1);
    foreach(const QString &logEntry, changeFileList){
      rowCounter++;

      QByteArray tArray = logEntry.trimmed().toLocal8Bit();
      QJsonDocument json_doc = QJsonDocument::fromJson(tArray);
      QJsonObject jsonObject = json_doc.object();
      QJsonObject obdata = jsonObject.value("Event").toObject().value("System").toObject();
      QJsonObject obdata2 = jsonObject.value("Event").toObject().value("System").toObject().value("TimeCreated").toObject();
      QString eventId = obdata["EventID"].toString();
      QString computerName = obdata["Computer"].toString();
      QString channel_ = obdata["Channel"].toString();
      QString timeCreated = obdata2["@SystemTime"].toString();

      if(rowCounter == 1 && mainHeaderSet == false){
            mainHeaderSet = true;
            table.append({"Event ID", "Computer Name", "Channel", "Time Created"});
            table.append({eventId, computerName, channel_, timeCreated});
      }
      else if(channel_ == "Security" && secHeaderSet == false){
            qDebug() << "In set security header.....";
            secHeaderSet = true;
            table.append({"", "", "", ""});
            table.append({eventId, computerName, channel_, timeCreated});
      }
      else if(channel_ == "System" && sysHeaderSet  == false){
            qDebug() << "In set system header.....";
            sysHeaderSet  = true;
            table.append({"", "", "", ""});
            table.append({eventId, computerName, channel_, timeCreated});
      }
      else if(channel_ == "Application" && appHeaderSet  == false){
            qDebug() << "In set application header.....";
            appHeaderSet  = true;
            table.append({"", "", "", ""});
            table.append({eventId, computerName, channel_, timeCreated});
      }
      else{
            table.append({eventId, computerName, channel_, timeCreated}); 
        }
    }
    secHeaderSet = false;
    sysHeaderSet  = false;
    appHeaderSet = false;
    flagsHeaderSet = false;
    endInsertRows();
    rowCounter = 0;
    return true;
}

void TableModel::getSelectedData(QString selectedData){
    selectedFile = selectedData;
}
