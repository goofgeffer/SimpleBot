# Cross-platform Makefile for simplebot (Windows, Linux, macOS)
# Usage: make        (or mingw32-make on Windows)
#        make run    (compiles and runs SimpleBot)
#        make clean

CC     = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude
SRC    = $(wildcard src/*.c)

# Force Windows cmd.exe if we are on Windows
ifeq ($(OS),Windows_NT)
    SHELL = cmd.exe
.SHELLFLAGS = /c
endif

# ---------- Platform detection ----------
ifeq ($(OS),Windows_NT)
  TARGET  = simplebot.exe
  NULL    = NUL
  RM_F    = -del /q
  RUN_CMD = $(TARGET)
else
  TARGET  = simplebot
  NULL    = /dev/null
  RM_F    = -rm -f
  RUN_CMD = ./$(TARGET)
endif

# ---------- Optional icon (Windows only) ----------
EXTRA =
ifeq ($(OS),Windows_NT)
  ifneq ($(wildcard assets/simplebot.ico),)
    ifneq ($(shell windres --version 2>$(NULL)),)
      EXTRA = simplebot_res.o
    else
      $(warning windres not found, building without the icon)
    endif
  else
    $(info No simplebot.ico found, building without a custom icon)
  endif
endif

.PHONY: all run clean

all: $(TARGET)
	@echo Compiled OK: $(TARGET)

$(TARGET): $(SRC) $(EXTRA)
	$(CC) $(SRC) $(EXTRA) -o $@ $(CFLAGS)

# Compile and instantly launch SimpleBot (platform-safe execution)
run: all
	$(RUN_CMD)

# Icon resource: generate the .rc, compile it to a COFF object, remove the .rc
simplebot_res.o: assets/simplebot.ico
	$(file >simplebot.rc,1 ICON "assets/simplebot.ico")
	windres simplebot.rc -O coff -o $@
	$(RM_F) simplebot.rc

clean:
	$(RM_F) $(TARGET) simplebot_res.o simplebot.rc