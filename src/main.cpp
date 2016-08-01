/*
 * Copyright (c) 2016, Timothy Vaccarelli
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#include "Chip.h"

#include <SDL.h>
#include <cstdlib>
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>

Chip chip;
const uint32_t CyclesPerSecond = 500;
const uint32_t TimerCallsPerSecond = 60;

std::atomic_bool running;

/// Sets running to false, calls SDL_Quit on program termination
void exitHandler()
{
    running.exchange(false);
    SDL_Quit();
}

/// Calls the chip-8 timer decrement method at a rate of 60 HZ
void timerCallback()
{
    uint32_t startTime, delta;

    while (running.load())
    {
        startTime = SDL_GetTicks();

        chip.processTimers();

        delta = SDL_GetTicks() - startTime;
        if (delta < 1000 / TimerCallsPerSecond)
            std::this_thread::sleep_for(std::chrono::milliseconds((1000 / TimerCallsPerSecond) - delta));
    }
}

int main()
{
    std::atexit(exitHandler);

    std::string fileName;
    
    std::cout << "Program file name: ";
    std::cin >> fileName;

    chip.initialize();

    if (!chip.load(fileName))
    {
        std::cout << "Error opening file! Aborting..." << std::endl;
        return 0;
    }
    running.exchange(true);

    std::thread timer(timerCallback);
    timer.detach();

    uint32_t startTime, delta;

    while (running.load())
    {
        startTime = SDL_GetTicks();

        chip.cycle();

        delta = SDL_GetTicks() - startTime;
        if (delta < 1000 / CyclesPerSecond)
            SDL_Delay((1000 / CyclesPerSecond) - delta);
    }

    return 0;
}



