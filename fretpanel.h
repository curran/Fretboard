#ifndef FRETPANEL_H
#define FRETPANEL_H

#include <QWidget>
#include <list>
using namespace std;

class FretPanel : public QWidget
{
 public:
  FretPanel(QWidget *parent = 0);

 protected:
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  
 private:
  list< int > keys_pressed;
  list< int > keys_held; //keys kept in keys_pressed after they were released because the spacebar was down
  int space_is_down;

  static const int h_margin = 10;
  static const int v_margin = 10;
  static const int num_vertical_bars = 16;
  static const int num_horizontal_bars = 4;
  static const int circle_size = 14;

};


#endif
