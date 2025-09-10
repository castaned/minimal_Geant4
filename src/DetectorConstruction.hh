#pragma once
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  DetectorConstruction() = default;
  ~DetectorConstruction() override = default;
  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;

private:
  G4LogicalVolume* fPlaneLV = nullptr;
};
