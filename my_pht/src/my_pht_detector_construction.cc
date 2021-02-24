#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4PVReplica.hh"
#include "G4RotationMatrix.hh"
#include "globals.hh"

#include "my_pht_detector_construction.hh"

my_pht_detector_construction::my_pht_detector_construction()
: G4VUserDetectorConstruction()
{
}

my_pht_detector_construction::~my_pht_detector_construction()
{
}

G4VPhysicalVolume* my_pht_detector_construction::Construct()
{
  const int number_of_plates = 13;
  
  const int ssd_number_of_strips_upstream = 640;
  const int ssd_number_of_strips_midstream = 640;
  const int ssd_number_of_strips_downstream = 1280;
  
  double plate_positions[13] = {-32.0*cm, -31.4*cm, -2.4*cm, -1.8*cm, 1.2*cm, 1.8*cm, 5.4*cm, 6.0*cm, 6.6*cm, 24.0*cm, 24.6*cm, 36.6*cm, 37.2*cm};
  G4RotationMatrix* the_x_plates_rotation_matrix = new G4RotationMatrix();
  G4RotationMatrix* the_y_plates_rotation_matrix = new G4RotationMatrix();
  the_y_plates_rotation_matrix->rotateZ(90.*deg);
  G4RotationMatrix* the_d_plates_rotation_matrix = new G4RotationMatrix();
  the_d_plates_rotation_matrix->rotateZ(45.*deg);
  G4RotationMatrix* ssd_rotations[] =
      {the_x_plates_rotation_matrix, the_y_plates_rotation_matrix,
       the_x_plates_rotation_matrix, the_y_plates_rotation_matrix,
       the_x_plates_rotation_matrix, the_y_plates_rotation_matrix,
       the_d_plates_rotation_matrix,
       the_x_plates_rotation_matrix, the_y_plates_rotation_matrix,
       the_x_plates_rotation_matrix, the_y_plates_rotation_matrix,
       the_x_plates_rotation_matrix, the_y_plates_rotation_matrix};
  
  G4NistManager* nist = G4NistManager::Instance();
  
  G4Material* my_world_material  = nist->FindOrBuildMaterial("G4_AIR");
  G4Material* my_target_material = nist->FindOrBuildMaterial("G4_C");
  G4Material* my_strip_material  = nist->FindOrBuildMaterial("G4_Si");
  G4Material* my_plate_material  = nist->FindOrBuildMaterial("G4_C");

  G4double world_size = 1.4*m;
  G4double target_width = 0.2*m;
  G4double target_thickness = 0.02*m;
  
  double ssd_plate_width_upstream = 3.84*cm;
  double ssd_plate_length_upstream = 3.84*cm;
  double ssd_plate_width_midstream = 3.84*cm;
  double ssd_plate_length_midstream = 3.84*cm;
  double ssd_plate_width_downstream = 7.68*cm;
  double ssd_plate_length_downstream = 7.68*cm;
  double ssd_plate_thickness = 0.08*cm;
  double ssd_array_thickness = 0.03*cm;
  double ssd_strip_width = 0.060*mm;

  G4ThreeVector target_position = G4ThreeVector(0.*m, 0.*m, 0.*cm);
  
  G4ThreeVector ssd_plate_positions[number_of_plates];
  
  for (int i = 0; i < number_of_plates; i++)
  {
    ssd_plate_positions[i] = G4ThreeVector(0., 0., plate_positions[i]);
  }
  
  G4Box* solid_world = new G4Box("solid_world", 0.5 * world_size, 0.5 * world_size, 0.5 * world_size);
  
  G4LogicalVolume* logical_world = new G4LogicalVolume(solid_world, my_world_material, "logical_world");
  
  G4VPhysicalVolume* physical_world =
  new G4PVPlacement(0,                     // no rotation
                    G4ThreeVector(),       // position
                    logical_world,         // its logical volume
                    "physical_world",      // its name
                    0,                     // its mother  volume
                    false,                 // no boolean operation
                    0,                     // copy number
                    true);                 // overlaps checking
  
  G4Box* solid_target = new G4Box("solid_target", 0.5 * target_width, 0.5 * target_width, 0.5 * target_thickness);
  
  G4LogicalVolume* logical_target = new G4LogicalVolume(solid_target, my_target_material, "logical_target");
  
 
  new G4PVPlacement(0,                  //no rotation
                    target_position,    //at position
                    logical_target,     //its logical volume
                    "physical_target",  //its name
                    logical_world,      //its mother  volume
                    false,              //no boolean operation
                    0,                  //copy number
                    true);              //overlaps checking
 
  
  G4Box* solid_ssd_plate_upstream = new G4Box("solid_ssd_plate", 0.5 * ssd_plate_length_upstream, 0.5 * ssd_plate_width_upstream, 0.5 * ssd_plate_thickness);
  
  G4LogicalVolume* logical_ssd_plate_upstream = new G4LogicalVolume(solid_ssd_plate_upstream, my_plate_material, "logical_ssd_plate_upstream");
  
  G4Box* solid_ssd_plate_midstream = new G4Box("solid_ssd_plate", 0.5 * ssd_plate_length_midstream, 0.5 * ssd_plate_width_midstream, 0.5 * ssd_plate_thickness);
  
  G4LogicalVolume* logical_ssd_plate_midstream = new G4LogicalVolume(solid_ssd_plate_midstream, my_plate_material, "logical_ssd_plate_midstream");
  
  G4Box* solid_ssd_plate_downstream = new G4Box("solid_ssd_plate", 0.5 * ssd_plate_length_downstream, 0.5 * ssd_plate_width_downstream, 0.5 * ssd_plate_thickness);
  
  G4LogicalVolume* logical_ssd_plate_downstream = new G4LogicalVolume(solid_ssd_plate_downstream, my_plate_material, "logical_ssd_plate_downstream");
  
  for (int i = 0; i < number_of_plates; i++)
  {
    if (i < 4)
    {
      new G4PVPlacement(ssd_rotations[i],                //rotation
                      ssd_plate_positions[i],            //position
                      logical_ssd_plate_upstream,        //its logical volume
                      "physical_ssd_plate",              //its name
                      logical_world,                     //its mother  volume
                      false,                             //no boolean operation
                      i,                                 //copy number
                      true);                             //overlaps checking
    }
    else if (i < 9)
    {
      new G4PVPlacement(ssd_rotations[i],                //rotation
                        ssd_plate_positions[i],          //position
                        logical_ssd_plate_midstream,     //its logical volume
                        "physical_ssd_plate",            //its name
                        logical_world,                   //its mother  volume
                        false,                           //no boolean operation
                        i,                               //copy number
                        true);                           //overlaps checking
    }
    else
    {
      new G4PVPlacement(ssd_rotations[i],                //rotation
                        ssd_plate_positions[i],          //position
                        logical_ssd_plate_downstream,    //its logical volume
                        "physical_ssd_plate",            //its name
                        logical_world,                   //its mother  volume
                        false,                           //no boolean operation
                        i,                               //copy number
                        true);                           //overlaps checking
    }
  }
  
  G4Box* solid_ssd_array_upstream = new G4Box("solid_ssd_array", 0.5 * ssd_plate_length_upstream, 0.5 * ssd_plate_width_upstream, 0.5 * ssd_array_thickness);
  
  G4LogicalVolume* logical_ssd_array_upstream = new G4LogicalVolume(solid_ssd_array_upstream, my_strip_material, "logical_ssd_array_upstream");
  
  G4Box* solid_ssd_array_midstream = new G4Box("solid_ssd_array", 0.5 * ssd_plate_length_midstream, 0.5 * ssd_plate_width_midstream, 0.5 * ssd_array_thickness);
  
  G4LogicalVolume* logical_ssd_array_midstream = new G4LogicalVolume(solid_ssd_array_midstream, my_strip_material, "logical_ssd_array_midstream");
  
  G4Box* solid_ssd_array_downstream = new G4Box("solid_ssd_array", 0.5 * ssd_plate_length_downstream, 0.5 * ssd_plate_width_downstream, 0.5 * ssd_array_thickness);
  
  G4LogicalVolume* logical_ssd_array_downstream = new G4LogicalVolume(solid_ssd_array_downstream, my_strip_material, "logical_ssd_array_downstream");
  
  new G4PVPlacement(0,                            //no rotation
                    G4ThreeVector(),              //position
                    logical_ssd_array_upstream,   //its logical volume
                    "physical_ssd_array",         //its name
                    logical_ssd_plate_upstream,   //its mother  volume
                    false,                        //no boolean operation
                    0,                            //copy number
                    true);                        //overlaps checking
  
  new G4PVPlacement(0,                            //no rotation
                    G4ThreeVector(),              //position
                    logical_ssd_array_midstream,  //its logical volume
                    "physical_ssd_array",         //its name
                    logical_ssd_plate_midstream,  //its mother  volume
                    false,                        //no boolean operation
                    0,                            //copy number
                    true);                        //overlaps checking
  
  new G4PVPlacement(0,                              //no rotation
                    G4ThreeVector(),                //position
                    logical_ssd_array_downstream,   //its logical volume
                    "physical_ssd_array",           //its name
                    logical_ssd_plate_downstream,   //its mother  volume
                    false,                          //no boolean operation
                    0,                              //copy number
                    true);                          //overlaps checking
  
  G4Box* solid_ssd_strip_upstream = new G4Box("solid_ssd_strip_upstream", 0.5 * ssd_plate_length_upstream, 0.5 * ssd_strip_width, 0.5 * ssd_array_thickness);
  
  G4LogicalVolume* logical_ssd_strip_upstream = new G4LogicalVolume(solid_ssd_strip_upstream, my_strip_material, "logical_ssd_strip_upstream");
  
  new G4PVReplica("physical_ssd_strip", logical_ssd_strip_upstream, logical_ssd_array_upstream, kYAxis, ssd_number_of_strips_upstream, ssd_strip_width);
  
  G4Box* solid_ssd_strip_midstream = new G4Box("solid_ssd_strip_midstream", 0.5 * ssd_plate_length_midstream, 0.5 * ssd_strip_width, 0.5 * ssd_array_thickness);
  
  G4LogicalVolume* logical_ssd_strip_midstream = new G4LogicalVolume(solid_ssd_strip_midstream, my_strip_material, "logical_ssd_strip_midstream");
  
  new G4PVReplica("physical_ssd_strip", logical_ssd_strip_midstream, logical_ssd_array_midstream, kYAxis, ssd_number_of_strips_midstream, ssd_strip_width);
  
  G4Box* solid_ssd_strip_downstream = new G4Box("solid_ssd_strip_downstream", 0.5 * ssd_plate_length_downstream, 0.5 * ssd_strip_width, 0.5 * ssd_array_thickness);
  
  G4LogicalVolume* logical_ssd_strip_downstream = new G4LogicalVolume(solid_ssd_strip_downstream, my_strip_material, "logical_ssd_strip_downstream");
  
  new G4PVReplica("physical_ssd_strip", logical_ssd_strip_downstream, logical_ssd_array_downstream, kYAxis, ssd_number_of_strips_downstream, ssd_strip_width);
  
  return physical_world;
}
