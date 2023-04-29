#include <string>
#include "daisy_patch.h"
#include "daisysp.h"

#include "frequencyshifter.h"

using namespace daisy;
using namespace daisysp;

DaisyPatch hw;
FrequencyShifter fShifter; 

size_t n = 0;
float fine = 0.f;
float coarse = 0.f;

void AudioCallback(AudioHandle::InputBuffer in, AudioHandle::OutputBuffer out, size_t size)
{
	hw.ProcessAllControls();
    for (size_t i = 0; i < size; ++i) {
        out[0][i] = in[0][i];
    }
    fShifter.process(&out[0][0], &out[1][0], &in[1][0], &in[2][0], size); 
    
	for (size_t i = 0; i < size; i++)
	{
		out[2][i] = in[2][i];
		out[3][i] = in[3][i];
	}
}
void UpdateOled()
{
    hw.display.Fill(true);
	
	std::string str = "Shequency Frifter";
    hw.display.SetCursor(0, 0);
    char*       cstr = &str[0];
    hw.display.WriteString(cstr, Font_7x10, true);

    str = std::to_string(int(fine+coarse));
    hw.display.SetCursor(0, 30);
    hw.display.WriteString(cstr, Font_7x10, true);

    hw.display.Update();
}

void UpdateControls()
{
    hw.ProcessAnalogControls();

    //knobs
    float ctrlCoarse = hw.GetKnobValue((DaisyPatch::Ctrl)0);
    float ctrlFine = hw.GetKnobValue((DaisyPatch::Ctrl)1);
    coarse = powf(2.f,12.f*ctrlCoarse); //Hz
    fine = ctrlFine * 10;
    fShifter.frequency(coarse+fine);;
}

int main(void)
{
	hw.Init();

    fShifter.init(48000);
	hw.SetAudioBlockSize(16); // number of samples handled per callback
	hw.SetAudioSampleRate(SaiHandle::Config::SampleRate::SAI_48KHZ);
	hw.StartAdc();
	hw.StartAudio(AudioCallback);

	while(1) {		
        UpdateControls();
		UpdateOled();
	}
}
