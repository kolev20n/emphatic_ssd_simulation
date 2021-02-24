#ifndef my_pht_primary_generator_action_h
#define my_pht_primary_generator_action_h

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4GeneralParticleSource.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;

class my_pht_primary_generator_action : public G4VUserPrimaryGeneratorAction
{
  public:
    my_pht_primary_generator_action();
    virtual ~my_pht_primary_generator_action();

    virtual void GeneratePrimaries(G4Event* an_event);
  
    const G4GeneralParticleSource* GetParticleGun() const {return my_particle_gun;}
  
  private:
    G4GeneralParticleSource *my_particle_gun;
};

#endif
