#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class PublisherNode : public rclcpp::Node {
public:
  PublisherNode() : Node("publisher_node") {
    publisher_ = create_publisher<std_msgs::msg::String>("chatter", 10);
    timer_ = create_wall_timer(std::chrono::seconds(1), std::bind(&PublisherNode::publish_message, this));
  }

private:
  void publish_message() {
    auto message = std_msgs::msg::String();
    message.data = "Hello! ROS2 is fun";
    RCLCPP_INFO(get_logger(), "Publishing: %s", message.data.c_str());
    publisher_->publish(message);
  }

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<PublisherNode>());
  rclcpp::shutdown();
  return 0;
}

