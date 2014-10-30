#ifndef asynPortClient_H
#define asynPortClient_H

#include <epicsTypes.h>
#include <epicsString.h>

#include <asynDriver.h>
#include <asynInt32.h>
#include <asynInt32SyncIO.h>
#include <asynUInt32Digital.h>
#include <asynUInt32DigitalSyncIO.h>
#include <asynFloat64.h>
#include <asynFloat64SyncIO.h>
#include <asynOctet.h>
#include <asynOctetSyncIO.h>
#include <asynInt8Array.h>
#include <asynInt8ArraySyncIO.h>
#include <asynInt16Array.h>
#include <asynInt16ArraySyncIO.h>
#include <asynInt32Array.h>
#include <asynInt32ArraySyncIO.h>
#include <asynFloat32Array.h>
#include <asynFloat32ArraySyncIO.h>
#include <asynFloat64Array.h>
#include <asynFloat64ArraySyncIO.h>
#include <asynGenericPointer.h>
#include <asynGenericPointerSyncIO.h>

#define DEFAULT_TIMEOUT 1.0


class asynClient {
public:
    asynClient(const char *portName, int addr, const char* asynInterfaceType, const char *drvInfo, double timeout);
    virtual ~asynClient();
    void setTimeout(double timeout)
        { timeout_ = timeout; };
    void report(FILE *fp, int details);
protected:
    asynUser *pasynUser_;
    asynUser *pasynUserSyncIO_;
    asynInterface *pasynInterface_;
    double timeout_;
    char *portName_;
    int addr_;
    char *asynInterfaceType_;
    char *drvInfo_;
    void *drvPvt;
    void *interruptPvt_;
};


class asynInt32Client : public asynClient {
public:
    asynInt32Client(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT)
    : asynClient(portName, addr, asynInt32Type, drvInfo, timeout) {
        pInterface_ = (asynInt32 *)pasynInterface_->pinterface;
        if (pasynInt32SyncIO->connect(portName, addr, &pasynUserSyncIO_, drvInfo)) 
            throw std::runtime_error(std::string("pasynInt32SyncIO->connect failed"));
    };
    virtual ~asynInt32Client() { 
        pasynInt32SyncIO->disconnect(pasynUserSyncIO_); 
    }; 
    virtual asynStatus read(epicsInt32 *value) { 
        return pasynInt32SyncIO->read(pasynUserSyncIO_, value, timeout_);
    };
    virtual asynStatus write(epicsInt32 value) { 
        return pasynInt32SyncIO->write(pasynUserSyncIO_, value, timeout_); 
    };
    virtual asynStatus getBounds(epicsInt32 *low, epicsInt32 *high) { 
        return pasynInt32SyncIO->getBounds(pasynUserSyncIO_, low, high); 
    };
    virtual asynStatus registerInterruptUser(interruptCallbackInt32 pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, &interruptPvt_); 
    };
private:
    asynInt32 *pInterface_;
};


class asynUInt32DigitalClient : public asynClient {
public:
    asynUInt32DigitalClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT)
    : asynClient(portName, addr, asynUInt32DigitalType, drvInfo, timeout) {
        pInterface_ = (asynUInt32Digital *)pasynInterface_->pinterface;
        if (pasynInt32SyncIO->connect(portName, addr, &pasynUserSyncIO_, drvInfo))
            throw std::runtime_error(std::string("pasynInt32SyncIO->connect failed"));
    };
    virtual ~asynUInt32DigitalClient() {
        pasynUInt32DigitalSyncIO->disconnect(pasynUserSyncIO_); 
    }; 
    virtual asynStatus read(epicsUInt32 *value, epicsUInt32 mask) { 
        return pasynUInt32DigitalSyncIO->read(pasynUserSyncIO_, value, mask, timeout_); 
    };
    virtual asynStatus write(epicsUInt32 value, epicsUInt32 mask){ 
        return pasynUInt32DigitalSyncIO->write(pasynUserSyncIO_, value, mask, timeout_); 
    };
    virtual asynStatus setInterrupt(epicsUInt32 mask, interruptReason reason) { 
        return pasynUInt32DigitalSyncIO->setInterrupt(pasynUserSyncIO_, mask, reason, timeout_); 
    };
    virtual asynStatus clearInterrupt(epicsUInt32 mask) { 
        return pasynUInt32DigitalSyncIO->clearInterrupt(pasynUserSyncIO_, mask, timeout_); 
    };
    virtual asynStatus getInterrupt(epicsUInt32 *mask, interruptReason reason) { 
        return pasynUInt32DigitalSyncIO->getInterrupt(pasynUserSyncIO_, mask, reason, timeout_); 
    };
    virtual asynStatus registerInterruptUser(interruptCallbackUInt32Digital pCallback, epicsUInt32 mask) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, mask, &interruptPvt_); 
    };
