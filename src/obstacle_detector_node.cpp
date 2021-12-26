/* obstacle_detector_node.cpp

 * Copyright (C) 2021 SS47816

 * ROS Node for 3D LiDAR Obstacle Detection & Tracking

**/

#include <iostream>
#include <string>
#include <vector>

#include <ros/ros.h>
#include <ros/console.h>
#include <pcl/common/common.h>

#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/PoseStamped.h>
#include <jsk_recognition_msgs/BoundingBox.h>
#include <jsk_recognition_msgs/BoundingBoxArray.h>
#include <autoware_msgs/DetectedObjectArray.h>

namespace lidar_obstacle_detector 
{

class ObstacleDetectorNode
{
 public:
  ObstacleDetectorNode();
  virtual ~ObstacleDetectorNode() {};

 private:
  float bbox_filter_size_;
  std::string bbox_target_frame_;
  ros::NodeHandle nh;
  tf2_ros::Buffer tf2_buffer;
  tf2_ros::TransformListener tf2_listener;

  ros::Subscriber sub_lidar_points;
  ros::Publisher pub_cloud_ground;
  ros::Publisher pub_cloud_clusters;
  // ros::Publisher pub_jsk_bboxes;
  // ros::Publisher pub_autoware_objects;

  void lidarPointsCallback(const sensor_msgs::PointCloud2::ConstPtr& lidar_points);
  // jsk_recognition_msgs::BoundingBox transformJskBbox(const lidar_obstacle_detector::Detection3D::ConstPtr& lgsvl_detection3d, const geometry_msgs::Pose& pose_transformed);
  // autoware_msgs::DetectedObject transformAutowareObject(const lidar_obstacle_detector::Detection3D::ConstPtr& lgsvl_detection3d, const geometry_msgs::Pose& pose_transformed);
};

ObstacleDetectorNode::ObstacleDetectorNode() : tf2_listener(tf2_buffer)
{
  ros::NodeHandle private_nh("~");
  
  std::string lidar_points_topic;
  std::string cloud_ground_topic;
  std::string cloud_clusters_topic;
  // std::string jsk_bboxes_topic;
  // std::string autoware_objects_topic;
  
  ROS_ASSERT(private_nh.getParam("lidar_points_topic", lidar_points_topic));
  ROS_ASSERT(private_nh.getParam("cloud_ground_topic", cloud_ground_topic));
  ROS_ASSERT(private_nh.getParam("cloud_clusters_topic", cloud_clusters_topic));
  // ROS_ASSERT(private_nh.getParam("jsk_bboxes_topic", jsk_bboxes_topic));
  // ROS_ASSERT(private_nh.getParam("autoware_objects_topic", autoware_objects_topic));

  sub_lidar_points = nh.subscribe(lidar_points_topic, 1, &ObstacleDetectorNode::lidarPointsCallback, this);
  // jsk_bboxes_pub = nh.advertise<jsk_recognition_msgs::BoundingBoxArray>(jsk_bboxes_topic, 1);
  // autoware_objects_pub = nh.advertise<autoware_msgs::DetectedObjectArray>(autoware_objects_topic, 1);
}

void ObstacleDetectorNode::lidarPointsCallback(const sensor_msgs::PointCloud2::ConstPtr& pointcloud)
{
  
}


/**
 
jsk_recognition_msgs::BoundingBox ObstacleDetectorNode::transformJskBbox(const lidar_obstacle_detector::Detection3D::ConstPtr& lgsvl_detection3d, const geometry_msgs::Pose& pose_transformed)
{
  jsk_recognition_msgs::BoundingBox jsk_bbox;
  jsk_bbox.header = lgsvl_detection3d->header;
  jsk_bbox.header.frame_id = bbox_target_frame_;
  jsk_bbox.pose = pose_transformed;
  jsk_bbox.pose.position.z += lgsvl_detection3d->bbox.size.z/2;
  jsk_bbox.dimensions = lgsvl_detection3d->bbox.size;
  jsk_bbox.value = lgsvl_detection3d->score;
  if (lgsvl_detection3d->label == "Pedestrian")
  { 
    jsk_bbox.label = 2;
  }
  else if (lgsvl_detection3d->label == "Bicyclist")
  { 
    jsk_bbox.label = 1;
  }
  else
  { 
    jsk_bbox.label = 0;
  }

  return std::move(jsk_bbox);
}

autoware_msgs::DetectedObject ObstacleDetectorNode::transformAutowareObject(const lidar_obstacle_detector::Detection3D::ConstPtr& lgsvl_detection3d, const geometry_msgs::Pose& pose_transformed)
{
  autoware_msgs::DetectedObject autoware_object;
  autoware_object.header = lgsvl_detection3d->header;
  autoware_object.header.frame_id = bbox_target_frame_;
  autoware_object.id = lgsvl_detection3d->id;
  autoware_object.label = lgsvl_detection3d->label;
  autoware_object.score = lgsvl_detection3d->score;
  autoware_object.pose = pose_transformed;
  autoware_object.pose.position.z += lgsvl_detection3d->bbox.size.z/2;
  autoware_object.pose_reliable = true;
  autoware_object.dimensions = lgsvl_detection3d->bbox.size;
  autoware_object.velocity = lgsvl_detection3d->velocity;
  autoware_object.velocity_reliable = true;
  autoware_object.valid = true;
  if (lgsvl_detection3d->label == "Pedestrian")
  { 
    autoware_object.label = "person";
  }
  else if (lgsvl_detection3d->label == "Bicyclist")
  { 
    autoware_object.label = "bicycle";
  }
  else if (lgsvl_detection3d->label == "SchoolBus")
  { 
    autoware_object.label = "bus";
  }
  else if (lgsvl_detection3d->label == "BoxTruck")
  { 
    autoware_object.label = "truck";
  }
  else 
  { 
    autoware_object.label = "car";
  }

  return std::move(autoware_object);
}

**/

} // namespace lidar_obstacle_detector

int main(int argc, char** argv)
{
  ros::init(argc, argv, "obstacle_detector_node");
  lidar_obstacle_detector::ObstacleDetectorNode obstacle_detector_node;
  ros::spin();
  return 0;
}