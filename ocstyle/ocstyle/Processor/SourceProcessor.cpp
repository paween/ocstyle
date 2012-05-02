//
//  Created by paween on 5/1/12.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "SourceProcessor.h"
#include "Variable.h"

using namespace std;
using namespace ocstyle;

void adjustRecurseStack(CXCursor parent, SourceProcessor *sourceProcessor) {
    if (sourceProcessor->recurseStack->size() > 0) {
        // There is something in the stack, compare the parent
        unsigned int equals = clang_equalCursors(sourceProcessor->recurseStack->back(), parent);
        if (! equals) {
            bool found = false;
            for (int i = 0; i < sourceProcessor->recurseStack->size(); i++) {
                CXCursor curElem =sourceProcessor->recurseStack->at(i);
                if (clang_equalCursors(curElem, parent)) {
                    found = true;
                    break;
                }
            }
            if (found) {
                sourceProcessor->recurseStack->pop_back();
            } else {
                sourceProcessor->recurseStack->push_back(parent);
            }
        }
    } else {
        sourceProcessor->recurseStack->push_back(parent);
    }
}

CXChildVisitResult cursorVisitor(CXCursor cursor, CXCursor parent, CXClientData clientData) {
    SourceProcessor *sourceProcessor = (SourceProcessor *)clientData;
    adjustRecurseStack(parent, sourceProcessor);

    // Process the cursor
    CXSourceLocation location = clang_getCursorLocation(cursor);
    unsigned int line, col, offset;
    CXFile file;
    clang_getSpellingLocation(location, &file, &line, &col, &offset);

    if (file != sourceProcessor->sourceFile) {
        // Cursor comes from an include, or something not in the source file, ignore
        return CXChildVisit_Continue;
    }

    // Process the cursor
    CXString spelling = clang_getCursorSpelling(cursor);
    CXCursorKind kind = clang_getCursorKind(cursor);
    switch (kind) {
        case CXCursor_VarDecl:
        {
            Variable *variable = new Variable((char *)clang_getCString(spelling), LocalVariable);
            sourceProcessor->data->push_back(dynamic_cast<OCSBase *>(variable));
            break;
        }
        default:
        {
            // Do nothing
        }
    }

    std::cout << "Line: " << line << " Col : " << col << " Offset : " << offset;
    std::cout << "Cursor : " << clang_getCString(spelling) << "\t" << clang_getCString(clang_getCursorKindSpelling(kind)) << std::endl;

    return CXChildVisit_Recurse;
}

SourceProcessor::SourceProcessor(const char *sourceFilename, int argc, const char *argv[]) {
    index = clang_createIndex(0, 0);
    translationUnit = clang_parseTranslationUnit(index,
                                                sourceFilename,
                                                argv,
                                                argc,
                                                NULL,
                                                0,
                                                CXTranslationUnit_None);
    sourceFile = clang_getFile(translationUnit, sourceFilename);
    rootCursor = clang_getTranslationUnitCursor(translationUnit);
    recurseStack = new vector<CXCursor>();
    data = new vector<OCSBase *>();
}

SourceProcessor::~SourceProcessor() {
    clang_disposeTranslationUnit(translationUnit);
    clang_disposeIndex(index);
    delete recurseStack;
}

void SourceProcessor::parse() {
    clang_visitChildren(rootCursor, cursorVisitor, this);
}

void SourceProcessor::print() {

}