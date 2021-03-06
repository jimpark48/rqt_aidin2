#include "rqt_aidin2/rqt_aidin2.h"
#include <pluginlib/class_list_macros.h>
#include <QStringList>
#include <stdlib.h>
#include <thread>
#include <string.h>
//#include "rqt_aidin2/ui_rqt_aidin2.h"

#include <aidin_msgs/RQT.h>
#include <std_msgs/Float32.h>
#define PI 3.14159265359 
#define PI2 2*3.14159265359 

namespace rqt_aidin2
{
aidinPlugin2::aidinPlugin2()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
{
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("aidinPlugin2");
}

//global variables
QString qstr1;
QString qstr2;
QStringList list2;
char *message1;
char *plotstring = (char*)malloc(30);
int commandcount;
int count;
int checkedcount;
//slider variables
QString Camera;
double slider;
//std_msgs::Float32 msgAngle;
aidin_msgs::RQT msgAngle;
aidin_msgs::RQT msg;
//rqt_aidin2::msgaidin2 msgGoalPos;
//rqt_aidin2::msgaidin2 msgGoalOri;
//rqt_aidin2::msgaidin2 msgDo;

std::string robot_change;
int robotnum = 2;
int robotcount = 0;
int robotarray[10];

bool autoOn = false;//YH

//sum two strings
const char *sumstring(const char *a,const char *b) {
    int i,j;
    char *newstring;
    newstring=(char*)malloc(strlen(a)+strlen(b));
    for(i=0;i<strlen(a);i++)
      newstring[i]=a[i];
    for(j=0;j<strlen(b);j++)
      newstring[i+j]=b[j];
    newstring[i+j]='\0';
    return newstring;
}

//compare long string and short string
//if long string includes short string, comparestring function returns 
//starting position value of short string in long string 
int comparestring(const char *long1, const char *short1) {
  int i, j, count2;
  for(i=0; i<strlen(long1)-strlen(short1)+1; i++) {
    count2 = 0;
    for(j=0; j<strlen(short1); j++) {
      if(long1[i+j] == short1[j]) count2++;
    }
    if(count2 == strlen(short1)) return i;
  }
  return 10000;
}

//delete b string in a string
char *minusstring(char *a, char *b) {
  int k = comparestring(a, b);
  if(k == 10000) {
    return a;
  }
  else {
    int i=k;
    while(a[i+strlen(b)] != '\0') {
      a[i] = a[i+strlen(b)+1];
      i++;
    }
    a[i] = '\0';
    return a;
  }
}

void aidinPlugin2::on_pushButton_clicked1() 
{
    //QString -> char* conversion
    QByteArray bytename = qstr1.toLocal8Bit();
    char *message1 = bytename.data();

    ROS_INFO("%s", message1);

    //determine whether message1 is launch file or not
    const char *launchmsg = ".launch";
    int value = comparestring(message1, launchmsg);
    //if value is 10000, message1 doesn't launch file
    if(value != 10000) {
      /*const char *testmsg = "aidinvi walking_vis_test.launch";
      int index = comparestring(message1, testmsg);
      if(index != 10000) {
        ROS_INFO("robots_auto");
        system("gnome-terminal -e 'rosrun aidinvi robots_auto --screen'");
      } */
      const char *message2 = "gnome-terminal -e 'roslaunch "; //new terminal
      const char *message3 = " --screen'";
      //const char *message3 = "'";
      const char *message4 = sumstring(message2, message1);
      message4 = sumstring(message4, message3);
      ROS_INFO("%s", message4);
      system(message4);

    }
    //if commandcount is 1, it activate command slot
    else if(commandcount == 1) {
      for(int i = 1; i<=robotnum; i++) {
        if(robotarray[i] == 1) {
          msg.robot[i] = 1;
        }
        else if(robotarray[i] == 0) {
          msg.robot[i] = 0;
        }
      }

      //int count2 = 0;
      char *token = NULL;
      char s1[] = " ";
      token = strtok(message1, s1);
      message1 = strtok(NULL, s1);
      if(strcmp(message1, "Foottrajectory") == 0) {
        ros::Rate loop_rate(10);

        int num = 1;
        
        //ROS_INFO("%s", message1);
        ROS_INFO("on");
        //rqt_aidin2::msgaidin2 msg;
        msg.data = num;
        
        rqt_aidin2_pub.publish(msg); 
      }
      else if(strcmp(message1, "Footprint") == 0) {
        ros::Rate loop_rate(10);

        int num = 3;
        //ROS_INFO("%s", message1);
        ROS_INFO("on");
        //rqt_aidin2::msgaidin2 msg;
        msg.data = num;
        
        rqt_aidin2_pub.publish(msg);
      }
      else if(strcmp(message1, "Cobtrajectory") == 0) {
        ros::Rate loop_rate(10);

        int num = 5;
        //ROS_INFO("%s", message1);
        ROS_INFO("on");
        //rqt_aidin2::msgaidin2 msg;
        msg.data = num;
      }
    }
    else {
      const char *message2 = "gnome-terminal -e 'rosrun ";
      const char *message3 = "'";
      const char *message4 = sumstring(message2, message1);
      message4 = sumstring(message4, message3);
      //ROS_INFO("%s", message4);
      system(message4);
    }
}

void aidinPlugin2::on_pushButton_clicked2() 
{
  //QString -> char* conversion
  QByteArray bytename = qstr2.toLocal8Bit();
  char *message1 = bytename.data();

  //ROS_INFO("%s", message1);

  for(int i = 1; i<=robotnum; i++) {
    if(robotarray[i] == 1) {
      msg.robot[i] = 1;
    }
    else if(robotarray[i] == 0) {
      msg.robot[i] = 0;
    }
  }

  if(strcmp(message1, "Idle") == 0) {      
    ros::Rate loop_rate(10);

    int num = 0;
    ROS_INFO("%s", message1);
    //rqt_aidin2::msgaidin2 msg;
    msg.data = num;
    
    gait_pub.publish(msg);

  }
  else if(strcmp(message1, "Init") == 0) {      
    ros::Rate loop_rate(10);

    int num = 1;
    ROS_INFO("%s", message1);
    //rqt_aidin2::msgaidin2 msg;
    msg.data = num;

    gait_pub.publish(msg);
  }
  else if(strcmp(message1, "Walk") == 0) {      
    ros::Rate loop_rate(10);

    int num = 2;
    ROS_INFO("%s", message1);
    //rqt_aidin2::msgaidin2 msg;
    msg.data = num;

    gait_pub.publish(msg);
  }
  else if(strcmp(message1, "Trot") == 0) {
    ros::Rate loop_rate(10);

    int num = 3;
    ROS_INFO("%s", message1);
    //rqt_aidin2::msgaidin2 msg;
    msg.data = num;

    gait_pub.publish(msg);
  }
  else if(strcmp(message1, "StandTrot") == 0) {
    ros::Rate loop_rate(10);

    int num = 4;
    ROS_INFO("%s", message1);
    //rqt_aidin2::msgaidin2 msg;
    msg.data = num;

    gait_pub.publish(msg);
  }
  
}

void aidinPlugin2::on_pushButton_2_clicked1()
{
  for(int i = 1; i<=robotnum; i++) {
    if(robotarray[i] == 1) {
      msg.robot[i] = 1;
    }
    else if(robotarray[i] == 0) {
      msg.robot[i] = 0;
    }
  }

  //QString -> char* conversion
  QByteArray bytename = qstr1.toLocal8Bit();
  char *message1 = bytename.data();

  char *token = NULL;
  char s1[] = " ";
  token = strtok(message1, s1);
  message1 = strtok(NULL, s1);

  //ROS_INFO("%s", message1);

  if(commandcount == 1) {
    //ROS_INFO("%d", commandcount);
    ROS_INFO("%s", message1);
    if(strcmp(message1, "Foottrajectory") == 0) {
      ros::Rate loop_rate(10);

      ROS_INFO("off");

      int num = 0;
      //ROS_INFO("%s", message1);
      //rqt_aidin2::msgaidin2 msg;
      msg.data = num;
      rqt_aidin2_pub.publish(msg);
    }
    else if(strcmp(message1, "Footprint") == 0) {
      ros::Rate loop_rate(10);

      ROS_INFO("off");

      int num = 2;
      //rqt_aidin2::msgaidin2 msg;
      msg.data = num;
      rqt_aidin2_pub.publish(msg);
    }
    else if(strcmp(message1, "Cobtrajectory") == 0) {
      ros::Rate loop_rate(10);

      ROS_INFO("off");

      int num = 4;
      //rqt_aidin2::msgaidin2 msg;
      msg.data = num;
      rqt_aidin2_pub.publish(msg);
    }
  }
}

void aidinPlugin2::onClickListItem(const QModelIndex &index)
{
  QObject::disconnect(ui_.pushButton, SIGNAL(clicked()),
            this, SLOT(on_pushButton_clicked1()) );
  QObject::disconnect(ui_.pushButton_3, SIGNAL(clicked()),
            this, SLOT(on_pushButton_3_clicked1()) );
  QObject::disconnect(ui_.listView_2, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(onClickListItem2(const QModelIndex &))   );
  QObject::disconnect(ui_.pushButton_3, SIGNAL(clicked()),
            this, SLOT(on_pushButton_3_clicked2()) );
  QObject::disconnect(ui_.pushButton_2, SIGNAL(clicked()),
            this, SLOT(on_pushButton_2_clicked1())  );
  //initialize listView_2
  list2 = QStringList();
  model2->setStringList(QStringList{});
  count = 0;

  //qstr1 means selected row name in listView
  qstr1 = QString("%1").arg(index.data().toString());

  //QString -> char* conversion
  QByteArray bytename = qstr1.toLocal8Bit();
  /*char **/message1 = bytename.data();

  //divide message1 with s1
  char *token = NULL;
  char s1[] = " ";
  token = strtok(message1, s1);

  if(strcmp(token, "plot:") == 0) {
    message1 = strtok(NULL, s1);

    QObject::connect(ui_.pushButton_3, SIGNAL(clicked()),
            this, SLOT(on_pushButton_3_clicked1()) );

    //plot topic list menu setting to listView_2
    listView2Plugin(message1);
  }
  else if(strcmp(token, "command:") == 0) {
    message1 = strtok(NULL, s1);
    commandcount = 1;

    QObject::connect(ui_.pushButton_2, SIGNAL(clicked()),
              this, SLOT(on_pushButton_2_clicked1()) );

    listView2Plugin(message1);
  }

  QObject::connect(ui_.pushButton, SIGNAL(clicked()),
            this, SLOT(on_pushButton_clicked1()) );
}

void aidinPlugin2::onClickListItem2(const QModelIndex &index) {
  QObject::disconnect(ui_.pushButton_3, SIGNAL(clicked()),
            this, SLOT(on_pushButton_3_clicked1()) );
  QObject::disconnect(ui_.pushButton_3, SIGNAL(clicked()),
            this, SLOT(on_pushButton_3_clicked2()) );
  QObject::disconnect(ui_.pushButton, SIGNAL(clicked()),
            this, SLOT(on_pushButton_clicked2()) );

  //if checkedcount is 0, listView_2 activates as single section mode
  if(checkedcount == 0) {
    //qstr2 means selected row name in listView_2
    qstr2 = QString("%1").arg(index.data().toString());
    ui_.lineEdit->setText(qstr2);
  }
  //if checkedcount is 1, listView_2 activates as multi section mode
  else if(checkedcount == 1) {
    //qstr4 means new selected row name in listView_2
    QString qstr4 = QString("%1").arg(index.data().toString());
    
    //QString -> char* conversion
    QByteArray bytename = qstr2.toLocal8Bit();
    char *long1 = bytename.data();
    //QString -> char* conversion
    QByteArray bytename2 = qstr4.toLocal8Bit();
    char *short1 = bytename2.data();

    //when first selected
    if(strlen(long1) < strlen(short1)) {
      qstr2 = qstr4;
      ui_.lineEdit->setText(qstr2);
    }
    //after first selection
    else {
      //if item is selected twice, that item deletes in qstr2
      if(comparestring(long1, short1) != 10000) {
        long1 = minusstring(long1, short1);
        //char* -> QString conversion
        qstr2 = QString::fromLocal8Bit(long1);
        ui_.lineEdit->setText(qstr2);
      }
      //if item is selected once, that item adds in qstr2
      else {
        QString qstr3 = " ";
        qstr2 = qstr2 + qstr3 + qstr4;
        ui_.lineEdit->setText(qstr2);
      }
    }
  }
  QObject::connect(ui_.pushButton_3, SIGNAL(clicked()),
            this, SLOT(on_pushButton_3_clicked2()) );
  if(commandcount == 1) {
      QObject::connect(ui_.pushButton, SIGNAL(clicked()),
                this, SLOT(on_pushButton_clicked2()) );
  }
}

//checkbox function
void aidinPlugin2::onChecked(bool checked) {
  if(checked == true) {
    ui_.listView_2->setSelectionMode(QAbstractItemView::MultiSelection);
    
    //to cancel highlight, initialize listView_2
    list2 = QStringList();
    model2->setStringList(QStringList{});
    ui_.listView_2->setModel(model2);

    //QString -> char* conversion
    QByteArray bytename = qstr1.toLocal8Bit();
    /*char **/message1 = bytename.data();
    char *token = NULL;
    char s1[] = " ";
    token = strtok(message1, s1);
    message1 = strtok(NULL, s1);

    listView2Plugin(message1);
    //initialize qstr2
    qstr2 = "";
    checkedcount = 1;
  }
  else if(checked == false) {
    ui_.listView_2->setSelectionMode(QAbstractItemView::SingleSelection);

    list2 = QStringList();
    model2->setStringList(QStringList{});
    ui_.listView_2->setModel(model2);

    //QString -> char* conversion
    QByteArray bytename = qstr1.toLocal8Bit();
    /*char **/message1 = bytename.data();
    char *token = NULL;
    char s1[] = " ";
    token = strtok(message1, s1);
    message1 = strtok(NULL, s1);

    listView2Plugin(message1);

    qstr2 = "";
    checkedcount = 0;
  }
}
void aidinPlugin2::onChecked_2(bool checked) {
  if(checked == true) {
    autoOn = true;
  }
  else if(checked == false) {
    autoOn = false;
  }
}

void aidinPlugin2::onChecked_aidinvi1(bool checked) {
  if(checked == true) {
    robot_change = "/aidinvi1/";
    robotcount++;
    robotarray[1] = 1;
  }
  else if(checked == false) {
    robot_change = "";
    robotcount--;
    robotarray[1] = 0;
  }
  /*rqt_aidin2_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"command", 100);
  gait_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGait", 1);
  goalPos_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGoalPos", 4);
  goalOri_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGoalOri", 4);
  do_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdDo", 4);*/
  //Camera_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_camera_angle", 1);
}
void aidinPlugin2::onChecked_aidinvi2(bool checked) {
  if(checked == true) {
    robot_change = "/aidinvi2/";
    robotcount++;
    robotarray[2] = 1;
  }
  else if(checked == false) {
    robot_change = "";
    robotcount--;
    robotarray[2] = 0;
  }
  /*rqt_aidin2_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"command", 100);
  gait_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGait", 1);
  goalPos_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGoalPos", 4);
  goalOri_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGoalOri", 4);
  do_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdDo", 4);*/
  //Camera_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_camera_angle", 1);
}

//add topics of mesg to list2 
void alphasumstring(int sum, const char *mesg) {
  const char *ram = "/";
  for(int i=0; i<sum; i++) {
    char alpha = 97+i;
    int j;
    for(j=0; j<strlen(mesg); j++) {
      plotstring[j] = mesg[j];
    }
    plotstring[j] = ram[0];
    plotstring[j+1] = alpha;
    plotstring[j+2] = '\0';
    list2 << plotstring;
  }
}

//create detailed topics list of selected main topic in listView_2
void aidinPlugin2::listView2Plugin(const char* message) {
  //'malloc' function is too often used
  //char *plotstring = (char*)malloc(strlen(message)+2);
  if(strcmp(message, "/gazebo/aidinvi_footpos") == 0) {
    alphasumstring(12, message);
    model2->setStringList(list2);
    ui_.listView_2->setModel(model2);
  }
  else if(strcmp(message, "/gazebo/aidinvi_jointt") == 0) {
    alphasumstring(12, message);
    model2->setStringList(list2);
    ui_.listView_2->setModel(model2);
  }
  else if(strcmp(message, "/aidinvi_actp") == 0) {
    alphasumstring(12, message);
    model2->setStringList(list2);
    ui_.listView_2->setModel(model2);
  }
  else if(strcmp(message, "/aidinvi_actrawt") == 0) {
    alphasumstring(12, message);
    model2->setStringList(list2);
    ui_.listView_2->setModel(model2);
  }
  else if(strcmp(message, "/aidinvi_actt") == 0) {
    alphasumstring(12, message);
    model2->setStringList(list2);
    ui_.listView_2->setModel(model2);
  }
  else if(strcmp(message, "/aidinvi_contact") == 0) {
    alphasumstring(4, message);
    model2->setStringList(list2);
    ui_.listView_2->setModel(model2);
  }
  else if(strcmp(message, "gait") == 0) {
    list2 << "Idle"
          << "Init"
          << "Walk"
          << "Trot"
          << "StandTrot";
    model2->setStringList(list2);
    ui_.listView_2->setModel(model2);
  }

  QObject::disconnect(ui_.listView_2, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(onClickListItem2(const QModelIndex &))   );

  QObject::connect(ui_.listView_2, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(onClickListItem2(const QModelIndex &))   );
}

//plot button function1, when listView item selected
void aidinPlugin2::on_pushButton_3_clicked1() {
  //QString -> char* conversion
  QByteArray bytename = qstr1.toLocal8Bit();
  /*char **/message1 = bytename.data();

  //string is divided
  char *token = NULL;
  char s1[] = " ";
  token = strtok(message1, s1);
  message1 = strtok(NULL, s1);

  const char *message2 = "gnome-terminal -e 'rqt_plot ";
  const char *message3 = "'";
  const char *message4 = sumstring(message2, message1);
  message4 = sumstring(message4, message3);
  ROS_INFO("%s", message4);

  system(message4);
}

//plot button function2, when listView_2 item selected
void aidinPlugin2::on_pushButton_3_clicked2() {
  //QString -> char* conversion
  QByteArray bytename = qstr2.toLocal8Bit();
  char *message1 = bytename.data();

  const char *message2 = "gnome-terminal -e 'rqt_plot ";
  const char *message3 = "'";
  const char *message4 = sumstring(message2, message1);
  message4 = sumstring(message4, message3);
  ROS_INFO("%s", message4);

  system(message4);
}

void aidinPlugin2::on_quitButton_clicked() {
  exit(0);
}

void aidinPlugin2::on_enterGoalPosButton_clicked() {
  QString qstr_x = ui_.lineEdit_2->text();
  double goal_x = qstr_x.toDouble();
  QString qstr_y = ui_.lineEdit_3->text();
  double goal_y = qstr_y.toDouble();
  QString qstr_z = ui_.lineEdit_4->text();
  double goal_z = qstr_z.toDouble();

  aidin_msgs::RQT msgGoalPos;
  msgGoalPos.robot.resize(robotnum+1);
  msgGoalPos.x = goal_x;
  msgGoalPos.y = goal_y;
  msgGoalPos.z = goal_z;

  ROS_INFO("goal : %f %f %f", goal_x, goal_y, goal_z);

  for(int i = 1; i<=robotnum; i++) {
    if(robotarray[i] == 1) {
      msgGoalPos.robot[i] = 1;
    }
    else if(robotarray[i] == 0) {
      msgGoalPos.robot[i] = 0;
    }
  }
  goalPos_pub.publish(msgGoalPos);
}
void aidinPlugin2::on_enterGoalOriButton_clicked() {
  QString qstr_R = ui_.lineEdit_5->text();
  double goal_R = qstr_R.toDouble()*PI2/360;
  QString qstr_P = ui_.lineEdit_6->text();
  double goal_P = qstr_P.toDouble()*PI2/360;
  QString qstr_Y = ui_.lineEdit_7->text();
  double goal_Y = qstr_Y.toDouble()*PI2/360;

  aidin_msgs::RQT msgGoalOri;
  msgGoalOri.robot.resize(robotnum+1);
  msgGoalOri.x = goal_R;
  msgGoalOri.y = goal_P;
  msgGoalOri.z = goal_Y;

  ROS_INFO("goal : %f %f %f", goal_R, goal_P, goal_Y);

  for(int i = 1; i<=robotnum; i++) {
    if(robotarray[i] == 1) {
      msgGoalOri.robot[i] = 1;
    }
    else if(robotarray[i] == 0) {
      msgGoalOri.robot[i] = 0;
    }
  }
  goalOri_pub.publish(msgGoalOri);
}
void aidinPlugin2::on_doButton_clicked() {
  aidin_msgs::RQT msgDo;
  msgDo.robot.resize(robotnum+1);
  
  msgDo.doFlag = true;
  if (autoOn==true)
    msgDo.autoFlag = true;
  else if (autoOn==false)
    msgDo.autoFlag = false;

  ROS_INFO("auto : %s", msgDo.autoFlag ? "true" : "false");
  ROS_INFO("Do : %s", msgDo.doFlag ? "true" : "false");

  for(int i = 1; i<=robotnum; i++) {
    if(robotarray[i] == 1) {
      msgDo.robot[i] = 1;
    }
    else if(robotarray[i] == 0) {
      msgDo.robot[i] = 0;
    }
  }
  do_pub.publish(msgDo);
}
//slider functions
void aidinPlugin2::on_Camera_clicked() {
  Camera = ui_.Camera_angle->text();
  slider = Camera.toDouble();

  std::string check_topic;
  /*
  nh.setParam("/robot_name_topic", "/aidinvi1");
  nh.getParam("/robot_name_topic", check_topic);
  std::cout << "/robot_name_topic : " << check_topic << std::endl;

  nh.getParam("/aidinvi1/robot_name_topic", check_topic);
  std::cout << "/aidinvi1/robot_name_topic" << check_topic << std::endl;

  nh.getParam("/aidinvi2/robot_name_topic", check_topic);
  std::cout << "/aidinvi2/robot_name_topic" << check_topic << std::endl;*/

  msgAngle.x = slider;
  ROS_INFO("camera_angle : %f", slider);
  for(int i = 1; i<=robotnum; i++) {
    if(robotarray[i] == 1) {
      msgAngle.robot[i] = 1;
    }
    else if(robotarray[i] == 0) {
      msgAngle.robot[i] = 0;
    }
  }
  std::cout << msgAngle << std::endl;
  Camera_pub.publish(msgAngle);

}
void aidinPlugin2::on_Camera_slider_move(int value) {
  slider = value;
  Camera = QString::number(slider);
  ui_.Camera_angle->setText(Camera);

  msgAngle.x = slider;
  for(int i = 1; i<=robotnum; i++) {
    if(robotarray[i] == 1) {
      msgAngle.robot[i] = 1;
    }
    else if(robotarray[i] == 0) {
      msgAngle.robot[i] = 0;
    }
  }
  std::cout << msgAngle << std::endl;
  Camera_pub.publish(msgAngle);
}
void aidinPlugin2::on_Camera_slider_text(const QString &angle_text) {
  slider = angle_text.toDouble();
  ui_.Camera_slider->setValue(slider);
}

QString flat_angle;
std_msgs::Float32 msgflat;
double flat_angle2;
void aidinPlugin2::on_flat_angle_button()
{
  flat_angle = ui_.flat_angle_line->text();
  flat_angle2 = flat_angle.toDouble();

  std::string check_topic;
  /*
  nh.setParam("/robot_name_topic", "/aidinvi2");
  nh.getParam("/robot_name_topic", check_topic);
  std::cout << "/robot_name_topic : " << check_topic << std::endl;

  nh.getParam("/aidinvi1/robot_name_topic", check_topic);
  std::cout << "/aidinvi1/robot_name_topic : " << check_topic << std::endl;

  nh.getParam("/aidinvi2/robot_name_topic", check_topic);
  std::cout << "/aidinvi2/robot_name_topic : " << check_topic << std::endl;*/

  msgflat.data = flat_angle2;
  flat_angle_pub.publish(msgflat);
}

void msgCallbackrobotnumber(const std_msgs::Float32::ConstPtr &msg) {
  int numbering = msg->data;
  robotnum = numbering;
}

//set initial connection of gui and functions
void aidinPlugin2::connectionfunc()
{
    QObject::connect(ui_.pushButton, SIGNAL(clicked()),
            this, SLOT(on_pushButton_clicked1()) ); 
    QObject::connect(ui_.listView, SIGNAL(clicked(const QModelIndex &)),
            this, SLOT(onClickListItem(const QModelIndex &))  );
    QObject::connect(ui_.pushButton_2, SIGNAL(clicked()),
            this, SLOT(on_pushButton_2_clicked1())  );
    QObject::connect(ui_.checkBox, SIGNAL(toggled(bool )),
            this, SLOT(onChecked(bool ))  );
    QObject::connect(ui_.pushButton_4, SIGNAL(clicked()),
            this, SLOT(on_quitButton_clicked())  );
    QObject::connect(ui_.pushButton_5, SIGNAL(clicked()),
            this, SLOT(on_enterGoalPosButton_clicked())  );
    QObject::connect(ui_.pushButton_7, SIGNAL(clicked()),
            this, SLOT(on_enterGoalOriButton_clicked())  );
    QObject::connect(ui_.checkBox_2, SIGNAL(toggled(bool )),
            this, SLOT(onChecked_2(bool ))  );
    QObject::connect(ui_.pushButton_6, SIGNAL(clicked()),
            this, SLOT(on_doButton_clicked())  );
    //slider functions
    QObject::connect(ui_.Camera, SIGNAL(clicked()),
            this, SLOT(on_Camera_clicked())   );
    /*QObject::connect(ui_.Camera_slider, SIGNAL(valueChanged(int)),
            this, SLOT(on_Camera_slider_changed(int))   );*/
    QObject::connect(ui_.Camera_angle, SIGNAL(textChanged(const QString &)),
            this, SLOT(on_Camera_slider_text(const QString &))  );
    QObject::connect(ui_.Camera_slider, SIGNAL(sliderMoved(int)),
            this, SLOT(on_Camera_slider_move(int))  );
    QObject::connect(ui_.flat_angle_button, SIGNAL(clicked()), 
            this, SLOT(on_flat_angle_button())  );

    QObject::connect(ui_.aidinvi1, SIGNAL(toggled(bool )),
            this, SLOT(onChecked_aidinvi1(bool )) );
    QObject::connect(ui_.aidinvi2, SIGNAL(toggled(bool )),
            this, SLOT(onChecked_aidinvi2(bool )) );
    //"this" means source code, and in this case, it means "aidinPlugin".

}

void aidinPlugin2::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  QStringList argv = context.argv();
  // create QWidget
  widget_ = new QWidget();
  // extend the widget with all attributes and children from UI file
  ui_.setupUi(widget_);
  // add widget to the user interface
  context.addWidget(widget_);
/*
  rqt_aidin2_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"command", 100);
  gait_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGait", 1);
  goalPos_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGoalPos", 4);
  goalOri_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdGoalOri", 4);
  do_pub = nh.advertise<rqt_aidin2::msgaidin2>(robot_change+"rqt_cmdDo", 4);
  Camera_pub = nh.advertise<rqt_aidin2::msgaidin2>("/rqt_camera_angle", 1);
  flat_angle_pub = nh.advertise<std_msgs::Float32>("flat_angle", 1);
*/
  rqt_aidin2_pub = nh.advertise<aidin_msgs::RQT>("/command", 100);
  gait_pub = nh.advertise<aidin_msgs::RQT>("/rqt_cmdGait", 1);
  goalPos_pub = nh.advertise<aidin_msgs::RQT>("/rqt_cmdGoalPos", 4);
  goalOri_pub = nh.advertise<aidin_msgs::RQT>("/rqt_cmdGoalOri", 4);
  do_pub = nh.advertise<aidin_msgs::RQT>("/rqt_cmdDo", 4);
  Camera_pub = nh.advertise<aidin_msgs::RQT>("/rqt_camera_angle", 1);
  flat_angle_pub = nh.advertise<aidin_msgs::RQT>("flat_angle", 1);

