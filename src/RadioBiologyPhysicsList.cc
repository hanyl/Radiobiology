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

#include "RadioBiologyPhysicsList.hh"

// general
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ProcessManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleWithCuts.hh"
#include "G4ProcessVector.hh"
#include "G4RunManager.hh"


// physics lists
//#include "RadioBiologyPhysListEmStandardSS.hh"
#include "G4EmStandardPhysics.hh"
#include "G4EmPenelopePhysics.hh"
#include "G4DecayPhysics.hh"

RadioBiologyPhysicsList::RadioBiologyPhysicsList():  G4VModularPhysicsList(){

    fTimeStepMin = 2.E2 * CLHEP::angstrom;
    fTransverseVariationMax = 2.E-2 * CLHEP::angstrom;    


    //fEmPhysicsList = new RadioBiologyPhysListEmStandardSS();
    fEmPhysicsList = new G4EmStandardPhysics();
    //fEmPhysicsList = new G4EmPenelopePhysics();
    fParticleList = new G4DecayPhysics();

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologyPhysicsList::~RadioBiologyPhysicsList(){
    delete fEmPhysicsList;
    delete fParticleList;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyPhysicsList::ConstructProcess(){
    
    AddTransportation();

    fEmPhysicsList->ConstructProcess();
    
    //G4cout << "### RadioBiologyPhysicsList::ConstructProcess is done" << G4endl;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyPhysicsList::ConstructParticle(){
    //fEmPhysicsList->ConstructParticle();
    fParticleList->ConstructParticle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyPhysicsList::SetCuts()
{
    // These values are used as the default production thresholds
    // for the world volume.
    SetCutsWithDefault();
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

