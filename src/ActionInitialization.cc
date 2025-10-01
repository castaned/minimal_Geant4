#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "StrackingAction.hh"

void ActionInitialization::BuildForMaster() const {
  SetUserAction(new RunAction());
}

void ActionInitialization::Build() const {
  auto runAction = new RunAction();
  
  SetUserAction(new PrimaryGeneratorAction());
  SetUserAction(runAction);
  SetUserAction(new StackingAction(runAction));
}
