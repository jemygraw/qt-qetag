#ifndef QNETAG_H
#define QNETAG_H
class QString;
class QByteArray;

class QNETag
{
private:
    const static int CHUNK_SIZE = 1<<22; //4M
public:
    QNETag();
    ~QNETag();
    QString UrlSafeBase64Encode(QByteArray data);
    QByteArray Sha1(QByteArray data);
    QString CalcETag(QString fileName);
};

#endif // QNETAG_H