private:
    asynUInt32Digital *pInterface_;
};


class asynFloat64Client : public asynClient {
public:
    asynFloat64Client(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT)
    : asynClient(portName, addr, asynFloat64Type, drvInfo, timeout) {
        pInterface_ = (asynFloat64 *)pasynInterface_->pinterface;
        if (pasynFloat64SyncIO->connect(portName, addr, &pasynUserSyncIO_, drvInfo))
            throw std::runtime_error(std::string("pasynFloat64SyncIO->connect failed"));
    };
    virtual ~asynFloat64Client() { 
        pasynFloat64SyncIO->disconnect(pasynUserSyncIO_); 
    }; 
    virtual asynStatus read(epicsFloat64 *value) {
        return pasynFloat64SyncIO->read(pasynUserSyncIO_, value, timeout_); 
    };
    virtual asynStatus write(epicsFloat64 value) { 
        return pasynFloat64SyncIO->write(pasynUserSyncIO_, value, timeout_); 
    };
    virtual asynStatus registerInterruptUser(interruptCallbackFloat64 pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, &interruptPvt_); 
    };
private:
    asynFloat64 *pInterface_;
};


class asynOctetClient : public asynClient {
public:
    asynOctetClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT)
    : asynClient(portName, addr, asynOctetType, drvInfo, timeout) {
        pInterface_ = (asynOctet *)pasynInterface_->pinterface;
        if (pasynOctetSyncIO->connect(portName, addr, &pasynUserSyncIO_, drvInfo)) 
            throw std::runtime_error(std::string("pasynOctetSyncIO->connect failed"));
    };
    virtual ~asynOctetClient() { 
        pasynOctetSyncIO->disconnect(pasynUserSyncIO_); 
    }; 
    virtual asynStatus write(const char *buffer, size_t bufferLen, size_t *nActual) { 
        return pasynOctetSyncIO->write(pasynUserSyncIO_, buffer, bufferLen, timeout_, nActual); 
    };
    virtual asynStatus read(char *buffer, size_t bufferLen, size_t *nActual, int *eomReason) {
        return pasynOctetSyncIO->read(pasynUserSyncIO_, buffer, bufferLen, timeout_, nActual, eomReason); 
    };
    virtual asynStatus writeRead(const char *writeBuffer, size_t writeBufferLen, char *readBuffer, size_t readBufferLen, 
                                 size_t *nBytesOut, size_t *nBytesIn, int *eomReason) { 
        return pasynOctetSyncIO->writeRead(pasynUserSyncIO_, writeBuffer, writeBufferLen, readBuffer, readBufferLen,
                                           timeout_, nBytesOut, nBytesIn, eomReason); 
    };
    virtual asynStatus flush() { 
        return pasynOctetSyncIO->flush(pasynUserSyncIO_); 
    };
    virtual asynStatus setInputEos(const char *eos, int eosLen) { 
        return pasynOctetSyncIO->setInputEos(pasynUserSyncIO_, eos, eosLen); 
    };
    virtual asynStatus getInputEos(char *eos, int eosSize, int *eosLen) { 
        return pasynOctetSyncIO->getInputEos(pasynUserSyncIO_, eos, eosSize, eosLen); 
    };
    virtual asynStatus setOutputEos(const char *eos, int eosLen) { 
        return pasynOctetSyncIO->setOutputEos(pasynUserSyncIO_, eos, eosLen); 
    };
    virtual asynStatus getOutputEos(char *eos, int eosSize, int *eosLen) { 
        return pasynOctetSyncIO->getOutputEos(pasynUserSyncIO_, eos, eosSize, eosLen); 
    };
    virtual asynStatus registerInterruptUser(interruptCallbackOctet pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, &interruptPvt_); 
    };
private:
    asynOctet *pInterface_;
};
  

class asynInt8ArrayClient : public asynClient {
public:
    asynInt8ArrayClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynInt8ArrayClient() {
        pasynInt8ArraySyncIO->disconnect(pasynUserSyncIO_);
    };
    virtual asynStatus read(epicsInt8 *value, size_t nElements, size_t *nIn) {
        return pasynInt8ArraySyncIO->read(pasynUserSyncIO_, value, nElements, nIn, timeout_);
    };
    virtual asynStatus write(epicsInt8 *value, size_t nElements) {
        return pasynInt8ArraySyncIO->write(pasynUserSyncIO_, value, nElements, timeout_);
    };
    virtual asynStatus registerInterruptUser(interruptCallbackInt8Array pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                      pCallback, this, &interruptPvt_); 
    };
private:
    asynInt8Array *pInterface_;
};


