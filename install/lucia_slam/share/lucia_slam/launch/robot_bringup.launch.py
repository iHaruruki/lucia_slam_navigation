import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.conditions import LaunchConfigurationEquals
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import LifecycleNode, Node


def generate_launch_description():

    # Declare arguments
    declare_arg_namespace = DeclareLaunchArgument(
        'namespace',default_value='',
        description='Set namespace for tf tree')
    
    #lidar_port = DeclareLaunchArgument(
    
    declare_arg_lidar = DeclareLaunchArgument(
        'lidar',default_value='none',
        description='Set "none", "urg"')
        
    declare_arg_lidar_frame = DeclareLaunchArgument(
        'lidar_frame',default_value='laser',
        description='Set frame_id for lidar')
    
    #declare_arg_joydev = DeclareLaunchArgument(
        
    #eclare_arg_joyconfig = DeclareLaunchArgument(
        
    #Launch files and nodes
    
    #mouse_node = Node(
        
    urg_launch = Node(
        name='urg_node_driver',
        package='urg_node',executable='urg_node_driver',output='screen',
        #parameters=[{'frame_id': LaunchConfiguration('lidar_frame')}])
        condition=LaunchConfigurationEquals('lidar','urg'),
    )
    
    description_params = {'lidar': LaunchConfiguration('lidar'),
                          'lidar_frame': LaunchConfiguration('lidar_frame'),
                          'namespace': LaunchConfiguration('namespace')
                          }.items()
    
    display_robot_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([os.path.join(
            get_package_share_directory('lucia_slam'), 'launch/'),
            'description.launch.py']),
        launch_arguments=description_params
    )
    
    ld = LaunchDescription()
    ld.add_action(declare_arg_namespace)
    ld.add_action(declare_arg_lidar_frame)
    ld.add_action(urg_launch)
    ld.add_action(display_robot_launch)
    
    return ld
    