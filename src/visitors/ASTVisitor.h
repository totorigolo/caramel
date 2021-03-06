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

#include "../utils/Common.h"
#include "../Console.h"
#include "../utils/SourceFileUtil.h"
#include "../ast/context/Context.h"
#include "../ast/operators/binaryoperators/BinaryOperatorIndex.h"
#include "../ast/operators/prefixoperators/PrefixOperatorIndex.h"
#include "../ast/operators/postfixoperators/PostfixOperatorIndex.h"

#include <CaramelBaseVisitor.h>

#include <stdexcept>
#include <iostream>

namespace caramel::visitors {

class ContextPusher;

class ASTVisitor : public CaramelBaseVisitor {

public:
    explicit ASTVisitor(std::string const &sourceFileName);

    antlrcpp::Any visitR(CaramelParser::RContext *ctx) override;

    /// Returns vector<Statement::Ptr>
    antlrcpp::Any visitStatements(CaramelParser::StatementsContext *ctx) override;

    /// Returns vector<Statement::Ptr>
    antlrcpp::Any visitBlock(CaramelParser::BlockContext *ctx) override;

    /// Returns vector<Statement::Ptr>
    antlrcpp::Any visitDeclarations(CaramelParser::DeclarationsContext *ctx) override;

    /// Returns vector<Statement::Ptr>
    antlrcpp::Any visitInstructions(CaramelParser::InstructionsContext *ctx) override;

    /// Returns std::string
    antlrcpp::Any visitValidIdentifier(CaramelParser::ValidIdentifierContext *ctx) override;

    /// Returns SymbolType::Ptr (in a Symbol::Ptr)
    antlrcpp::Any visitTypeParameter(CaramelParser::TypeParameterContext *ctx) override;

    /// Returns Statement::Ptr
    antlrcpp::Any visitInstruction(CaramelParser::InstructionContext *ctx) override;

    /// Returns Statement::Ptr
    antlrcpp::Any visitTypeDefinition(CaramelParser::TypeDefinitionContext *ctx) override;

    /// Returns Jump::Ptr
    antlrcpp::Any visitReturnJump(CaramelParser::ReturnJumpContext *ctx) override;

    /// Returns Jump::Ptr
    antlrcpp::Any visitBreakJump(CaramelParser::BreakJumpContext *ctx) override;

    //--------------------------------------------------------------------------------------------------------
    // Variables

    /// Returns vector<Statement::Ptr>
    antlrcpp::Any visitVariableDeclaration(CaramelParser::VariableDeclarationContext *ctx) override;

    /// Returns vector<Statement::Ptr>
    antlrcpp::Any visitVariableDefinition(CaramelParser::VariableDefinitionContext *ctx) override;

    //--------------------------------------------------------------------------------------------------------
    // Functions

    /// Returns Statement::Ptr
    antlrcpp::Any visitFunctionDeclaration(CaramelParser::FunctionDeclarationContext *ctx) override;

    /// Returns Statement::Ptr
    antlrcpp::Any visitFunctionDefinition(CaramelParser::FunctionDefinitionContext *ctx) override;

    /// Returns std::vector< visitFunctionArgument()::returnType >
    antlrcpp::Any visitFunctionArguments(CaramelParser::FunctionArgumentsContext *ctx) override;

    /// Returns FunctionParameterSignature
    antlrcpp::Any visitFunctionArgument(CaramelParser::FunctionArgumentContext *ctx) override;

    //--------------------------------------------------------------------------------------------------------
    // Arrays

    /// Returns Statement::Ptr
    antlrcpp::Any visitArrayDeclaration(CaramelParser::ArrayDeclarationContext *ctx) override;

    /// Returns Statement::Ptr
    antlrcpp::Any visitArrayDefinition(CaramelParser::ArrayDefinitionContext *ctx) override;

    /// Returns std::vector<Expression::Ptr>
    antlrcpp::Any visitArrayBlock(CaramelParser::ArrayBlockContext *ctx) override;

    //--------------------------------------------------------------------------------------------------------
    // Expressions

