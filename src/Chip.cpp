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

#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <thread>

const uint8_t FontSet[80] =
{
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};

Chip::Chip() : 
    m_I(0),
    m_PC(512),
    m_SP(0),
    m_DT(0),
    m_ST(0),
    m_input(),
    m_graphics(),
    m_sound()
{
    srand(time(NULL));
}

void Chip::initialize()
{
    memset(&m_memory[0], 0, 4096);
    memset(&m_V[0], 0, 16);
    memset(&m_stack[0], 0, 16);

    // Load font data
    for (int i = 0; i < 80; ++i)
        m_memory[i] = FontSet[i];
}

bool Chip::load(std::string fileName)
{
    std::ifstream f;
    f.open(fileName, std::ifstream::in | std::ifstream::binary);

    if (!f.is_open())
        return false;

    // Load data into memory beginning at address 512
    int idx = 512;
    
    uint8_t tmp = (uint8_t) f.get();

    while (f.good() && idx < 4096)
    {
        m_memory[idx++] = tmp;
        tmp = (uint8_t) f.get();
    }

    f.close();

    m_PC = 512;
    m_graphics.createWindow(64, 32, 4);

    return true;
}

void Chip::cycle()
{
    // Fetch opcode (16 bits)
    uint16_t opcode = (m_memory[m_PC] << 8) | m_memory[m_PC + 1];

    // Handle opcode
    switch (opcode & 0xF000)
    {
        // Jump to address
        case 0x1000:
            m_PC = opcode & 0x0FFF;
            break;
        // Call subroutine
        case 0x2000:
            m_stack[m_SP++] = m_PC;
            m_PC = opcode & 0x0FFF;
            break;
        // Skip next instruction if Vx = kk
        case 0x3000:
        {
            uint8_t x = ((opcode & 0x0F00) >> 8);
            if (m_V[x] == (opcode & 0x00FF))
                m_PC += 4;
            else
                m_PC += 2;
            break;
        }
        // Skip next instruction if Vx != kk
        case 0x4000:
        {
            uint8_t x = ((opcode & 0x0F00) >> 8);
            if (m_V[x] != (opcode & 0x00FF))
                m_PC += 4;
            else
                m_PC += 2;
            break;
        }
        // Skip next instruction if Vx = Vy
        case 0x5000:
        {
            uint8_t x = ((opcode & 0x0F00) >> 8);
            uint8_t y = ((opcode & 0x00F0) >> 4);
            if (m_V[x] == m_V[y])
                m_PC += 4;
            else
                m_PC += 2;
            break;
        }
        // Set Vx = kk
        case 0x6000:
        {
            uint8_t x = ((opcode & 0x0F00) >> 8);
            m_V[x] = opcode & 0x00FF;
            m_PC += 2;
            break;
        }
        // Set Vx = Vx + kk
        case 0x7000:
        {
            uint8_t x = ((opcode & 0x0F00) >> 8);
            m_V[x] += opcode & 0x00FF;
            m_PC += 2;
            break;
        }
        // Set Vx to ...  **depends on z in 8xyz**
        case 0x8000:
        {
            uint8_t x = ((opcode & 0x0F00) >> 8);
            uint8_t y = ((opcode & 0x00F0) >> 4);

            switch (opcode & 0x000F)
            {
                case 0x0000:
                    m_V[x] = m_V[y];
                    break;
                case 0x0001:
                    m_V[x] |= m_V[y];
                    break;
                case 0x0002:
                    m_V[x] &= m_V[y];
                    break;
                case 0x0003:
                    m_V[x] ^= m_V[y];
                    break;
                case 0x0004:
                {
                    m_V[15] = (m_V[x] + m_V[y] > 0xFF) ? 1 : 0;
                    m_V[x] += m_V[y]; 
                    break;
                }
                case 0x0005:
                    m_V[15] = (m_V[x] > m_V[y]) ? 1 : 0;
                    m_V[x] -= m_V[y];
                    break;
                case 0x0006:
                    m_V[15] = (m_V[x] & 0x1);
                    m_V[x] >>= 1;
                    break;
                case 0x0007:
                    m_V[15] = (m_V[y] > m_V[x]) ? 1 : 0;
                    m_V[x] = m_V[y] - m_V[x];
                    break;
                case 0x000E:
                    m_V[15] = (m_V[x] & 0x8) ? 1 : 0;
                    m_V[x] <<= 1;
                    break;
            }
            m_PC += 2;
            break;
        }
        // Skip next instruction if Vx != Vy
        case 0x9000:
            if (m_V[((opcode & 0x0F00) >> 8)] != m_V[((opcode & 0x00F0) >> 4)])
                m_PC += 2;
            m_PC += 2;
            break;
        // Set I = nnn
        case 0xA000:
            m_I = opcode & 0x0FFF;
            m_PC += 2;
            break;
        // Jump to location nnn + V0
        case 0xB000:
            m_PC = m_V[0] + (opcode & 0x0FFF);
            break;
        // Set Vx = random byte AND kk
        case 0xC000:
            m_V[((opcode & 0x0F00) >> 8)] = (rand() % 256) & (opcode & 0x00FF);
            m_PC += 2;
            break;
        // Display n-byte sprite at memory location I at (Vx, Vy), set VF = collision
        case 0xD000:
            m_V[15] = m_graphics.drawSprite(
                    m_V[((opcode & 0x0F00) >> 8)], m_V[((opcode & 0x00F0) >> 4)],
                    (opcode & 0x000F), &m_memory[m_I]);
            m_PC += 2;
            break;
        // Skip next instruction if ... (depends on last nibble in opcode)
        case 0xE000:
            switch (opcode & 0x00FF)
            {
                case 0x009E:
                    // skip next instruction if key w/ value of m_V[x] IS pressed
                    if (m_input.isKeyActive(m_V[((opcode & 0x0F00) >> 8)]))
                    {
                        m_input.deactivate(m_V[((opcode & 0x0F00) >> 8)]);
                        m_PC += 2;
                    }
                    break;
                case 0x00A1:
                    // skip if key with value of m_V[x] NOT pressed
                    if (!m_input.isKeyActive(m_V[((opcode & 0x0F00) >> 8)]))
                        m_PC += 2;
                    break;
            }
            m_PC += 2;
            break;
        // Conditional (depends on final two nibbles)
        case 0xF000:
        {
            uint8_t x = (opcode & 0x0F00) >> 8;
            switch (opcode & 0x00FF)
            {
                // set Vx := delay timer value
                case 0x0007:
                    m_V[x] = m_DT;
                    break;
                // Wait for key press, set Vx to value
                case 0x000A:
                    m_V[x] = m_input.waitForKeyPress();
                    m_input.deactivate(m_V[x]);
                    break;
                // Set delay timer := Vx
                case 0x0015:
                    m_DT = m_V[x];
                    break;
                // Set sound timer := Vx
                case 0x0018:
                    m_ST = m_V[x];
                    break;
                // Set I := I + Vx
                case 0x001E:
                    m_I += m_V[x];
                    break;
                // Set I = location in memory of sprite corresponding to the digit at register Vx
                case 0x0029:
                    m_I = m_V[x] * 5;
                    break;
                // Store BCD representation of Vx in memory locations I, I+1, & I+2
                case 0x0033:
                    m_memory[m_I]     = m_V[x] / 100;
                    m_memory[m_I + 1] = (m_V[x] / 10) % 10;
                    m_memory[m_I + 2] = (m_V[x] % 100) % 10;
                    break;
                // Store registers V0 through Vx in memory beginning with location I
                case 0x0055:
                    for (uint8_t i = 0; i <= x; ++i)
                        m_memory[m_I + i] = m_V[i];
                    break;
                // Store memory values beginning with location I into registers V0 through Vx
                case 0x0065:
                    for (uint8_t i = 0; i <= x; ++i)
                        m_V[i] = m_memory[m_I + i];
                    break;
            }
            m_PC += 2;
            break;
        }
        default:
            switch (opcode & 0x00FF)
            {
                // Clear the Display
                case 0x00E0:
                    m_graphics.clearScreen();
                    m_PC += 2;
                    break;
                // Return from a subroutine
                case 0x00EE:
                    m_PC = m_stack[--m_SP] + 2;
                    break;
                // Call RCA 1802 program
                default:
                    m_PC += 2;
                    break;
            }
    }

    // Check for keyboard input
    m_input.pollForInput();
}

void Chip::processTimers()
{
    // Delay Timer
    if (m_DT)
        --m_DT;

    // Sound Timer
    if (m_ST)
    {
        if (m_ST == 1)
        {
            // Make a beep / noise
            m_sound.play();
        }
        --m_ST;
    }
}

