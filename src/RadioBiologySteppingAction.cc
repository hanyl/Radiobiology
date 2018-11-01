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

#include "RadioBiologySteppingAction.hh"
#include "RadioBiologyDetectorConstruction.hh"
#include "RadioBiologyTrackingAction.hh"
#include "RadioBiologyAnalysis.hh"

#include "G4SteppingManager.hh"
#include "G4Gamma.hh"
#include "G4Positron.hh"
#include "G4Electron.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologySteppingAction::RadioBiologySteppingAction(RadioBiologyDetectorConstruction* det):
  fDetector(det),
  fWorld(0), fAirBox(0)
{ 
  first = true;
  fTrackSegm = 0.;
  fDirectionOut = G4ThreeVector(0.,0.,0.);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologySteppingAction::~RadioBiologySteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologySteppingAction::UserSteppingAction(const G4Step* step)
{
 //get fDetector pointers
 if (first) {
   fWorld   = fDetector->GetWorld();
   fAirBox   = fDetector->GetAirBox();
   fNbOfLayers = fDetector->GetNumberOfWaterLayer();
   for(G4int i = 0; i< fNbOfLayers;i++){
     fWaterBox[i]   = fDetector->GetWaterBox(i);
   }
   first  = false;
 }

 const G4Event *evt = G4RunManager::GetRunManager()->GetCurrentEvent();
 G4int evtID = evt->GetEventID();

 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  
 //get volume
 G4StepPoint* point1 = step->GetPreStepPoint();
 G4VPhysicalVolume* volume = point1->GetTouchableHandle()->GetVolume();
  
 G4StepPoint* point2 = step->GetPostStepPoint(); 

 if ((point2->GetStepStatus() == fGeomBoundary) && (volume == fAirBox)){
   if (step->GetTrack()->GetDefinition() ==  G4Electron::Electron()){
     fDirectionOut = point2->GetMomentumDirection();
     fMomentum = point2->GetMomentum();
     fPosition = point2->GetPosition();
     energy = point2->GetTotalEnergy();
     time = point2->GetGlobalTime(); // since the event is created
     //time = point2->GetLocalTime();    // since the track is created

     analysisManager->FillNtupleDColumn(0,fPosition.x()/CLHEP::millimeter);
     analysisManager->FillNtupleDColumn(1,fPosition.y()/CLHEP::millimeter);
     analysisManager->FillNtupleDColumn(2,fPosition.z()/CLHEP::millimeter);
     analysisManager->FillNtupleDColumn(3,fMomentum.x()/CLHEP::GeV);
     analysisManager->FillNtupleDColumn(4,fMomentum.y()/CLHEP::GeV);
     analysisManager->FillNtupleDColumn(5,fMomentum.z()/CLHEP::GeV);
     analysisManager->FillNtupleDColumn(6,energy/CLHEP::GeV);
     analysisManager->FillNtupleIColumn(7,3);
     analysisManager->AddNtupleRow();
   }
   return;
 }



 if ((point2->GetStepStatus() == fGeomBoundary)){ 
   for(G4int i = 0; i < fNbOfLayers; i++){
     if (volume == fWaterBox[i] && step->GetTrack()->GetDefinition() ==  G4Electron::Electron()){
       fDirectionOut = point2->GetMomentumDirection();
       fMomentum = point2->GetMomentum();
       fPosition = point2->GetPosition();
       energy = point2->GetTotalEnergy();
       time = point2->GetGlobalTime(); // since the event is created
       //time = point2->GetLocalTime();    // since the track is created

       analysisManager->FillNtupleDColumn(0,fPosition.x()/CLHEP::millimeter);
       analysisManager->FillNtupleDColumn(1,fPosition.y()/CLHEP::millimeter);
       analysisManager->FillNtupleDColumn(2,fPosition.z()/CLHEP::millimeter);
       analysisManager->FillNtupleDColumn(3,fMomentum.x()/CLHEP::GeV);
       analysisManager->FillNtupleDColumn(4,fMomentum.y()/CLHEP::GeV);
       analysisManager->FillNtupleDColumn(5,fMomentum.z()/CLHEP::GeV);
       analysisManager->FillNtupleDColumn(6,energy/CLHEP::GeV);
       analysisManager->FillNtupleIColumn(7,10 + i);
       analysisManager->AddNtupleRow();
       return;
     }
   }
 } 

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


