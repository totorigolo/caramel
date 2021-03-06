grammar Caramel;
r
  : statements EOF
  ;

// Program statements
statements
  : MultilineWhiteSpace* statement (MultilineWhiteSpace* statement)* MultilineWhiteSpace*
  ;
statement
  : escaped
  | jump MultilineWhiteSpace* InstructionSeparator
  | controlBlock
  | functionDefinition
  | functionDeclaration MultilineWhiteSpace* InstructionSeparator
  | arrayDefinition MultilineWhiteSpace* InstructionSeparator
  | variableDefinition MultilineWhiteSpace* InstructionSeparator
  | expression MultilineWhiteSpace* InstructionSeparator
  | InstructionSeparator
  ;

// Escaped blocks
escaped
  : comment
  | macro
  ;
comment : (SingleLineComment | BlockComment) ;
macro : Macro ;

BlockComment : FragmentBlockComment ;

// Declarations
functionDeclaration
  : typeParameter InlineWhiteSpace+ validIdentifier namedArguments
  ;
functionDefinition
  : functionDeclaration MultilineWhiteSpace* block ;

variableDeclaration
  : typeParameter InlineWhiteSpace+ validIdentifier (InlineWhiteSpace* Comma InlineWhiteSpace* validIdentifier)*
  ;
variableDefinition
  : variableDeclaration (MultilineWhiteSpace* Assignment InlineWhiteSpace* expression)?
  ;

arrayDeclarationVoid
  : typeParameter InlineWhiteSpace+ validIdentifier InlineWhiteSpace* arraySizeDeclarationVoid
  ;
arrayDeclaration
  : typeParameter InlineWhiteSpace+ validIdentifier InlineWhiteSpace* arraySizeDeclaration
  ;
arrayDefinition
  : arrayDeclarationVoid MultilineWhiteSpace* Assignment MultilineWhiteSpace* arrayBlock
  | arrayDeclaration (MultilineWhiteSpace* Assignment MultilineWhiteSpace* arrayBlock)*
  ;
arraySizeDeclaration
  : L_Bracket InlineWhiteSpace* positiveConstant InlineWhiteSpace* R_Bracket
  ;
arraySizeDeclarationVoid
  : L_Bracket InlineWhiteSpace* R_Bracket
  ;

// Jump instructions
jump
  : breakJump
  | returnJump
  ;
returnJump
  : ReturnKeyword InlineWhiteSpace* expression
  | ReturnKeyword
  ;
breakJump : BreakKeyword ;

// Control block
controlBlock
  : ifBlock
  | whileBlock
  ;
ifBlock
  : IfKeyword MultilineWhiteSpace* L_Par MultilineWhiteSpace* expression InlineWhiteSpace* R_Par MultilineWhiteSpace* block? (MultilineWhiteSpace* ElseKeyword MultilineWhiteSpace* (ifBlock|block))?
  ;
whileBlock
  : WhileKeyWord MultilineWhiteSpace* L_Par InlineWhiteSpace* expression InlineWhiteSpace* R_Par MultilineWhiteSpace* block?
  ;

// Blocks
block
  : L_CBracket MultilineWhiteSpace* statements? MultilineWhiteSpace* R_CBracket
  | L_CBracket MultilineWhiteSpace*
  ;

arrayBlock
  : L_CBracket MultilineWhiteSpace* R_CBracket
  | L_CBracket MultilineWhiteSpace* expression (MultilineWhiteSpace* Comma MultilineWhiteSpace* expression)* MultilineWhiteSpace* R_CBracket
  ;

// Function definition helpers
namedArguments
  : L_Par InlineWhiteSpace* R_Par
  | L_Par MultilineWhiteSpace* namedArgument (MultilineWhiteSpace* Comma MultilineWhiteSpace*  namedArgument)* MultilineWhiteSpace* R_Par
  ;
namedArgument
  : variableDeclaration
  | typeParameter
  ;

// Type & identifiers
typeParameter
  : Identifier ;
validIdentifier
  : Identifier ;

// Left & Right values
lvalue
  : validIdentifier arrayAccess?
  ;
atomicExpression // As right value
  : L_Par MultilineWhiteSpace* expression MultilineWhiteSpace* R_Par // '(' e ')'
  | validIdentifier
  | numberConstant
  | charConstant
  ;

assignment
  : lvalue InlineWhiteSpace* assignmentOperators InlineWhiteSpace* expression
  ;

assignmentOperators
  : Assignment
  | TimesAssign
  | DivAssign
  | ModAssign
  | PlusAssign
  | MinusAssign
  ;

expression : disjunction | assignment ;

disjunction :               conjunction                 (MultilineWhiteSpace* OrOp                      MultilineWhiteSpace* conjunction)*               ;
conjunction :               equalityComparison          (MultilineWhiteSpace* AndOp                     MultilineWhiteSpace* equalityComparison)*        ;
equalityComparison :        comparison                  (MultilineWhiteSpace* equalityOperator          MultilineWhiteSpace* comparison)*                ;
comparison :                additiveExpression          (MultilineWhiteSpace* comparativeOperator       MultilineWhiteSpace* additiveExpression)*        ;
additiveExpression :        multiplicativeExpression    (MultilineWhiteSpace* additiveOperator          MultilineWhiteSpace* multiplicativeExpression)*  ;
multiplicativeExpression :  prefixUnaryExpression       (MultilineWhiteSpace* multiplicativeOperator    MultilineWhiteSpace* prefixUnaryExpression)*     ;

