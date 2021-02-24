#include "my_pht_primary_generator_action.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

my_pht_primary_generator_action::my_pht_primary_generator_action()
: G4VUserPrimaryGeneratorAction(), my_particle_gun(0)
{
  my_particle_gun = new G4GeneralParticleSource();

  // default particle kinematic

}

my_pht_primary_generator_action::~my_pht_primary_generator_action()
{
  delete my_particle_gun;
}

void my_pht_primary_generator_action::GeneratePrimaries(G4Event* an_event)
{
 
  //my_particle_gun->SetParticlePosition(G4ThreeVector(1.*cm, 0.5*cm, -0.2*m));

  my_particle_gun->GeneratePrimaryVertex(an_event);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

