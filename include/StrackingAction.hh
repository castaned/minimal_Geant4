#ifndef StackingAction_h
#define StackingAction_h 1

#include "G4UserStackingAction.hh"
#include "G4VProcess.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"

#include "RunAction.hh"

class G4Track;
class RunAction;

class StackingAction : public G4UserStackingAction{
public:
  StackingAction(RunAction* Run) : fRunAction(Run){}
  G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* trk) override{
    if (trk -> GetParentID()>0){
      G4String     name = trk->GetDefinition()->GetParticleName();
      G4double     ekin = trk->GetKineticEnergy();
      G4ThreeVector pos = trk->GetPosition();
      G4ThreeVector mom = trk->GetMomentumDirection();
      G4String     proc = trk->GetCreatorProcess() ?
	                  trk->GetCreatorProcess()->GetProcessName() : "primary";

      fRunAction -> RecordSecondary(name,ekin,pos,mom,proc);

    }
    return fUrgent;
  }
  
private:
  RunAction*fRunAction;
  
};

#endif
