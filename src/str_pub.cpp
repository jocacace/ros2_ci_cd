#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <memory>

using namespace std::chrono_literals;

class StringPublisher : public rclcpp::Node
{
public:
    StringPublisher() : Node("cicd_test") {
        _str_pub = this->create_publisher<std_msgs::msg::String>("topic", 10);
        _timer = this->create_wall_timer(500ms, std::bind(&StringPublisher::publish_string, this));
    }

private:
    void publish_string() {
        std_msgs::msg::String msg;
        msg.data = "CI/CD using ROS 2 and github actions";
        _str_pub->publish(msg);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr _str_pub;
    rclcpp::TimerBase::SharedPtr _timer;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<StringPublisher>());
    rclcpp::shutdown();
    return 0;
}

