
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

#include "LValue.h"
#include "../../../symboltable/ArraySymbol.h"


namespace caramel::ast {

class ArrayAccess : public LValue {
public:
    using Ptr = std::shared_ptr<ArrayAccess>;
    using WeakPtr = std::weak_ptr<ArrayAccess>;

public:
    ArrayAccess(
            caramel::ast::Expression::Ptr index,
            antlr4::Token *startToken
    );
    ~ArrayAccess() override = default;

    Symbol::Ptr getSymbol() const override;
    void setSymbol(ArraySymbol::Ptr symbol);

    Expression::Ptr getIndex() const;

    std::string getArrayName() const;

    PrimaryType::Ptr getPrimaryType() const override;

    bool shouldReturnAnIR() const override;

    std::shared_ptr<ir::IR> getIR(std::shared_ptr<caramel::ir::BasicBlock> &currentBasicBlock) override;

    void acceptAstDotVisit() override;
    void visitChildrenAstDot() override;

private:
    Symbol::Ptr mSymbol;
    Expression::Ptr mIndex;
};

} // namespace caramel::ast
