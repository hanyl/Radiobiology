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
/// \file channeling/src/RadioBiologyDetectorConstructionMessenger.cc
/// \brief Implementation of the RadioBiologyDetectorConstructionMessenger class
//

#include "RadioBiologyDetectorConstructionMessenger.hh"
#include "RadioBiologyDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"
#include "G4RunManager.hh"

#include "G4ios.hh"

RadioBiologyDetectorConstructionMessenger::
RadioBiologyDetectorConstructionMessenger(
        RadioBiologyDetectorConstruction* mpga)
:fDetector(mpga){
    fMyAirBoxDirectory = new G4UIdirectory("/AirBox/");
    fMyAirBoxDirectory->SetGuidance("AirBox setup control commands.");

    fAirBoxSizeCmd = new G4UIcmdWith3VectorAndUnit("/AirBox/setSize",this);
    fAirBoxSizeCmd->SetGuidance("Set AirBox size.");
    fAirBoxSizeCmd->SetParameterName("AirBoxSizeX",
                                   "AirBoxSizeY",
                                   "AirBoxSizeZ",
                                   true);
    fAirBoxSizeCmd->SetDefaultValue(G4ThreeVector(5.,5.,10.));
    fAirBoxSizeCmd->SetDefaultUnit("cm");
    
    fAddAirBox = new G4UIcmdWithAString("/addAirBox",this);
    fAddAirBox->SetGuidance("Add AirBox.");
    fAddAirBox->SetParameterName("addAirBox",true);

    fWaterBoxSizeCmd = new G4UIcmdWith3VectorAndUnit("/WaterBox/setSize",this);
    fWaterBoxSizeCmd->SetGuidance("Set WaterBox size.");
    fWaterBoxSizeCmd->SetParameterName("WaterBoxSizeX",
                                   "WaterBoxSizeY",
                                   "WaterBoxSizeZ",
                                   true);
    fWaterBoxSizeCmd->SetDefaultValue(G4ThreeVector(2.5,2.5,10.));
    fWaterBoxSizeCmd->SetDefaultUnit("mm");

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

RadioBiologyDetectorConstructionMessenger::
~RadioBiologyDetectorConstructionMessenger(){
    delete fAirBoxSizeCmd;
    delete fAddAirBox;
    delete fWaterBoxSizeCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void RadioBiologyDetectorConstructionMessenger::SetNewValue(
                                                    G4UIcommand *command,
                                                    G4String newValue){
    if(command==fAirBoxSizeCmd ){
        fDetector->SetAirBoxSize(fAirBoxSizeCmd->GetNew3VectorValue(newValue));
    }
    if(command==fAddAirBox ){
        fDetector->AddAirBoxTarget();
    }
    if(command==fWaterBoxSizeCmd ){
        fDetector->SetWaterBoxSize(fWaterBoxSizeCmd->GetNew3VectorValue(newValue));
    }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

G4String RadioBiologyDetectorConstructionMessenger::GetCurrentValue(
                                                    G4UIcommand * command){
    G4String cv;
    
    if( command==fAirBoxSizeCmd ){
        cv = fAirBoxSizeCmd->ConvertToString(fDetector->GetAirBoxSize(),"mm");
    }
    if( command==fWaterBoxSizeCmd ){
        cv = fWaterBoxSizeCmd->ConvertToString(fDetector->GetWaterBoxSize(),"mm");
    }
    
    return cv;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
