#ifndef my_pht_run_action_h
#define my_pht_run_action_h

#include "G4UserRunAction.hh"
#include "G4Accumulable.hh"
#include "globals.hh"

class G4Run;
class my_pht_histo_manager;

class my_pht_run_action : public G4UserRunAction
{
  public:
    my_pht_run_action(my_pht_histo_manager* a_histo_manager);
    virtual ~my_pht_run_action();
    virtual void BeginOfRunAction(const G4Run* a_run);
    virtual void EndOfRunAction(const G4Run* a_run);
private:
  my_pht_histo_manager* the_histo_manager;
};

#endif

