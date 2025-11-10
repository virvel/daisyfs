#include "daisy_seed.h"

#include "../virveldsp/include/virveldsp/frequencyshifter.h"

daisy::DaisySeed hw;
FrequencyShifter fShifter;

size_t n = 0;
float fine = 0.f;
float coarse = 0.f;

void AudioCallback(daisy::AudioHandle::InputBuffer in, daisy::AudioHandle::OutputBuffer out, size_t size) {
	for (size_t i = 0; i < size; ++i) {
		out[0][i] = in[0][i];
	}
	fShifter.process(&out[0][0], &out[1][0], &in[1][0], &in[2][0], size);

	for (size_t i = 0; i < size; i++) {
		out[2][i] = in[2][i];
		out[3][i] = in[3][i];
	}
}

float inc = 0.001f;
float ph = 0.01;

void UpdateControls() {
	// hw.ProcessAnalogControls();
	//
	// //knobs
	// float ctrlCoarse = hw.GetKnobValue((DaisyPatch::Ctrl)0);
	// float ctrlFine = hw.GetKnobValue((DaisyPatch::Ctrl)1);
}

int main(void) {
	hw.Init();

	fShifter.init(48000);
	hw.SetAudioBlockSize(16); // number of samples handled per callback
	hw.SetAudioSampleRate(daisy::SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAudio(AudioCallback);

	while (1) {
		UpdateControls();
	}
}
