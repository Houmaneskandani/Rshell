
#ifndef __OUTPUT_REDIRECT_H__
#define __OUTPUT_REDIRECT_H__

#include "interface.h"
#include "connector.h"

using namespace std;

class OutputRedirect : public Connector
{
    public:
        OutputRedirect() {}
        OutputRedirect(Interface* left, string filename ): Connector(left, filename){
        };

        bool execute();
        string getCommand();
        
};

#endif
