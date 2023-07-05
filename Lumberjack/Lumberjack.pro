QT += quick
QT += widgets
QT += xml
QT += core

SOURCES += \
        main.cpp \
        maincontroller.cpp \
        tablemodel.cpp

resources.files = main.qml 
resources.prefix = /$${TARGET}

RESOURCES += resources \
    images.qrc

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
    maincontroller.h \
    tablemodel.h

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/Aspose.Words.Cpp/lib/x64/release/ -lAspose.Words.Cpp_vc14x64
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/Aspose.Words.Cpp/lib/x64/debug/ -lAspose.Words.Cpp_vc14x64

#INCLUDEPATH += $$PWD/Aspose.Words.Cpp/include/Aspose.Words.Cpp
#DEPENDPATH += $$PWD/Aspose.Words.Cpp/include/Aspose.Words.Cpp
