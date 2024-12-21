FUNCTION scanner(sourceCode):
    DECLARE tokens AS EMPTY LIST
    DECLARE currentChar AS EMPTY
    DECLARE currentToken AS EMPTY
    DECLARE position AS 0
    
    WHILE position < LENGTH(sourceCode):
        currentChar = sourceCode[position]
        
        // Skip whitespace
        IF isWhitespace(currentChar):
            position += 1
            CONTINUE
        
        // Handle identifiers and keywords
        IF isAlphabet(currentChar):
            currentToken = ""
            WHILE position < LENGTH(sourceCode) AND (isAlphabet(sourceCode[position]) OR isDigit(sourceCode[position])):
                currentToken += sourceCode[position]
                position += 1
            IF isKeyword(currentToken):
                tokens.APPEND({type: "KEYWORD", value: currentToken})
            ELSE:
                tokens.APPEND({type: "IDENTIFIER", value: currentToken})
            CONTINUE
        
        // Handle numbers
        IF isDigit(currentChar):
            currentToken = ""
            WHILE position < LENGTH(sourceCode) AND isDigit(sourceCode[position]):
                currentToken += sourceCode[position]
                position += 1
            tokens.APPEND({type: "NUMBER", value: currentToken})
            CONTINUE
        
        // Handle strings
        IF currentChar == '"':
            currentToken = ""
            position += 1 // Skip the opening quote
            WHILE position < LENGTH(sourceCode) AND sourceCode[position] != '"':
                currentToken += sourceCode[position]
                position += 1
            position += 1 // Skip the closing quote
            tokens.APPEND({type: "STRING", value: currentToken})
            CONTINUE
        
        // Handle operators and punctuation
        IF isOperator(currentChar):
            tokens.APPEND({type: "OPERATOR", value: currentChar})
            position += 1
            CONTINUE
        
        IF isPunctuation(currentChar):
            tokens.APPEND({type: "PUNCTUATION", value: currentChar})
            position += 1
            CONTINUE
        
        // Handle unrecognized characters
        THROW ERROR("Unrecognized character: " + currentChar)
    
    RETURN tokens

// Helper functions
FUNCTION isWhitespace(char):
    RETURN char IN [' ', '\t', '\n', '\r']

FUNCTION isAlphabet(char):
    RETURN char IN ['a'..'z', 'A'..'Z']

FUNCTION isDigit(char):
    RETURN char IN ['0'..'9']

FUNCTION isKeyword(token):
    RETURN token IN ["if", "else", "while", "for", "return", ...] // List of keywords

FUNCTION isOperator(char):
    RETURN char IN ['+', '-', '*', '/', '=', '<', '>', ...]

FUNCTION isPunctuation(char):
    RETURN char IN [';', ',', '(', ')', '{', '}', '[', ']', ...]
