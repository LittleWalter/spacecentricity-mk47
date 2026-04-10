#pragma once

#include QMK_KEYBOARD_H

// ─────────────────────────────────────────────────────────────
// Programming Macro Function Parameter Types
// ─────────────────────────────────────────────────────────────

// Common surround symbol pairs
typedef enum {
    SUR_PAREN,      // () parenthesis
    SUR_BRC,        // [] brackets
    SUR_CBR,        // {} curly braces
    SUR_VWS_CBR,    // {} curly braces w/ vertical whitespace
    SUR_ABR,        // <> angle brackets
    SUR_DQUO,       // "" double quotes
    SUR_QUOT,       // '' single quotes
    SUR_GRV,        // `` grave/backtick symbols
} surround_char_t;

// Common programming operators
typedef enum {
    OP_ASSIGN,      // `=`  Standard assigment operator
    OP_COLN_ASSIGN, // `:=` Go: declare & assign; Python: assign & eval (walrus operator)
    OP_COMP_ADD,    // `+=` Compound assignment: addition
    OP_COMP_SUB,    // `-=` Compound assignment: subtraction
    OP_COMP_MUL,    // `*=` Compound assignment: multiplication
    OP_COMP_DIV,    // `/=` Compound assignment: division
    OP_EQ,          // `==` Equality
    OP_NEQ,         // `!=` Inquality
    OP_LTE,         // `<=` Less than or equals
    OP_GTE,         // `>=` Greater than or equals
    OP_AND,         // `&&` Logical and
    OP_OR,          // `||` Logical or
    OP_INCREMENT,   // `++` increment
    OP_DECREMENT,   // `--` decrement
    OP_RIGHT_ARROW, // `->` Member access, mapping
    OP_LEFT_ARROW,  // `<-` Assignment, binding, Go: channel recieve
    OP_FAT_ARROW,   // `=>` Lambda, mapping, matching arm, association
    OP_TERNARY      // ` ? : ` Ternary operator, cursor placed at start
} operator_t;

// Various coding n-grams such as comments, etc.
typedef enum {
    CODE_COMMENT_INLINE,    // `// ` Inline comment
    CODE_COMMENT_MULTILINE, // `/*  */` multiline comment w/ cursor inside
    CODE_COMMENT_HTML,      // `<!--  -->`
    CODE_MARKDOWN_BLOCK,    // ```
    CODE_MARKDOWN_LINK,     // `[]()` Link w/ cursor inside brackets
    CODE_MARKDOWN_IMAGE     // `![]()`
} code_t;

// Common programming keywords
typedef enum {
    KW_IF,        // `if` conditional keyword
    KW_ELSE_IF,   // `else if` conditional keyword
    KW_ELIF,      // `elif` conditional keyword
    KW_ELSE,      // `else` conditional keyword
    KW_BREAK,     // `break` control-flow keyword
    KW_CONTINUE,  // `continue` control-flow keyword
    KW_TRUE,      // `true` Boolean keyword
    KW_FALSE,     // `false` Boolean keyword
    KW_FOR,       // `for` loop keyword
    KW_WHILE,     // `while` loop keyword
    KW_SWITCH,    // `switch` control-flow keyword
    KW_CASE,      // `case` switch label
    KW_DEFAULT,   // `default` switch label
    KW_RETURN,    // `return` exit keyword
    KW_NULL,      // `null` reference keyword
    KW_NULL_CAPS, // `NULL` reference keyword
    KW_NIL        // `nil` reference keyword
} keyword_t;

// ─────────────────────────────────────────────────────────────
// Programming Macro Function Declarations
// ─────────────────────────────────────────────────────────────

// Punctuation-comma bigrams
void punc_space_macro(const uint16_t punc_keycode);

// Programming language operators
void prog_operator_macro(const operator_t operator, const bool extra_space);

// Common surrounding characters: `()`, `[]`, `{}`, `<>`, double/single quotes, grave/backtick
// symbols
void surround_macro(const surround_char_t pair);

// Various coding n-grams such as C-style comments, Markdown Images/Links, etc.
void code_macro(const code_t ngram);

// Common keywords used by most programming languages
void keyword_macro(const keyword_t keyword, const bool with_space);
