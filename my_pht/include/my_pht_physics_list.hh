#ifndef my_pht_physics_list_h
#define my_pht_physics_list_h

#include "G4VModularPhysicsList.hh"
#include "globals.hh"

/*
class G4Cerenkov;
class G4Scintillation;
class G4OpAbsorption;
class G4OpRayleigh;
class G4OpMieHG;
class G4OpBoundaryProcess;
*/

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class my_pht_physics_list: public G4VModularPhysicsList
{
public:
  my_pht_physics_list();
  ~my_pht_physics_list();

  virtual void ConstructParticle();
  void ConstructProcess();
  void ConstructGeneral();
  void ConstructEM();
  virtual void SetCuts();

private:

   
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
