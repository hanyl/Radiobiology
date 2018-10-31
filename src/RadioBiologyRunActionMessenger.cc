#include "RadioBiologyRunActionMessenger.hh"
#include "RadioBiologyRunAction.hh"
#include "G4UIcmdWithAString.hh"
#include "G4SystemOfUnits.hh"

//--------------------------------------------------------------------//
//
RadioBiologyRunActionMessenger::RadioBiologyRunActionMessenger(
    RadioBiologyRunAction* action):
  G4UImessenger(),fRunAction(action),
  fFileNameCmd(0)
{

  fFileNameCmd = new G4UIcmdWithAString("/output/filename",this);
  fFileNameCmd->SetParameterName("filename",true);
  fFileNameCmd->SetDefaultValue("RadioBiology");

}

//--------------------------------------------------------------------//
//

RadioBiologyRunActionMessenger::~RadioBiologyRunActionMessenger()
{
  delete fFileNameCmd;
}

//--------------------------------------------------------------------//
//

void RadioBiologyRunActionMessenger::SetNewValue(G4UIcommand * command,
    G4String newValue){
  if( command == fFileNameCmd ){
    fRunAction->SetFileName(newValue);
    return;
  }
}

//--------------------------------------------------------------------//
//
