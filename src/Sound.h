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
