#ifndef ELIGIBILITYSERVICEIMPL_H
#define ELIGIBILITYSERVICEIMPL_H

#include<eligibilityservice.h>

class EligibilityServiceImpl: public EligibilityService
{
    Q_OBJECT
public :
    ~EligibilityServiceImpl() {}
    void fetchEligibilityStatus(quint32 accountNumber);

};

#endif // ELIGIBILITYSERVICEIMPL_H