  ros::Subscriber robotnumber_sub = nh.subscribe("/robotnumber", 1, msgCallbackrobotnumber);

  msgAngle.robot.resize(robotnum+1);
  msg.robot.resize(robotnum+1);

  // add menu to the listview
  model = new QStringListModel(this); //dynamic memories allocates
  QStringList list; //
  list  << "aidinvi walking_vis.launch"
        << "aidinvi walking_vis_test.launch"
        << "aidinvi aidinvi_cam_vision.launch"
        << "aidinvi aidinvi_cam_vision_multi.launch"
        << "aidinvi robots_auto"
        << "ros2pcl ros2pcl"
        << "ros2pcl flat2"
        << "rviz rviz" //set the menu list
        << "command: gait"
        << "plot: /gazebo/aidinvi_footpos"
        << "plot: /aidinvi_actp"
        << "plot: /gazebo/aidinvi_jointt"
        << "plot: /aidinvi_actrawt"
        << "plot: /aidinvi_actt"
        << "plot: /aidinvi_contact"
        << "command: Foottrajectory" //msg topic command
        << "command: Footprint"
        << "command: Cobtrajectory"
        ;
  model->setStringList(list);
  ui_.listView->setModel(model);

  model2 = new QStringListModel(this);

  //slider setting
  ui_.Camera_slider->setMaximum(360);
  ui_.Camera_slider->setMinimum(0);
  ui_.Camera_slider->setValue(80);
  ui_.Camera_angle->setText("80");

  connectionfunc();
}

//additional functions must exist before shutdownPlugin function!!!!!!!!!!!!!
void aidinPlugin2::shutdownPlugin()
{
  // unregister all publishers here
}

void aidinPlugin2::saveSettings(qt_gui_cpp::Settings& plugin_settings,
    qt_gui_cpp::Settings& instance_settings) const
{
  // instance_settings.setValue(k, v)
}

void aidinPlugin2::restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
    const qt_gui_cpp::Settings& instance_settings)
{
  // v = instance_settings.value(k)
}

/*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/

}  // namespace rqt_aidin2

PLUGINLIB_EXPORT_CLASS(rqt_aidin2::aidinPlugin2, rqt_gui_cpp::Plugin)
