#pragma once
#include "G4VSensitiveDetector.hh"
#include <vector>
#include <unordered_map>

class TargetProcessSD: public G4VSensitiveDetector {
public:
  TargetProcessSD(const G4String& name, G4int nBins, G4double halfZ);
  ~TargetProcessSD() override = default;
  G4bool ProcessHits (G4Step* step, G4TouchableHistory*) override;
  const std::vector<std::unordered_map<int,int>>& Counts () const {return fCounts;}

  
private:
  G4int fNBins;
  G4double fHalfZ;
  std::vector<std::unordered_map<int,int>> fCounts;
};
