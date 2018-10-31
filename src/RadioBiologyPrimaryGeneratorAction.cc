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
/// \file channeling/src/RadioBiologyPrimaryGeneratorAction.cc
/// \brief Implementation of the RadioBiologyPrimaryGeneratorAction class
//

#include "RadioBiologyPrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "Randomize.hh"

#include "G4GeneralParticleSource.hh"
#include "G4ParticleGun.hh"
#include "RadioBiologyAnalysis.hh"

#include "RadioBiologyPrimaryGeneratorActionMessenger.hh"

#include "G4HEPEvtInterface.hh"

#include <list>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologyPrimaryGeneratorAction::RadioBiologyPrimaryGeneratorAction():
  AirBoxThick(1.4*CLHEP::millimeter)
{
    fParticleGun = new G4ParticleGun();
    fGunMessenger = new RadioBiologyPrimaryGeneratorActionMessenger(this);
    //HEPEvt = new G4HEPEvtInterface("pythia_event.data");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologyPrimaryGeneratorAction::~RadioBiologyPrimaryGeneratorAction(){
    delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){

  G4ParticleDefinition* particle  = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particle);

  G4double px,py,pz,p,x,y,z;
  G4double xp,yp,energy;
  G4double m_e = 0.511e-3 * CLHEP::GeV; // GeV

  std::string line;
  std::ifstream ifile0("beam_prae_radiobiology.dat.3000",std::ios_base::in);
  while(getline(ifile0,line)){
    if (!line.length() || line[0] == '#')
      continue;
    std::istringstream iss(line);
    iss>>energy>>x>>y>>z>>xp>>yp;

    x = x * 1.0e-6 * CLHEP::meter;   // um to meter
    y = y * 1.0e-6 * CLHEP::meter;   // um to meter
    z = z * 1.0e-6 * CLHEP::meter; // um to meter

    xp *= 1.0e-6;  // milliradian to micron radian
    yp *= 1.0e-6;  // milliradian to micron radian

    energy *= CLHEP::GeV;

    p = sqrt(energy*energy - m_e*m_e);

    px = p *xp;
    py = p *yp;
    pz = p * sqrt(1 - xp*xp -yp*yp);

    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    analysisManager->FillNtupleDColumn(0,x/CLHEP::millimeter);
    analysisManager->FillNtupleDColumn(1,y/CLHEP::millimeter);
    analysisManager->FillNtupleDColumn(2,z/CLHEP::millimeter);
    analysisManager->FillNtupleDColumn(3,px);
    analysisManager->FillNtupleDColumn(4,py);
    analysisManager->FillNtupleDColumn(5,pz);
    analysisManager->FillNtupleDColumn(6,energy);
    analysisManager->FillNtupleIColumn(7,0);
    analysisManager->AddNtupleRow();

    fParticleGun->SetParticlePosition(G4ThreeVector(x,y,z-2.0*CLHEP::meter));
    fParticleGun->SetParticleEnergy(energy);
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(xp,yp,pz/p));
    fParticleGun->SetParticleTime(0);
    //fParticleGun->SetParticleMomentum(momentum_emission);
    fParticleGun->GeneratePrimaryVertex(anEvent);

  }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

void RadioBiologyPrimaryGeneratorAction::SetAirBoxThick(G4double value){
  AirBoxThick = value;
}
