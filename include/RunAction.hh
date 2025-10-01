#pragma once
#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"

#include "SecondaryInfo.hh"

#include <vector>

class RunAction : public G4UserRunAction {
public:
  RunAction();
  ~RunAction() override = default;

  void BeginOfRunAction(const G4Run*) override;
  void EndOfRunAction(const G4Run*) override;

  void RecordSecondary(const G4String& name, G4double ekin,
		       const G4ThreeVector& pos, const G4ThreeVector& mom,
		       const G4String& proc) {
    fSecondaries.push_back({name, ekin, pos, mom, proc});
  };

private:
  std::vector<SecondaryInfo> fSecondaries;
};
