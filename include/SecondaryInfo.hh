#ifndef SecondaryInfo_h
#define SecondaryInfo_h 1

#include "globals.hh"
#include "G4ThreeVector.hh"

struct SecondaryInfo{
  G4String name;
  G4double ekin;
  G4ThreeVector pos;
  G4ThreeVector mom;
  G4String proc;
};

#endif
