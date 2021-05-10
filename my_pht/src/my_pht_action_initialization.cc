#include "my_pht_action_initialization.hh"
#include "my_pht_primary_generator_action.hh"
#include "my_pht_run_action.hh"
#include "my_pht_event_action.hh"
#include "my_pht_stepping_action.hh"
#include "my_pht_tracking_action.hh"
#include "my_pht_histo_manager.hh"

my_pht_action_initialization::my_pht_action_initialization(my_pht_histo_manager *a_histo_manager)
: G4VUserActionInitialization(),
the_histo_manager(a_histo_manager)
{
}

my_pht_action_initialization::~my_pht_action_initialization()
{
}

void my_pht_action_initialization::BuildForMaster() const
{
  my_pht_run_action* run_action = new my_pht_run_action(the_histo_manager);
  SetUserAction(run_action);
}

void my_pht_action_initialization::Build() const
{
  SetUserAction(new my_pht_primary_generator_action());

  my_pht_run_action* run_action = new my_pht_run_action(the_histo_manager);
  SetUserAction(run_action);
  
  my_pht_event_action* event_action = new my_pht_event_action(run_action, the_histo_manager);
  SetUserAction(event_action);
  
  my_pht_tracking_action* tracking_action = new my_pht_tracking_action(the_histo_manager);
  SetUserAction(tracking_action);
  
  SetUserAction(new my_pht_stepping_action(event_action, the_histo_manager));
}  
