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

#include "../ast/symboltable/Symbol.h"
#include <memory>

namespace caramel::ir {

class BasicBlock;
class IRVisitor;

enum class Operation {
    empty,
    ldconst,
    copy,
    add,
    sub,
    mul,
    mod,
    div,
    lbs,
    rbs,
    band,
    bor,
    bxor,
    rmem,
    wmem,
    call,
    cmp_eq,
    cmp_lt,
    cmp_le,
    cmp_ge,
    cmp_gt,
    pushq,
    movq,
    ret,
    prolog,
    epilog,
    leave,
    nope,
    popq,
    ftr // equivalent of ser
};

class IR {
public:
    using Ptr = std::shared_ptr<IR>;
    using WeakPt = std::weak_ptr<IR>;

    static constexpr const char* COUNTER_REG = "%rcx";
    static constexpr const char* DATA_REG = "%rdx";
    static constexpr const char* BASE_REG = "%rbx";
    static constexpr const char* SOURCE_REG = "%rsi";
    static constexpr const char* DEST_REG = "%rdi";
    static constexpr const char* BASE_POINTER_REG = "%rbp";
    static constexpr const char* STACK_POINTER_REG = "%rsp";
    static constexpr const char* ACCUMULATOR = "%rax";
    static constexpr const char* ACCUMULATOR_1 = "%r10"; // FIXME: deprecated
    static constexpr const char* ACCUMULATOR_2 = "%r11"; // FIXME: deprecated
    static constexpr const char* REGISTER_8 = "%r8";
    static constexpr const char* REGISTER_9 = "%r9";
    static constexpr const char* REGISTER_10 = "%r10";
    static constexpr const char* REGISTER_11 = "%r11";

public:
    explicit IR(
            Operation operation,
            std::shared_ptr<BasicBlock> parentBlock,
            ast::PrimaryType::Ptr type
    );
    explicit IR(
            std::string const& name,
            Operation operation,
            std::shared_ptr<BasicBlock> parentBlock,
            ast::PrimaryType::Ptr type
    );

    virtual ~IR() = default;

    virtual Operation getOperation() const;

    virtual std::string getReturnName() const;

    ast::PrimaryType::Ptr getType() const;

    std::shared_ptr<BasicBlock> getParentBlock();

    Operation getOperation();

    virtual void accept(std::shared_ptr<IRVisitor> const &visitor, std::ostream &os) = 0;

private:
    std::string mName;
    Operation mOperation;
    std::shared_ptr<BasicBlock> mParentBlock;
    ast::PrimaryType::Ptr mType;
};

} // namespace caramel::ir
