#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QTableView>
#include <QModelIndex>
#include <QVariant>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QThread>

class TableModel : public QAbstractTableModel{
    Q_OBJECT

   // enum TableRoles{
        //TableDataRole = Qt::UserRole + 1,
        //HeadingRole
   // };

public:
    explicit TableModel(QObject *parent = nullptr);

signals:

public slots:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    void loadHeaderData();
    bool removeRows(int, int, const QModelIndex &parent) override;
    bool insertRows(int , int , const QModelIndex &parent) override;
    //void clearTable();
    void getSelectedData(QString);


private:
    QVector<QVector<QString>> table;
    QStringList eventEntryList;
    QStringList changeFileList;
    int rowCounter = 0;
    //QList<QList<QVariant>> m_data;
    QString selectedFile = "";

    bool sysHeaderSet = false;
    bool appHeaderSet = false;
    bool secHeaderSet = false;
    bool mainHeaderSet = false;
    bool flagsHeaderSet = false;

};

#endif // TABLEMODEL_H
