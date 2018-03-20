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

#include "AbstractSyntaxTreeVisitor.h"
#include "../datastructure/Constant.h"

using namespace Caramel::Visitors;

antlrcpp::Any AbstractSyntaxTreeVisitor::visitR(CaramelParser::RContext *ctx) {
    pushNewContext();
    return visitChildren(ctx);
}

antlrcpp::Any AbstractSyntaxTreeVisitor::visitStatement(CaramelParser::StatementContext *ctx) {

    using namespace Caramel::Colors;

    std::cout << "Visited statement: " << yellow << ctx->getText() << reset << std::endl;

    return visitChildren(ctx);
}

antlrcpp::Any AbstractSyntaxTreeVisitor::visitNumberConstant(CaramelParser::NumberConstantContext *ctx) {
    int value = stoi(ctx->getText());

    return Constant::Create(value);
}

antlrcpp::Any AbstractSyntaxTreeVisitor::visitCharConstant(CaramelParser::CharConstantContext *ctx) {
    return CaramelBaseVisitor::visitCharConstant(ctx);
}

void AbstractSyntaxTreeVisitor::pushNewContext() {
    mContextStack.push(Context::Create());
}

Context::Ptr AbstractSyntaxTreeVisitor::currentContext() {
    return mContextStack.top();
}