#include "RadioBiologyPrimaryGeneratorActionMessenger.hh"
#include "RadioBiologyPrimaryGeneratorAction.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4SystemOfUnits.hh"

//--------------------------------------------------------------------//
//
RadioBiologyPrimaryGeneratorActionMessenger::RadioBiologyPrimaryGeneratorActionMessenger(
    RadioBiologyPrimaryGeneratorAction* action):
  G4UImessenger(),fPrimaryGeneratorAction(action),
  fAirBoxThickCmd(0)
{

  fAirBoxThickCmd = new G4UIcmdWithADoubleAndUnit("/gun/AirBoxThick",this);
  fAirBoxThickCmd->SetParameterName("AirBoxThick",true);
  fAirBoxThickCmd->SetDefaultValue(1.4);
  fAirBoxThickCmd->SetDefaultUnit("mm");

}

//--------------------------------------------------------------------//
//

RadioBiologyPrimaryGeneratorActionMessenger::~RadioBiologyPrimaryGeneratorActionMessenger()
{
  delete fAirBoxThickCmd;
}

//--------------------------------------------------------------------//
//

void RadioBiologyPrimaryGeneratorActionMessenger::SetNewValue(G4UIcommand * command,
    G4String newValue){
  if( command == fAirBoxThickCmd ){
    fPrimaryGeneratorAction->SetAirBoxThick(fAirBoxThickCmd->GetNewDoubleValue(newValue));
    return;
  }
}

//--------------------------------------------------------------------//
//
