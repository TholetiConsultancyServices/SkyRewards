#ifndef MOCKELIGIBILITYSERVICE_H
#define MOCKELIGIBILITYSERVICE_H

#include<eligibilityservice.h>

class MockEligibilityService: public EligibilityService
{

    Q_OBJECT
public :
    ~MockEligibilityService() {}
    void fetchEligibilityStatus(quint32 accountNumber);

};

#endif // MOCKELIGIBILITYSERVICE_H
