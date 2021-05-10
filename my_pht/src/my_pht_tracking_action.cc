#include "G4Step.hh"
#include "G4Track.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"

#include "my_pht_tracking_action.hh"
#include "my_pht_histo_manager.hh"
#include "my_pht_data_structures.hh"

using namespace std;

my_pht_tracking_action::my_pht_tracking_action(my_pht_histo_manager* a_histo_manager)
: G4UserTrackingAction(),
  the_histo_manager(a_histo_manager)
{}

my_pht_tracking_action::~my_pht_tracking_action()
{}

void my_pht_tracking_action::PreUserTrackingAction(const G4Track* a_track)
{
  the_histo_manager->initialize_current_particle();
}

void my_pht_tracking_action::PostUserTrackingAction(const G4Track* a_track)
{
  my_pht_track_info a_track_info;
  
  G4ParticleDefinition* particle_type = a_track->GetDefinition();
  
  a_track_info.track_id = a_track->GetTrackID();
  a_track_info.particle_code = particle_type->GetPDGEncoding();
  a_track_info.parent_track_id = a_track->GetParentID();
  
  if (a_track->GetCreatorProcess() != nullptr)
  {
    a_track_info.creator_process = a_track->GetCreatorProcess()->GetProcessName();
  }
  else
  {
    a_track_info.creator_process = "NA";
  }
  
  G4ThreeVector particle_position = a_track->GetVertexPosition();
  a_track_info.x_vertex = particle_position.x();
  a_track_info.y_vertex = particle_position.y();
  a_track_info.z_vertex = particle_position.z();

  G4ThreeVector particle_momentum_direction = a_track->GetVertexMomentumDirection();
  a_track_info.px_vertex = particle_momentum_direction.x();
  a_track_info.py_vertex = particle_momentum_direction.y();
  a_track_info.pz_vertex = particle_momentum_direction.z();

  a_track_info.ekin_vertex = a_track->GetVertexKineticEnergy();
  
  the_histo_manager->initialize_track(a_track_info);
  the_histo_manager->add_track();
  
  //cout << a_track->GetTrackID() << " " << a_track->GetParentID() << " " << a_track->GetDefinition()->GetPDGEncoding() << " " <<  a_track->GetVertexPosition() << " " << a_track->GetVertexKineticEnergy() << endl;
  //cout << "---------------" << endl;
}
