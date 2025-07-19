#include "debug.h"

int main() {
    Debug::print_tokens("");
    Debug::print_tokens("@");     
    Debug::print_tokens("12345");
    Debug::print_tokens("var_name");
    Debug::print_tokens("+ - * / =");
    Debug::print_tokens("\"Hello, World!\"");    
    return 0;
}
