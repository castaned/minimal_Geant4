#include "PrimaryGeneratorAction.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "G4Event.hh"
#include <cmath>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
  fGun = new G4ParticleGun(1);
  auto eMinus = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fGun->SetParticleDefinition(eMinus);
  fGun->SetParticleEnergy(fE_MeV*MeV);
  fGun->SetParticlePosition({0,0, fZ0_mm*mm});
  fGun->SetParticleMomentumDirection({0,0,1});
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() { delete fGun; }

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
  const G4double x = G4RandGauss::shoot(0., fSigmaX_mm)*mm;
  const G4double y = G4RandGauss::shoot(0., fSigmaY_mm)*mm;

  const G4double thx = G4RandGauss::shoot(0., fSigmaTh_mrad)*1.e-3;
  const G4double thy = G4RandGauss::shoot(0., fSigmaTh_mrad)*1.e-3;

  G4ThreeVector u(std::tan(thx), std::tan(thy), 1.0);
  u = u.unit();

  fGun->SetParticlePosition({x, y, fZ0_mm*mm});
  fGun->SetParticleMomentumDirection(u);
  fGun->SetParticleEnergy(fE_MeV*MeV);

  fGun->GeneratePrimaryVertex(event);
}
