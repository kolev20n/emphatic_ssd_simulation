#include "my_pht_session.hh"

my_pht_session::my_pht_session()
{
  log_file.open("output.txt");
}

my_pht_session::~my_pht_session()
{
  log_file.close();
}

G4int my_pht_session::ReceiveG4cout(const G4String& coutString)
{
  log_file << coutString;
  return 0;
}
