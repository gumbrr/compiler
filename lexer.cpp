#include "Lexer.h" 
#include <cctype>      

Lexer::Lexer(const std::string& input): input(input), input_position(0), token_position{1, 1}{}

bool Lexer::is_finished(){
    return input_position >= input.length();
}

char Lexer::lookahead(){
    if (!is_finished()){
        return input[input_position];
    }
    else {
        return '\0';
    }
}

char Lexer::consume(){
    char c = input[input_position++];

    if (c == '\n'){
        token_position.row++;
        token_position.column = 1;
    }
    else {
        token_position.column++;
    }
    return c;
}

void Lexer::ignore_whitespace(){
    while(!is_finished() && isspace(lookahead()) ){
        consume();
    }
}

Token Lexer::match_token(){
    State current_state = State::start_state;
    std::string lexeme;
    Position start_position = token_position;

    while(!is_finished()){
        char current_char = lookahead();

        switch(current_state){

            case State::start_state:

                if (isspace(current_char)){
                    ignore_whitespace();
                }
                else if (isdigit(current_char)){
                    current_state = State::number_state;
                    lexeme += consume();
                }
                else if (isalpha(current_char)){
                    current_state = State::identifier_state;
                    lexeme += consume();
                }
                else if (current_char == '"'){
                    current_state = State::string_state;
                    consume();
                }
                else if(current_char == '+' ||current_char == '-' ||current_char == '/' ||current_char == '*' ||current_char == '=') {
                    //current_state = State::operator_state;
                    lexeme += consume();
                    return Token{Tokentype::operator_token, lexeme, start_position};//needs to be expanded
                }
                else {
                    lexeme += consume(); //still consume unkown char
                    return Token{Tokentype::unknown_token, lexeme, start_position}; //return unknown token
                }
                break;

            case State::number_state:

                if(isdigit(current_char)){
                    lexeme += consume();
                }
                else {
                    return Token{Tokentype::number_token, lexeme, start_position};
                }
                break;

            case State::string_state:

                if (current_char == '"') {
                    consume();
                    return Token{Tokentype::string_token, lexeme, start_position};
                } 
                else if (current_char == '\n' || is_finished()) {
                    return Token{Tokentype::unknown_token, lexeme, start_position};
                } 
                else {
                    lexeme += consume();
                }
                break;

            case State::identifier_state:

                if (isalnum(current_char) || current_char == '_') {
                    lexeme += consume();
                } 
                else {
                    return Token{Tokentype::identifier_token, lexeme, start_position};
                }
                break;

            //case State::operator_state:
        }
    }

//fallback
if (current_state == State::number_state){
    return Token{Tokentype::number_token, lexeme, start_position};
}
else if (current_state == State::string_state){
    return Token{Tokentype::unknown_token, lexeme, start_position};
}
else if (current_state == State::identifier_state){
    return Token{Tokentype::identifier_token, lexeme, start_position};
}

return Token{Tokentype::eof_token, "", start_position};

}

std::vector<Token> Lexer::tokenize(){
    std::vector<Token> tokens;
    while (true) { 
        Token token = match_token();
        tokens.push_back(token);
        if (token.lexical_unit == Tokentype::eof_token) break;
    }
    return tokens;
}

