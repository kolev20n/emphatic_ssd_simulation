// This assumes a single thread.

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "my_pht_input_parameters.hh"

#include "my_pht_detector_construction.hh"
#include "my_pht_action_initialization.hh"
#include "my_pht_histo_manager.hh"
#include "my_pht_physics_list.hh"
#include "my_pht_session.hh"

#include <iostream>

int main(int argc,char** argv)
{
  my_pht_input_parameters my_input_parameters();
  
  G4UIExecutive* ui = 0;
  if (argc == 1)
  {
    ui = new G4UIExecutive(argc, argv);
  }
  
  G4Random::setTheEngine(new CLHEP::RanecuEngine);
  
  G4RunManager* my_run_manager = new G4RunManager();

  my_run_manager->SetUserInitialization(new my_pht_detector_construction());

  G4VModularPhysicsList* physics_list = new my_pht_physics_list();
  physics_list->SetVerboseLevel(1);
  my_run_manager->SetUserInitialization(physics_list);

  my_pht_histo_manager* my_histo_manager = new my_pht_histo_manager();

  my_run_manager->SetUserInitialization(new my_pht_action_initialization(my_histo_manager));

  G4VisManager* my_vis_manager = new G4VisExecutive();

  my_vis_manager->Initialize();
  
  G4UImanager* my_ui_manager = G4UImanager::GetUIpointer();

  // my_pht_session* logged_session = new my_pht_session();
  
  if (!ui)
  {
    // batch mode
    G4String command = "/control/execute ";
    G4String file_name = argv[1];
    my_ui_manager->ApplyCommand(command + file_name);
  }
  else
  {
    // interactive mode
    // my_ui_manager->SetCoutDestination(logged_session);
    my_ui_manager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }
  
  delete my_run_manager;
  delete my_histo_manager;
  delete my_vis_manager;
  // delete my_ui_manager;
 // delete logged_session;
  
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
