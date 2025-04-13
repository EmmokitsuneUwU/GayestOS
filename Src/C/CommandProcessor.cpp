#include "CommandProcessor.hpp"
#include "VGA.hpp"
#include "Util.hpp"
#include "Colours.hpp"
#include "Disk.hpp"
#define MAX_ARGS 5

void parse_command(char *input, char *args[], int *argc) {
    *argc = 0;

    while (*input) {
        while (*input == ' ') input++;
        if (*input == '\0') break;

        args[(*argc)++] = input;

        while (*input && *input != ' ') input++;
        if (*input) *(input++) = '\0';

        if (*argc >= MAX_ARGS) break;
    }
}

void proccessCommand(char *args[MAX_ARGS],int argc = 0)
{
    if (StrCmp(args[0], "CLEAR")) 
    {
        strPrint("OK\n", colorBrightGreen);
        clearScreen();
    } 
    else if (StrCmp(args[0], "ECHO") && argc > 1) 
    {
        strPrint("OK\n", colorBrightGreen);
        for (int i = 1; i < argc; i++)
        {
            strPrint(args[i], colorYellow);
            strPrint(" ", colorYellow);
        }
        strPrint("\n", colorYellow);
    }
    else if(StrCmp(args[0],"OSFETCH"))
    {
        strPrint("Running: ",colorYellow);
        strPrint("GayestOS\n",colorBrightGreen);
        strPrint("Version: ",colorYellow);
        strPrint("0.0.6\n",colorBrightGreen);
    }
    else if(StrCmp(args[0],"DISKTEST") && argc > 2)
    {
        int sector = args[1][0] - 48;
        uint8_t testBuffer[512];
        strPrint("OK\n", colorBrightGreen);
        ataRead(sector, testBuffer);
        strPrint("Disk test completed. Data:\n", colorYellow);

        if(StrCmp(args[2], "ASCII"))
        {
            for(int i = 0; i < 512; i++)
            {
                charPrint(testBuffer[i], colorYellow);
                charPrint(' ', colorYellow);
            }
        }
        else if(StrCmp(args[2], "HEX"))
        {
            for(int i = 0; i < 512; i++)
            {
                hexPrint(testBuffer[i], colorYellow);
                charPrint(' ', colorYellow);
            }
        }
        else
        {
            strPrint("ERROR: Invalid format. Use 'ascii' or 'hex'.\n", colorRed);
        }
        strPrint("\n", colorYellow);
    }
    else if(StrCmp(args[0],"DISKTESTWRITE") && argc > 1)
    {
        int sector = args[1][0] - 48;
        uint8_t testBuffer[512];

        for(int i = 0; i < 512; i++)
        {
            testBuffer[i] = i +48;
        }

        strPrint("OK\n", colorBrightGreen);
        ataWrite(sector, testBuffer);
        strPrint("Disk test completed. Data:\n", colorYellow);
    }
    else if(StrCmp(args[0],"REBOOT"))
    {
        strPrint("OK\n", colorBrightGreen);
        reboot();
    }
    else if(StrCmp(args[0],"HALT"))
    {
        asm("hlt");
    }
    else
    {
        strPrint("ERROR\n", colorRed);
    }
}