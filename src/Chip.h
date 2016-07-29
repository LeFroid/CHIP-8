#pragma once

#include "Graphics.h"
#include "Input.h"

#include <cstdint>
#include <string>

/// Interprets instructions in the Chip-8 language
class Chip
{
public:
    /// Chip-8 constructor
    Chip();

    /// Initializes the chip-8 interpreter
    void initialize();

    /// Loads the instruction set contained within the specified file (given the name & location) into memory
    bool load(std::string fileName);

    /// Emulates one full cycle of the chip-8 CPU
    void cycle();

    /// Decreases the delay and sound timers by one unit, if applicable
    void processTimers();

private:
    /// Chip-8 allocated memory
    uint8_t m_memory[4096];

    /// Chip-8 general purpose registers
    uint8_t m_V[16];

    /// Register index
    uint16_t m_I;

    /// Program Counter (currently executing address)
    uint16_t m_PC;

    /// Stack Pointer
    uint8_t m_SP;

    /// The stack
    uint16_t m_stack[16];

    /// Delay Timer
    uint8_t m_DT;

    /// Sound Timer
    uint8_t m_ST;

    /// Key state management system 
    Input m_input;

    /// Graphics system
    Graphics m_graphics;
};
