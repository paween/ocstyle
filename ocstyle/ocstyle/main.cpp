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

CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData clientData)
{
    CXString spelling = clang_getCursorSpelling(cursor);
//    CXType type = clang_getCursorType(cursor);
    CXCursorKind kind = clang_getCursorKind(cursor);
//    CXString typeKind = clang_getTypeKindSpelling(type.kind);


    std::cout << "Cursor : " << clang_getCString(spelling) << "\t" << clang_getCString(clang_getCursorKindSpelling(kind)) << std::endl;
    return CXChildVisit_Recurse;
}


int main(int argc, const char * argv[])
{
    CXIndex index = clang_createIndex(0, 0);
    char sourceFilename[] = "/Users/paween/test.c";
    CXTranslationUnit translationUnit = clang_parseTranslationUnit(index, sourceFilename, argv, argc, NULL, 0, CXTranslationUnit_None);

    CXCursor rootCursor = clang_getTranslationUnitCursor(translationUnit);

    clang_visitChildren(rootCursor, &cursorVisitor, NULL);


    clang_disposeTranslationUnit(translationUnit);
    clang_disposeIndex(index);
    return 0;
}

