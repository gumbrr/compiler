#include "debug.h"

int main() {
    Debug::print_tokens("x = 42 + 8 >= 5 != (foo_123) \"hello\" # \"unterminated");
    return 0;
}
