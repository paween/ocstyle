//
//  Created by paween on 4/30/12.
//
//


#include "Variable.h"
#include <sstream>

namespace ocstyle
{
    using namespace std;

    const char *Variable::getVariableTypeSpelling(VariableType type) {
        static const char * const VARIABLE_TYPE_SPELLING[] = {
            "LocalVariable",
            "InstanceVariable",
            "StaticVariable"
        };

        return VARIABLE_TYPE_SPELLING[type];
    }

    Variable::Variable() {
        this->mVariableName = NULL;
        this->mVariableType = LocalVariable;
    };

    Variable::~Variable() {
        if (mVariableName != NULL) {
            free(mVariableName);
        }
    }

    Variable::Variable(char *name, VariableType type) {
        mVariableName = NULL;
        setVariableName(name);
        this->mVariableType = type;
    }

    char * Variable::getVariableName() {
        return mVariableName;
    }

    void Variable::setVariableName(char *name) {
        if (name != mVariableName) {
            if (mVariableName != NULL) {
                free(mVariableName);
            }
            const size_t length = strlen(name);
            mVariableName = (char *) malloc(length * sizeof(char));
            memmove(mVariableName, name, length);
        }
    }

    VariableType Variable::getVariableType() {
        return mVariableType;
    }

    void Variable::setVariableType(ocstyle::VariableType type) {
        mVariableType = type;
    }

    const char *Variable::toString() {
        stringstream stream;
        stream << "{ " << mVariableName << " : " << getVariableTypeSpelling(mVariableType) << " }";
        return stream.str().c_str();
    }
}