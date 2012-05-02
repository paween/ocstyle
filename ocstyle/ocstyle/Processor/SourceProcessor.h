//
//  Created by paween on 5/1/12.
//
//



#ifndef __SourceProcessor_H_
#define __SourceProcessor_H_

#include <iostream>
#include <vector>
#include <clang-c/Index.h>
#include "OCSBase.h"

using namespace std;

namespace ocstyle{

    class SourceProcessor {
        private:

        public:
        CXFile sourceFile;
        CXTranslationUnit translationUnit;
        CXCursor rootCursor;
        vector<CXCursor> *recurseStack;
        vector<OCSBase *> *data;
        CXIndex index;

        SourceProcessor(const char *sourceFilename, int argc, const char *argv[]);
        ~SourceProcessor();
        void parse();
        void print();
    };
}


#endif //__SourceProcessor_H_
