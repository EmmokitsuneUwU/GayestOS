#include "VGA.hpp"
#include "Keyboard.hpp"
#include "Colours.hpp"
#include "Util.hpp"
#include "CommandProcessor.hpp"
#include "Disk.hpp"

#define MAX_ARGS 5

char commandsBuffer[75];
int commandsBufferIndex = 0;

bool isKeyPressed[256] = {false};

extern "C" void main(){
    clearScreen();
    strPrint("Welcome to the gayest Operating System \n",colorYellow);
    strPrint("/->",colorYellow);
    while (1)
    {
        uint8_t scancode = read_key_polling();

        if (scancode != 0) {
            bool isPressed = (scancode & 0x80) == 0;

            if (isPressed && !isKeyPressed[scancode]) {
                isKeyPressed[scancode] = true;
                
                char c = scancodeToIntChar(scancode);
                if (c != '?' && commandsBufferIndex < 74)
                {
                    commandsBuffer[commandsBufferIndex++] = c;
                    charPrint(c, colorYellow);
                }

                // If enter key is pressed, process the command.
                else if (scancode == 0x1C)
                {
                    charPrint('\n', colorYellow);
                    commandsBuffer[commandsBufferIndex] = '\0';

                    char *args[MAX_ARGS];
                    int argc = 0;
                    parse_command(commandsBuffer, args, &argc);

                    // arg 0 is the command itself.
                    if (argc > 0) 
                    {
                        proccessCommand(args, argc);

                        commandsBufferIndex = 0;
                        commandsBuffer[0] = '\0';
                        strPrint("/->",colorYellow);
                    }
            }
        }

        if (scancode != 0 && (scancode & 0x80)) {
            isKeyPressed[scancode & 0x7F] = false;
        }
    }
    }
}
