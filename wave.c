/**
 * WAV file handler for PSP
 * Original Author: ?
 */

#include <pspkernel.h>
#include <pspdebug.h>
#include <pspaudiolib.h>
#include <pspaudio.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "wave.h"

#define SND_MAXSLOT 16

wavout_wavinfo_t wavout_snd_wavinfo[SND_MAXSLOT];
int wavout_snd_playing[SND_MAXSLOT];

short   *samples;
unsigned long req;

static void wavout_snd_callback(void *_buf, unsigned int _reqn, void *pdata)
{
   int i,slot;
   wavout_wavinfo_t *wi;
   unsigned long ptr,frac;
   short *buf=_buf;

   samples = _buf;
   req = _reqn;

   for (slot=0; slot<SND_MAXSLOT; slot++)
   {
      pspDebugScreenSetXY(0,3+slot);
/*
       if (wavout_snd_playing[slot])
          printf("%02d active  ",slot);
       else
          printf("%02d inactive",slot);
*/
   }

   for (i=0; i<_reqn; i++)
   {
      int outr=0,outl=0;

      for (slot=0; slot<SND_MAXSLOT; slot++)
      {
         if (!wavout_snd_playing[slot]) continue;


         wi=&wavout_snd_wavinfo[slot];
         frac=wi->playptr_frac+wi->rateratio;
         wi->playptr=ptr=wi->playptr+(frac>>16);
         wi->playptr_frac=(frac&0xffff);

         if (ptr>=wi->samplecount)
         {
            if (wi->playloop)
            {
              wi->playptr=0;
              wi->playptr_frac=0;
              ptr = 0;
              }
              else
              {
                wavout_snd_playing[slot]=0;
                break;
                }
         }
         short *src=(short *)wi->wavdata;
         if (wi->channels==1)
         {
            outl+=(int)(src[ptr]*wi->volume*(1-wi->pan));
            outr+=(int)(src[ptr]*wi->volume*wi->pan);
         }
         else
         {
            outl+=(int)(src[ptr*2]*wi->volume*(1-wi->pan));
            outr+=(int)(src[ptr*2+1]*wi->volume*wi->pan);
         }
	  }
      if (outl<-32768)
         outl=-32768;
      else if (outl>32767)
         outl=32767;
      if (outr<-32768)
         outr=-32768;
      else if (outr>32767)
         outr=32767;

      *(buf++)=outl;
      *(buf++)=outr;
   }
}

void wavHalt(char *string,char *name)
{
   pspDebugScreenInit();
   pspDebugScreenSetBackColor(0x00FF0000);
   pspDebugScreenSetTextColor(0xFFFFFFFF);
   pspDebugScreenClear();
   //printf("I regret to inform you file %s\nfailed with error %s\n",name,string);
}

int wavInit()
{
   int i;
   pspAudioInit();
   pspAudioSetChannelCallback(0, wavout_snd_callback, 0);

   for (i=0; i<SND_MAXSLOT; i++)
   {
      wavout_snd_playing[i]=0;
   }
   return 0;
}


//stop all
void wavoutStopPlay()
{
   int i;
   for (i=0; i<SND_MAXSLOT; i++)
      wavout_snd_playing[i]=0;
}

//return slot number if success
int wavPlay(wavout_wavinfo_t *wi)
{
   int i;
   wavout_wavinfo_t *wid;
   for (i=0; i<SND_MAXSLOT; i++) if (wavout_snd_playing[i]==0) break;
   if (i==SND_MAXSLOT) return -1;
   wid=&wavout_snd_wavinfo[i];
   wid->channels=wi->channels;
   wid->samplerate=wi->samplerate;
   wid->samplecount=wi->samplecount;
   wid->datalength=wi->datalength;
   wid->wavdata=wi->wavdata;
   wid->rateratio=wi->rateratio;
   wid->playptr=0;
   wid->playptr_frac=0;
   wid->playloop=wi->playloop;
   wavout_snd_playing[i]=1;
   wid->volume = wi->volume;
   wid->pan = wi->pan;
   return i;
}

int wavPlay_VolPanPitch(wavout_wavinfo_t *wi, float volume, float pan, float pitch)
{
   int i;
   wavout_wavinfo_t *wid;
   for (i=0; i<SND_MAXSLOT; i++) if (wavout_snd_playing[i]==0) break;
   if (i==SND_MAXSLOT) return -1;
   wid=&wavout_snd_wavinfo[i];
   wid->channels=wi->channels;
   wid->samplerate=wi->samplerate;
   wid->samplecount=wi->samplecount;
   wid->datalength=wi->datalength;
   wid->wavdata=wi->wavdata;
   wid->rateratio=wi->rateratio;
   wid->playptr=0;
   wid->playptr_frac=0;
   wid->playloop=wi->playloop;
   adjustVolume(i, volume);
   adjustPitch(i, pitch);
   adjustPan(i, pan);
   wavout_snd_playing[i]=1;
   return i;
}

