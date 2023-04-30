# raspicat_speak2 [![build-test](https://github.com/CIT-Autonomous-Robot-Lab/raspicat_speak2/actions/workflows/build-test.yaml/badge.svg)](https://github.com/CIT-Autonomous-Robot-Lab/raspicat_speak2/actions/workflows/build-test.yaml)

## Overview
[raspicat_speak](https://github.com/CIT-Autonomous-Robot-Lab/raspicat_speak)のROS 2実装です。

## Input / Output

### Input

| **Name（Topic）** | **Type**                                          | **Description**                             | 
| ------------- | --------------------------------------------- | --------------------------------------- | 
| `/speak`          | `std_msgs::msgs::String`                  | 喋ってほしい文字列を受け取る         | 
| `config/speak_list.param.yamlに書かれているTopic`          | `*::*::*`                  | あるトピックをサブスクライブした場合に喋ってほしい文章を設定         | 

### Parameters

| **Name（Parameter）**   | **Type**        | **Description**            | 
| ------------------- | ----------- | ---------------------- | 
| `additional_half_tone`           | `double` |      基本周波数の調整      | 
| `all_pass_constant`          | `double` |    周波数特性の平滑化    | 
| `speech_speed_rate`         | `double` | 喋る速さ         | 
| `voice_model`       | `std::string`         | 声のモデル   |

# How to use

## 任意の文章を喋らせる

```
ros2 launch raspicat_speak2 raspicat_speak2.launch.py
ros2 topic pub --once  /speak std_msgs/String "data: 'i am らずぱいきゃとにあん'"
```

## [yamlに設定した文章を喋らせる](config/speak_list.param.yaml)

```
ros2 launch raspicat_speak2 raspicat_speak2.launch.py
ros2 topic pub /hoge1 std_msgs/Empty --once
ros2 topic pub /hoge2 std_msgs/Empty --once
ros2 topic pub /hoge3 std_msgs/Empty --once
ros2 topic pub /hoge4 std_msgs/Empty --once
ros2 topic pub /hoge5 std_msgs/Empty --once
ros2 topic pub /hoge6 std_msgs/Empty --once
ros2 topic pub /hoge7 std_msgs/Empty --once
```