#ifndef my_pht_data_structures_h
#define my_pht_data_structures_h

#include <vector>
#include <string>

const int number_of_plates = 13;

class my_pht_track_info
{
public:
  int track_id;
  int particle_code;
  int parent_track_id;
  std::string creator_process;
  double  x_vertex,  y_vertex,  z_vertex; // where it is created
  double px_vertex, py_vertex, pz_vertex; // this is the momentum direction
  double ekin_vertex;
};

class my_pht_step_info
{
public:
  std::string volume_name;
  int plate_id; // -1 if not in ssd_strip
  double  x_step_i,  y_step_i,  z_step_i; // initial position of the step
  double px_step_i, py_step_i, pz_step_i;
  double  x_step_f,  y_step_f,  z_step_f; // final position of the step
  double px_step_f, py_step_f, pz_step_f;
  double initial_energy, final_energy; // kinetic energies
  std::string process;
};

class my_pht_particle_info
{
public:
  my_pht_particle_info();
  ~my_pht_particle_info();
  
  void initialize();
  void add_track(my_pht_track_info a_track_info);
  void add_step(my_pht_step_info a_step_info);
  void print();
  void set_strip_visit(int a_plate_id);
  my_pht_track_info get_track_info();
  int get_is_strip_visited(int a_plate_of_strips);
  my_pht_step_info get_step_info(int a_step_number);
  int get_number_of_steps();
  
//private:
  my_pht_track_info the_track_info;
  std::vector<my_pht_step_info> the_step_infos;
  int visited_strips[number_of_plates];
};

#endif
