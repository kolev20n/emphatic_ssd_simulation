#include "globals.hh"
//#include "G4SystemOfUnits.hh"
#include "TFile.h"
#include "TTree.h"
//#include "G4RotationMatrix.hh"

#include "my_pht_histo_manager.hh"
#include "my_pht_data_structures.hh"

using namespace std;

my_pht_histo_manager::my_pht_histo_manager()
:my_root_file(0)
{
  high_energy_particles.clear();
}

my_pht_histo_manager::~my_pht_histo_manager()
{
  if (my_root_file) delete my_root_file;
}

void my_pht_histo_manager::initialize_energy_arrays()
{
  for (int i = 0; i < number_of_plates; i++)
  {
    for (int j = 0; j < 2560; j++)
    {
      the_total_energy_deposited[i][j] = 0.;
      the_non_ionization_energy_deposited[i][j] = 0.;
      contributing_tracks_list[i][j].clear();
    }
  }
  
  the_plate_number.clear();
  the_strip_number.clear();
  the_total_energy_values.clear();
  the_non_ionization_energy_values.clear();
  the_contributing_tracks.clear();

  
  track_id.clear();
  particle_code.clear();
  parent_track_id.clear();
  creator_process.clear();
  x_vertex.clear();
  y_vertex.clear();
  z_vertex.clear();
  px_vertex.clear();
  py_vertex.clear();
  pz_vertex.clear();
  ekin_vertex.clear();
  visited_plates.clear();
  
  step_track_id.clear();
  step_volume_name.clear();
  step_plate_id.clear();
  step_x_i.clear();
  step_y_i.clear();
  step_z_i.clear();
  step_px_i.clear();
  step_py_i.clear();
  step_pz_i.clear();
  step_x_f.clear();
  step_y_f.clear();
  step_z_f.clear();
  step_px_f.clear();
  step_py_f.clear();
  step_pz_f.clear();
  step_initial_energy.clear();
  step_final_energy.clear();
  step_process_name.clear();
}

void my_pht_histo_manager::Book()
{
  G4String file_name = "my_pht_06.root";
  my_root_file = new TFile(file_name,"RECREATE");
  
  if (!my_root_file)
  {
    G4cout << "my_pht_histo_manager::book: "
    << "problem creating the ROOT file."
    << G4endl;
    
    return;
  }
  
  my_ntuple_1 = new TTree("ssd_energy", "ssd_energy");
  my_ntuple_2 = new TTree("particle_truth", "particle_truth");
  my_ntuple_3 = new TTree("steps_truth", "steps_truth");

  my_ntuple_1->Branch("plate_id", "vector<int>", &the_plate_number);
  my_ntuple_1->Branch("strip_id", "vector<int>", &the_strip_number);
  my_ntuple_1->Branch("ssd_total_energy_deposited", "vector<double>", &the_total_energy_values);
  my_ntuple_1->Branch("ssd_non_ionization_energy_deposited", "vector<double>", &the_non_ionization_energy_values);
  my_ntuple_1->Branch("contributing_tracks", "vector<vector<double>>", &the_contributing_tracks);

  my_ntuple_2->Branch("track_id", "vector<int>", &track_id);
  my_ntuple_2->Branch("particle_code", "vector<int>", &particle_code);
  my_ntuple_2->Branch("parent_track_id", "vector<int>", &parent_track_id);
  my_ntuple_2->Branch("creator_process", "vector<string>", &creator_process);
  my_ntuple_2->Branch("x_vertex", "vector<double>", &x_vertex);
  my_ntuple_2->Branch("y_vertex", "vector<double>", &y_vertex);
  my_ntuple_2->Branch("z_vertex", "vector<double>", &z_vertex);
  my_ntuple_2->Branch("px_vertex", "vector<double>", &px_vertex);
  my_ntuple_2->Branch("py_vertex", "vector<double>", &py_vertex);
  my_ntuple_2->Branch("pz_vertex", "vector<double>", &pz_vertex);
  my_ntuple_2->Branch("ekin_vertex", "vector<double>", &ekin_vertex);
  my_ntuple_2->Branch("visited_plates", "vector<vector<double>>", &visited_plates);
  
  my_ntuple_3->Branch("step_track_id", "vector<int>", &step_track_id);
  my_ntuple_3->Branch("step_volume_name", "vector<string>", &step_volume_name);
  my_ntuple_3->Branch("step_plate_id", "vector<int>", &step_plate_id);
  my_ntuple_3->Branch("step_x_i", "vector<double>", &step_x_i);
  my_ntuple_3->Branch("step_y_i", "vector<double>", &step_y_i);
  my_ntuple_3->Branch("step_z_i", "vector<double>", &step_z_i);
  my_ntuple_3->Branch("step_px_i", "vector<double>", &step_px_i);
  my_ntuple_3->Branch("step_py_i", "vector<double>", &step_py_i);
  my_ntuple_3->Branch("step_pz_i", "vector<double>", &step_pz_i);
  my_ntuple_3->Branch("step_x_f", "vector<double>", &step_x_f);
  my_ntuple_3->Branch("step_y_f", "vector<double>", &step_y_f);
  my_ntuple_3->Branch("step_z_f", "vector<double>", &step_z_f);
  my_ntuple_3->Branch("step_px_f", "vector<double>", &step_px_f);
  my_ntuple_3->Branch("step_py_f", "vector<double>", &step_py_f);
  my_ntuple_3->Branch("step_pz_f", "vector<double>", &step_pz_f);
  my_ntuple_3->Branch("step_initial_energy", "vector<double>", &step_initial_energy);
  my_ntuple_3->Branch("step_final_energy", "vector<double>", &step_final_energy);
  my_ntuple_3->Branch("step_process_name", "vector<string>", &step_process_name);
}

