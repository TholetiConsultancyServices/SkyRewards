#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QHash>
#include<rewardsserviceimpl.h>

QT_BEGIN_NAMESPACE
class QCheckBox;
class QListWidget;
QT_END_NAMESPACE

class Client: public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);

private slots:
     void checkBoxToggled();
     void accountNumberChanged(int index);
    void rewardsStatusReceived(QList<RewardsService::RewardType> rewards, RewardsService::RewardsError* error);

private:
    QListWidget *m_rewardsListWidget;
    int m_currentAccountNumberIndex;
    RewardsService *m_rewardsService;
    QHash<QCheckBox *, RewardsService::ChannelType> m_channelsCheckboxMap;
    void getRewards();
};

#endif // CLIENT_H
