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

#include "Graphics.h"

#include <cstring>

Graphics::Graphics() :
    m_window(nullptr),
    m_renderer(nullptr)
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    memset(&m_pixels[0], 0, 2048);
}

Graphics::~Graphics()
{
    if (m_renderer)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
    
    if (m_window)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}

void Graphics::createWindow(int width, int height, int scale)
{
    m_scale = scale;

    SDL_CreateWindowAndRenderer(width * scale, height * scale, SDL_WINDOW_SHOWN,
        &m_window, &m_renderer);
}

bool Graphics::drawSprite(uint16_t x, uint16_t y, uint16_t height, uint8_t *memory)
{
    bool retVal = false;

    for (uint16_t i = 0; i < height; ++i, ++memory)
    {
        uint16_t vert = y + i;

        uint8_t row = *memory;

        for (uint16_t j = 0; j < 8; ++j)
        {
            if ( (row >> (7 - j)) & 0x01 )
            {
                uint16_t horiz = x + j;

                int arrayPos = (vert * 64) + horiz;
                if (arrayPos > 64 * 32)
                    continue;

                if (m_pixels[arrayPos])
                    retVal = true;

                // update pixel state
                m_pixels[arrayPos] ^= 1;
            }
        }
    }

    redraw();

    return retVal;
}

void Graphics::clearScreen()
{
    memset(&m_pixels[0], 0, 2048);
    redraw();
}

void Graphics::redraw()
{
    // Default to black
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);

    int idx = 0;
    for (int y = 0; y < 32 * m_scale; y += m_scale)
    {
        for (int x = 0; x < 64 * m_scale; x += m_scale)
        {
            bool gfxValue = (m_pixels[idx++]);

            if (gfxValue)
                SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

            // draw scaled pixels
            if (m_scale > 1)
            {
                SDL_Rect scaledRect = { x, y, m_scale, m_scale };
                SDL_RenderFillRect(m_renderer, &scaledRect);
            }
            else
                SDL_RenderDrawPoint(m_renderer, x, y);
            
            if (gfxValue)
                SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        }
    }

    SDL_RenderPresent(m_renderer);
}


