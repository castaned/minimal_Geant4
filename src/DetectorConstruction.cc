#include "DetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4VisAttributes.hh"
#include "PhaseSpaceSD.hh"

G4VPhysicalVolume* DetectorConstruction::Construct() {
  auto nist = G4NistManager::Instance();

  auto worldMat = nist->FindOrBuildMaterial("G4_AIR");
  auto W        = nist->FindOrBuildMaterial("G4_W");

  const G4double worldXY = 20.*cm;
  const G4double worldZ  = 20.*cm;

  auto solidWorld = new G4Box("World", worldXY/2, worldXY/2, worldZ/2);
  auto logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
  auto physWorld  = new G4PVPlacement(nullptr, {}, logicWorld, "World", nullptr, false, 0);

  //World Attributes 
  G4VisAttributes * WorldAttr = new G4VisAttributes;
  WorldAttr->SetVisibility(false);
  logicWorld->SetVisAttributes(WorldAttr);
  
  const G4double targetR   = 10.*mm;
  const G4double targetDz  = 1.*mm;
  auto solidTarget = new G4Tubs("Target", 0., targetR, targetDz, 0.*deg, 360.*deg);
  auto logicTarget = new G4LogicalVolume(solidTarget, W, "Target");
  new G4PVPlacement(nullptr, {0,0, +targetDz}, logicTarget, "Target", logicWorld, false, 0);

  //Target Attributes
  G4VisAttributes * TargetAttr = new G4VisAttributes(G4Colour::Gray);
  TargetAttr->SetVisibility(true);
  TargetAttr->SetForceSolid(true);
  logicTarget->SetVisAttributes(TargetAttr);
  
  const G4double planeXY = 40.*mm;
  const G4double planeDz = 5.*um;
  auto solidPlane = new G4Box("Plane", planeXY/2, planeXY/2, planeDz);
  fPlaneLV = new G4LogicalVolume(solidPlane, worldMat, "Plane");

  new G4PVPlacement(nullptr, {0,0, -0.05*mm}, fPlaneLV, "Plane", logicWorld, false, 0);

  //Plane Attributes
  G4VisAttributes * PlaneAttr = new G4VisAttributes(G4Colour::Blue);
  PlaneAttr->SetVisibility(true);
  PlaneAttr->SetForceSolid(true);
  fPlaneLV->SetVisAttributes(PlaneAttr);

    
  return physWorld;
}

void DetectorConstruction::ConstructSDandField() {
  auto sd = new PhaseSpaceSD("PhaseSpaceSD");
  auto sdm = G4SDManager::GetSDMpointer();
  sdm->AddNewDetector(sd);
  fPlaneLV->SetSensitiveDetector(sd);
}
