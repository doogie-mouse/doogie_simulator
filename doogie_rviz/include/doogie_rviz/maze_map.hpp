#ifndef DOOGIE_RVIZ_MAZE_MAP_HPP_
#define DOOGIE_RVIZ_MAZE_MAP_HPP_

#include <cstddef>

#include <ros/ros.h>
#include <grid_map_core/grid_map_core.hpp>
#include <nav_msgs/OccupancyGrid.h>

#include "doogie_msgs/MazeCellMultiArray.h"
#include "doogie_msgs/MazeCell.h"
#include "doogie_msgs/DoogiePose.h"

namespace doogie_rviz {

class MazeMap {
 public:
  MazeMap();
  void init();
  inline void drawNorthWall(uint8_t row, uint8_t column);
  inline void drawSouthWall(uint8_t row, uint8_t column);
  inline void drawEastWall(uint8_t row, uint8_t column);
  inline void drawWestWall(uint8_t row, uint8_t column);
  void drawWalls(uint8_t row, uint8_t column, doogie_msgs::MazeCell cell_walls);
  void publishMap();
  void run();
 
 private:
  void loadParameters();
  void drawWall(grid_map::Position start, grid_map::Position end);
  grid_map::Position computeStartPoint(uint8_t row, uint8_t column);
  void doogiePoseCallback(const doogie_msgs::DoogiePoseConstPtr& doogie_pose);
  void mazeObstacleMatrixCallback(const doogie_msgs::MazeCellMultiArrayConstPtr& maze_obstacle_matrix);

  grid_map::GridMap maze_map_;
  ros::NodeHandle nh_;
  ros::Publisher maze_map_pub_;
  ros::Subscriber doogie_pose_sub_;
  ros::Subscriber maze_obstacle_matrix_sub_;

  doogie_msgs::DoogiePose doogie_pose_;
  doogie_msgs::MazeCell cell_walls_;
  nav_msgs::OccupancyGrid maze_map_grid_;


  uint8_t number_of_rows_;
  uint8_t number_of_columns_;
  float cell_size_;
  float pivo_dim_;
  float wall_size_;
  float pub_rate_;
  float map_resolution_;

  bool is_to_update_map_;
};

} // namespace doogie_rviz

#endif  // DOOGIE_RVIZ_MAZE_MAP_HPP_
