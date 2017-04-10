### PROJECT SETTINGS ###
BIN_NAME = bg2
PBP_PATH = Bundle
RES_PATH = Assets
SRC_PATH = .
BIN_PATH = bin
BUILD_PATH = build

# Basic configuration for PSPSDK. Refer to $(PSPSDK)/lib/build.mak
PSP_EBOOT_TITLE = Battlegrounds2
PSP_EBOOT_ICON = $(PBP_PATH)/ICON0.png
#PSP_EBOOT_ICON1 = $(PBP_PATH)/icon1.pmf
#PSP_EBOOT_UNKPNG = $(PBP_PATH)/pic0.png
#PSP_EBOOT_PIC1 = $(PBP_PATH)/pic1.png
#PSP_EBOOT_SND0 = $(PBP_PATH)/snd0.at3
#PSP_EBOOT_PSAR = $(PBP_PATH)/data.psar
PSP_EBOOT_SFO = $(BUILD_PATH)/PARAM.SFO
PSP_EBOOT = $(BIN_PATH)/EBOOT.PBP
EXTRA_TARGETS = $(PSP_EBOOT)
TARGET = $(BUILD_PATH)/$(BIN_NAME)
#BUILD_PRX = 1

OBJS = main.o xgraphics.o xdraw.o xvertex.o xtext.o xtexture.o xparticle.o \
	xastar.o xlib.o xmath.o xconsole.o wave.o
OBJS := $(addprefix $(BUILD_PATH)/,$(OBJS))

CFLAGS = -O2 -g -Wall -D LOAD_TGA
CXXFLAGS = -fno-exceptions -fno-rtti

INCDIR = $(SRC_PATH)
LIBDIR =
LIBS = -lpspgum_vfpu -lpspvfpu -lpspgu -lpspvram -lm -lpspaudiolib -lpspaudio \
	-lpsppower -lpsprtc -lpspmath -lstdc++
LDFLAGS =
### END PROJECT SETTINGS ###

# Generally should not need to edit below this line

DEPS = $(OBJS:.o=.d)

.PHONY: all
all: dirs deploy

.PHONY: dirs
dirs:
	@echo "Creating directories ..."
	mkdir -p $(sort $(dir $(OBJS))) $(BIN_PATH)

.PHONY: deploy
deploy:
	rsync -a README.txt $(RES_PATH)/ $(BIN_PATH)

.PHONY: clean_all
clean_all:
	$(RM) $(DEPS) $(BIN_PATH)/xlog.txt
	$(RM) -r bin build

.PHONY: clean
clean: clean_all

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

-include $(DEPS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -MP -MMD -c $(CFLAGS) -o $@ $<

$(BUILD_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(CXX) -MP -MMD -c $(CXXFLAGS) -o $@ $<
