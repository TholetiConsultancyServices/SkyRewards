#include "eligibilityserviceimpl.h"
#include <QtCore>

static const QHash< quint32, EligibilityService::EligibilityStatus > k_customersEligibiltyStatusMap =
{
    {123456, EligibilityService::CUSTOMER_ELIGIBLE},
    {234567, EligibilityService::CUSTOMER_INELIGIBLE},
    {345678, EligibilityService::TECHNICAL_FAILURE}
 };


 void EligibilityServiceImpl:: fetchEligibilityStatus(quint32 accountNumber)
 {
    if (k_customersEligibiltyStatusMap.contains(accountNumber)) {
        emit eligibilityStatus (accountNumber, k_customersEligibiltyStatusMap[accountNumber]);
    } else {
        emit eligibilityStatus(accountNumber, EligibilityService::INVALID_ACCOUNT_NUMBER );
    }
 }


