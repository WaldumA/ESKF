#pragma once

#include "ESKF.h"
//#include "common.h"

#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "nav_msgs/Odometry.h"
#include "eskf-slam.h"
#include <sensor_msgs/LaserScan.h>
#include <vector>

const Eigen::Matrix3d R_ACC((Eigen::Matrix3d() << 4, 0, 0, 0, 4, 0, 0, 0, 4).finished());
const Eigen::Matrix3d R_ACCBIAS((Eigen::Matrix3d() << 6e-5, 0, 0, 0, 6e-5, 0, 0, 0, 6e-5).finished());
const Eigen::Matrix3d R_GYRO((Eigen::Matrix3d() << 12e-3, 0, 0, 0, 12e-3, 0, 0, 0, 12e-3).finished());
const Eigen::Matrix3d R_GYROBIAS((Eigen::Matrix3d() << 3e-7, 0, 0, 0, 3e-7, 0, 0, 0, 3e-7).finished());
constexpr double P_GYRO_BIAS{ 0.0001 };
constexpr double P_ACC_BIAS{ 0.0001 };
const Eigen::Matrix3d
  S_A((Eigen::Matrix3d() << -0.9990, 1.9804e-04, -0.0450, 1.3553e-20, 1.0, 0.0044, 0.0450, 0.0044, -0.9990).finished());
const Eigen::Matrix3d
  S_G((Eigen::Matrix3d() << -0.9990, 1.9804e-04, -0.0450, 1.3553e-20, 1.0, 0.0044, 0.0450, 0.0044, -0.9990).finished());
const Eigen::Matrix3d S_DVL((Eigen::Matrix3d() << 1.0, 0, 0, 0, 1.0, 0, 0, 0, 1.0).finished());
const Eigen::Matrix3d S_INC(
  (Eigen::Matrix3d() << -0.9990, 1.9804e-04, -0.0450, 1.3553e-20, 1.0, 0.0044, 0.0450, 0.0044, -0.9990).finished());
const Eigen::Matrix3d R_DVL((Eigen::Matrix3d() << 1.0e-10, 0, 0, 0, 1.0e-10, 0, 0, 0, 1.0e-10).finished());
const Eigen::MatrixXd R_PRESSUREZ((Eigen::MatrixXd(1, 1) << 2.2500).finished());

const Eigen::Vector3d IMURPYTONED((Eigen::Vector3d() << 0.0, M_PI, 0.0).finished());
const Eigen::Vector3d IMUALIGNMENT((Eigen::Vector3d() << -0.004635, 0.009897, 0).finished());  // Roll -0.004397 , pitch
                                                                                               // 0.0450556 , yaw

const Eigen::Vector3d roll_pitch_yaw_NED_and_alignment_corrected = IMURPYTONED + IMUALIGNMENT;

class ESKF_Node
{
public:
  ESKF_Node(const ros::NodeHandle& nh, const ros::NodeHandle& pnh);
  //~ESKF_Node();

  // void getParametersFromYamlFile();

private:
  ros::NodeHandle nh_;
  bool init_;

  Eigen::Matrix3d R_dvl_;
  Eigen::Matrix<double, 1, 1> R_pressureZ_;

  eskf::ESKF eskf_;

  // Variables for SLAM
  bool do_slam_update;
  sensor_msgs::LaserScan sonar_data;
  std::vector<ESKF_SLAM_MAP> local_maps;

  // Load from Yaml file
  eskf::parametersInESKF loadParametersFromYamlFile();

  // ROS subscribers
  ros::Subscriber subcribeDVL_;
  ros::Subscriber subscribeIMU_;
  ros::Subscriber subscribePressureZ_;
  ros::Subscriber subscribeSonar_;
  ros::Timer pubTImer_;

  // ROS publisher
  ros::Publisher publishPose_;
  ros::Publisher publishMap_;

  // Callbacks
  void imuCallback(const sensor_msgs::Imu::ConstPtr& imu_Message_data);
  void dvlCallback(const nav_msgs::Odometry::ConstPtr& dvl_Message_data);
  void publishPoseState(const ros::TimerEvent&);
  void pressureZCallback(const nav_msgs::Odometry::ConstPtr& pressureZ_Message_data);
  void sonarCallback(const sensor_msgs::LaserScan::ConstPtr& msg);


  // Execution time
	std::vector<double> execution_time_vector_; 
	bool publish_execution_time_;

};