class asynInt16ArrayClient : public asynClient {
public:
    asynInt16ArrayClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynInt16ArrayClient() {
        pasynInt16ArraySyncIO->disconnect(pasynUserSyncIO_);
    };
    virtual asynStatus read(epicsInt16 *value, size_t nElements, size_t *nIn) {
        return pasynInt16ArraySyncIO->read(pasynUserSyncIO_, value, nElements, nIn, timeout_);
    };
    virtual asynStatus write(epicsInt16 *value, size_t nElements) {
        return pasynInt16ArraySyncIO->write(pasynUserSyncIO_, value, nElements, timeout_);
    };
    virtual asynStatus registerInterruptUser(interruptCallbackInt16Array pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                       pCallback, this, &interruptPvt_); 
    };
private:
    asynInt16Array *pInterface_;
};


class asynInt32ArrayClient : public asynClient {
public:
    asynInt32ArrayClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynInt32ArrayClient() {
        pasynInt32ArraySyncIO->disconnect(pasynUserSyncIO_);
    };
    virtual asynStatus read(epicsInt32 *value, size_t nElements, size_t *nIn) {
        return pasynInt32ArraySyncIO->read(pasynUserSyncIO_, value, nElements, nIn, timeout_);
    };
    virtual asynStatus write(epicsInt32 *value, size_t nElements) {
        return pasynInt32ArraySyncIO->write(pasynUserSyncIO_, value, nElements, timeout_);
    };
    virtual asynStatus registerInterruptUser(interruptCallbackInt32Array pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, &interruptPvt_); 
    };
private:
    asynInt32Array *pInterface_;
};

class asynFloat32ArrayClient : public asynClient {
public:
    asynFloat32ArrayClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynFloat32ArrayClient() {
        pasynFloat32ArraySyncIO->disconnect(pasynUserSyncIO_);
    };
    virtual asynStatus read(epicsFloat32 *value, size_t nElements, size_t *nIn) {
        return pasynFloat32ArraySyncIO->read(pasynUserSyncIO_, value, nElements, nIn, timeout_);
    };
    virtual asynStatus write(epicsFloat32 *value, size_t nElements) {
        return pasynFloat32ArraySyncIO->write(pasynUserSyncIO_, value, nElements, timeout_);
    };
    virtual asynStatus registerInterruptUser(interruptCallbackFloat32Array pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, &interruptPvt_); 
    };
private:
    asynFloat32Array *pInterface_;
};


class asynFloat64ArrayClient : public asynClient {
public:
    asynFloat64ArrayClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynFloat64ArrayClient() {
        pasynFloat64ArraySyncIO->disconnect(pasynUserSyncIO_);
    };
    virtual asynStatus read(epicsFloat64 *value, size_t nElements, size_t *nIn) {
        return pasynFloat64ArraySyncIO->read(pasynUserSyncIO_, value, nElements, nIn, timeout_);
    };
    virtual asynStatus write(epicsFloat64 *value, size_t nElements) {
        return pasynFloat64ArraySyncIO->write(pasynUserSyncIO_, value, nElements, timeout_);
    };
    virtual asynStatus registerInterruptUser(interruptCallbackFloat64Array pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, &interruptPvt_); 
    };
private:
    asynFloat64Array *pInterface_;
};


class asynGenericPointerClient : public asynClient {
public:
    asynGenericPointerClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynGenericPointerClient();
    virtual asynStatus read(void *pointer) {
        return pasynGenericPointerSyncIO->read(pasynUserSyncIO_, pointer, timeout_);
    };
    virtual asynStatus write(void *pointer) {
        return pasynGenericPointerSyncIO->write(pasynUserSyncIO_, pointer, timeout_);
    };
    virtual asynStatus registerInterruptUser(interruptCallbackGenericPointer pCallback) { 
        return pInterface_->registerInterruptUser(pasynInterface_->drvPvt, pasynUser_,
                                                  pCallback, this, &interruptPvt_); 
    };
private:
    asynGenericPointer *pInterface_;
};


class asynOptionClient : public asynClient {
public:
    asynOptionClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynOptionClient();
    virtual asynStatus read(const char *key, char *value, int maxChars);
    virtual asynStatus write(const char *key, const char *value);
};


class asynEnumClient : public asynClient {
public:
    asynEnumClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynEnumClient();
    virtual asynStatus read(char *strings[], int values[], int severities[], size_t nElements, size_t *nIn);
    virtual asynStatus write(char *strings[], int values[], int severities[], size_t nElements);
};


class asynCommonClient : public asynClient {
public:
    asynCommonClient(const char *portName, int addr, const char *drvInfo, double timeout=DEFAULT_TIMEOUT);
    virtual ~asynCommonClient();
    virtual void report(FILE *fp, int details);
    virtual asynStatus connect();
    virtual asynStatus disconnect();
};  
    
#endif
