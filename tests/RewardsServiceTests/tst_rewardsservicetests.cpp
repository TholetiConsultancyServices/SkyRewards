#include <QtTest>

#include<eligibilityservice.h>
#include<eligibilityserviceimpl.h>
#include<rewardsserviceimpl.h>

// add necessary includes here

class RewardsServiceTests : public QObject
{
    Q_OBJECT

public:
    RewardsServiceTests();
    ~RewardsServiceTests();

private slots:
    void testRelevantRewardsReturnedWhenCustomerIsEligible();
    void testNoRewardsReturnedWhenCustomerIsNotEligible();
    void testNoRewardsReturnedWhenTechnicalFailureOccurs();
    void testNoRewardsAndInvalidAccountNumberReturnedWhenAccountNumberIsInvalid();

private:
    EligibilityService *m_eligibilityService;
    RewardsService *m_rewardsService;

};

RewardsServiceTests::RewardsServiceTests()
{
    m_eligibilityService = new EligibilityServiceImpl();
    m_rewardsService = new RewardsServiceImpl(m_eligibilityService);
}

RewardsServiceTests::~RewardsServiceTests()
{
    delete m_eligibilityService;
    delete m_rewardsService;
}

void RewardsServiceTests::testRelevantRewardsReturnedWhenCustomerIsEligible()
{
    QSignalSpy spy(m_rewardsService, SIGNAL(rewardsStatusReceived(QList<RewardsService::RewardType>, RewardsService::RewardsError*)));
    m_rewardsService->fetchRewards(123456, { RewardsService::CHANNELTYPE_MUSIC, RewardsService:: CHANNELTYPE_SPORTS });
    QCOMPARE(spy.isValid(), true);
    QList<RewardsService::RewardType> rewards = qvariant_cast<QList<RewardsService::RewardType>>(spy.at(0).at(0));

    QVERIFY(rewards.count() == 2);

    QVERIFY(rewards.contains(RewardsService::REWARDTYPE_KARAOKE_PRO_MICROPHONE) == true);
    QVERIFY(rewards.contains(RewardsService::REWARDTYPE_CHAMPIONS_LEAGUE_FINAL_TICKET) == true);
     QVERIFY(rewards.contains(RewardsService::REWARDTYPE_PIRATES_OF_THE_CARIBBEAN_COLLECTIONs) == false);
}

void RewardsServiceTests::testNoRewardsReturnedWhenCustomerIsNotEligible()
{
    QSignalSpy spy(m_rewardsService, SIGNAL(rewardsStatusReceived(QList<RewardsService::RewardType>, RewardsService::RewardsError*)));
    m_rewardsService->fetchRewards(234567, { RewardsService:: CHANNELTYPE_SPORTS });
    QCOMPARE(spy.isValid(), true);
    QList<RewardsService::RewardType> rewards = qvariant_cast<QList<RewardsService::RewardType>>(spy.at(0).at(0));

    QVERIFY(rewards.isEmpty() == true);
}

void RewardsServiceTests::testNoRewardsReturnedWhenTechnicalFailureOccurs()
{
    QSignalSpy spy(m_rewardsService, SIGNAL(rewardsStatusReceived(QList<RewardsService::RewardType>, RewardsService::RewardsError*)));
    m_rewardsService->fetchRewards(345678, { RewardsService:: CHANNELTYPE_SPORTS });
    QCOMPARE(spy.isValid(), true);
    QList<RewardsService::RewardType> rewards = qvariant_cast<QList<RewardsService::RewardType>>(spy.at(0).at(0));

    QVERIFY(rewards.isEmpty() == true);
}

void RewardsServiceTests::testNoRewardsAndInvalidAccountNumberReturnedWhenAccountNumberIsInvalid()
{
    QSignalSpy spy(m_rewardsService, SIGNAL(rewardsStatusReceived(QList<RewardsService::RewardType>, RewardsService::RewardsError*)));
    m_rewardsService->fetchRewards(1111, { RewardsService:: CHANNELTYPE_SPORTS });
    QCOMPARE(spy.isValid(), true);
    QList<RewardsService::RewardType> rewards = qvariant_cast<QList<RewardsService::RewardType>>(spy.at(0).at(0));
    RewardsService::RewardsError* error = qvariant_cast<RewardsService::RewardsError*>(spy.at(0).at(1));

    QVERIFY(rewards.isEmpty() == true);
    QVERIFY(*error == RewardsService::FETCH_REWARDS_ERROR_INVALID_ACCOUNT_NUMBER);
}

QTEST_APPLESS_MAIN(RewardsServiceTests)

#include "tst_rewardsservicetests.moc"
