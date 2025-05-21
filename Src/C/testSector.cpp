#include "VGA.hpp"
#include "Colours.hpp"

extern "C" int program()
{
    clearScreen();
    charPrint('k', colorBrightGreen);
    return 0;
}
