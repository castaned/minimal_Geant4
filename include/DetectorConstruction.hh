#pragma once
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
//#include "G4LogicalVolume"

class G4LogicalVolume;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  DetectorConstruction() = default;
  ~DetectorConstruction() override = default;
  G4VPhysicalVolume* Construct() override;
  void ConstructSDandField() override;
  G4LogicalVolume * GetTargetLV() const{ return fTargetLV;}
  
  
private:
  G4LogicalVolume * fPlaneLV  = nullptr;
  G4LogicalVolume * fTargetLV = nullptr;
};
