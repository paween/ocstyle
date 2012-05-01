//
//  Created by frank on 4/30/12.
//
//



#ifndef __Function_H_
#define __Function_H_

#include <iostream>
#include <vector>
#include <cstdarg>
#include "OCSBase.h"

namespace ocstyle
{
    using namespace std;

    class Function : OCSBase {
    private:
        char *mFunctionName;
        vector<char *> *mParameters;

    public:
        Function();
        Function(char *functionName);
        ~Function();
        char *getFunctionName();
        void setFunctionName(char * functionName);
        vector<char *> *getParameters();
        void setParameters(vector<char *> *params);
        const char * toString();
    };
}


#endif //__Function_H_
