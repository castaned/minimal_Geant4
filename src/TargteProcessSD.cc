#include "TargetProcessSD.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4TouchableHistory.hh"

TargetProcessSD::TargetProcessSD(const G4String& name, G4int nBins, G4double halfZ) : G4VSensitiveDetector(name), fNBins(nBins), fHalfZ(halfZ), fCounts(nBins) {}

G4bool TargetProcessSD::ProcessHits(G4Step * step, G4TouchableHistory*){
  auto * proc = step->GetPostStepPoint()->GetProcessDefinedStep();
  if (!proc) return false;

  auto pname = proc->GetProcessName();
  if (pname == "Transportation" || pname == "StepLimiter") return false;

  auto pre   = step->GetPreStepPoint();
  auto glob  = pre->GetPosition();
  auto local = pre->GetTouchableHandle()->GetHistory()->GetTopTransform().TransformPoint(glob);
  int zbin = int((local.z()+fHalfZ)/(2.*fHalfZ) * fNBins);

  if (zbin < 0) zbin = 0;
  if (zbin > fNBins) zbin =fNBins-1;
  int subtype = proc->GetProcessSubType();
  fCounts[zbin][subtype]++;
  return true; 

}
