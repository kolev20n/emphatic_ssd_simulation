#ifndef my_pht_stepping_action_h
#define my_pht_stepping_action_h

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class my_pht_event_action;
class my_pht_histo_manager;

class my_pht_stepping_action : public G4UserSteppingAction
{
  public:
    my_pht_stepping_action(my_pht_event_action *an_event_action, my_pht_histo_manager* a_histo_manager);
    virtual ~my_pht_stepping_action();

    virtual void UserSteppingAction(const G4Step* a_step);

private:
  my_pht_event_action* my_event_action;
  my_pht_histo_manager* the_histo_manager;
};

#endif
