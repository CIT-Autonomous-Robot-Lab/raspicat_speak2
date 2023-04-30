// SPDX-FileCopyrightText: 2023 Tatsuhiro Ikebe <beike315@icloud.com>
// SPDX-License-Identifier: Apache-2.0

#include "raspicat_speak2/raspicat_speak2.hpp"

using namespace std::chrono_literals;

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);

  auto node = std::make_shared<raspicat_speak2::RaspicatSpeak2>(
      "raspicat_speak2_node", argv[1]);

  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}