#ifndef my_pht_detector_construction_h
#define my_pht_detector_construction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

class my_pht_detector_construction : public G4VUserDetectorConstruction
{
public:
  my_pht_detector_construction();
  virtual ~my_pht_detector_construction();

  virtual G4VPhysicalVolume* Construct();
};

#endif
