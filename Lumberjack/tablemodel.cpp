#include "tablemodel.h"

TableModel::TableModel(QObject *parent) : QAbstractTableModel(parent){
    loadData();

}

int TableModel::rowCount(const QModelIndex &) const{
    return table.size(); //num of rows
}

int TableModel::columnCount(const QModelIndex &) const{
    return table.at(0).size(); //num of columns
}

QVariant TableModel::data(const QModelIndex &index, int role) const{
    switch (role) {
    case TableDataRole:{
        return table.at(index.row()).at(index.column());
    }
    case HeadingRole:{
        if(index.row()==0){
            return true;
        }
       // else if(table.value().contains("Security") && index.row()!= 0){
           // return true;
        //}
        else{
            return false;
        }
    }
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const{

    QHash<int,QByteArray> roles;
    roles[TableDataRole] = "tabledata";
    roles[HeadingRole] = "heading";
    return roles;

    //return { {Qt::DisplayRole, "display"} };
}

void TableModel::loadData(){
    table.append({"Event ID", "Computer Name", "Channel", "Time Created"});
   // table.setSpan(2,1,1,1);


    table.append({"", "", "Security", ""});
    table.append({"153000", "DESKTOP-16CCCDN", "Security", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});
    table.append({"1200", "DESKTOP-16CCCDN", "System", "2022-08-22 06:15:57.4070168"});
    table.append({"153000", "DESKTOP-16CCCDN", "System", "2022-09-22 069:15:57.4070168"});

}
