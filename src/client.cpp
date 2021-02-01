#include <QtWidgets>
#include "client.h"
#include<rewardsserviceimpl.h>
#include<eligibilityserviceimpl.h>

static const QHash< QString, RewardsService::ChannelType > k_channelsMap =
{
    {"Sports", RewardsService::CHANNELTYPE_SPORTS},
    {"Kids", RewardsService::CHANNELTYPE_KIDS},
    {"Music", RewardsService::CHANNELTYPE_MUSIC},
    {"News", RewardsService::CHANNELTYPE_NEWS},
    {"Movies", RewardsService::CHANNELTYPE_MOVIES},
};


static const QHash< RewardsService::RewardType, QString > k_rewardsMap =
{
    {RewardsService::REWARDTYPE_CHAMPIONS_LEAGUE_FINAL_TICKET, "CHAMPIONS_LEAGUE_FINAL_TICKET"},
    {RewardsService::REWARDTYPE_KARAOKE_PRO_MICROPHONE, "KARAOKE_PRO_MICROPHONE"},
    {RewardsService::REWARDTYPE_PIRATES_OF_THE_CARIBBEAN_COLLECTIONs,"PIRATES_OF_THE_CARIBBEAN_COLLECTIONs" },
};

static const QList<quint32> k_accountNumbers = {123456, 234567, 345678, 1111111};

static const QString k_accountNumbersInfo =
        "123456  - Eligible customer\n"
        "234567  - Not an eligible customer\n"
        "345678  - Technical failure\n"
        "1111111 - Invalid account number\n";

Client:: Client(QWidget *parent)
    : QWidget(parent),
      m_currentAccountNumberIndex( 0 )
{
    QLabel* accountsInfoLabel = new QLabel(k_accountNumbersInfo);

    QLabel *accountNumbersLabel = new QLabel("Account Number:");
    QComboBox *accountNumbersComboBox = new QComboBox();

    for (int i = 0; i < k_accountNumbers.size(); i++ ) {
        accountNumbersComboBox->addItem(QString::number(k_accountNumbers.at(i)));
    }

    connect(accountNumbersComboBox, &QComboBox::currentIndexChanged,
            this, &Client::accountNumberChanged);

    QLabel *channelsLabel = new QLabel("Channels:");
    QGroupBox *groupBox = new QGroupBox("");

    QGridLayout *groupBoxLayout = new QGridLayout;
    QHash< QString, RewardsService::ChannelType >::const_iterator i = k_channelsMap.constBegin();
    while (i != k_channelsMap.constEnd()) {
        QCheckBox *checkBox = new QCheckBox(i.key());
        connect(checkBox, &QCheckBox::toggled,
                this, &Client::checkBoxToggled);
        m_channelsCheckboxMap.insert(checkBox, i.value());
        groupBoxLayout->addWidget(checkBox);
        ++i;
    }

    groupBox->setLayout(groupBoxLayout);

    QLabel *rewardsLabel = new QLabel("Rewards");

    m_rewardsListWidget = new QListWidget(this);

    //! [layout]
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(accountsInfoLabel, 0, 0);
    mainLayout->addWidget(accountNumbersLabel, 1, 0);
    mainLayout->addWidget(accountNumbersComboBox, 1, 1);
    mainLayout->addWidget(channelsLabel, 2, 0);
    mainLayout->addWidget(groupBox, 2, 1);
    mainLayout->addWidget(rewardsLabel, 3, 0);
    mainLayout->addWidget(m_rewardsListWidget, 3, 1);
    //! [layout]

    //![setting the layout]
    setLayout(mainLayout);
    setWindowTitle(tr("Rewards Information"));

    EligibilityService *eligibilityService = new EligibilityServiceImpl();
    m_rewardsService = new RewardsServiceImpl(eligibilityService);

    connect(m_rewardsService, &RewardsService::rewardsStatusReceived,
            this, &Client::rewardsStatusReceived);
}

void Client:: accountNumberChanged(int index)
{
    QCheckBox * checkbox;
    foreach(checkbox, m_channelsCheckboxMap.keys()) {
        checkbox->setChecked(false);
    }
    m_currentAccountNumberIndex = index;
    m_rewardsListWidget->clear();
    getRewards();
}

void Client::checkBoxToggled()
{
    m_rewardsListWidget->clear();
    getRewards();
}

void Client::rewardsStatusReceived(QList<RewardsService::RewardType> rewards, RewardsService::RewardsError* error)
{
    QTextStream out(stdout);

    if (rewards.isEmpty()) {
        if (error == nullptr) {
            m_rewardsListWidget->addItem("No rewards are available");
        } else if (*error == RewardsService::FETCH_REWARDS_ERROR_INVALID_ACCOUNT_NUMBER) {
            m_rewardsListWidget->addItem("Invalid account number");
        }
        return;
    } else {
        for(int index = 0; index < rewards.count(); index++) {
            if (k_rewardsMap.contains(rewards[index])) {
                QString reward = k_rewardsMap[rewards[index]];
                m_rewardsListWidget->addItem(reward);
            }
        }
    }
}

void Client::getRewards()
{
    QList<RewardsService::ChannelType> channels;
    QHash<QCheckBox *, RewardsService::ChannelType>::const_iterator i = m_channelsCheckboxMap.constBegin();
    while (i != m_channelsCheckboxMap.constEnd()) {
        QCheckBox * checkBox = i.key();
        if (checkBox->isChecked()) {
            channels.append(i.value());
        }
        ++i;
    }

    if (channels.count() > 0) {
        quint32 accountNumber = k_accountNumbers[m_currentAccountNumberIndex];
        m_rewardsService->fetchRewards(accountNumber, channels);
    }
}