void my_pht_histo_manager::Save()
{
  if (!my_root_file) return;
  
  my_root_file->Write();
  my_root_file->Close();
  
  G4cout << "Histograms and ntuples have been saved." << G4endl;
}

void my_pht_histo_manager::initialize_particle_info()
{
  the_particle_info.clear();
}

void my_pht_histo_manager::initialize_current_particle()
{
  current_particle.initialize();
}

void my_pht_histo_manager::initialize_track(my_pht_track_info a_track_info)
{
  current_particle.add_track(a_track_info);
}

void my_pht_histo_manager::add_total_energy_deposited(G4int a_plate_number, G4int a_strip_number, G4double an_energy, G4int a_contributing_track)
{
  the_total_energy_deposited[a_plate_number][a_strip_number] += an_energy;
  contributing_tracks_list[a_plate_number][a_strip_number].push_back(a_contributing_track);
}

void my_pht_histo_manager::add_non_ionization_energy_deposited(G4int a_plate_number, G4int a_strip_number, G4double an_energy)
{
  the_non_ionization_energy_deposited[a_plate_number][a_strip_number] += an_energy;
}

void my_pht_histo_manager::add_step(my_pht_step_info a_step_info)
{
  current_particle.add_step(a_step_info);
  
  if (a_step_info.plate_id >= 0 && a_step_info.plate_id < number_of_plates)
  {
    current_particle.set_strip_visit(a_step_info.plate_id);
  }
}

void my_pht_histo_manager::add_track()
{
  the_particle_info.push_back(current_particle);
}

