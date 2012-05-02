//
//  Created by paween on 4/30/12.
//
//



#ifndef __Variable_H_
#define __Variable_H_

#include <iostream>
#include <string>
#include "OCSBase.h"

namespace ocstyle
{
    using namespace std;

    typedef enum {
        LocalVariable,
        InstanceVariable,
        StaticVariable,
    } VariableType;

    class Variable : public OCSBase {
        private:
        char *mVariableName;
        VariableType mVariableType;
        void *context;

        public:
        static const char *getVariableTypeSpelling(VariableType type);

        Variable();
        ~Variable();
        const char *toString();
        Variable(char *name, VariableType type);
        char *getVariableName();
        void setVariableName(char *name);
        VariableType getVariableType();
        void setVariableType(VariableType type);
    };

}

#endif //__Variable_H_
