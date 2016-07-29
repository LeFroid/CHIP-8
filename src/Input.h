#pragma once

#include <SDL.h>
#include <cstdint>

/// Keyboard input handler for the Chip-8 emulator
class Input
{
public:
    /// Default constructor
    Input();

    /// Polls for keyboard related events
    void pollForInput();

    /// Waits for a key press, returning the code for the key that has been pressed
    uint8_t waitForKeyPress();

    /// Returns true if the specified key is active, false if not
    bool isKeyActive(uint8_t code);

    /// Deactivates the given key
    void deactivate(uint8_t keycode);

private:
    /// The keys supported by chip-8
    uint8_t m_keys[16];
};
