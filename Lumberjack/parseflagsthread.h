#ifndef PARSEFLAGSTHREAD_H
#define PARSEFLAGSTHREAD_H
#include <QThread>
#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDomDocument>
#include <QXmlStreamReader>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QStringList>
#include <QStandardPaths>

class ParseFlagsThread : public QThread{
    Q_OBJECT

public:
    ParseFlagsThread(QThread *parent = 0);
    void run();
};

#endif // PARSEFLAGSTHREAD_H
