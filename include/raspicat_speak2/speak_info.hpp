// SPDX-FileCopyrightText: 2023 Tatsuhiro Ikebe <beike315@icloud.com>
// SPDX-License-Identifier:  Apache-2.0

#ifndef RaspicatSpeak2__SpeakInfo_HPP_
#define RaspicatSpeak2__SpeakInfo_HPP_

#include <string>

struct SpeakInfo {
  std::string topic;
  std::string sentence;
  std::string voice_model;
};

#endif // RaspicatSpeak2__SpeakInfo_HPP_