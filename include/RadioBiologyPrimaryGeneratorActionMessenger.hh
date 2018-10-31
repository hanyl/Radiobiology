#ifndef RadioBiologyPrimaryGeneratorActionMessenger_h
#define RadioBiologyPrimaryGeneratorActionMessenger_h 1

#include "G4UImessenger.hh"

class RadioBiologyPrimaryGeneratorAction;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithADouble;

class RadioBiologyPrimaryGeneratorActionMessenger: public G4UImessenger{

  public:
    RadioBiologyPrimaryGeneratorActionMessenger(RadioBiologyPrimaryGeneratorAction*);
    virtual ~RadioBiologyPrimaryGeneratorActionMessenger();
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    RadioBiologyPrimaryGeneratorAction* fPrimaryGeneratorAction;
    G4UIcmdWithADoubleAndUnit* fAirBoxThickCmd; 
};

#endif
