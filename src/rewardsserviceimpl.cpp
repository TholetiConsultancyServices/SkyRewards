#include<QtCore>
#include "rewardsserviceimpl.h"

RewardsServiceImpl::RewardsServiceImpl( EligibilityService *eligibilityService )
    : RewardsService( eligibilityService )
{
    connect(m_eligibilityService, &EligibilityService::eligibilityStatus,
            this, &RewardsServiceImpl::handleEligibilityStatus);
}

void RewardsServiceImpl::fetchRewards(quint32 accountNumber, QList<RewardsService::ChannelType> subscribedChannels)
{
    m_accountToChannelsMap.insert(accountNumber, subscribedChannels);
    m_eligibilityService->fetchEligibilityStatus(accountNumber);
}


void RewardsServiceImpl:: handleEligibilityStatus(quint32 accountNumber, EligibilityService::EligibilityStatus status)
{
     QList<RewardsService::RewardType> rewards;
    switch (status) {
    case EligibilityService:: CUSTOMER_ELIGIBLE: {
        QList<RewardsService::ChannelType> portfolio = m_accountToChannelsMap.value(accountNumber);
        for(int index = 0; index < portfolio.count(); index++) {
            RewardType type = k_channelRewardMap[portfolio[index]];
            rewards.append(type);
        }

        emit rewardsStatusReceived(rewards, nullptr);
        break;
    }
    case EligibilityService::CUSTOMER_INELIGIBLE:
    case EligibilityService:: TECHNICAL_FAILURE:
        emit rewardsStatusReceived(rewards, nullptr);
        break;
    case EligibilityService::INVALID_ACCOUNT_NUMBER:
        RewardsError *error = new RewardsError;
        *error = RewardsService::FETCH_REWARDS_ERROR_INVALID_ACCOUNT_NUMBER;
        emit rewardsStatusReceived(rewards, error);
        break;
       }

    m_accountToChannelsMap.remove(accountNumber);
}


