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

#pragma once

#include "AtomicExpression.h"
#include "../../../symboltable/Symbol.h"
#include "../../../symboltable/FunctionSymbol.h"


namespace caramel::ast {

class FunctionCall : public AtomicExpression {
public:
    using Ptr = std::shared_ptr<FunctionCall>;
    using WeakPtr = std::shared_ptr<FunctionCall>;

    explicit FunctionCall(std::vector<Expression::Ptr> &&arguments, antlr4::Token *startToken);
    ~FunctionCall() override = default;

    Symbol::Ptr getSymbol() const;
    void setSymbol(FunctionSymbol::Ptr symbol);

    PrimaryType::Ptr getPrimaryType() const override;

    std::vector<PrimaryType::Ptr> getArgumentsPrimaryTypes() const;

    void acceptAstDotVisit() override;
    void visitChildrenAstDot() override;

    bool shouldReturnAnIR() const override { return true; }
    std::shared_ptr<ir::IR> getIR(std::shared_ptr<ir::BasicBlock> &currentBasicBlock) override;

private:
    Symbol::Ptr mSymbol;
    std::vector<Expression::Ptr> mArguments;
};

} // namespace caramel::ast
