
.PHONY: all clean

PROJECT_NAME       ?= game
RAYLIB_VERSION     ?= 5.0.0
RAYLIB_PATH        ?= ..\..

COMPILER_PATH      ?= C:/raylib/w64devkit/bin
PLATFORM           ?= PLATFORM_DESKTOP

RAYLIB_INSTALL_PATH ?= $(DESTDIR)/lib
RAYLIB_H_INSTALL_PATH ?= $(DESTDIR)/include

RAYLIB_LIBTYPE        ?= STATIC
BUILD_MODE            ?= RELEASE
USE_EXTERNAL_GLFW     ?= FALSE
USE_WAYLAND_DISPLAY   ?= FALSE

PLATFORM_OS=WINDOWS
export PATH := $(COMPILER_PATH):$(PATH)
RAYLIB_RELEASE_PATH 	?= $(RAYLIB_PATH)/src
EXAMPLE_RUNTIME_PATH   ?= $(RAYLIB_RELEASE_PATH)

CC = g++
MAKE = mingw32-make
CFLAGS += -Wall -std=c++14 -D_DEFAULT_SOURCE -Wno-missing-braces

ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -O0
else
    CFLAGS += -s -O1
endif

CFLAGS += $(RAYLIB_PATH)/src/raylib.rc.data
INCLUDE_PATHS = -I. -I$(RAYLIB_PATH)/src -I$(RAYLIB_PATH)/src/external
LDFLAGS = -L

ifneq ($(wildcard $(RAYLIB_RELEASE_PATH)/.*),)
    LDFLAGS += -L$(RAYLIB_RELEASE_PATH)
endif
ifneq ($(wildcard $(RAYLIB_PATH)/src/.*),)
    LDFLAGS += -L$(RAYLIB_PATH)/src
endif

LDLIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))

SRC_DIR = src
OBJ_DIR = obj

SRC = $(call rwildcard, *.c, *.h)
OBJS ?= main.c

MAKEFILE_PARAMS = $(PROJECT_NAME)
all:
	$(MAKE) $(MAKEFILE_PARAMS)

$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)
clean:
	del *.o *.exe /s
