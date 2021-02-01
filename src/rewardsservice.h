#ifndef REWARDSSERVICE_H
#define REWARDSSERVICE_H

#endif // REWARDSSERVICE_H
#include<QtCore>

class EligibilityService;

class RewardsService: public QObject
{
    Q_OBJECT
public:
    RewardsService(EligibilityService *eligibilityService): m_eligibilityService( eligibilityService ) {}
    virtual ~RewardsService() {}

    enum ChannelType {
         CHANNELTYPE_SPORTS,
         CHANNELTYPE_KIDS,
         CHANNELTYPE_MUSIC,
         CHANNELTYPE_NEWS,
         CHANNELTYPE_MOVIES,
    };

    enum RewardType {
        REWARDTYPE_NONE,
        REWARDTYPE_CHAMPIONS_LEAGUE_FINAL_TICKET,
        REWARDTYPE_KARAOKE_PRO_MICROPHONE,
        REWARDTYPE_PIRATES_OF_THE_CARIBBEAN_COLLECTIONs
    };

    enum RewardsError {
        FETCH_REWARDS_ERROR_INVALID_ACCOUNT_NUMBER,
        FETCH_REWARDS_ERROR_GENERIC

    };

    virtual void fetchRewards(quint32 accountNumber, QList<ChannelType> subscribedChannels) = 0;

signals:
    void rewardsStatusReceived(QList<RewardsService::RewardType> rewards, RewardsService::RewardsError* error);


protected:
    EligibilityService *m_eligibilityService;

    static inline const QHash<ChannelType, RewardType> k_channelRewardMap = {
        {  CHANNELTYPE_SPORTS, REWARDTYPE_CHAMPIONS_LEAGUE_FINAL_TICKET },
        {  CHANNELTYPE_KIDS, REWARDTYPE_NONE },
        {  CHANNELTYPE_MUSIC, REWARDTYPE_KARAOKE_PRO_MICROPHONE },
        {  CHANNELTYPE_NEWS, REWARDTYPE_NONE },
        {  CHANNELTYPE_MOVIES, REWARDTYPE_PIRATES_OF_THE_CARIBBEAN_COLLECTIONs }
    };
};
