# emphatic_ssd_simulation
Simulation of the silicon strips for EMPHATIC (stand-alone).

This is a stand-alone simulation for the silicon strip detectors of EMPHATIC. It is a "research and development" version, in the sense that geometry and other things are supposed to change frequently, and it provides a lot of truth information.

The physics is the same as the DetectorSim physics. One difference is that the DefaultCutValue is set to 0.01 mm and is varied in different runs so that experiments can be made at low energy regarding the multiplicity of strips fired in a cluster (by the same particle).

All the geometry information is in the detector_construction files; it does not follow the messenger mechanism used in DetectorSim because the geometry is moving to GDML anyway. It can be reworked if needed. I have tried to avoid using hard-coded numbers (like number of plates, plate size or number of strips) except in detector_construction, but a couple may have slipped through.

The output is grouped in 3 trees:

-> "ssd_energy": silicon plate hits, containing plate number, strip number, energy deposited, non-ionization energy deposited (mostly as a double check) and contributing tracks. Contributing tracks is there to provide connection with the track tree. In production, only the plate number, the strip number and energy deposited (after processing) will be available. This tree is the "experimental" tree.

-> "particle_truth": all particles in the event, their id number, particle code, parent, creator process, vertex position, momentum and energy, and plates visited.

-> "step_truth": all the steps in the event, with recorded track id, volume name, plate id (if in plate), position and momentum and energy (initial and final for the step), step process name.

The truth trees are for research purposes - comparison and matching, so that the best reconstruction algorithm and parameters can be found. The step_truth tree is very large and the particle_truth tree is large, so that output root files can easily go above 1 GB; if the goal is simply to analyze the SSD hits, the two truth ntuples can simply be not filled (comment their Fill() calls in my_pht_histo_manager::fill_ntuples()).

Just before those lines are som options about event selection. Multi-track events can be selected by requiring more than one track on all midstream and downstream plates, etc. Note that track_contribution_counter[] checks for charged pions, kaons and protons with vertex kinetic energy > 500 MeV (one hard-coded number!) and if there is more than one (the original incoming particle) it is called a multi-track event. These selections are geomtry dependent. They can be done in a more general and consistent way, e.g. reading number of upstream plates from geometry, etc.

This works on MacOS 10.14.6 Mojave with XCode 10.0 (10A255), geant 4.10.04p02 and ROOT 6.22.06. It should work with minor adjustments on all Linux and MacOS platforms.

The next task will be to integrate the relevant parts into the general EMPHATIC simulation.

2021-02-24
Nikolay Kolev
kolev20n@uregina.ca

