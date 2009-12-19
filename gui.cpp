#include "gui.h"
#include "fretpanel.h"
#include "midi.h"
#include "instrument.h"
#include <QSpinBox>
#include <QLabel>
#include <QWidget>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCloseEvent>
#include <QVariant>
#include <iostream>

GUI::GUI(QWidget *parent)
  : QWidget(parent)
{
  FretPanel *grid = new FretPanel;
  QWidget *controls = new QWidget;

  instrument_selector.setFocusProxy(grid);
  connect(&instrument_selector, SIGNAL(activated(int)),
	  this, SLOT(selectInstrument(int)));

  Instrument guitar;
  guitar.setLowestNote(62);
  guitar.setOffset(0,0);
  guitar.setOffset(1,5);
  guitar.setOffset(2,9);
  guitar.setOffset(3,14);
  QVariant guitarVariant(QVariant::UserType);
  guitarVariant.setValue(guitar);
  instrument_selector.addItem(tr("Guitar"),guitarVariant);

  Instrument bass;
  bass.setLowestNote(40);
  bass.setOffset(0,0);
  bass.setOffset(1,5);
  bass.setOffset(2,10);
  bass.setOffset(3,15);

  QVariant bassVariant(QVariant::UserType);
  bassVariant.setValue(bass);
  instrument_selector.addItem(tr("Bass"),bassVariant);


  Instrument cello;
  cello.setLowestNote(48);
  cello.setOffset(0,0);
  cello.setOffset(1,7);
  cello.setOffset(2,14);
  cello.setOffset(3,21);
  QVariant celloVariant(QVariant::UserType);
  celloVariant.setValue(cello);
  instrument_selector.addItem(tr("Cello"),celloVariant);

  Instrument violin;
  violin.setLowestNote(55);
  violin.setOffset(0,0);
  violin.setOffset(1,7);
  violin.setOffset(2,14);
  violin.setOffset(3,21);
  QVariant violinVariant(QVariant::UserType);
  violinVariant.setValue(violin);
  instrument_selector.addItem(tr("Violin"),violinVariant);

  QSpinBox *lowest_note_selector = new QSpinBox;
  lowest_note_selector->setMinimum(0);
  lowest_note_selector->setMaximum(255);
  lowest_note_selector->setValue(50);
  connect(lowest_note_selector, SIGNAL(valueChanged(int)), this, SLOT(setLowestNote(int)));
  connect(this,SIGNAL(lowestNoteChanged(int)),lowest_note_selector,SLOT(setValue(int)));

  QHBoxLayout *controls_layout = new QHBoxLayout;
  controls_layout->addWidget(&instrument_selector);
  controls_layout->addWidget(new QLabel(tr("Base:")));
  controls_layout->addWidget(lowest_note_selector);
  controls_layout->addWidget(new QLabel(tr("Offsets:")));
  controls_layout->setContentsMargins(0,0,0,0);
  controls_layout->setSpacing(2);

  QSpinBox *offset0_control = new QSpinBox();
  connect(offset0_control, SIGNAL(valueChanged(int)), this, SLOT(setOffset0(int)));
  connect(this,SIGNAL(offset0Changed(int)),offset0_control,SLOT(setValue(int)));
  controls_layout->addWidget(offset0_control);

  QSpinBox *offset1_control = new QSpinBox();
  connect(offset1_control, SIGNAL(valueChanged(int)), this, SLOT(setOffset1(int)));
  connect(this,SIGNAL(offset1Changed(int)),offset1_control,SLOT(setValue(int)));
  controls_layout->addWidget(offset1_control);

  QSpinBox *offset2_control = new QSpinBox();
  connect(offset2_control, SIGNAL(valueChanged(int)), this, SLOT(setOffset2(int)));
  connect(this,SIGNAL(offset2Changed(int)),offset2_control,SLOT(setValue(int)));
  controls_layout->addWidget(offset2_control);

  QSpinBox *offset3_control = new QSpinBox();
  connect(offset3_control, SIGNAL(valueChanged(int)), this, SLOT(setOffset3(int)));
  connect(this,SIGNAL(offset3Changed(int)),offset3_control,SLOT(setValue(int)));
  controls_layout->addWidget(offset3_control);

  controls->setLayout(controls_layout);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(controls);
  layout->addWidget(grid);
  layout->setContentsMargins(0,0,0,0);
  layout->setSpacing(0);
  setLayout(layout);

  grid->setFocus(Qt::OtherFocusReason);

  selectInstrument(instrument_selector.currentIndex());
}

void GUI::closeEvent(QCloseEvent *event){
  disconnect_from_jack();
  event->accept();
}

void GUI::selectInstrument(int i){
  instrument = instrument_selector.itemData(i).value<Instrument>();
  emit lowestNoteChanged(instrument.getLowestNote());
  emit offset0Changed(instrument.getOffset(0));
  emit offset1Changed(instrument.getOffset(1));
  emit offset2Changed(instrument.getOffset(2));
  emit offset3Changed(instrument.getOffset(3));
}

void GUI::setLowestNote(int note){
  if(instrument.getLowestNote() != note){
    cout << "here";flush(cout);
    instrument.setLowestNote(note);
    emit lowestNoteChanged(note);
  }
}
void GUI::setOffset0(int offset){
  if(instrument.getOffset(0) != offset){
    instrument.setOffset(0,offset);
    emit offset0Changed(offset);
  }
}
void GUI::setOffset1(int offset){
  if(instrument.getOffset(1) != offset){
    instrument.setOffset(1,offset);
    emit offset1Changed(offset);
  }
}
void GUI::setOffset2(int offset){
  if(instrument.getOffset(2) != offset){
    instrument.setOffset(2,offset);
    emit offset2Changed(offset);
  }
}
void GUI::setOffset3(int offset){
  if(instrument.getOffset(3) != offset){
    instrument.setOffset(3,offset);
    emit offset3Changed(offset);
  }
}
