#include "instrument.h"

Instrument::Instrument(){}
int Instrument::getNote(int x,int y){ return lowest_note + x + offsets[y];}
void Instrument::setOffset(int y,int offset){ offsets[y] = offset;}
int Instrument::getOffset(int y){return offsets[y];}
void Instrument::setLowestNote(int note){ lowest_note = note;}
int Instrument::getLowestNote(){return lowest_note;}
template<class Archive>
void Instrument::serialize(Archive & ar, const unsigned int /*version*/)
{
  ar & lowest_note;
  ar & offsets;
}
