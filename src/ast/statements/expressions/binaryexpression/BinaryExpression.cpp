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

#include "BinaryExpression.h"


namespace caramel::ast {

BinaryExpression::BinaryExpression(
        std::shared_ptr<Expression> const &leftExpression,
        std::shared_ptr<BinaryOperator> const &binaryOperator,
        std::shared_ptr<Expression> const &rightExpression,
        antlr4::Token *startToken
) : Expression(startToken, StatementType::BinaryExpression),
    mLeftExpression{leftExpression},
    mBinaryOperator{binaryOperator},
    mRightExpression{rightExpression} {}

std::shared_ptr<ir::IR>
BinaryExpression::getIR(
        std::shared_ptr<ir::BasicBlock> &currentBasicBlock
) {
    return mBinaryOperator->getIR(currentBasicBlock, mLeftExpression, mRightExpression);
}

ir::GetBasicBlockReturn BinaryExpression::getBasicBlock(ir::CFG *controlFlow) {
    return mBinaryOperator->getBasicBlock(controlFlow, mLeftExpression, mRightExpression);
}

bool BinaryExpression::shouldReturnAnIR() const {
    return mBinaryOperator->shouldReturnAnIR();
}

bool BinaryExpression::shouldReturnABasicBlock() const {
    return mBinaryOperator->shouldReturnABasicBlock();
}

PrimaryType::Ptr BinaryExpression::getPrimaryType() const {
    return PrimaryType::max(mLeftExpression->getPrimaryType(), mRightExpression->getPrimaryType());
}

void BinaryExpression::acceptAstDotVisit() {
    addNode(thisId(), "BinaryExpression: " + std::string(mBinaryOperator->getToken()));
    visitChildrenAstDot();
}

void BinaryExpression::visitChildrenAstDot() {
    addEdge(thisId(), mLeftExpression->thisId(), "left");
    addEdge(thisId(), mRightExpression->thisId(), "right");
    mLeftExpression->acceptAstDotVisit();
    mRightExpression->acceptAstDotVisit();
}

} // namespace caramel::ast
