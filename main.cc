#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "FTFP_BERT.hh"

#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"

int main(int argc, char** argv) {
  auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Serial);
  runManager->SetUserInitialization(new DetectorConstruction());
  runManager->SetUserInitialization(new FTFP_BERT());
  runManager->SetUserInitialization(new ActionInitialization());

  //runManager->Initialize();
  
  auto * visManager = new G4VisExecutive();
  visManager->Initialize();

  auto* UImanager = G4UImanager::GetUIpointer();

  if (argc == 1) {
    auto* ui = new G4UIExecutive(argc, argv);
    // Si quieres cargar visualización básica por defecto:
    UImanager->ApplyCommand("/control/execute macros/vis_start.mac");
    
    ui->SessionStart();
    delete ui;
  }else {
    G4String macro = argv[1];
    UImanager->ApplyCommand("/control/execute " + macro);
  }

  delete visManager;
  delete runManager;
  return 0;
}
