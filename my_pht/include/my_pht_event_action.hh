#ifndef my_pht_event_action_h
#define my_pht_event_action_h

#include "G4UserEventAction.hh"
#include "globals.hh"

class my_pht_run_action;
class my_pht_histo_manager;

class my_pht_event_action : public G4UserEventAction
{
public:
  my_pht_event_action(my_pht_run_action* run_action, my_pht_histo_manager* a_histo_manager);
  virtual ~my_pht_event_action();

  virtual void BeginOfEventAction(const G4Event* event);
  virtual void EndOfEventAction(const G4Event* event);

private:
  my_pht_run_action* my_run_action;
  my_pht_histo_manager* the_histo_manager;
};

#endif

    
