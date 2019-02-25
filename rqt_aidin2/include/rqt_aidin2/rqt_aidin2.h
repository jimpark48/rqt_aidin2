#ifndef RQT_AIDIN2_RQT_AIDIN2_H
#define RQT_AIDIN2_RQT_AIDIN2_H

#include <rqt_gui_cpp/plugin.h>
#include <rqt_aidin2/ui_rqt_aidin2.h>
#include <QWidget>
//using QPushButton
#include <QPushButton>
#include <QApplication>

#include <ros/ros.h>
#include <std_msgs/Int32.h>
//using QListView 
#include <QString>
#include <QStringList>
#include <QStringListModel>

namespace rqt_aidin2
{

class aidinPlugin2
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  aidinPlugin2();

  virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  virtual void shutdownPlugin();
  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings,
      qt_gui_cpp::Settings& instance_settings) const;
  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
      const qt_gui_cpp::Settings& instance_settings);
  
  virtual void listView2Plugin(const char* message1);

  virtual void connectionfunc();

  // Comment in to signal that the plugin has a way to configure it
  // bool hasConfiguration() const;
  // void triggerConfiguration();

private:
  Ui::MyPluginWidget ui_;
  QWidget* widget_;
  QStringListModel* model;
  QStringListModel* model2;

  ros::NodeHandle nh;
  ros::Publisher rqt_aidin2_pub;
  ros::Publisher test_pub;
  ros::Publisher gait_pub;
  ros::Publisher goal_pub;

  Q_SIGNALS:
    void clicked();
    void clicked(const QString &qstr2);
    void clicked(const QModelIndex &index);
    void toggled(bool checked);
private slots:
  void on_pushButton_clicked1(); //반드시 slots 안에 정의할 것
  void on_pushButton_clicked2();
  void onClickListItem(const QModelIndex &index);
  void onClickListItem2(const QModelIndex &index);
  void on_pushButton_2_clicked1();
  void on_pushButton_3_clicked1();
  void on_pushButton_3_clicked2();
  void onChecked(bool checked);
  void on_quitButton_clicked();
  void on_enterButton_clicked();
};
}  // namespace rqt_aidin2
#endif  // RQT_AIDIN_RQT_AIDIN2_H
