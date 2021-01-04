#ifndef CLOGGER_H
#define CLOGGER_H

#include <QObject>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "concurrentqueue/concurrentqueue.h"
#include <string.h>
#include <condition_variable>
#include <memory>
#include <thread>

class CLogger : public QObject
{
    Q_OBJECT
public:
    explicit CLogger(QObject *parent = nullptr);
    ~CLogger();
    Q_PROPERTY(QString msgLog READ getLog WRITE setLog NOTIFY changedLog)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY changedName)
    Q_INVOKABLE void test();
    QString getLog() const;
    QString name() const;

public slots:
    void setLog(QString msgLog);
    void setName(QString name);

signals:
    void changedLog(QString msgLog);
    void changedName(QString name);

private:
    std::mutex mtxLog;
    std::condition_variable cvLog;
    moodycamel::ConcurrentQueue<std::string> logQ;
    std::shared_ptr< std::thread > m_LogQTread;
    void LogQFunc();
    void LogQStart();
    void LogQStop();
    bool m_bLogQRun = false;

    QString m_msgLog;
    QString m_name;
};

#endif // CLOGGER_H
