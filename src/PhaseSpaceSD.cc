#include "PhaseSpaceSD.hh"
#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

G4bool PhaseSpaceSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
  // Registrar SOLO cuando el paso ENTRA al volumen sensible
  if (step->GetPreStepPoint()->GetStepStatus() != fGeomBoundary) return false;

  auto* p   = step->GetTrack()->GetDynamicParticle();
  auto  pre = step->GetPreStepPoint();

  const auto pos = pre->GetPosition();              // posición de entrada al plano
  const auto dir = p->GetMomentumDirection();
  const auto Ek  = p->GetKineticEnergy();
  const auto t   = step->GetTrack()->GetGlobalTime();
  const auto w   = step->GetTrack()->GetWeight();
  const auto pdg = p->GetDefinition()->GetPDGEncoding();

  auto man = G4AnalysisManager::Instance();
  man->FillNtupleDColumn(0, pos.x()/mm);
  man->FillNtupleDColumn(1, pos.y()/mm);
  man->FillNtupleDColumn(2, pos.z()/mm);
  man->FillNtupleDColumn(3, dir.x());
  man->FillNtupleDColumn(4, dir.y());
  man->FillNtupleDColumn(5, dir.z());
  man->FillNtupleDColumn(6, Ek/MeV);
  man->FillNtupleDColumn(7, t/ns);
  man->FillNtupleDColumn(8, w);
  man->FillNtupleIColumn(9, pdg);
  man->AddNtupleRow();
  return true;
}

