#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H
#include <QObject>
#include <QWidget>
#include <QProcess>
#include <QStringList>
#include <QDebug>

class MainController:  public QWidget{
    Q_OBJECT

public:
    MainController(QWidget *parent = nullptr);

signals:

public slots:
    void getLogInfo();
    void processLogInfo();
    void processStdOutLogInfo();
    void processErrorLogInfo();
    void sendLogInfoToQml();

private:
    QProcess getWinLogs;

    QByteArray b_StdOutLogInfo;
    QByteArray b_StdErrLogInfo;

    QString s_StdOutLogInfo;
    QString s_StdErrLogInfo;
    QString LogInfoText;


};

#endif // MAINCONTROLLER_H
