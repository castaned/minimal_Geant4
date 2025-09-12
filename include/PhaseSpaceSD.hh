#pragma once
#include "G4VSensitiveDetector.hh"

class PhaseSpaceSD : public G4VSensitiveDetector {
public:
  PhaseSpaceSD(const G4String& name) : G4VSensitiveDetector(name) {}
  ~PhaseSpaceSD() override = default;
  G4bool ProcessHits(G4Step* step, G4TouchableHistory*) override;
};
