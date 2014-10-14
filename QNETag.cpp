#include "QNETag.h"
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QCryptographicHash>
#include <QFileInfo>
#include <QDataStream>
#include <QDebug>
QNETag::QNETag()
{
}
QNETag::~QNETag()
{
}

QString QNETag::UrlSafeBase64Encode(QByteArray data)
{
    QByteArray encodedData = data.toBase64();
    QString encodedStr = QString(encodedData);
    encodedStr = encodedStr.replace("+","-").replace("/","_");
    return encodedStr;
}

QByteArray QNETag::Sha1(QByteArray data)
{
    QCryptographicHash sha1Hash(QCryptographicHash::Sha1);
    sha1Hash.addData(data);
    return sha1Hash.result();
}

/*
    This method will return an non-empty string if the file exists and readable
*/
QString QNETag::CalcETag(QString fileName)
{
    QString etag = "";
    QFileInfo fi(fileName);
    if(fi.exists() && fi.permission(QFile::ReadUser))
    {
        QFile fh(fileName);
        bool opened = fh.open(QIODevice::ReadOnly);
        if (opened){
            qint64 fileLen = fh.size();
            if(fileLen <= CHUNK_SIZE)
            {
                QByteArray fileData = fh.readAll();
                QByteArray sha1Data = Sha1(fileData);
                QByteArray hashData = sha1Data;
                hashData.insert(0,0x16);
                etag = UrlSafeBase64Encode(hashData);
            }
            else
            {
                int chunkCount = fileLen / CHUNK_SIZE;
                if(fileLen % CHUNK_SIZE != 0)
                {
                    chunkCount += 1;
                }
                QByteArray sha1AllData;
                for(int i=0; i<chunkCount; i++)
                {
                    qint64 chunkSize = CHUNK_SIZE;
                    if(i == chunkCount-1)
                    {
                        chunkSize = fileLen-(chunkCount-1)*CHUNK_SIZE;
                    }
                    QByteArray buf = QByteArray(chunkSize,' ');
                    fh.read(buf.data(),chunkSize);
                    QByteArray sha1Data = Sha1(buf);
                    sha1AllData.append(sha1Data);
                }
                QByteArray hashData = Sha1(sha1AllData);
                hashData.insert(0,0x96);
                etag = UrlSafeBase64Encode(hashData);
            }
            fh.close();
        }
    }
    return etag;
}
