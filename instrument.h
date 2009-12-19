#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include <fstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <QMetaType>

class Instrument
{
private:
  friend class boost::serialization::access;
  template<class Archive>
    void serialize(Archive & ar, const unsigned int /*version*/);
  int lowest_note;
  int offsets[4];
public:
  Instrument();
  int getNote(int x,int y);
  void setOffset(int y,int offset);
  int getOffset(int y);
  void setLowestNote(int note);
  int getLowestNote();
};
Q_DECLARE_METATYPE(Instrument)

#endif
