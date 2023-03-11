// SPDX-FileCopyrightText: 2023 Tatsuhiro Ikebe <beike315@icloud.com>
// SPDX-License-Identifier:  Apache-2.0

#include <chrono>
#include <iostream>
#include <memory>
#include <utility>

#include "ament_index_cpp/get_package_share_directory.hpp"
#include "rclcpp/node_impl.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rosbag2_transport/qos.hpp"
#include "std_msgs/msg/string.hpp"

#include "raspicat_speak2/raspicat_speak2.hpp"

using namespace std::chrono_literals;

namespace RaspicatSpeak2 {

RaspicatSpeak2::RaspicatSpeak2(const rclcpp::NodeOptions &options)
    : Node("raspicat_speak2", options), count_(0) {
  setParam();
  getParam();
  // initPublisher();
  // initTimer();

  // getSpeakInfo();
  // getVoiceConfig();
}

void RaspicatSpeak2::setParam() {
  declare_parameter("voice_config.additional_half_tone", 1.0);
  declare_parameter("voice_config.all_pass_constant", 0.55);
  declare_parameter("voice_config.speech_speed_rate", 1.0);
  declare_parameter("voice_config.voice_interval", 1.0);
  declare_parameter("voice_config.voice_model", "mei_normal.htsvoice");
}

void RaspicatSpeak2::getParam() {
  voc_.additional_half_tone =
      get_parameter("voice_config.additional_half_tone").as_double();
  voc_.all_pass_constant =
      get_parameter("voice_config.all_pass_constant").as_double();
  voc_.speech_speed_rate =
      get_parameter("voice_config.speech_speed_rate").as_double();
  voc_.voice_model = get_parameter("voice_config.voice_model").as_string();

  auto param_client =
      std::make_shared<rclcpp::AsyncParametersClient>(this, this->get_name());

  param_client->wait_for_service(1s);
  std::vector<std::string> parameter_names;
  auto future = param_client->describe_parameters(parameter_names);

  rclcpp::spin_until_future_complete(get_node_base_interface(), future);

  for (auto unko : future.get()) {
    std::cout << unko.name << "\n";
    RCLCPP_INFO(get_logger(), "%s", unko.name.c_str());
  }
}

void RaspicatSpeak2::initPublisher() {
  pub_ = create_publisher<std_msgs::msg::String>("chatter", 10);
}

void RaspicatSpeak2::initTimer() {
  timer_ =
      create_wall_timer(printf_ms_, std::bind(&RaspicatSpeak2::on_timer, this));
}

void RaspicatSpeak2::getSpeakInfo(){

};
void RaspicatSpeak2::getVoiceConfig(){};

void RaspicatSpeak2::on_timer() { subscribe_topic(); }

void RaspicatSpeak2::subscribe_topic() {
  auto all_topics = getTopicsNameType();
  auto unsub_topics = filterTopics(all_topics);

  if (unsub_topics.size()) {
    for (const auto unsub_topic : unsub_topics) {
      auto rclcpp_qos = rosbag2_transport::Rosbag2QoS::adapt_request_to_offers(
          unsub_topic.first, get_publishers_info_by_topic(unsub_topic.first));

      auto subscription =
          createSubscription(unsub_topic.first, unsub_topic.second, rclcpp_qos);

      subscriptions_.emplace(unsub_topic.first, subscription);
    }
  }
}

std::shared_ptr<rclcpp::GenericSubscription>
RaspicatSpeak2::createSubscription(const std::string &topic_name,
                                   const std::string &topic_type,
                                   const rclcpp::QoS &qos) {

  auto subscription = create_generic_subscription(
      topic_name, topic_type, qos,
      [topic_name, topic_type](
          std::shared_ptr<const rclcpp::SerializedMessage> message) {});
  return subscription;
}

std::unordered_map<std::string, std::string> RaspicatSpeak2::filterTopics(
    std::unordered_map<std::string, std::string> all_topics) {
  std::unordered_map<std::string, std::string> filter_topics;

  for (const auto topic : all_topics) {
    if (not isSubscribed(topic.first)) {
      filter_topics.insert(topic);
      subscribed_topics_.emplace_back(topic.first);
    }
  }

  return filter_topics;
}

bool RaspicatSpeak2::isSubscribed(std::string topic_name) {
  return subscriptions_.find(topic_name) != subscriptions_.end();
}

std::unordered_map<std::string, std::string>
RaspicatSpeak2::getTopicsNameType() {
  auto get_topics = this->get_topic_names_and_types();

  std::unordered_map<std::string, std::string> all_topics;
  for (const auto &[topic_name, topic_types] : get_topics) {
    all_topics.insert(std::make_pair(topic_name, topic_types[0]));
  }
  return all_topics;
}

void RaspicatSpeak2::speak(const std::string topic_name) {
  std::string open_jtalk =
      "echo " + speak_info_[topic_name].sentence + " | open_jtalk -x " +
      "/var/lib/mecab/dic/open-jtalk/naist-jdic -m " +
      ament_index_cpp::get_package_share_directory("raspicat_speak2") +
      "/voice_model/" + voc_.voice_model + " -r " +
      std::to_string(voc_.speech_speed_rate) + "-fm" +
      std::to_string(voc_.additional_half_tone) + "-a" +
      std::to_string(voc_.all_pass_constant) + " -ow  /dev/stdout | aplay & ";

  if (system(open_jtalk.c_str())) {
    RCLCPP_ERROR(get_logger(), "shell is not available on the system!");
  }
}

} // namespace RaspicatSpeak2

#include "rclcpp_components/register_node_macro.hpp"

RCLCPP_COMPONENTS_REGISTER_NODE(RaspicatSpeak2::RaspicatSpeak2)
