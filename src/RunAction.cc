
#include "G4SDManager.hh"
#include "G4AnalysisManager.hh"

#include "RunAction.hh"
#include "TargetProcessSD.hh"

#include <vector>
#include <fstream>
#include <map>


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

void RunAction::BeginOfRunAction(const G4Run*) {
  //Sensitive Detectors
  G4AnalysisManager::Instance()->OpenFile();

  //SecondaryParticles
  fSecondaries.clear();
  
}


void RunAction::EndOfRunAction(const G4Run*)   {

  //SensitiveDetectors
  auto man=G4AnalysisManager::Instance(); man->Write(); man->CloseFile();

  if(!IsMaster()) return;
  auto* tsdm = G4SDManager::GetSDMpointer();
  auto* tsd  = dynamic_cast<TargetProcessSD*> (tsdm->FindSensitiveDetector("TargetProcSD",false));

  G4cout<<"tsd encontrado"<<G4endl;
    
  if(!tsd) return;
  const auto& counts = tsd->Counts();
  std::ofstream ofs("dominant_by_depth.csv");
  ofs << "zbin,subtype,count\n";
  
  for (size_t b=0; b < counts.size(); ++b){
    int bestSubType = -1, bestCount = 0;
    for (const auto& kv : counts[b]){
      if (kv.second > bestCount){ bestCount = kv.second; bestSubType = kv.first;}
    }
    ofs << b << "," << bestSubType << "," << bestCount << "\n";

  }

  //SecondaryParticles

  std::map<G4String,int> typeCount;
  std::ofstream outFile("Secondary.csv");
  outFile<< "name,ekin_MeV,posX_mm,posY_mm,posZ_mm,"
	 << "momX,momY,momZ,process\n";
  for (auto& sec : fSecondaries){
    typeCount[sec.name]++;
    outFile << sec.name << ","
	    << sec.ekin/CLHEP::MeV << ","
	    << sec.pos.x()/CLHEP::mm << ","
            << sec.pos.y()/CLHEP::mm << ","
            << sec.pos.z()/CLHEP::mm << ","
            << sec.mom.x() << ","
	    << sec.mom.y() << ","
	    << sec.mom.z() << ","
	    << sec.proc << "\n";
  };

  outFile.close();

  G4cout << "\n === Secondary particle summary ===\n"<<G4endl;
  for (auto& kv : typeCount){
    G4cout << kv.first << ":" <<  kv.second <<G4endl;
  };
  
}


