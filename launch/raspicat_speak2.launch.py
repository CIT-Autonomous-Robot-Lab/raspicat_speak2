# SPDX-FileCopyrightText: 2023 Tatsuhiro Ikebe <beike315@icloud.com>
# SPDX-License-Identifier: Apache-2.0

import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import GroupAction
from launch_ros.actions import Node


def generate_launch_description():
    ros2_cpp_template_dir = get_package_share_directory('raspicat_speak2')
    speal_list = os.path.join(
        ros2_cpp_template_dir, 'config', 'speak_list.param.yaml')
    voice_config = os.path.join(
        ros2_cpp_template_dir, 'config', 'voice_config.param.yaml')

    launch_node = GroupAction([
        Node(
            name='raspicat_speak2',
            package='raspicat_speak2',
            executable='raspicat_speak2_node',
            arguments=[speal_list],
            parameters=[voice_config],
            output='screen')
    ])

    ld = LaunchDescription()
    ld.add_action(launch_node)

    return ld