//return waveinfo * if success
wavout_wavinfo_t *wavLoad(char *filename) {
   unsigned int filelen;
   int fd;
   unsigned long channels;
   unsigned long samplerate;
   unsigned long blocksize;
   unsigned long bitpersample;
   unsigned long datalength;
   unsigned long samplecount;

   char          *wavfile;
   char         path_name[256];

   wavout_wavinfo_t *wi;

   SceIoStat stat;

   sprintf(path_name,"%s",filename);

   fd = sceIoOpen(filename, PSP_O_RDONLY, 0777);

   if (fd<0)
   {
      wavHalt("file failed",path_name);
      return NULL;
   }

   sceIoGetstat(path_name,&stat);

   //wi = malloc(stat.st_size + sizeof(wavout_wavinfo_t));
   //wavfile = (char*)(wi+sizeof(wavout_wavinfo_t));
   wi = malloc(stat.st_size + sizeof(wavout_wavinfo_t));
   wavfile = (char*)(wi)+sizeof(wavout_wavinfo_t);

   filelen = sceIoRead(fd, wavfile, stat.st_size);
   sceIoClose(fd);


   if (memcmp(wavfile,"RIFF",4)!=0)
   {
      wavHalt("format error not RIFF",path_name);
      free(wi);
      return NULL;
   }

   if (memcmp(wavfile+8,"WAVEfmt \x10\x00\x00\x00\x01\x00",14)!=0)
   {
      wavHalt("format error no WAVEfmt string",path_name);
      free(wi);
      return NULL;
   }

   channels=*(short *)(wavfile+0x16);
   samplerate=*(long *)(wavfile+0x18);
   blocksize=*(short *)(wavfile+0x20);
   bitpersample=*(short *)(wavfile+0x22);

   int i;
   for (i=0; memcmp(wavfile+0x24+i,"data",4)!=0; i++) { // searching for data chunk
	   if (i == 0xFF) {
	      wavHalt("no data chunk found",path_name);
	      free(wi);
      return NULL;
	   } // if
   } //for

   datalength=*(unsigned long *)(wavfile+0x28+i);

   if (datalength+0x2c>filelen)
   {
      wavHalt("buffer is supposed to be bigger than this",path_name);
      free(wi);
      return NULL;
   }

   if (channels!=2 && channels!=1)
   {
      wavHalt("not Mono or Stereo sample",path_name);
      free(wi);
      return NULL;
   }

   if (samplerate>100000 || samplerate<2000)
   {
      wavHalt("sample rate is wrong",path_name);
      free(wi);
      return NULL;
   }

   if (blocksize!=channels*2)
   {
      wavHalt("BLOCKSIZE MISMATCH",path_name);
      free(wi);
      return NULL;
}

   if (bitpersample!=16)
   {
      wavHalt("Bits Per Sample Error",path_name);
      free(wi);
      return NULL;
   }

   if (channels==2)
   {
      samplecount=datalength/4;
   }
   else
   {
      samplecount=datalength/2;
   }

   if (samplecount<=0)
   {
      wavHalt("no samples",path_name);
      free(wi);
      return NULL;
   }

   wi->channels=channels;
   wi->samplerate=samplerate;
   wi->samplecount=samplecount;
   wi->datalength=datalength;
   wi->wavdata=wavfile+0x2c+i;
   wi->rateratio=(samplerate*0x4000)/11025;
   wi->playptr=0;
   wi->playptr_frac=0;
   wi->playloop=0;
   wi->volume=1.0;
   wi->pan=0.5;

   return wi;
}

void adjustPitch(int slot, float pitch) {
	if (slot!=-1) {
		wavout_wavinfo_t *wi = &wavout_snd_wavinfo[slot];
		wi->rateratio=((wi->samplerate*0x4000)/11025)*pitch;
		if (wi->rateratio < ((2000*0x4000)/11025)) wi->rateratio = (2000*0x4000)/11025;
		else if (wi->rateratio > ((100000*0x4000)/11025)) wi->rateratio = (100000*0x4000)/11025;
	} // if
} // pitchshift

void adjustVolume(int slot, float volume) {
	if (slot!=-1) {
		wavout_wavinfo_t *wi = &wavout_snd_wavinfo[slot];
		if (volume < 0.0) volume = 0.0;
		wi->volume = volume*volume; //exponential
	} // if
} // adjustVolume

void adjustPan(int slot, float pan) {
	if (slot!=-1) {
		if (pan > 1.0) pan = 1.0;
		else if (pan < 0.0) pan = 0.0;
		wavout_wavinfo_t *wi = &wavout_snd_wavinfo[slot];
		if (pan <= 1.0 && pan >= 0.0) wi->pan = pan;
	} // if
} //adjustPan
