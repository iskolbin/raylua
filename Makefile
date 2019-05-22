LUA    ?= 53
RAYLIB ?= 25
CC     ?= cc
CFLAGS ?= -O2
PLATFORM ?= PLATFORM_DESKTOP
EMSDK ?= '/emsdk'

ifeq ($(PLATFORM),PLATFORM_DESKTOP)
    ifeq ($(OS),Windows_NT)
        PLATFORM_OS = WINDOWS
    else
        UNAMEOS = $(shell uname)
        ifeq ($(UNAMEOS),Linux)
            PLATFORM_OS = LINUX
        endif
        ifeq ($(UNAMEOS),FreeBSD)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),OpenBSD)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),NetBSD)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),DragonFly)
            PLATFORM_OS = BSD
        endif
        ifeq ($(UNAMEOS),Darwin)
            PLATFORM_OS = OSX
        endif
    endif
endif
ifeq ($(PLATFORM),PLATFORM_RPI)
    UNAMEOS = $(shell uname)
    ifeq ($(UNAMEOS),Linux)
        PLATFORM_OS = LINUX
    endif
endif


STATIC_LUA=lua$(LUA)/src/liblua.a
STATIC_RAYLIB=raylib$(RAYLIB)/src/libraylib.a


ifeq ($(PLATFORM_OS),WINDOWS)
    LIBS = -static-libgcc -lopengl32 -lgdi32 -lwinmm
    LUAPLAT ?= mingw
endif
ifeq ($(PLATFORM_OS),OSX)
    LIBS = -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
    LUAPLAT ?= macosx
endif
ifeq ($(PLATFORM_OS),LINUX)
    LIBS = -lGL -lc -lm -lpthread -ldl -lrt
    LUAPLAT ?= linux
endif
ifeq ($(PLATFORM_OS),BSD)
    LIBS = -lGL -lpthread
    LUAPLAT ?= bsd
endif
ifeq ($(PLATFORM),PLATFORM_WEB)
    CC = emcc
    CFLAGS += -Os -s USE_GLFW=3 -s FORCE_FILESYSTEM=1 -s EMTERPRETIFY=1 -s EMTERPRETIFY_ASYNC=1 -Iraylib$(RAYLIB)/src/external/glfw/include --preload-file main.lua
    LUAPLAT ?= web
    STATIC_RAYLIB=raylib$(RAYLIB)/src/libraylib.bc
endif
ifeq ($(PLATFORM),PLATFORM_RPI)
    LIBS = -L/opt/vc/lib -lbrcmGLESv2 -lbrcmEGL -lpthread -lrt -lm -lbcm_host -ldl
endif

LUAPLAT ?= posix

all:
	pushd lua$(LUA)/src && $(MAKE) $(LUAPLAT) && popd && pushd raylib$(RAYLIB)/src && $(MAKE) && popd && $(CC) $(CFLAGS) -I./lua$(LUA)/src -I./raylib$(RAYLIB)/src main.c $(STATIC_LUA) $(STATIC_RAYLIB) $(LIBS)

clean:
	pushd lua$(LUA)/src && $(MAKE) clean && popd && pushd raylib$(RAYLIB)/src && $(MAKE) clean && popd
