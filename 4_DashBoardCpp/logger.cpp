#include "logger.h"
#include <QDebug>
CLogger::CLogger(QObject *parent) : QObject(parent)
{
    m_name = "";
    LogQStart();
}

CLogger::~CLogger()
{
    LogQStop();
}

void CLogger::test()
{
    for(int i =0 ; i < 100 ; i++)
    {
        logQ.enqueue("msgLog.toStdString()""");
        cvLog.notify_one();
    }
}

QString CLogger::getLog() const
{
    return m_msgLog;
}

QString CLogger::name() const
{
    return m_name;
}

void CLogger::setLog(QString msgLog)
{
    if (m_msgLog == msgLog || m_name == "")
        return;

    m_msgLog = msgLog;

    logQ.enqueue(msgLog.toStdString());
    cvLog.notify_one();
    emit changedLog(m_msgLog);
}

void CLogger::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit changedName(m_name);
}

void CLogger::LogQFunc()
{
    while (m_bLogQRun)
    {
        std::unique_lock<std::mutex> lk(mtxLog);
        cvLog.wait(lk, [&] { return !(logQ.size_approx() == 0) || !m_bLogQRun; });
        std::string strLog;
        if (logQ.try_dequeue(strLog))
        {
            QString szLogFileName = QString("%1.log").arg(m_name);
            std::string strLogFileName = szLogFileName.toStdString();
            auto my_logger = spdlog::basic_logger_mt("info", strLogFileName);
            my_logger->info(strLog);
            spdlog::shutdown();
        }
        lk.unlock();
    }
}

void CLogger::LogQStart()
{
    m_bLogQRun = true;
    m_LogQTread = std::shared_ptr<std::thread>(
        new std::thread(std::bind(&CLogger::LogQFunc, this))
     );
}

void CLogger::LogQStop()
{
    m_bLogQRun = false;
    cvLog.notify_all();
    if (m_LogQTread.get())
    {
        while (1)
        {
            if (m_LogQTread->joinable())
            {
                m_LogQTread->join();
                m_LogQTread.reset();
                break;
            }
//            while (::PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
//            {
//                ::TranslateMessage(&msg);
//                ::DispatchMessage(&msg);
//            }
        }
    }
}
