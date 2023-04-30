// SPDX-FileCopyrightText: 2023 Tatsuhiro Ikebe <beike315@icloud.com>
// SPDX-License-Identifier:  Apache-2.0

#ifndef RaspicatSpeak2__VoiceConfig_HPP_
#define RaspicatSpeak2__VoiceConfig_HPP_

#include <string>

struct VoiceConfig {
  double additional_half_tone;
  double all_pass_constant;
  double speech_speed_rate;
  std::string voice_model;
};

#endif // RaspicatSpeak2__VoiceConfig_HPP_