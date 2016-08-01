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

#include "Graphics.h"
#include "Input.h"
#include "Sound.h"

#include <cstdint>
#include <atomic>
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
    std::atomic<uint8_t> m_DT;
    //uint8_t m_DT;

    /// Sound Timer
    std::atomic<uint8_t> m_ST;
    //uint8_t m_ST;

    /// Key state management system 
    Input m_input;

    /// Graphics system
    Graphics m_graphics;

    /// Sound system
    Sound m_sound;
};
