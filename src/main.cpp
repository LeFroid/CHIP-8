#include "Chip.h"

#include <SDL.h>
#include <iostream>

const uint32_t CyclesPerSecond = 500;

int main()
{
    Chip chip;

    std::string fileName;
    
    std::cout << "Program file name: ";
    std::cin >> fileName;

    chip.initialize();

    if (!chip.load(fileName))
    {
        std::cout << "Error opening file! Aborting..." << std::endl;
        return 0;
    }

    uint32_t startTime, delta;

    while (true)
    {
        startTime = SDL_GetTicks();

        chip.cycle();
        chip.processTimers();

        delta = SDL_GetTicks() - startTime;
        if (delta < 1000 / CyclesPerSecond)
            SDL_Delay((1000 / CyclesPerSecond) - delta);
    }

    return 0;
}
