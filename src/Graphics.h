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

