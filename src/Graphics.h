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

#pragma once

#include <SDL.h>
#include <cstdint>

/// Handles the graphical backend of the CHIP-8 system
class Graphics
{
public:
    /// Graphics constructor, which initializes the SDL library
    Graphics();

    /// Graphics destructor, cleans up the SDL systems which were being used
    ~Graphics();

    /// No copying
    Graphics(const Graphics&) = delete;

    /// No assignment
    Graphics& operator=(const Graphics&) = delete;

    /// Creates the window which will be used by the graphics system
    void createWindow(int width, int height, int scale = 1);

    /**
     * Draws a sprite at (Vx, Vy) with width of 8px and the
     * specified height (from 1 to 15px). Sprite represents
     * the value of the memory which the final parameter should
     * point to
     * @return The value to store in VF (carry flag): true if a pixel was unset, false if else.
     */
    bool drawSprite(uint16_t x, uint16_t y, uint16_t height, uint8_t *memory);

    /// Clears and redraws the screen
    void clearScreen();

    /// Redraws / renders the screen again, representing the boolean data in m_pixels
    void redraw();

private:
    /// The window created by the SDL library
    SDL_Window *m_window;

    /// The renderer used to draw / modify pixels on the window
    SDL_Renderer *m_renderer;

    /// Array of pixel states on the virtual screen (1 or 0)
    uint8_t m_pixels[2048];

    /// Scale of the actual screen vs the virtual one
    int m_scale;
};

