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

#include "../symboltable/SymbolTable.h"
#include "../statements/Statement.h"

#include <memory>
#include <vector>
#include <ostream>


namespace caramel::ast {

class Context : public AstDotNode {
public:
    using Ptr = std::shared_ptr<Context>;
    using WeakPtr = std::weak_ptr<Context>;

    Context();
    explicit Context(std::shared_ptr<Context> const &parent);

    std::shared_ptr<Context> getParent() const;

    std::shared_ptr<SymbolTable> getSymbolTable() const;

    void addStatements(std::vector<std::shared_ptr<Statement>> &&statements);
    std::vector<std::shared_ptr<Statement>> getStatements();

    void acceptAstDotVisit() override;
    void visitChildrenAstDot() override;

    friend std::ostream &operator<<(std::ostream &os, Context const &context);

private:
    std::shared_ptr<Context> mParent;
    std::shared_ptr<SymbolTable> mSymbolTable;
    std::vector<std::shared_ptr<Statement>> mStatements;
};

} // namespace caramel::dataStructure
