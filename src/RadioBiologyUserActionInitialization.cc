//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file channeling/src/RadioBiologyUserActionInitialization.cc
/// \brief Implementation of the RadioBiologyUserActionInitialization class
//

#ifdef G4MULTITHREADED
#include "RadioBiologyUserActionInitialization.hh"
#include "RadioBiologyPrimaryGeneratorAction.hh"
#include "RadioBiologyTrackingAction.hh"
#include "RadioBiologySteppingAction.hh"
#include "RadioBiologyEventAction.hh"
#include "RadioBiologyRunAction.hh"
#include "G4GeneralParticleSource.hh"
#include "G4ParticleTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
RadioBiologyUserActionInitialization::RadioBiologyUserActionInitialization(RadioBiologyDetectorConstruction* det)
:fDetector(det){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologyUserActionInitialization::~RadioBiologyUserActionInitialization() {
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyUserActionInitialization::Build() const {
    SetUserAction(new RadioBiologyPrimaryGeneratorAction());
    SetUserAction(new RadioBiologyEventAction());
    SetUserAction(new RadioBiologySteppingAction(fDetector));
    SetUserAction(new RadioBiologyTrackingAction());
    SetUserAction(new RadioBiologyRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void RadioBiologyUserActionInitialization::BuildForMaster() const {
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
#endif
