#pragma once
#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();
  ~PrimaryGeneratorAction() override;

  void GeneratePrimaries(G4Event* event) override;

private:
  G4ParticleGun* fGun = nullptr;
  G4double fE_MeV       = 6.0;
  G4double fSigmaX_mm   = 1.0;
  G4double fSigmaY_mm   = 1.0;
  G4double fSigmaTh_mrad= 3.0;
  G4double fZ0_mm       = -10.0;
};