void my_pht_histo_manager::fill_ntuples()
{
  int high_energy_particle_counter = 0;
  int high_energy_charged_hadron_counter = 0;
  
  vector<double> temp_contributing_tracks;
  
  map<int, int> track_contribution_counter[number_of_plates];
  
  for (int i = 0; i < the_particle_info.size(); i++)
  {
    // the_particle_info[i].print();
  }
  
  for (int i = 0; i < number_of_plates; i++)
  {
    for (int j = 0; j < 2560; j++)
    {
      if (the_total_energy_deposited[i][j] != 0. || the_non_ionization_energy_deposited[i][j] != 0.)
      {
        //G4cout << i << " " << j << " " << the_total_energy_deposited[i][j] << " " << the_non_ionization_energy_deposited[i][j] << G4endl;
        
        the_plate_number.push_back(i);
        the_strip_number.push_back(j);
        the_total_energy_values.push_back(the_total_energy_deposited[i][j]);
        the_non_ionization_energy_values.push_back(the_non_ionization_energy_deposited[i][j]);
        
        for (int k = 0; k < contributing_tracks_list[i][j].size(); k++)
        {
          temp_contributing_tracks.clear();
          temp_contributing_tracks.push_back(contributing_tracks_list[i][j].at(k));
        }
        the_contributing_tracks.push_back(temp_contributing_tracks);
      }
    }
  }
  
  for (int i = 0; i < the_particle_info.size(); i++)
  {
    my_pht_track_info current_particle = the_particle_info[i].get_track_info();
    
    if (current_particle.ekin_vertex > 500.)
    {
      //G4cout << current_particle.track_id << " " << current_particle.parent_track_id << " " << current_particle.particle_code << " " << current_particle.ekin_vertex << endl;
      
      high_energy_particle_counter++;
      // high_energy_particles.insert(std::pair<int, int>(current_particle.particle_code, 1));
      high_energy_particles[current_particle.particle_code]++;
      
      if (abs(current_particle.particle_code) == 2212 || abs(current_particle.particle_code) == 211 || abs(current_particle.particle_code) == 321)
      {
        high_energy_charged_hadron_counter++;
      }
    }
    
    track_id.push_back(current_particle.track_id);
    particle_code.push_back(current_particle.particle_code);
    parent_track_id.push_back(current_particle.parent_track_id);
    creator_process.push_back(current_particle.creator_process);
    x_vertex.push_back(current_particle.x_vertex);
    y_vertex.push_back(current_particle.y_vertex);
    z_vertex.push_back(current_particle.z_vertex);
    px_vertex.push_back(current_particle.px_vertex);
    py_vertex.push_back(current_particle.py_vertex);
    pz_vertex.push_back(current_particle.pz_vertex);
    ekin_vertex.push_back(current_particle.ekin_vertex);
    
    vector<double> temp_visited_plates;
    
    for (int j = 0; j < number_of_plates; j++)
    {
      if(the_particle_info[i].get_is_strip_visited(j) == 1)
      {
        temp_visited_plates.push_back(j);
      }
      
      // G4cout << the_particle_info[i].get_is_strip_visited(j);
    }
    // G4cout << G4endl;
    
    /*
    if (high_energy_charged_hadron_counter > 1)
    {
      G4cout << "Visited plates: " << G4endl;
      
      for (int kk = 0; kk < temp_visited_plates.size(); kk++)
      {
        G4cout << temp_visited_plates.at(kk) << " ";
      }
      G4cout << G4endl;
    }
    */
    
    visited_plates.push_back(temp_visited_plates);
    temp_visited_plates.clear();
    
    for (int j = 0; j < the_particle_info[i].get_number_of_steps(); j++)
    {
      my_pht_step_info current_step = the_particle_info[i].get_step_info(j);
      
      step_track_id.push_back(current_particle.track_id);
      step_volume_name.push_back(current_step.volume_name);
      step_plate_id.push_back(current_step.plate_id);
      step_x_i.push_back(current_step.x_step_i);
      step_y_i.push_back(current_step.y_step_i);
      step_z_i.push_back(current_step.z_step_i);
      step_px_i.push_back(current_step.px_step_i);
      step_py_i.push_back(current_step.py_step_i);
      step_pz_i.push_back(current_step.pz_step_i);
      step_x_f.push_back(current_step.x_step_f);
      step_y_f.push_back(current_step.y_step_f);
      step_z_f.push_back(current_step.z_step_f);
      step_px_f.push_back(current_step.px_step_f);
      step_py_f.push_back(current_step.py_step_f);
      step_pz_f.push_back(current_step.pz_step_f);
      step_initial_energy.push_back(current_step.initial_energy);
      step_final_energy.push_back(current_step.final_energy);
      step_process_name.push_back(current_step.process);
    }
  }


  if (high_energy_charged_hadron_counter > 1)
  {
    for (int i = 0; i < the_plate_number.size(); i++)
    {
      //G4cout << the_plate_number.at(i) << " " << the_strip_number.at(i) << " " << the_total_energy_values.at(i) << ": ";
      
      for (int j = 0; j < the_contributing_tracks.at(i).size(); j++)
      {
        //G4cout << the_contributing_tracks.at(i).at(j) << " ";
        
        track_contribution_counter[the_plate_number.at(i)][the_contributing_tracks.at(i).at(j)]++;
      }
      
      //G4cout << "|";
    }
    //G4cout << G4endl;
    
    /*
    if (track_contribution_counter[13].size() > 1 && track_contribution_counter[12].size() > 1 &&
        track_contribution_counter[11].size() > 1 && track_contribution_counter[10].size() > 1 &&
        track_contribution_counter[9].size()  > 1 && track_contribution_counter[8].size()  > 1 &&
        track_contribution_counter[7].size()  > 1 && track_contribution_counter[6].size()  > 1 &&
        track_contribution_counter[5].size()  > 1 && track_contribution_counter[4].size()  > 1 &&
        track_contribution_counter[0].size() == 1 && track_contribution_counter[1].size() == 1 &&
        track_contribution_counter[2].size() == 1 && track_contribution_counter[3].size() == 1)
    */
    /*
    if (track_contribution_counter[13].size() == 1 && track_contribution_counter[12].size() == 1 &&
        track_contribution_counter[11].size() == 1 && track_contribution_counter[10].size() == 1 &&
        track_contribution_counter[9].size()  == 1 && track_contribution_counter[8].size()  == 1 &&
        track_contribution_counter[7].size()  == 1 && track_contribution_counter[6].size()  == 1 &&
        track_contribution_counter[5].size()  == 1 && track_contribution_counter[4].size()  == 1 &&
        track_contribution_counter[0].size() == 1 && track_contribution_counter[1].size() == 1 &&
        track_contribution_counter[2].size() == 1 && track_contribution_counter[3].size() == 1)
    */
    
    
    if (//track_contribution_counter[0].size() == 1 && track_contribution_counter[1].size() == 1 &&
        //track_contribution_counter[2].size() == 1 && track_contribution_counter[3].size() == 1 &&
        track_contribution_counter[4].size()  > 1 && track_contribution_counter[5].size()  > 1 &&
        track_contribution_counter[6].size()  > 1 && track_contribution_counter[7].size()  > 1 &&
        track_contribution_counter[8].size()  > 1 && track_contribution_counter[9].size()  > 1 &&
        track_contribution_counter[10].size() > 1 && track_contribution_counter[11].size() > 1 &&
        track_contribution_counter[12].size() > 1 &&
        track_contribution_counter[4].size()  < 7 && track_contribution_counter[5].size()  < 7 &&
        track_contribution_counter[6].size()  < 7 && track_contribution_counter[7].size()  < 7 &&
        track_contribution_counter[8].size()  < 7 && track_contribution_counter[9].size()  < 7 &&
        track_contribution_counter[10].size() < 7 && track_contribution_counter[11].size() < 7 &&
        track_contribution_counter[12].size() < 7)
    
    {
      my_ntuple_1->Fill();
      my_ntuple_2->Fill();
      my_ntuple_3->Fill();
      
    /*
      for (int s = 0; s < step_track_id.size(); s++)
      {
        cout << "+++ " << step_track_id.at(s) << " "
        << step_volume_name.at(s) << " "
        << step_x_i.at(s) << " "
        << step_y_i.at(s) << " "
        << step_z_i.at(s) << endl;
      }
    */
    }
  }
 
  
  /*
  G4ThreeVector v1 = G4ThreeVector(0., 1., 0.);
  G4RotationMatrix* r1 = new G4RotationMatrix();
  r1->rotateX(90.*deg);
  G4ThreeVector v2 = (*r1) * v1;
  G4cout << "ssss " << v2.x() << " " << v2.y() << " " << v2.z() << G4endl;
  */
}

void my_pht_histo_manager::print_high_energy_particle_map()
{
  for (map<int, int>::iterator it = high_energy_particles.begin(); it != high_energy_particles.end(); it++)
  {
    G4cout << "hepmap " << it->first << " " << it->second << G4endl;
  }
}
