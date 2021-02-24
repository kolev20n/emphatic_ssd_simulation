#include <iostream>
#include <string>

#include "my_pht_stepping_action.hh"
#include "my_pht_event_action.hh"
#include "my_pht_detector_construction.hh"
#include "my_pht_histo_manager.hh"
#include "my_pht_data_structures.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4RotationMatrix.hh"

using namespace std;

my_pht_stepping_action::my_pht_stepping_action(my_pht_event_action *an_event_action, my_pht_histo_manager* a_histo_manager)
: G4UserSteppingAction(),
  my_event_action(an_event_action),
  the_histo_manager(a_histo_manager)
{
}

my_pht_stepping_action::~my_pht_stepping_action()
{
}

void my_pht_stepping_action::UserSteppingAction(const G4Step* a_step)
{
  my_pht_step_info a_step_info;
  
  G4StepPoint* the_pre_step_point = a_step->GetPreStepPoint();
  G4StepPoint* the_post_step_point = a_step->GetPostStepPoint();
  
  G4TouchableHistory* touch_pre = (G4TouchableHistory*)(the_pre_step_point->GetTouchable());
  G4TouchableHistory* touch_post = (G4TouchableHistory*)(the_post_step_point->GetTouchable());
  
  if (touch_pre != nullptr)
  {
    a_step_info.volume_name = touch_pre->GetVolume()->GetName();
    
    if (touch_pre->GetVolume()->GetName() == "physical_ssd_strip")
    {
      a_step_info.plate_id = touch_pre->GetVolume(2)->GetCopyNo();
    }
    else
    {
      a_step_info.plate_id = -1;
    }
  }
  else
  {
    a_step_info.volume_name = "NA";
  }
  
  if (the_pre_step_point != nullptr && the_pre_step_point->GetProcessDefinedStep() != nullptr)
  {
    a_step_info.initial_energy = the_pre_step_point->GetKineticEnergy();
    a_step_info.process = the_pre_step_point->GetProcessDefinedStep()->GetProcessName();
  }
  else
  {
    a_step_info.initial_energy = -1.;
    a_step_info.process = "NA";
  }
  
  if (the_post_step_point != nullptr && the_post_step_point->GetProcessDefinedStep() != nullptr)
  {
    a_step_info.final_energy = the_post_step_point->GetKineticEnergy();
  }
  else
  {
    a_step_info.final_energy = -1.;
  }
  
  if (the_pre_step_point != nullptr)
  {
    G4ThreeVector temp_vector = the_pre_step_point->GetPosition();
    a_step_info.x_step_i = temp_vector.x();
    a_step_info.y_step_i = temp_vector.y();
    a_step_info.z_step_i = temp_vector.z();

    temp_vector = the_pre_step_point->GetMomentum();
    a_step_info.px_step_i = temp_vector.x();
    a_step_info.py_step_i = temp_vector.y();
    a_step_info.pz_step_i = temp_vector.z();
  }
  
  if (the_post_step_point != nullptr)
  {
    G4ThreeVector temp_vector = the_post_step_point->GetPosition();
    a_step_info.x_step_f = temp_vector.x();
    a_step_info.y_step_f = temp_vector.y();
    a_step_info.z_step_f = temp_vector.z();

    temp_vector = the_post_step_point->GetMomentum();
    a_step_info.px_step_f = temp_vector.x();
    a_step_info.py_step_f = temp_vector.y();
    a_step_info.pz_step_f = temp_vector.z();
  }
  
  the_histo_manager->add_step(a_step_info);
  
  if (touch_pre->GetVolume()->GetName() == "physical_ssd_strip")
  {
    G4int strip_number = touch_pre->GetVolume()->GetCopyNo();
    G4int mother_copy_number = touch_pre->GetVolume(1)->GetCopyNo();
    G4int plate_number = touch_pre->GetVolume(2)->GetCopyNo();
    G4int replica_number = touch_pre->GetReplicaNumber();
    
    if (a_step->GetTotalEnergyDeposit() != 0.)
    {
      the_histo_manager->add_total_energy_deposited(plate_number, replica_number, a_step->GetTotalEnergyDeposit(), a_step->GetTrack()->GetTrackID());
      the_histo_manager->add_non_ionization_energy_deposited(plate_number, replica_number, a_step->GetNonIonizingEnergyDeposit());
      
cout << a_step->GetTrack()->GetTrackID() << " " <<  a_step->GetTrack()->GetVertexPosition() << endl;
cout << plate_number << " " << strip_number << " " << touch_pre->GetReplicaNumber() << " " << a_step->GetTotalEnergyDeposit() << " " << a_step->GetTrack()->GetTrackID() << endl;
    }
  }
 
  
  if (the_pre_step_point != nullptr)
  {
    //cout << "pre " << the_pre_step_point->GetPosition() << endl;
  }
  
  if (the_post_step_point != nullptr)
  {
    //cout << "post " << the_post_step_point->GetPosition() << endl;
  }
  
}
