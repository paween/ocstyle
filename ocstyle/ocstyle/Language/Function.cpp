//
//  Created by frank on 4/30/12.
//
//


#include <sstream>
#include <string>
#include "Function.h"


namespace ocstyle
{

    using namespace std;

    Function::Function() {
        mFunctionName = NULL;
        mParameters = new vector<char *>();
    }

    Function::Function(char *functionName) {
        mFunctionName = NULL;
        mParameters = new vector<char *>();
        setFunctionName(functionName);
    }

    Function::~Function() {
        if (mFunctionName != NULL) {
            free(mFunctionName);
        }
        if (mParameters != NULL) {
            delete mParameters;
        }
    }

    char *Function::getFunctionName() {
        return mFunctionName;
    }

    void Function::setFunctionName(char *functionName) {
        if (functionName != mFunctionName) {
            if (mFunctionName != NULL) {
                free(mFunctionName);
            }
            const size_t length = strlen(functionName);
            mFunctionName = (char *) malloc(sizeof(char *) * length);
            memmove(mFunctionName, functionName, length);
        }
    }

    vector<char *> *Function::getParameters() {
        return mParameters;
    }

    void Function::setParameters(std::vector<char *> * params) {
        if (params != mParameters) {
            if (mParameters != NULL) {
                delete mParameters;
            }
            mParameters = params;
        }
    }

    const char * Function::toString() {
        stringstream stream;
        stream << "{ " << mFunctionName << " : ";
        for (vector<char *>::iterator it = mParameters->begin(); it != mParameters->end(); ++it) {
            stream << (*it) << ", ";
        }
        string description = stream.str();
        if (mParameters->size() > 0) {
            description = description.substr(0, description.length() - 2);
        }
        description.append(" }");

        return description.c_str();
    }
}