prefixUnaryExpression :     prefixUnaryOperator* postfixUnaryExpression;
postfixUnaryExpression :    atomicExpression postfixUnaryOperation* ;

// Operators
multiplicativeOperator : ( Times | Div | Mod ) ;
additiveOperator : ( Plus | Minus ) ;
comparativeOperator : ( LowerThan | LowerEqThan | GreaterThan | GreaterEqThan ) ;
equalityOperator : ( EqualityOp | DiffOp ) ;
postfixUnaryOperator : ( IncOp | DecOp ) ;
prefixUnaryOperator : ( IncOp | DecOp | InvOp | cast InlineWhiteSpace* | NotOp ) ;

postfixUnaryOperation
  : callSufix
  | arrayAccess
  | postfixUnaryOperator
  ;

cast
  : L_Par InlineWhiteSpace* typeParameter InlineWhiteSpace* R_Par
  ;


callSufix
  : L_Par InlineWhiteSpace* R_Par
  | L_Par InlineWhiteSpace* expression (InlineWhiteSpace* Comma InlineWhiteSpace* expression )* InlineWhiteSpace* R_Par
  ;

arrayAccess
  : L_Bracket InlineWhiteSpace* expression InlineWhiteSpace* R_Bracket
  ;

// Constants
numberConstant
  : PositiveNumber
  | Minus PositiveNumber
  ;
positiveConstant : PositiveNumber;
charConstant
  : '\''.'\''
  | EscapedNL
  | EscapedCR
  | EscapedTB
  | EscapedSimpeQuote
  | EscapedDoubleQuote
  | EscapedAntibackslash
  ;

InstructionSeparator : Semilicon ;
PositiveNumber : FragmentNumber;
Identifier : FragmentIdentifier ;

// Do not delete the following comment line
// InjectedTokens
NewLine : '\\n' ;
FragmentNumber : Digit+;
Digit : ('0'|'1'|'2'|'3'|'4'|'5'|'6'|'7'|'8'|'9') ;
LowerCaseLetter : ('a'|'b'|'c'|'d'|'e'|'f'|'g'|'h'|'i'|'j'|'k'|'l'|'m'|'n'|'o'|'p'|'q'|'r'|'s'|'t'|'u'|'v'|'w'|'x'|'y'|'z') ;
UpperCaseLetter : ('A'|'B'|'C'|'D'|'E'|'F'|'G'|'H'|'I'|'J'|'K'|'L'|'M'|'N'|'O'|'P'|'Q'|'R'|'S'|'T'|'U'|'V'|'W'|'X'|'Y'|'Z') ;
Underscore : '_' ;
DigitSeparator : '.' ;
CarryReturn : '\\r' ;
Tab : '\\t' ;
InlineWhiteSpace : ( WS | Tab | CarryReturn );
MultilineWhiteSpace : ( InlineWhiteSpace | NewLine );
TimesAssign : '*=' ;
DivAssign : '/=' ;
ModAssign : '%=' ;
PlusAssign : '+=' ;
MinusAssign : '-=' ;
WS : ' ' ;
Plus : '+' ;
Minus : '-' ;
Times : '*' ;
Div : '/' ;
Mod : '%' ;
IncOp : '++' ;
DecOp : '--' ;
L_Par : '(' ;
R_Par : ')' ;
L_CBracket : '{' ;
R_CBracket : '}' ;
L_Bracket : '[' ;
R_Bracket : ']' ;
LowerThan : '<' ;
GreaterThan : '>' ;
LowerEqThan : '<=' ;
GreaterEqThan : '>=' ;
EqualityOp : '==' ;
RefEqualityOp : '===' ;
DiffOp : '!=' ;
Letter : ( LowerCaseLetter | UpperCaseLetter ) ;
FragmentIdentifier : ( Underscore? Letter AnyCharacter* ) ;
AnyCharacter : ( Underscore | Letter | Digit ) ;
Assignment : '=' ;
Comma : ',' ;
EscapedNL : '\'\\\\n\'';
EscapedCR : '\'\\\\r\'';
EscapedTB : '\'\\\\t\'';
EscapedSimpeQuote : '\'\\\\\'\'';
EscapedDoubleQuote : '\'\\\\"\'';
EscapedAntibackslash : '\'\\\\\\\\\'';
Semilicon : ';' ;
InvOp : '!' ;
AndOp : '&&' ;
OrOp : '||' ;
IfKeyword : 'if' ;
WhileKeyWord : 'while' ;
ElseKeyword : 'else' ;
SingleLineComment : '//' ~('\\n')+? NewLine+ ;
FragmentBlockComment : '/*' (.|'.')+? '*/' MultilineWhiteSpace+ ;
Macro : '#' (~('\\n')|'.')+? NewLine+ ;
ReturnKeyword : 'return' ;
BreakKeyword : 'break' ;
NotOp : ('~'|'!') ;
