# Cross-platform Makefile for simplebot (Windows, Linux, macOS)
# Usage: make   (or mingw32-make on Windows)
#        make clean

CC     = gcc
CFLAGS = -Wall -Wextra -O2
SRC    = main.c

# ---------- Platform detection ----------
ifeq ($(OS),Windows_NT)
  TARGET = simplebot.exe
  ifneq (,$(findstring cmd,$(notdir $(SHELL))))
    # Plain Windows cmd.exe (e.g. mingw32-make without MSYS)
    NULL  = NUL
    RM_F  = -del /q
  else
    # MSYS2 / Git Bash / Cygwin on Windows
    NULL  = /dev/null
    RM_F  = -rm -f
  endif
else
  TARGET = simplebot
  NULL   = /dev/null
  RM_F   = -rm -f
endif

# ---------- Optional icon (Windows only) ----------
EXTRA =
ifeq ($(OS),Windows_NT)
  ifneq ($(wildcard simplebot.ico),)
    ifneq ($(shell windres --version 2>$(NULL)),)
      EXTRA = simplebot_res.o
    else
      $(warning windres not found, building without the icon)
    endif
  else
    $(info No simplebot.ico found, building without a custom icon)
  endif
endif

.PHONY: all clean

all: $(TARGET)
	@echo Compiled OK: $(TARGET)

$(TARGET): $(SRC) $(EXTRA)
	$(CC) $(SRC) $(EXTRA) -o $@ $(CFLAGS)

# Icon resource: generate the .rc, compile it to a COFF object, remove the .rc
simplebot_res.o: simplebot.ico
	$(file >simplebot.rc,1 ICON "simplebot.ico")
	windres simplebot.rc -O coff -o $@
	$(RM_F) simplebot.rc

clean:
	$(RM_F) $(TARGET) simplebot_res.o simplebot.rc