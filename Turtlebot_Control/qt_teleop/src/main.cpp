#include "teleop_widget.h"
#include <QApplication>

int main(int argc, char **argv) {
    ros::init(argc, argv, "qt_teleop");
    ros::NodeHandle nh;

    QApplication app(argc, argv);
    TeleopWidget widget(nh);
    widget.setWindowTitle("ROS Qt Teleop");
    widget.resize(400, 300);
    widget.show();

    return app.exec();
}
