#include "Action.h"

bool Action::cutOnce = true;

Action::Action(ApplicationManager *pApp) : pManager(pApp)
{
	// The constructor initializes the ApplicationManager pointer data member
}

Action::~Action()
{
}

