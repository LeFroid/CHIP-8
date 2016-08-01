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

/// Sound generator
class Sound
{
public:
    /// Sound constructor, generates the audio to be played on request
    Sound();

    /// Sound destructor
    ~Sound();

    /// Plays a preset sound
    void play();

private:
    /// Audio callback
    void callback(void *userdata, uint8_t *stream, int len);

    /// Generates the sound waves
    void generateSound();

    /// Open the audio device
    void openAudio();

private:
    /// Duration of the sound (ms)
    uint32_t m_duration;

    /// Samples per second
    uint32_t m_sampleRate;

    /// Music samples
    uint16_t *m_samples;

    /// Number of music samples
    size_t m_numSamples;

    /// Frequency of the repeated sound
    float m_frequency;

    /// SDL library audio spec
    SDL_AudioSpec m_wavSpec;

    /// SDL audio device ID
    SDL_AudioDeviceID m_audioDevID;
};

