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

#include "RadioBiologyDetectorConstruction.hh"
#include "G4RunManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4UniformMagField.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4String.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSDoseDeposit.hh"
#include "G4PSNofSecondary.hh"
#include "G4SDParticleFilter.hh"
#include "G4PSFlatSurfaceCurrent.hh"
#include "G4TransportationManager.hh"

#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ClassicalRK4.hh"
#include "G4ChordFinder.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4UserLimits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RadioBiologyDetectorConstruction::RadioBiologyDetectorConstruction():
fWorldLogic(0),fAirBoxLogic(0){
    
    fAirBox = true;
    fAirBoxSize = G4ThreeVector(20 * CLHEP::centimeter,
                              20 * CLHEP::centimeter,
                              10 * CLHEP::centimeter);
    fWaterBox = true;
    fWaterBoxSize = G4ThreeVector(20 * CLHEP::centimeter,
        20 * CLHEP::centimeter,
        3 * CLHEP::centimeter);

    fNbOfLayers = 10;

    fMessenger = new RadioBiologyDetectorConstructionMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

RadioBiologyDetectorConstruction::~RadioBiologyDetectorConstruction(){
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....

G4VPhysicalVolume* RadioBiologyDetectorConstruction::Construct(){
    //** World **//
    fWorldSize = G4ThreeVector(0.5 * CLHEP::meter,
                               0.5 * CLHEP::meter,
                               6. * CLHEP::meter);
    fWorldMaterial = G4NistManager::
        Instance()->FindOrBuildMaterial("G4_Galactic");
    
    fWorldSolid = new G4Box("World",
                            fWorldSize.x()/2.,
                            fWorldSize.y()/2.,
                            fWorldSize.z()/2.);
    
    fWorldLogic = new G4LogicalVolume(fWorldSolid,
                                      fWorldMaterial,
                                      "World");
    
    fWorldPhysical = new G4PVPlacement(0,
                                       G4ThreeVector(),
                                       fWorldLogic,
                                       "World",
                                       0,
                                       false,
                                       0);
    
    //** AirBox **//
    if(fAirBox){
            ConstructAirBox();
    }

    // WaterBox
    if(fWaterBox){
      ConstructWaterBox();
    }

    return fWorldPhysical;
}  



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyDetectorConstruction::ConstructAirBox(){

  fAirBoxSolid = new G4Box("AirBox",
      fAirBoxSize.x()/2,fAirBoxSize.y()/2,fAirBoxSize.z()/2);

  fAirBoxLogic = new G4LogicalVolume(fAirBoxSolid,
      G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"),
      "AirBox");

  fAirBoxLocation = G4ThreeVector(0.,0.,-fWorldSize.z()/3 + fAirBoxSize.z()/2 + 1.0 * CLHEP::centimeter);

  fAirBoxPhysical = new G4PVPlacement(0,
      fAirBoxLocation,
      fAirBoxLogic,"AirBox",
      fWorldLogic,
      false,
      0);
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.

void RadioBiologyDetectorConstruction::ConstructWaterBox(){

  fWaterBoxSolid = new G4Box("WaterBox",
      fWaterBoxSize.x()/2,fWaterBoxSize.y()/2,fWaterBoxSize.z()/2);

  fWaterBoxLogic = new G4LogicalVolume(fWaterBoxSolid,
      G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER"),
      "WaterBox");

  fWaterBoxLocation = fAirBoxLocation + G4ThreeVector(0.,0.,fAirBoxSize.z()/2 + fWaterBoxSize.z()/2);;

  for(G4int i = 0; i<fNbOfLayers;i++){
    fWaterBoxLocation = fAirBoxLocation + G4ThreeVector(0.,0.,fAirBoxSize.z()/2 + fWaterBoxSize.z()/2 + fWaterBoxSize.z()*i);
    fWaterBoxPhysical[i] = new G4PVPlacement(0,
        fWaterBoxLocation,
        fWaterBoxLogic,"WaterBox",
        fWorldLogic,
        false,
        0);
  }

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyDetectorConstruction::SetAirBoxSize(G4ThreeVector size) {
  if(fAirBoxSize != size) {
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    fAirBoxSize = size;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RadioBiologyDetectorConstruction::SetWaterBoxSize(G4ThreeVector size) {
  if(fWaterBoxSize != size) {
    G4RunManager::GetRunManager()->GeometryHasBeenModified();
    fWaterBoxSize = size;
  }
}
