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

  //G4int evtID = anEvent->GetEventID();

  //G4double AirBox_thick = this->AirBoxThick;

  //G4double x0=0.,y0=0.; // mm
  //G4double sigmaXY = this->sigmaUserXY; // mm
  //G4double sigmaZ = this->sigmaUserZ; // mm
  //G4double deltaE = this->DeltaE;
  //G4double Energy = this->primaryEnergy;  // GeV
  //G4double px0 = 0, py0 = 0;
  //G4double sigmaPxy = this->sigmaUserPxy; // radian
  //G4double z0 = -5.0 * sigmaZ;
  //G4double time = 0;

  ////G4cout<< "The energy is "<<Energy<<G4endl;
  ////G4cout<< "The AirBox thick is "<<AirBox_thick<<G4endl;
  ////G4cout<< "The sigmaXY is "<<sigmaXY<<G4endl;
  ////G4cout<< "The sigmaZ is "<<sigmaZ<<G4endl;
  ////G4cout<< "The sigmaPxy is "<<sigmaPxy<<G4endl;
  ////G4cout<< "The deltaE is "<<deltaE<<G4endl;

  //G4double primary_energy = G4RandGauss::shoot(Energy,Energy * deltaE);
  //G4double gamma=primary_energy;
  //G4double x = G4RandGauss::shoot(x0,sigmaXY);
  //G4double y = G4RandGauss::shoot(y0,sigmaXY);
  //G4double z = G4RandGauss::shoot(z0,sigmaZ);
  //time = (z-z0)/CLHEP::c_light;

  //G4double px = G4RandGauss::shoot(px0,sigmaPxy) * primary_energy; 
  //G4double py = G4RandGauss::shoot(py0,sigmaPxy) * primary_energy; 
  //G4double pz = 0; 

  //G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //analysisManager->FillNtupleDColumn(0,x/CLHEP::millimeter);
  //analysisManager->FillNtupleDColumn(1,y/CLHEP::millimeter);
  //analysisManager->FillNtupleDColumn(2,z/CLHEP::millimeter);
  //analysisManager->FillNtupleDColumn(3,px);
  //analysisManager->FillNtupleDColumn(4,py);
  //analysisManager->FillNtupleDColumn(5,pz);
  //analysisManager->FillNtupleDColumn(6,primary_energy/CLHEP::GeV);
  //analysisManager->FillNtupleIColumn(7,0);
  //analysisManager->FillNtupleIColumn(8,evtID);
  //analysisManager->FillNtupleDColumn(9,time/(CLHEP::millimeter/CLHEP::c_light));
  //analysisManager->AddNtupleRow();

  ////fParticleGun->SetParticlePosition(position_emission);
  ////fParticleGun->SetParticleEnergy(kineticEnergy);
  ////fParticleGun->SetParticleMomentumDirection(direction_emission);
  ////fParticleGun->SetParticleTime(time);
  //////fParticleGun->SetParticleMomentum(momentum_emission);
  ////fParticleGun->GeneratePrimaryVertex(anEvent);


  ////HEPEvt->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
  ////HEPEvt->GeneratePrimaryVertex(anEvent);

  G4ParticleDefinition* particle  = G4ParticleTable::GetParticleTable()->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particle);

  G4double px,py,pz,p,x,y,z;
  G4double xp,yp,energy;
  G4double m_e = 0.511e-3 * CLHEP::GeV; // GeV

  std::string line;
  std::ifstream ifile0("beam_prae_radiobiology.dat.200",std::ios_base::in);
  while(getline(ifile0,line)){
    if (!line.length() || line[0] == '#')
      continue;
    std::istringstream iss(line);
    iss>>energy>>x>>y>>z>>xp>>yp;

    x = x * 1.0e-6 * CLHEP::meter;   // um to micron meter
    y = y * 1.0e-6 * CLHEP::meter;   // um to micron meter
    z = z * 1.0e-6 * CLHEP::meter; // um to micron meter

    xp *= 1.0e-6;  // milliradian to micron radian
    yp *= 1.0e-6;  // milliradian to micron radian

    energy *= CLHEP::GeV;

    p = sqrt(energy*energy - m_e*m_e);

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
