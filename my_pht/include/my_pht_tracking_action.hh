#ifndef my_pht_tracking_action_h
#define my_pht_tracking_action_h

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class my_pht_histo_manager;

class my_pht_tracking_action : public G4UserTrackingAction
{
public:
  my_pht_tracking_action(my_pht_histo_manager* a_histo_manager);
  virtual ~my_pht_tracking_action();
  void PreUserTrackingAction(const G4Track*);
  void PostUserTrackingAction(const G4Track*);
private:
  my_pht_histo_manager* the_histo_manager;
};

#endif

