#include "my_pht_event_action.hh"
#include "my_pht_run_action.hh"
#include "my_pht_histo_manager.hh"

#include "globals.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"

my_pht_event_action::my_pht_event_action(my_pht_run_action *a_run_action, my_pht_histo_manager* a_histo_manager)
: G4UserEventAction(),
  my_run_action(a_run_action),
  the_histo_manager(a_histo_manager)
{
}

my_pht_event_action::~my_pht_event_action()
{
}

void my_pht_event_action::BeginOfEventAction(const G4Event* an_event)
{
  the_histo_manager->initialize_particle_info();
  the_histo_manager->initialize_energy_arrays();
}

void my_pht_event_action::EndOfEventAction(const G4Event* an_event)
{
  the_histo_manager->fill_ntuples();
  
  if ((an_event->GetEventID() + 1) % 1000 == 0)
  {
    G4cout << an_event->GetEventID() + 1 << G4endl;
  }
}
