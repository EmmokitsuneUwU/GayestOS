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
    else if(StrCmp(args[0],"DISKREAD") && argc > 2)
    {
        int sector = args[1][0] - 48;
        uint8_t* testBuffer = (uint8_t*) simple_malloc(512);
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
        simple_free(testBuffer);
        strPrint("\n", colorYellow);
    }
    else if(StrCmp(args[0],"DISKWRITE") && argc > 1)
    {
        int sector = args[1][0] - 48;
        uint8_t* testBuffer = (uint8_t*) simple_malloc(512);

        for(int i = 0; i < 512; i++)
        {
            testBuffer[i] = i +48;
        }

        strPrint("OK\n", colorBrightGreen);
        ataWrite(sector, testBuffer);
        strPrint("Disk test completed.\n", colorYellow);
        simple_free(testBuffer);
    }
    else if(StrCmp(args[0],"REBOOT"))
    {
        strPrint("OK\n", colorBrightGreen);
        reboot();
    }
    else if (StrCmp(args[0], "TESTALLOC")) {
        void* ptr = simple_malloc(128);
        if (ptr) {
            strPrint("Memory allocator working.\n", colorBrightGreen);
            simple_free(ptr);
        } else {
            strPrint("The memory allocator failed.\n", colorRed);
        }
        simple_free(ptr);
    }
    else if(StrCmp(args[0],"HALT"))
    {
        __asm__ (
            "cli\n"
            "hlt\n"
        );
    }
    else if(StrCmp(args[0],"LOAD") && argc > 1)
    {
        #define LOAD_ADDR ((void*)0x1000)

        strPrint("Loading program from the selected sector... \n", colorYellow);
        
        int sector = args[1][0] - '0';
        uint8_t* ReadedBuffer = (uint8_t*) simple_malloc(512);
        
        strPrint("OK\n", colorBrightGreen);
        ataRead(sector, ReadedBuffer);
        
        strPrint("Program loaded. Executing...\n", colorYellow);
        clearScreen();
        
        cpyDatTBuffer((uint8_t*)LOAD_ADDR, (const char*)ReadedBuffer, 512);
        
        __asm__ volatile (
            "jmp *%0"
            :
            : "r"(LOAD_ADDR)
        );
        simple_free(ReadedBuffer);
    }
    else
    {
        strPrint("ERROR\n", colorRed);
    }
}