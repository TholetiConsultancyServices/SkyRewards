#ifndef REWARDSSERVICEIMPL_H
#define REWARDSSERVICEIMPL_H

#include<rewardsservice.h>
#include<eligibilityservice.h>

class RewardsServiceImpl: public RewardsService
{
    Q_OBJECT
public:
     RewardsServiceImpl( EligibilityService *eligibilityService );
     ~RewardsServiceImpl() { }

    void fetchRewards(quint32 accountNumber, QList<ChannelType> subscribedChannels);

private:
    RewardsServiceImpl();
    QMap<quint32, QList<ChannelType>> m_accountToChannelsMap;

private slots:
    void handleEligibilityStatus(quint32 accountNumber, EligibilityService::EligibilityStatus);
};

#endif // REWARDSSERVICEIMPL_H
