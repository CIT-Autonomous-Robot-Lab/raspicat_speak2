// SPDX-FileCopyrightText: 2023 Tatsuhiro Ikebe <beike315@icloud.com>
// SPDX-License-Identifier: Apache-2.0

#include "raspicat_speak2/raspicat_speak2.hpp"

using namespace std::chrono_literals;

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);

  rclcpp::NodeOptions node_options;
  node_options.allow_undeclared_parameters(true);
  node_options.automatically_declare_parameters_from_overrides(true);

  auto node = std::make_shared<raspicat_speak2::RaspicatSpeak2>(
      "raspicat_speak2_node", node_options);

  // auto client = std::make_shared<rclcpp::AsyncParametersClient>(node,
  // node->get_name()); auto ready = client->wait_for_service(5s);

  // auto future = client->list_parameters(std::vector<std::string>(10),0);
  // rclcpp::spin_until_future_complete(node->shared_from_this(), future);

  // for (auto x : future.get().names)
  // {
  //   std::cout << x << "\n";
  // }
  rclcpp::spin(node);

  rclcpp::shutdown();
  return 0;
}