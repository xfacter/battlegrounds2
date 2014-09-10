TARGET = Battlegrounds3D
OBJS = xgraphics.o xdraw.o xvertex.o xtext.o xtexture.o xparticle.o xastar.o xlib.o xmath.o wave.o xconsole.o main.o

CFLAGS = -O2 -G0 -Wall -D LOAD_TGA
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LIBS = -lpspgum_vfpu -lpspvfpu -lpspgu -lpspvram -lm -lpspaudiolib -lpspaudio -lpsppower -lpsprtc -lpspmath -lstdc++
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Battlegrounds3D
PSP_EBOOT_ICON = ICON0.PNG
#PSP_EBOOT_PIC1 = PIC1.PNG

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

xgraphics.o: xgraphics.c xgraphics.h

xdraw.o: xdraw.cpp xdraw.h

xvertex.o: xvertex.c xvertex.h

xtext.o: xtext.cpp xtext.h

xtexture.o: xtexture.cpp xtexture.h

xparticle.o: xparticle.cpp xparticle.h

xastar.o: xastar.cpp xastar.h

xlib.o: xlib.cpp xlib.h

xmath.o: xmath.c xmath.h

wave.o: wave.c wave.h

xconsole.o: xconsole.cpp xconsole.h

main.o: main.cpp main.h models.h xtexture.o xparticle.o xastar.o xlib.o wave.o

EBOOT.PBP: main.o
