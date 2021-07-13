#include "Notification.h"


void Notification::Trigger(unsigned int ID)
{
    vector< function<void(unsigned int)> >::iterator i = FuncVec.begin();
    for(i; i != FuncVec.end(); i++)
    {
        (*i)(ID);
    }
}

