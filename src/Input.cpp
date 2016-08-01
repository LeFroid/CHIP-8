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

#include "Input.h"
#include <cstring>
#include <cstdlib>

Input::Input()
{
    memset(&m_keys[0], 0, 16);
}

void Input::pollForInput()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN)
        {
            // check if the key matters for the chip
            switch (event.key.keysym.sym)
            {
                case SDLK_1:
                    m_keys[0] = 1;
                    break;
                case SDLK_2:
                    m_keys[1] = 1;
                    break;
                case SDLK_3:
                    m_keys[2] = 1;
                    break;
                case SDLK_4:
                    m_keys[3] = 1;
                    break;
                case SDLK_q:
                    m_keys[4] = 1;
                    break;
                case SDLK_w:
                    m_keys[5] = 1;
                    break;
                case SDLK_e:
                    m_keys[6] = 1;
                    break;
                case SDLK_r:
                    m_keys[7] = 1;
                    break;
                case SDLK_a:
                    m_keys[8] = 1;
                    break;
                case SDLK_s:
                    m_keys[9] = 1;
                    break;
                case SDLK_d:
                    m_keys[10] = 1;
                    break;
                case SDLK_f:
                    m_keys[11] = 1;
                    break;
                case SDLK_z:
                    m_keys[12] = 1;
                    break;
                case SDLK_x:
                    m_keys[13] = 1;
                    break;
                case SDLK_c:
                    m_keys[14] = 1;
                    break;
                case SDLK_v:
                    m_keys[15] = 1;
                    break;
                // quit program key
                case SDLK_ESCAPE:
                    std::exit(0);
                    return;
            }
        }
        else if (event.type == SDL_KEYUP)
        {
            // check if relevant
            switch (event.key.keysym.sym)
            {
                case SDLK_1:
                    m_keys[0] = 0;
                    break;
                case SDLK_2:
                    m_keys[1] = 0;
                    break;
                case SDLK_3:
                    m_keys[2] = 0;
                    break;
                case SDLK_4:
                    m_keys[3] = 0;
                    break;
                case SDLK_q:
                    m_keys[4] = 0;
                    break;
                case SDLK_w:
                    m_keys[5] = 0;
                    break;
                case SDLK_e:
                    m_keys[6] = 0;
                    break;
                case SDLK_r:
                    m_keys[7] = 0;
                    break;
                case SDLK_a:
                    m_keys[8] = 0;
                    break;
                case SDLK_s:
                    m_keys[9] = 0;
                    break;
                case SDLK_d:
                    m_keys[10] = 0;
                    break;
                case SDLK_f:
                    m_keys[11] = 0;
                    break;
                case SDLK_z:
                    m_keys[12] = 0;
                    break;
                case SDLK_x:
                    m_keys[13] = 0;
                    break;
                case SDLK_c:
                    m_keys[14] = 0;
                    break;
                case SDLK_v:
                    m_keys[15] = 0;
                    break;
            }
        }
    }
}

uint8_t Input::waitForKeyPress()
{
    // Check if already applicable
    for (int i = 0; i < 16; ++i)
    {
        if (m_keys[i] == 1)
            return 1;
    }

    SDL_Event event;
    bool hasHadKeyPress = false;

    while (!hasHadKeyPress)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                // check if the key matters for the chip
                switch (event.key.keysym.sym)
                {
                    case SDLK_1:
                        return 0;
                    case SDLK_2:
                        return 1;
                    case SDLK_3:
                        return 2;
                    case SDLK_4:
                        return 3;
                    case SDLK_q:
                        return 4;
                    case SDLK_w:
                        return 5;
                    case SDLK_e:
                        return 6;
                    case SDLK_r:
                        return 7;
                    case SDLK_a:
                        return 8;
                    case SDLK_s:
                        return 9;
                    case SDLK_d:
                        return 10;
                    case SDLK_f:
                        return 11;
                    case SDLK_z:
                        return 12;
                    case SDLK_x:
                        return 13;
                    case SDLK_c:
                        return 14;
                    case SDLK_v:
                        return 15;
                    case SDLK_ESCAPE:
                        std::exit(0);
                }
            }
        }
    }
    return 0;
}

bool Input::isKeyActive(uint8_t code)
{
    if (code > 15)
        return false;
    
    return (m_keys[code] == 1);
}

void Input::deactivate(uint8_t keycode)
{
    if (keycode > 15)
        return;

    m_keys[keycode] = 0;
}

