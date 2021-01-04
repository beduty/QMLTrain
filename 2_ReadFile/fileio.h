#ifndef FILEIO_H
#define FILEIO_H

// QML에서 파일을 읽고 쓰는 기능을 제공하지 않는다.
// C++엔진에서 파일을 읽고, QML로 넘겨주는 방식을 채택하였다.
#include <QObject>

class FileIO : public QObject
{
    Q_OBJECT

public:
    explicit FileIO(QObject *parent = nullptr);

    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_INVOKABLE QString read();
    Q_INVOKABLE bool write(const QString& data);

public:
    QString source() const;

public slots:
    void setSource(QString source);

signals:
    void sourceChanged(QString source);
    void error(const QString& msg);

private:
    QString m_source;
};

#endif // FILEIO_H
