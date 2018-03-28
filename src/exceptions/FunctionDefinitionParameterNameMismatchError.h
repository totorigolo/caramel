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

#include "../Console.h"
#include "SemanticError.h"

#include <stdexcept>
#include <ParserRuleContext.h>


namespace caramel::exceptions {

class FunctionDefinitionParameterNameMismatchError : public SemanticError {
public:
    FunctionDefinitionParameterNameMismatchError(std::string const &message,
                                                 antlr4::ParserRuleContext *antlrContext,
                                                 std::string declaredName,
                                                 std::string definedName)
            : SemanticError(message),
              mAntlrContext{antlrContext},
              mDeclaredName{std::move(declaredName)},
              mDefinedName{std::move(definedName)} {
    }

    void explain(SourceFileUtil sourceFileUtil) const override {
        //todo
        logger.fatal() << what();
    }

private:
    antlr4::ParserRuleContext *mAntlrContext;
    std::string mDeclaredName;
    std::string mDefinedName;
};

} // namespace caramel::exceptions