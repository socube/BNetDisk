#ifndef BDISKOPERATIONREQUEST_H
#define BDISKOPERATIONREQUEST_H

#include <QSharedDataPointer>
#include <QString>
#include <QUrl>
#include <QDateTime>

#include "BDiskTokenProvider.h"
#include "BDiskConst.h"

class BDiskBaseOperationRequestPriv;
class BDiskBaseOperationRequest
{
public:
    enum OperationType {
        OPERATION_GET = 0x0,
        OPERATION_POST,
        OPERATION_UNDEFINED
    };

    BDiskBaseOperationRequest();
    BDiskBaseOperationRequest(const BDiskBaseOperationRequest &other);
    virtual ~BDiskBaseOperationRequest();

    void initiate();
    void setBaseUrl(const QString &url);
    QUrl initUrl() const;
    OperationType operationType();

    void setParameters(const QString &key, const QString &value);

    void appendPostDataParameters(const QString &key, const QString &value);
    QHash<QString, QString> postDataParameters() const;
    QString postDataParameter(const QString &key, const QString &defaultValue = QString()) const;

    bool operator == (const BDiskBaseOperationRequest &other);
    bool operator != (const BDiskBaseOperationRequest &other);
    BDiskBaseOperationRequest &operator = (const BDiskBaseOperationRequest &other);
    BDiskBaseOperationRequest &operator()(const QString &key, const QString &value);

protected:
    virtual OperationType initOperationType();
    virtual void initParameters();
    void setUrlPath(const QString &path, const QString &tag = QString());

private:
    QSharedDataPointer<BDiskBaseOperationRequestPriv> d;
};

class BDiskOpListDir : public BDiskBaseOperationRequest
{
public:
    BDiskOpListDir()
        : BDiskBaseOperationRequest()
    {
        setUrlPath("list");
        initiate();
    }

    // BDiskBaseOperationRequest interface
protected:
    void initParameters() {
//        showempty=0
//        app_id=
//        logid=
        (*this)
        ("dir", "/")
//        ("page", "1") //empty will show all list
//        ("num", "100") //empty will show all list
        ("order", "time")
        ("desc", "1")
        ("channel", "chunlei")
        ("clienttype", "0")
        ("web", "1")
        ("bdstoken", BDiskTokenProvider::instance()->bdstoken())
        ("t", QString::number(QDateTime::currentMSecsSinceEpoch()))
        ;
    }
    OperationType initOperationType() {
        return OPERATION_GET;
    }
};

class BDisOpDownload : public BDiskBaseOperationRequest
{
public:
    BDisOpDownload()
        : BDiskBaseOperationRequest() {
        setBaseUrl(BDISK_URL_PCS_REST);
//        setUrlPath();
        initiate();

    }

    // BDiskBaseOperationRequest interface
protected:
    OperationType initOperationType() {
        return OPERATION_GET;
    }

    void initParameters() {
        (*this)
        ("method", "download")
        ("app_id", "250528")
        ("path", "")
        ;
    }
};

class BDiskOpPubShare : public BDiskBaseOperationRequest
{
public:
    BDiskOpPubShare()
        : BDiskBaseOperationRequest() {
        setBaseUrl("http://pan.baidu.com/share/set");
        initiate();
        appendPostDataParameters("fid_list", "[]"); // file or dir object fs_id
        appendPostDataParameters("schannel", "0");
        appendPostDataParameters("channel_list", "[]");
    }
    virtual ~BDiskOpPubShare() {}

    // BDiskBaseOperationRequest interface
protected:
    OperationType initOperationType() {
        return OPERATION_POST;
    }

    void initParameters() {
        (*this)
        ("channel", "chunlei")
        ("clienttype", "0")
        ("web", "1")
        ("app_id", "250528")  //去掉appid也可以实现分享，暂时不知道appid从何而来， 当前本机测试为250528
        ("bdstoken", "")
//        ("logid", "")
        ;
    }
};

class BDiskOpPrivShare : public BDiskBaseOperationRequest
{
public:
    BDiskOpPrivShare()
        : BDiskBaseOperationRequest() {
        setBaseUrl("http://pan.baidu.com/share/set");
        initiate();
        appendPostDataParameters("fid_list", "[]"); // file or dir object fs_id
        appendPostDataParameters("schannel", "4");
        appendPostDataParameters("channel_list", "[]");
        appendPostDataParameters("pwd", "bdpw");
    }
    virtual ~BDiskOpPrivShare() {}

    // BDiskBaseOperationRequest interface
protected:
    OperationType initOperationType() {
        return OPERATION_POST;
    }

    void initParameters() {
        (*this)
        ("channel", "chunlei")
        ("clienttype", "0")
        ("web", "1")
        ("app_id", "250528")  //去掉appid也可以实现分享，暂时不知道appid从何而来， 当前本机测试为250528
        ("bdstoken", "")
//        ("logid", "")
        ;
    }
};

#endif // BDISKOPERATIONREQUEST_H
