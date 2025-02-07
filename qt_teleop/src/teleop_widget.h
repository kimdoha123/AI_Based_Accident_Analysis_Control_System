#ifndef TELEOP_WIDGET_H
#define TELEOP_WIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <QSet>
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

class TeleopWidget : public QWidget {
    Q_OBJECT
public:
    explicit TeleopWidget(ros::NodeHandle &nh, QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void publishCommand();

private:
    QSet<int> pressedKeys;      // 눌린 키 목록
    QTimer *timer;              // 주기적으로 ROS 명령을 보낼 타이머
    ros::Publisher cmdVelPub;   // ROS cmd_vel publisher

    // 속도 설정
    const double max_linear_speed = 0.7;   // m/s
    const double max_angular_speed = 1.5;  // rad/s
};

#endif // TELEOP_WIDGET_H
