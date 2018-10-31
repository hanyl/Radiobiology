#ifndef RadioBiologyRunActionMessenger_h
#define RadioBiologyRunActionMessenger_h 1

#include "G4UImessenger.hh"

class RadioBiologyRunAction;
class G4UIcmdWithAString;

class RadioBiologyRunActionMessenger: public G4UImessenger{

  public:
    RadioBiologyRunActionMessenger(RadioBiologyRunAction*);
    virtual ~RadioBiologyRunActionMessenger();
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    RadioBiologyRunAction* fRunAction;
    G4UIcmdWithAString* fFileNameCmd; 
};

#endif
