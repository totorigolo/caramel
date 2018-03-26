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

#include "Declaration.h"

#include <memory>

namespace caramel::dataStructure::statements::declaration {

class VariableDeclaration : public caramel::dataStructure::statements::declaration::Declaration {
public:
    using Ptr = std::shared_ptr<VariableDeclaration>;

    VariableDeclaration(
            std::weak_ptr<caramel::dataStructure::symbolTable::VariableSymbol> symbol,
            antlr4::Token *startToken
    );

    static Ptr Create(
            std::weak_ptr<caramel::dataStructure::symbolTable::VariableSymbol> symbol,
            antlr4::Token *startToken
    ) {
        return std::make_shared<VariableDeclaration>(symbol, startToken);
    }

public:

    std::weak_ptr<caramel::dataStructure::symbolTable::Symbol> getSymbol() override {
        throw std::runtime_error("Cannot get the VariableSymbol as Symbol");
    };

    std::weak_ptr<caramel::dataStructure::symbolTable::VariableSymbol>
    getVariableSymbol();

private:
    std::weak_ptr<caramel::dataStructure::symbolTable::VariableSymbol> mSymbol;
};

} // namespace caramel::dataStructure::statements::declaration
