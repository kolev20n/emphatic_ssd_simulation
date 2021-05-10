#include "my_pht_run_action.hh"
#include "my_pht_primary_generator_action.hh"
#include "my_pht_detector_construction.hh"
#include "my_pht_histo_manager.hh"

#include "G4RunManager.hh"
#include "G4Run.hh"

my_pht_run_action::my_pht_run_action(my_pht_histo_manager* a_histo_manager)
: G4UserRunAction(),
  the_histo_manager(a_histo_manager)
{}

my_pht_run_action::~my_pht_run_action()
{}

void my_pht_run_action::BeginOfRunAction(const G4Run* a_run)
{ 
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  the_histo_manager->Book();
}

void my_pht_run_action::EndOfRunAction(const G4Run* a_run)
{
  G4int number_of_events = a_run->GetNumberOfEvent();
  
  if (number_of_events == 0) return;
  
  the_histo_manager->Save();
  
  the_histo_manager->print_high_energy_particle_map();
}
