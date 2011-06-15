// Devin Koepl

#include <stdlib.h>
#include <gtkmm.h>
#include <stdlib.h>
#include <cairomm/context.h>

#include <ros/ros.h>

#include <geometry_msgs/Pose.h>

#include <drl_plugins/position_body_srv.h>

// GUI objects
Gtk::Window *window;

Gtk::HScale *x_position_hscale;
Gtk::HScale *y_position_hscale;
Gtk::HScale *z_position_hscale;

Gtk::CheckButton *x_translation_checkbutton;
Gtk::CheckButton *y_translation_checkbutton;
Gtk::CheckButton *z_translation_checkbutton;

//Gtk::CheckButton *x_rotation_checkbutton;
//Gtk::CheckButton *y_rotation_checkbutton;
//Gtk::CheckButton *z_rotation_checkbutton;

Gtk::ToggleButton *pause_play_button;
Gtk::ToggleButton *hold_release_button;
Gtk::Button *get_position_button;

ros::ServiceClient simulation_client;
drl_plugins::position_body_srv simulation_srv;

geometry_msgs::Pose desired_pose;

void pause_play();
void hold_release();
void get_position();
void desired_pose_changed();
