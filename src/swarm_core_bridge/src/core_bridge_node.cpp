#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class CoreBridgeNode : public rclcpp::Node
{
public:
  CoreBridgeNode()
  : Node("core_bridge_node"), count_(0)
  {
    RCLCPP_INFO(this->get_logger(), "Primary Edge Node Initialized. Booting subsystems...");
    publisher_ = this->create_publisher<std_msgs::msg::String>("swarm_status", 10);
    timer_ = this->create_wall_timer(
      500ms, std::bind(&CoreBridgeNode::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    message.data = "Drone 1 Status: NOMINAL | Uptime: " + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(), "Broadcasting: '%s'", message.data.c_str());
    publisher_->publish(message);
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<CoreBridgeNode>());
  rclcpp::shutdown();
  return 0;
}
