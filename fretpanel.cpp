#include "fretpanel.h"
#include "keymap.h"
#include "midi.h"
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>

FretPanel::FretPanel(QWidget *parent)
  : QWidget(parent) 
{
  setFocusPolicy(Qt::StrongFocus);
  setPalette(QPalette(Qt::white));
  setAutoFillBackground(true);
  setMinimumSize(295,100);
  space_is_down = 0;
}

void FretPanel::paintEvent(QPaintEvent * /* event */)
{
  QPainter painter(this);

  int w = rect().width();
  int h_interval = (w-2*h_margin)/(num_vertical_bars-1);
  //  w = h_interval*(num_vertical_bars-1);

  int h = rect().height();
  int v_interval = (h-2*v_margin)/(num_horizontal_bars-1);
  h = v_interval*(num_horizontal_bars-1);

  painter.setPen(QColor(150,150,150));
  
  for(int i=0;i<num_vertical_bars;i++)
    painter.drawLine(i*h_interval+h_margin,v_margin,i*h_interval+h_margin,h+v_margin);

  for(int i=0;i<num_horizontal_bars;i++)
    painter.drawLine(h_margin,i*v_interval+v_margin,w,i*v_interval+v_margin);

  int x;int y;
  painter.setPen(Qt::NoPen);
  painter.setBrush(QColor(0,0,0));
  painter.setRenderHint(QPainter::Antialiasing);

  list<int>keys_pressed_copy = keys_pressed;//use copy to avoid race condition
  for(list<int>::iterator i = keys_pressed_copy.begin();i != keys_pressed_copy.end();i++) {
    translate_key_to_grid(*i,x,y);
    painter.drawEllipse(h_margin+x*h_interval-circle_size/2,v_margin+h-y*v_interval-circle_size/2,circle_size,circle_size);
  }
}
void FretPanel::keyPressEvent(QKeyEvent *event){
  if(event->isAutoRepeat()) return;
  if(event->key() == 0x20 /*space*/)
    space_is_down = 1;
  else{
    int key_held = 0;
    for(list<int>::iterator i = keys_pressed.begin();i != keys_pressed.end();i++)
      if(*i == event->key()){key_held = 1;break;}
    
    if(key_held){
      keys_held.remove(event->key());
      key_up_queue.push(event->key());
      keys_pressed.remove(event->key());
      update();
    }
    else{
      key_down_queue.push(event->key());
      keys_pressed.push_front(event->key());
      update();
    }
  }
}
void FretPanel::keyReleaseEvent(QKeyEvent *event){
  if(event->isAutoRepeat()) return;
  if(event->key() == 0x20 /*space*/){
    space_is_down = 0;
    for(list<int>::iterator i = keys_held.begin();i != keys_held.end();i++){
      keys_pressed.remove(*i);
      key_up_queue.push(*i);
    }
    keys_held.clear();
    update();
  }
  else{
    if(!space_is_down){
      key_up_queue.push(event->key());
      keys_pressed.remove(event->key());
      update();
    }
    else
      keys_held.push_front(event->key());
  }
}
