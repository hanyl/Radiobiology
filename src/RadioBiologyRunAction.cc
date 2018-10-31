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

#include "RadioBiologyRunAction.hh"
#include "RadioBiologyRunActionMessenger.hh"
#include "RadioBiologyRun.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "RadioBiologyAnalysis.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologyRunAction::RadioBiologyRunAction(): G4UserRunAction(),fFileName("RadioBiology"){

  fRunActionMessenger = new RadioBiologyRunActionMessenger(this);

    //G4RunManager::GetRunManager()->SetPrintProgress(1);
    
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    //G4cout << "Using " << analysisManager->GetType() << G4endl;
    
    // Create directories
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetFirstHistoId(1);

    // Creating ntuple
    analysisManager->CreateNtuple("tree", "Angles and Positions");
    //analysisManager->CreateNtupleDColumn("edep1");

    analysisManager->CreateNtupleDColumn("x");
    analysisManager->CreateNtupleDColumn("y");
    analysisManager->CreateNtupleDColumn("z");
    analysisManager->CreateNtupleDColumn("px");
    analysisManager->CreateNtupleDColumn("py");
    analysisManager->CreateNtupleDColumn("pz");
    analysisManager->CreateNtupleDColumn("e");
    analysisManager->CreateNtupleIColumn("type");

    analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologyRunAction::~RadioBiologyRunAction(){
    delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* RadioBiologyRunAction::GenerateRun(){
    return new RadioBiologyRun;
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyRunAction::BeginOfRunAction(const G4Run* /*run*/){
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    G4String FileName = this->fFileName;
    analysisManager->OpenFile(FileName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyRunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();    
    analysisManager->Write();
    analysisManager->CloseFile();
}
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void RadioBiologyRunAction::SetFileName(G4String value){
  fFileName = value;
}

