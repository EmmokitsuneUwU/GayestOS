#include "VGA.hpp"
#include "Colours.hpp"

extern "C" int program()
{
    clearScreen();
    strPrint("Hello, World!\n", colorYellow);
    //strPrint("Neoa is super cute and beautiful\n", colorBrightGreen);
    //strPrint("<3\n", colorRed);
    return 0;
}
