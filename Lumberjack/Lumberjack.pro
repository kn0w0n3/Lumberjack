QT += quick
QT += widgets
QT += xml
QT += core

SOURCES += \
        appeventcounterthread.cpp \
        archivecreatorthread.cpp \
        main.cpp \
        maincontroller.cpp \
        parseflagsthread.cpp \
        seceventcounterthread.cpp \
        syseventcounterthread.cpp \
        tablemodel.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}

RESOURCES += resources \
    images.qrc

RC_FILE = lumberjack.rc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

#win32 {
    #RC_FILE = lumberjack.rc
#}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    appeventcounterthread.h \
    archivecreatorthread.h \
    maincontroller.h \
    parseflagsthread.h \
    seceventcounterthread.h \
    syseventcounterthread.h \
    tablemodel.h
