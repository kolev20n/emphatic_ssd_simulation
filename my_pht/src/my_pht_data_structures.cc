#include "globals.hh"

#include "my_pht_data_structures.hh"

using namespace std;

my_pht_particle_info::my_pht_particle_info()
{
}

my_pht_particle_info::~my_pht_particle_info()
{
}

void my_pht_particle_info::initialize()
{
  the_track_info.track_id = -1;
  the_track_info.particle_code = 0;
  the_track_info.parent_track_id = -1;
  the_track_info.creator_process = "";
  the_track_info.x_vertex = 0.;
  the_track_info.y_vertex = 0.;
  the_track_info.z_vertex = -10000.;
  the_track_info.px_vertex = 100.; // these are components of the momentum direction only
  the_track_info.py_vertex = 100.;
  the_track_info.pz_vertex = 100.;
  the_track_info.ekin_vertex = -1.;
  
  the_step_infos.clear();
  
  for (int i = 0; i < number_of_plates; i++)
  {
    visited_strips[i] = 0;
  }
}

void my_pht_particle_info::add_track(my_pht_track_info a_track_info)
{
  the_track_info = a_track_info;
}

void my_pht_particle_info::add_step(my_pht_step_info a_step_info)
{
  the_step_infos.push_back(a_step_info);
}

void my_pht_particle_info::print()
{
  G4cout << "->->->-----------------------------" << G4endl;
  G4cout << the_track_info.track_id << " " << the_track_info.particle_code << " " << the_track_info.parent_track_id << " " << the_track_info.creator_process << " "
      << the_track_info.x_vertex << " "
  << the_track_info.y_vertex << " "
  << the_track_info.z_vertex << " "
  << the_track_info.px_vertex << " "
  << the_track_info.py_vertex << " "
  << the_track_info.pz_vertex << " "
  << the_track_info.ekin_vertex << G4endl;
  
  for (int i = 0; i < the_step_infos.size(); i++)
  {
    G4cout << the_step_infos[i].volume_name << " "
    << the_step_infos[i].plate_id << " "
    << the_step_infos[i].process << " "
    << the_step_infos[i].initial_energy << " "
    << the_step_infos[i].final_energy << " "
    << the_step_infos[i].z_step_i << " " << the_step_infos[i].z_step_f << G4endl;
  }
  
  for (int i = 0; i < number_of_plates; i++)
  {
    G4cout << visited_strips[i] << " ";
  }
  G4cout << G4endl;
}

void my_pht_particle_info::set_strip_visit(int a_plate_id)
{
  visited_strips[a_plate_id] = 1;
}

int my_pht_particle_info::get_is_strip_visited(int a_plate_of_strips)
{
  return visited_strips[a_plate_of_strips];
}

my_pht_track_info my_pht_particle_info::get_track_info()
{
  return the_track_info;
}

my_pht_step_info my_pht_particle_info::get_step_info(int a_step_number)
{
  return the_step_infos.at(a_step_number);
}

int my_pht_particle_info::get_number_of_steps()
{
  return the_step_infos.size();
}
