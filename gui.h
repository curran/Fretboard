#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QComboBox>

class QCloseEvent;

class GUI : public QWidget
{
  Q_OBJECT

 public:
  GUI(QWidget *parent = 0);
 signals:
  void offset0Changed(int newOffset);
  void offset1Changed(int newOffset);
  void offset2Changed(int newOffset);
  void offset3Changed(int newOffset);
  void lowestNoteChanged(int newLowestNote);
 public slots:
  void setLowestNote(int note);
  void setOffset0(int offset);
  void setOffset1(int offset);
  void setOffset2(int offset);
  void setOffset3(int offset);
  void selectInstrument(int i);
 protected:
  void closeEvent(QCloseEvent *event);
 private:
  QComboBox instrument_selector;
};

#endif
