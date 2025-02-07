#include "teleop_widget.h"
#include <QVBoxLayout>
#include <QLabel>

TeleopWidget::TeleopWidget(ros::NodeHandle &nh, QWidget *parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus); // 키보드 이벤트를 받을 수 있도록 설정

    cmdVelPub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);

    // UI 표시 (간단한 안내 메시지)
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Turtlebot Controller", this);
    layout->addWidget(label);
    setLayout(layout);

    // 50ms마다 publishCommand() 호출
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &TeleopWidget::publishCommand);
    timer->start(50);
}

// 키가 눌렸을 때 호출
void TeleopWidget::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) { // 자동 반복 입력 방지
        pressedKeys.insert(event->key());
    }
}

// 키가 해제되었을 때 호출
void TeleopWidget::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        pressedKeys.remove(event->key());
    }
}

// 주기적으로 현재 눌린 키 상태를 기반으로 ROS 명령을 발행
void TeleopWidget::publishCommand() {
    geometry_msgs::Twist twist;
    double linear = 0.0;
    double angular = 0.0;

    if (pressedKeys.contains(Qt::Key_Up))    linear += max_linear_speed;
    if (pressedKeys.contains(Qt::Key_Down))  linear -= max_linear_speed;
    if (pressedKeys.contains(Qt::Key_Left))  angular += max_angular_speed;
    if (pressedKeys.contains(Qt::Key_Right)) angular -= max_angular_speed;

    twist.linear.x = linear;
    twist.angular.z = angular;
    cmdVelPub.publish(twist);
}