    /// Returns Expression::Ptr
    antlrcpp::Any visitExpression(CaramelParser::ExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitAdditiveExpression(CaramelParser::AdditiveExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitAtomicExpression(CaramelParser::AtomicExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitComparison(CaramelParser::ComparisonContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitEqualityComparison(CaramelParser::EqualityComparisonContext *ctx) override;

    /// Returns AtomicExpression::Ptr
    antlrcpp::Any visitNumberConstant(CaramelParser::NumberConstantContext *ctx) override;

    /// Returns AtomicExpression::Ptr
    antlrcpp::Any visitCharConstant(CaramelParser::CharConstantContext *ctx) override;

    /// Returns AtomicExpression::Ptr
    antlrcpp::Any visitPositiveConstant(CaramelParser::PositiveConstantContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitPrefixUnaryExpression(CaramelParser::PrefixUnaryExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitPostfixUnaryExpression(CaramelParser::PostfixUnaryExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitBitwiseShiftExpression(CaramelParser::BitwiseShiftExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitMultiplicativeExpression(CaramelParser::MultiplicativeExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitAndBitwiseExpression(CaramelParser::AndBitwiseExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitOrBitwiseExpression(CaramelParser::OrBitwiseExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitXorBitwiseExpression(CaramelParser::XorBitwiseExpressionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitConjunction(CaramelParser::ConjunctionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitDisjunction(CaramelParser::DisjunctionContext *ctx) override;

    /// Returns Expression::Ptr
    antlrcpp::Any visitAssignment(CaramelParser::AssignmentContext *ctx) override;

    /// Returns LValue::Ptr
    antlrcpp::Any visitLvalue(CaramelParser::LvalueContext *ctx) override;

    //--------------------------------------------------------------------------------------------------------
    // Operators

    /// Returns BinaryOperator::Ptr
    antlrcpp::Any visitMultiplicativeOperator(CaramelParser::MultiplicativeOperatorContext *ctx) override;

    /// Returns BinaryOperator::Ptr
    antlrcpp::Any visitBitwiseShiftOperator(CaramelParser::BitwiseShiftOperatorContext *ctx) override;

    /// Returns BinaryOperator::Ptr
    antlrcpp::Any visitComparativeOperator(CaramelParser::ComparativeOperatorContext *ctx) override;

    /// Returns BinaryOperator::Ptr
    antlrcpp::Any visitAdditiveOperator(CaramelParser::AdditiveOperatorContext *ctx) override;

    /// Returns BinaryOperator::Ptr
    antlrcpp::Any visitAssignmentOperator(CaramelParser::AssignmentOperatorContext *ctx) override;

    /// Returns BinaryOperator::Ptr
    antlrcpp::Any visitEqualityOperator(CaramelParser::EqualityOperatorContext *ctx) override;

    /// Returns UnaryOperator::Ptr
    antlrcpp::Any visitPostfixUnaryOperator(CaramelParser::PostfixUnaryOperatorContext *ctx) override;

    /// Returns UnaryOperator::Ptr
    antlrcpp::Any visitPrefixUnaryOperator(CaramelParser::PrefixUnaryOperatorContext *ctx) override;

    //--------------------------------------------------------------------------------------------------------
    // Control blocks

    /// Returns ControlBlock::Ptr
    antlrcpp::Any visitControlBlock(CaramelParser::ControlBlockContext *ctx) override;

    /// Returns IfBlock::Ptr
    antlrcpp::Any visitIfBlock(CaramelParser::IfBlockContext *ctx) override;

    /// Returns ForBlock::Ptr
    antlrcpp::Any visitForBlock(CaramelParser::ForBlockContext *ctx) override;

    /// Returns WhileBlock::Ptr
    antlrcpp::Any visitWhileBlock(CaramelParser::WhileBlockContext *ctx) override;

    /// Returns DoWhileBlock::Ptr
    antlrcpp::Any visitDoWhileBlock(CaramelParser::DoWhileBlockContext *ctx) override;

private:
    std::shared_ptr<ast::Context> rootContext(); //
    std::shared_ptr<ast::Context> currentContext(); //
    friend class ContextPusher;

    antlrcpp::Any visitChildren(antlr4::tree::ParseTree *node) override;

    void incrementErrorCount();

public:
    int getErrorCount();

private:
    std::stack<std::shared_ptr<ast::Context>> mContextStack;
    std::string mSourceFilename;

    ast::BinaryOperatorIndex mBinaryOperatorIndex;
    ast::PrefixOperatorIndex mPrefixOperatorIndex;
    ast::PostfixOperatorIndex mPostfixOperatorIndex;
    int mErrorCount = 0;
};

class ContextPusher {
public:
    explicit ContextPusher(ASTVisitor &abstractSyntaxTreeVisitor);
    virtual ~ContextPusher();

    ast::Context::Ptr getContext();

    // TODO: Move to a proper class
    void verifUsageStatic(ast::Context::Ptr context);

private:
    ASTVisitor &mASTVisitor;
};

} // namespace caramel::visitors
