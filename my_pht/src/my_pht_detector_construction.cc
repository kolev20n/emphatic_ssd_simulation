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
  parser.Read("ssd_strips_detector.gdml");
  
  G4VPhysicalVolume* physical_world = parser.GetWorldVolume(); //world volume
  //physical_world->GetLogicalVolume()->SetVisAttributes(G4VisAttributes::Invisible);
  
  return physical_world;
}
