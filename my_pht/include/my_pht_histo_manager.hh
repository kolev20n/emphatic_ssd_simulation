#ifndef my_pht_histo_manager_h
#define my_pht_histo_manager_h

#include <vector>
#include <string>
#include <map>

#include "globals.hh"

#include "my_pht_data_structures.hh"

class TFile;
class TTree;

class my_pht_histo_manager
{
public:
  my_pht_histo_manager();
  ~my_pht_histo_manager();
  
  void Book();
  void Save();
  
  void initialize_energy_arrays();
  void initialize_particle_info();
  void initialize_current_particle();
  void initialize_track(my_pht_track_info a_track_info);
  
  void add_total_energy_deposited(G4int a_plate_number, G4int a_strip_number, G4double an_energy, G4int a_contributing_track);
  void add_non_ionization_energy_deposited(G4int a_plate_number, G4int a_strip_number, G4double an_energy);
  void add_track();
  void add_step(my_pht_step_info a_step_info);
  void fill_ntuples();
  void print_high_energy_particle_map();
  
private:
  my_pht_particle_info current_particle;
  std::vector<my_pht_particle_info> the_particle_info;
  
  G4double the_total_energy_deposited[number_of_plates][2560];
  G4double the_non_ionization_energy_deposited[number_of_plates][2560];
  std::vector<int> contributing_tracks_list[number_of_plates][2560];
  
  std::vector<int> the_plate_number;
  std::vector<int> the_strip_number;
  std::vector<double> the_total_energy_values;
  std::vector<double> the_non_ionization_energy_values;
  std::vector<std::vector<double>> the_contributing_tracks;
  
  std::vector<int> track_id;
  std::vector<int> particle_code;
  std::vector<int> parent_track_id;
  std::vector<std::string> creator_process;
  std::vector<double> x_vertex;
  std::vector<double> y_vertex;
  std::vector<double> z_vertex;
  std::vector<double> px_vertex;
  std::vector<double> py_vertex;
  std::vector<double> pz_vertex;
  std::vector<double> ekin_vertex;
  std::vector<std::vector<double>> visited_plates;
  
  // step arrays; need the track id so that to avoid vector of vector etc.
  std::vector<int> step_track_id;
  std::vector<std::string> step_volume_name;
  std::vector<int> step_plate_id;
  std::vector<double> step_x_i;
  std::vector<double> step_y_i;
  std::vector<double> step_z_i;
  std::vector<double> step_px_i;
  std::vector<double> step_py_i;
  std::vector<double> step_pz_i;
  std::vector<double> step_x_f;
  std::vector<double> step_y_f;
  std::vector<double> step_z_f;
  std::vector<double> step_px_f;
  std::vector<double> step_py_f;
  std::vector<double> step_pz_f;
  std::vector<double> step_initial_energy;
  std::vector<double> step_final_energy;
  std::vector<std::string> step_process_name;
  
  TFile* my_root_file;
  TTree* my_ntuple_1;
  TTree* my_ntuple_2;
  TTree* my_ntuple_3;
  
  std::map<int, int> high_energy_particles;
};

#endif

