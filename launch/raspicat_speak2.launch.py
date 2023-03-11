import os

from ament_index_python.packages import get_package_share_directory

from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, GroupAction
from launch_ros.actions import LoadComposableNodes, Node
from launch_ros.descriptions import ComposableNode
from launch.substitutions import LaunchConfiguration
from nav2_common.launch import RewrittenYaml


def generate_launch_description():
    raspicat_speak2_dir = get_package_share_directory('raspicat_speak2')
    config_dir = os.path.join(raspicat_speak2_dir, 'config')

    params_file = LaunchConfiguration('params_file')

    declare_params_file_cmd = DeclareLaunchArgument(
        'params_file',
        default_value=os.path.join(
            config_dir, 'speak_list.param.yaml'),
        description='Param')

    configured_params = RewrittenYaml(
        source_file=params_file,
        root_key="",
        param_rewrites={},
        convert_types=True)

    launch_component = GroupAction([
        Node(
            name='raspicat_speak2_component',
            package='rclcpp_components',
            executable='component_container_isolated',
            parameters=[configured_params],
            arguments=['--ros-args'],
            output='screen')
    ])

    load_composable_nodes = GroupAction(
        actions=[
            LoadComposableNodes(
                target_container="raspicat_speak2_component",
                composable_node_descriptions=[
                    ComposableNode(
                        package='raspicat_speak2',
                        plugin='RaspicatSpeak2::RaspicatSpeak2',
                        name='raspicat_speak2',
                        parameters=[configured_params]),
                ],
            )
        ]
    )

    ld = LaunchDescription()
    ld.add_action(declare_params_file_cmd)
    ld.add_action(load_composable_nodes)
    ld.add_action(launch_component)

    return ld
