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


#include "Symbol.h"

namespace caramel::ast {

class TypeSymbol : public Symbol {
public:
    using Ptr = std::shared_ptr<TypeSymbol>;
    using WeakPtr = std::weak_ptr<TypeSymbol>;

public:
    TypeSymbol(const std::string &mName, std::shared_ptr<PrimaryType> mType);

    ~TypeSymbol() override = default;

    bool isDeclared() override;
    bool isDefined() override;

    void onDeclaration(const std::shared_ptr<caramel::ast::Declaration> &declaration) override;
    void onDefinition(const std::shared_ptr<caramel::ast::Definition> &definition) override;

    void acceptAstDotVisit() override;

private:
    bool mDefined;
};

} // namespace caramel::dataStructure::symbolTable



