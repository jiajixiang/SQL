#include <QFileInfo>
#include "client.h"

FtpManager::FtpManager(QObject *parent)
    : QObject(parent)
{
    // 设置协议
    m_pUrl.setScheme("ftp");
    m_pUrl.setUserName("ftpname");
    m_pUrl.setPassword("123456");
    m_pUrl.setHost("118.89.51.72");
    m_pUrl.setPort(21);
}



// 上传文件
void FtpManager::put(const QString &fileName, const QString &path)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();

    m_pUrl.setPath(path);
    QNetworkReply *pReply = m_manager.put(QNetworkRequest(m_pUrl), data);

    connect(pReply, SIGNAL(uploadProgress(qint64, qint64)), this, SIGNAL(uploadProgress(qint64, qint64)));
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));
}

// 下载文件
void FtpManager::get(const QString &path, const QString &fileName)
{
    QFileInfo info;
    info.setFile(fileName);

    m_file.setFileName(fileName);
    m_file.open(QIODevice::WriteOnly | QIODevice::Append);
    m_pUrl.setPath(path);

    QNetworkReply *pReply = m_manager.get(QNetworkRequest(m_pUrl));

    connect(pReply, SIGNAL(finished()), this, SLOT(finished()));
    connect(pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));
}

// 下载过程中写文件
void FtpManager::finished()
{
    QNetworkReply *pReply = qobject_cast<QNetworkReply *>(sender());
    switch (pReply->error())
    {
    case QNetworkReply::NoError :
    {
        m_file.write(pReply->readAll());
        m_file.flush();
    }
        break;
    default:
        break;
    }

    m_file.close();
    pReply->deleteLater();
}
