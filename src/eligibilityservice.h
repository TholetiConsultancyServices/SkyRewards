#ifndef ELIGIBILITYSERVICE_H
#define ELIGIBILITYSERVICE_H

#include <QObject>

class EligibilityService : public QObject
{
    Q_OBJECT
public:
    virtual ~EligibilityService() {}

    enum EligibilityStatus
    {
        CUSTOMER_ELIGIBLE,
        CUSTOMER_INELIGIBLE,
        TECHNICAL_FAILURE,
        INVALID_ACCOUNT_NUMBER
    };

    virtual void fetchEligibilityStatus(quint32 accountNumber) = 0;

signals:
    void eligibilityStatus(quint32 accountNumber, EligibilityService::EligibilityStatus);
};


#endif // ELIGIBILITYSERVICE_H
