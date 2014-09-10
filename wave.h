#ifndef __WAVE_H__
#define __WAVE_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
   unsigned long channels;
   unsigned long samplerate;
   unsigned long samplecount;
   unsigned long datalength;
   unsigned long rateratio;      // samplerate / 44100 * 0x10000
   unsigned long playptr;
   unsigned long playptr_frac;
   int                playloop;
   char                *wavdata;
   float volume;
   float pan;
} wavout_wavinfo_t;

int    wavInit();
int    wavPlay(wavout_wavinfo_t *wi); // returns slot number
int    wavPlay_VolPanPitch(wavout_wavinfo_t *wi, float volume, float pan, float pitch);


wavout_wavinfo_t *wavLoad(char *filename);
void wavoutStopPlay();
void adjustPitch(int slot, float pitch);	// 1.0 = normal pitch
											// between 0.0 and 1.0 = lowered pitch
											// >1.0 higher pitch	

void adjustVolume(int slot, float volume);	// 1.0 is normal volume, 0.0 silence
 
void adjustPan(int slot, float pan);		// -6dB Panning Law
											// 0.5 = center
											// 0.0 = max left
											// 1.0 = max right

#ifdef __cplusplus
}
#endif

#endif
