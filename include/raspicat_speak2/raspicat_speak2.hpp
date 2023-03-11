// SPDX-FileCopyrightText: 2023 Tatsuhiro Ikebe <beike315@icloud.com>
// SPDX-License-Identifier: Apache-2.0

#ifndef RaspicatSpeak2__RaspicatSpeak2_HPP_
#define RaspicatSpeak2__RaspicatSpeak2_HPP_

#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include "raspicat_speak2/speak_info.hpp"
#include "raspicat_speak2/voice_config.hpp"

namespace RaspicatSpeak2 {

class RaspicatSpeak2 : public rclcpp::Node {
public:
  explicit RaspicatSpeak2(const rclcpp::NodeOptions &options);

protected:
  void initPublisher();
  void initTimer();
  void on_timer();
  void setParam();
  void getParam();

  void getSpeakInfo();
  void getVoiceConfig();

  void speak(const std::string topic_name);

  void subscribe_topic();
  std::shared_ptr<rclcpp::GenericSubscription>
  createSubscription(const std::string &topic_name,
                     const std::string &topic_type, const rclcpp::QoS &qos);
  std::unordered_map<std::string, std::string>
  filterTopics(std::unordered_map<std::string, std::string> all_topics);
  bool isSubscribed(std::string topic_name);

  std::unordered_map<std::string, std::string> getTopicsNameType();

private:
  size_t count_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr pub_;
  rclcpp::TimerBase::SharedPtr timer_;

  std::string printf_string_;
  std::chrono::milliseconds printf_ms_;

  std::vector<std::string> subscribed_topics_;
  std::unordered_map<std::string, std::shared_ptr<rclcpp::GenericSubscription>>
      subscriptions_;

  VoiceConfig voc_;
  std::map<std::string, SpeakInfo> speak_info_;
};

} // namespace RaspicatSpeak2

#endif // RaspicatSpeak2__RaspicatSpeak2_HPP_
