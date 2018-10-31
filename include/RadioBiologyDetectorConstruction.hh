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
// --------------------------------------------------------------
//

#ifndef RadioBiologyDetectorConstruction_h
#define RadioBiologyDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "RadioBiologyDetectorConstructionMessenger.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4RunManager.hh"
#include "G4MagneticField.hh"
#include "G4ElectricField.hh"

#include "globals.hh"

class G4UniformMagField;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class RadioBiologyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    
    RadioBiologyDetectorConstruction();
    ~RadioBiologyDetectorConstruction();
    
    G4VPhysicalVolume* Construct();

private:
    RadioBiologyDetectorConstructionMessenger* fMessenger;

private:
    G4ThreeVector fWorldSize;
    G4Box* fWorldSolid;
    G4LogicalVolume* fWorldLogic;
    G4VPhysicalVolume* fWorldPhysical;
    G4Material* fWorldMaterial;

    //** AirBox **//
public:
    void AddAirBoxTarget() {
        fAirBox = true;
        G4RunManager::GetRunManager()->GeometryHasBeenModified();
    };

    void AddWaterBoxTarget() {
      fWaterBox = true;
      G4RunManager::GetRunManager()->GeometryHasBeenModified();
    };

    G4ThreeVector GetWorldSize(){return fWorldSize;}

    void SetAirBoxSize(G4ThreeVector);
    G4ThreeVector GetAirBoxSize() {return fAirBoxSize;};
    G4ThreeVector GetAirBoxLocation(){return fAirBoxLocation;}
    
    void SetWaterBoxSize(G4ThreeVector);
    G4ThreeVector GetWaterBoxSize() {return fWaterBoxSize;};
    G4ThreeVector GetWaterBoxLocation() {return fWaterBoxLocation;};
    G4int GetNumberOfWaterLayer() {return fNbOfLayers;};

    G4VPhysicalVolume* GetWorld() {return fWorldPhysical;}
    G4VPhysicalVolume* GetAirBox() {return fAirBoxPhysical;}
    G4VPhysicalVolume* GetWaterBox(int index) {return fWaterBoxPhysical[index];}

private:
    void ConstructAirBox();
    void ConstructWaterBox();
    G4bool fAirBox;
    G4bool fWaterBox;
    
    G4ThreeVector fAirBoxSize;
    G4ThreeVector fAirBoxLocation; 
    G4VSolid* fAirBoxSolid;
    G4LogicalVolume* fAirBoxLogic;
    G4VPhysicalVolume* fAirBoxPhysical;

    G4int fNbOfLayers;
    G4ThreeVector fWaterBoxSize;
    G4ThreeVector fWaterBoxLocation;
    G4VSolid* fWaterBoxSolid;
    G4LogicalVolume* fWaterBoxLogic;
    G4VPhysicalVolume* fWaterBoxPhysical[10];

    G4ThreeVector fWaterLayerSize;
    G4ThreeVector fWaterLayerLocation;
    G4VSolid* fWaterLayerSolid;
    G4LogicalVolume* fWaterLayerLogic;
    G4VPhysicalVolume* fWaterLayerPhysical;

};

#endif
