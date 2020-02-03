
#ifndef __OUTPUT_REDIRECT_APPEND_H__
#define __OUTPUT_REDIRECT_APPEND_H__

#include "interface.h"
#include "connector.h"

using namespace std;

class OutputRedirectAppend : public Connector
{
    public:
        OutputRedirectAppend() {}
        OutputRedirectAppend(Interface* left, string filename ): Connector(left, filename){
        };

        bool execute();
        string getCommand();
        
};

#endif
