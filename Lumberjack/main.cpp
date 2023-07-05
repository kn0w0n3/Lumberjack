#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlContext>

#include "maincontroller.h"
#include "tablemodel.h"

int main(int argc, char *argv[]){

    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    //QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling)

    MainController mainController;
    engine.rootContext()->setContextProperty("mainController", &mainController);

    qmlRegisterType<TableModel>("TableModel", 0, 1, "TableModel");

    const QUrl url(u"qrc:/Lumberjack/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);
    app.setWindowIcon(QIcon("C:/Lumberjack/images/appicon.png"));
    //app.setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    //setWindowFlag(Qt::MaximizeUsingFullscreenGeometryHint,true) ;
     //QQuickView::setResizeMode(QQuickView::SizeRootObjectToView)

    return app.exec();
}
