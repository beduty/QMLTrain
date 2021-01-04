QT += quick

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        logger.cpp \
        main.cpp

RESOURCES += qml.qrc
QML_IMPORT_PATH =
QML_DESIGNER_IMPORT_PATH =
INCLUDEPATH += $$PWD/dependency/concurrentqueue/include
INCLUDEPATH += $$PWD/dependency/spdlog/include
LIBS += $$PWD/dependency/spdlog/debug/lib/fmtd.lib
LIBS += $$PWD/dependency/spdlog/debug/lib/spdlogd.lib
#LIBS += $$PWD/dependency/spdlog/release/lib/fmt.lib
#LIBS += $$PWD/dependency/spdlog/release/lib/spdlog.lib

#LIBS += C:/Users/jungt/Documents/SrcTreeRepo/QMLTrain/4_DashBoardCpp/dependency/spdlog/debug/lib/fmtd.lib \ C:/Users/jungt/Documents/SrcTreeRepo/QMLTrain/4_DashBoardCpp/dependency/spdlog/debug/lib/spdlogd.lib
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    logger.h

