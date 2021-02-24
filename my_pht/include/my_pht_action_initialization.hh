#ifndef my_pht_action_initialization_h
#define my_pht_action_initialization_h

#include "G4VUserActionInitialization.hh"

class my_pht_histo_manager;

class my_pht_action_initialization : public G4VUserActionInitialization
{
public:
  my_pht_action_initialization(my_pht_histo_manager *a_histo_manager);
  virtual ~my_pht_action_initialization();

  virtual void BuildForMaster() const;
  virtual void Build() const;
  
private:
  my_pht_histo_manager* the_histo_manager;
};

#endif

    
