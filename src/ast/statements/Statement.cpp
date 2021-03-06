/*
 * MIT License
 *
 * Copyright (c) 2018 insa.4if.hexanome_kalate
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

#include "Statement.h"
#include "../../ir/IR.h"


namespace caramel::ast {

long long Statement::lastTemVarNumber = -1;

Statement::Statement(antlr4::Token *startToken, StatementType type)
        : mType{type} {
    if (nullptr != startToken) {
        mLine = startToken->getLine();
        mColumn = startToken->getCharPositionInLine();
        mLength = startToken->getText().length();
    } else {
        mLine = 0;
        mColumn = 0;
        mLength = 0;
    }

    if (type == StatementType::Unknown) {
        logger.warning() << "Statement with Unknown StatementType created!";
    }
}

size_t Statement::getLine() const {
    return mLine;
}

size_t Statement::getColumn() const {
    return mColumn;
}

size_t Statement::getLength() const {
    return mLength;
}

StatementType Statement::getType() const {
    return mType;
}

void Statement::acceptAstDotVisit() {
    logger.warning() << "Default accept() for " << thisId() << ", which is a " << mType << '.';
}

} // namespace caramel::ast
