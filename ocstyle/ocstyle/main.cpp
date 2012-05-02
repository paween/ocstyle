//
//  main.cpp
//  ocstyle
//
//  Created by Itthipalkul, Paween on 4/26/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <clang-c/Index.h>
#include <vector>
#include "Variable.h"
#include "Function.h"
#include "SourceProcessor.h"

using namespace std;
using namespace ocstyle;

vector<CXCursor> *recurseStack;

CXChildVisitResult cursorVisitodfdfr(CXCursor cursor, CXCursor parent, CXClientData clientData)
{
    if (recurseStack->size() > 0) {
        // There is something in the stack, compare the parent
        unsigned int equals = clang_equalCursors(recurseStack->back(), parent);
        if (! equals) {
            bool found = false;
            for (int i = 0; i < recurseStack->size(); i++) {
                CXCursor curElem =recurseStack->at(i);
                if (clang_equalCursors(curElem, parent)) {
                    found = true;
                    break;
                }
            }
            if (found) {
                recurseStack->pop_back();
            } else {
                recurseStack->push_back(parent);
            }
        }
    } else {
        recurseStack->push_back(parent);
    }

    CXString spelling = clang_getCursorSpelling(cursor);
//    CXType type = clang_getCursorType(cursor);
    CXCursorKind kind = clang_getCursorKind(cursor);
//    CXString typeKind = clang_getTypeKindSpelling(type.kind);
    vector<OCSBase *> *list = (vector<OCSBase *> *)clientData;
    static Function *function = NULL;
    static CXCursor functionCursor;
    switch (kind) {
        case CXCursor_VarDecl:
        {
            Variable *var = new Variable((char *)clang_getCString(spelling), LocalVariable);
            list->push_back((OCSBase*)var);
            break;
        }
        case CXCursor_FunctionDecl:
        {
            function = new Function((char *)clang_getCString(spelling));
            list->push_back((OCSBase*)function);
            functionCursor = cursor;
            break;
        }
        case CXCursor_ParmDecl:
        {
            unsigned int equals = clang_equalCursors(parent, functionCursor);
            if (equals) {
                function->getParameters()->push_back((char *)clang_getCString(spelling));
            }
            break;
        }
        default:
        {

        }
    }

    for (int i = 0; i < recurseStack->size() - 1; i++) {
        cout << "\t";
    }

    CXSourceLocation location = clang_getCursorLocation(cursor);
    unsigned int line, col, offset;
    clang_getSpellingLocation(location, NULL, &line, &col, &offset);
    std::cout << "Line: " << line << " Col : " << col << " Offset : " << offset;

    std::cout << "Cursor : " << clang_getCString(spelling) << "\t" << clang_getCString(clang_getCursorKindSpelling(kind)) << std::endl;

    return CXChildVisit_Recurse;
}


int main(int argc, const char * argv[])
{
    SourceProcessor processor("/Users/paween/test.c", argc, argv);
    processor.parse();

//    recurseStack = new vector<CXCursor>();
//    CXIndex index = clang_createIndex(0, 0);
//    char sourceFilename[] = "/Users/frank/test.c";
//    CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, sourceFilename, argv, argc, NULL, 0, CXTranslationUnit_None);
//
//    CXCursor rootCursor = clang_getTranslationUnitCursor(translationUnit);
//
//    vector<OCSBase *> *list = new vector<OCSBase *>();
//    clang_visitChildren(rootCursor, &cursorVisitor, list);
//
//    for (vector<OCSBase *>::iterator it = list->begin(); it != list->end(); ++it) {
//        cout << (*it)->toString() << endl;
//    }
//
//    clang_disposeTranslationUnit(translationUnit);
//    clang_disposeIndex(index);
    return 0;
}

