#include "fileio.h"
#include <QFile>
#include <QTextStream>

FileIO::FileIO(QObject *parent) : QObject(parent)
{
}

QString FileIO::read()
{
    if(m_source.isEmpty()){
        emit error("source is empty");
        return QString();
    }

    QFile file(m_source);
    QString fileContent;
    if(file.open(QIODevice::ReadOnly)){
        QString line;
        QTextStream t(&file);
        do{
            line = t.readLine();
            fileContent += line;
        }while(!line.isNull());
        file.close();
    }
    else{
        emit error("Unable to open the file");
        return QString();
    }
    return fileContent;
}

bool FileIO::write(const QString &data)
{
    if(m_source.isEmpty())
        return false;

    QFile file(m_source);
    if(!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QTextStream out(&file);
    out << data;
    file.close();

    return  true;
}

QString FileIO::source() const
{
    return m_source;
}

void FileIO::setSource(QString source)
{
    if (m_source == source)
        return;

    m_source = source;
    emit sourceChanged(m_source);
}
