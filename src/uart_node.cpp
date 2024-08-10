#include "rclcpp/rclcpp.hpp"
#include "uart_mux_lib.h"  // MikroElektronikaのライブラリをインクルード

class UARTNode : public rclcpp::Node {
public:
  UARTNode() : Node("uart_node") {
    // UART初期化
    uart_init();
    // モータ制御関数の定期実行
    timer_ = this->create_wall_timer(
      30ms, std::bind(&UARTNode::send_motor_command, this));
  }

private:
  void send_motor_command() {
    // 速度コマンドを送信
    send_speed_command(0x01, 100);  // IDと速度を指定
  }

  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  auto node = std::make_shared<UARTNode>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
