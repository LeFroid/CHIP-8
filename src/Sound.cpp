#include "Sound.h"

#include <iostream>
#include <cmath>
#include <cstdlib>

Sound::Sound() :
    m_duration(300),
    m_sampleRate(44100),
    m_frequency(256.87f) // C4
{
    generateSound();
    openAudio();
}

Sound::~Sound()
{
    SDL_CloseAudioDevice(m_audioDevID);
    free(m_samples);
}

void Sound::play()
{
    SDL_QueueAudio(m_audioDevID, m_samples, m_numSamples); 
    SDL_PauseAudioDevice(m_audioDevID, 0);
}

void Sound::generateSound()
{
    float numSamplesF = ((float) m_duration / 1000.0f) * m_sampleRate;
    m_numSamples = sizeof(uint16_t) * numSamplesF;
    m_samples = (uint16_t*) malloc(m_numSamples);

    double waveLength = (double)m_sampleRate / m_frequency;
    for (int i = 0; i < numSamplesF; ++i)
    {
        m_samples[i] = 32767 * sin(2.0 * M_PI * i / waveLength);
    }
}

void Sound::openAudio()
{
    SDL_AudioSpec desired;
    SDL_zero(desired);
    SDL_zero(m_wavSpec);

    desired.freq     = m_sampleRate;
    desired.format   = AUDIO_U16SYS;
    desired.channels = 2;
    desired.samples  = 2048; 
    desired.callback = NULL; 
    desired.userdata = NULL;


    m_audioDevID = SDL_OpenAudioDevice(NULL, 0, &desired, &m_wavSpec,
        SDL_AUDIO_ALLOW_FORMAT_CHANGE);
    if (!m_audioDevID)
        std::cout << "Cannot open audio device, error: " << SDL_GetError() << std::endl;

}

