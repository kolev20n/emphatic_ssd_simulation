#ifndef my_pht_session_h
#define my_pht_session_h

#include <fstream>

#include "G4UIsession.hh"
#include "G4String.hh"

class my_pht_session : public G4UIsession
{
public:
  my_pht_session();
  ~my_pht_session();
  virtual G4int ReceiveG4cout(const G4String& coutString);
  
  std::ofstream log_file;
};

#endif

