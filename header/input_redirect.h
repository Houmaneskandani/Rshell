#ifndef __INPUT_REDIRECT_H__
#define __INPUT_REDIRECT_H__

#include "interface.h"
#include "connector.h"

using namespace std;

class InputRedirect : public Connector
{
    public:
        InputRedirect() {}
        InputRedirect(Interface* left, string filename ): Connector(left, filename){
        };

        bool execute();
        string getCommand();
        
};

#endif
