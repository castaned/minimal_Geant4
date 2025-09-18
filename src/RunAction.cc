#include <fstream>
#include "G4SDManager.hh"
#include "TargetProcessSD.hh"
#include "G4AnalysisManager.hh"
#include "RunAction.hh"

RunAction::RunAction() {
  auto man = G4AnalysisManager::Instance();

  // Usa el backend que tengas:
  man->SetDefaultFileType("root");   // o "csv" si no tienes ROOT
  man->SetFileName("phsp");

  // <<--- Activa el merging por C++ (funciona aunque no exista el comando de macro)
  man->SetNtupleMerging(true);

  man->CreateNtuple("phsp", "phase space at plane (before W target)");
  man->CreateNtupleDColumn("x_mm");
  man->CreateNtupleDColumn("y_mm");
  man->CreateNtupleDColumn("z_mm");
  man->CreateNtupleDColumn("ux");
  man->CreateNtupleDColumn("uy");
  man->CreateNtupleDColumn("uz");
  man->CreateNtupleDColumn("E_MeV");
  man->CreateNtupleDColumn("t_ns");
  man->CreateNtupleDColumn("w");
  man->CreateNtupleIColumn("pdg");
  man->FinishNtuple();
}

void RunAction::BeginOfRunAction(const G4Run*) { G4AnalysisManager::Instance()->OpenFile(); }
void RunAction::EndOfRunAction(const G4Run*)   {
  auto man=G4AnalysisManager::Instance(); man->Write(); man->CloseFile();

  //  auto tman =G4AnalysisManager::Instance();
  //tman->Write();
  //tman->CloseFile();

  if(!IsMaster()) return;
  auto* tsdm = G4SDManager::GetSDMpointer();
  auto* tsd  = dynamic_cast<TargetProcessSD*> (tsdm->FindSensitiveDetector("TargetProcSD",false));

  G4cout<<"tsd encontrado"<<G4endl;
    
  if(!tsd) return;
  const auto& counts = tsd->Counts();
  std::ofstream ofs("dominan_by_step.csv");
  ofs << "zbin,subtype,count\n";
  
  for (size_t b=0; b < counts.size(); ++b){
    int bestSubType = -1, bestCount = 0;
    for (const auto& kv : counts[b]){
      if (kv.second > bestCount){ bestCount = kv.second; bestSubType = kv.first;}
    }
    ofs << b << "," << bestSubType << "," << bestCount << "\n";

  }
  
}


