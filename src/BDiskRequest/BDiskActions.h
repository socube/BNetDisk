#ifndef BDISKACTIONS_H
#define BDISKACTIONS_H

#include "BDiskBaseRequest.h"
#include "BDiskOperationRequest.h"

#define CREATE_OPR(Class) \
    Class op; \
    return dynamic_cast<BDiskBaseOperationRequest&>(op);

class BDiskActionListDir : public BDiskBaseRequest
{
    Q_OBJECT
public:
    explicit BDiskActionListDir(QObject *parent = 0) : BDiskBaseRequest(parent) {}

    // BDiskBaseRequest interface
protected:
    BDiskBaseOperationRequest operation() {
//        BDiskOpListDir op;
//        return dynamic_cast<BDiskBaseOperationRequest&>(op);
        CREATE_OPR(BDiskOpListDir);
    }
};


class BDiskActionPubShare : public BDiskBaseRequest
{
    Q_OBJECT
public:
    explicit BDiskActionPubShare(QObject *parent = 0): BDiskBaseRequest(parent) {}

    // BDiskBaseRequest interface
protected:
    BDiskBaseOperationRequest operation() {
        CREATE_OPR(BDiskOpPubShare);
    }
};

class BDiskActionPrivShare : public BDiskBaseRequest
{
    Q_OBJECT
public:
    explicit BDiskActionPrivShare(QObject *parent = 0): BDiskBaseRequest(parent) {}

    // BDiskBaseRequest interface
protected:
    BDiskBaseOperationRequest operation() {
        CREATE_OPR(BDiskOpPrivShare);
    }
};

#endif // BDISKACTIONS_H
