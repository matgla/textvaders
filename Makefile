CC ?= armv8m-tcc
CFLAGS = -fPIE -fpie -g -mcpu=cortex-m33 -fvisibility=hidden -I../../rootfs/usr/include
LDFLAGS = -fpie -fPIE -fvisibility=hidden -g -L../../rootfs/lib -Wl,-Ttext=0x0 -Wl,-section-alignment=0x4 -lncurses 
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, build/%.o, $(SRCS))

TARGET = build/textvaders

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
INCLUDEDIR ?= $(PREFIX)/include

# Rules
all: $(TARGET) $(TARGET).elf

build/%.o: %.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -Wl,-oformat=yaff $^ -o $@

$(TARGET).elf: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

install: $(TARGET) 
	mkdir -p $(BINDIR)
	cp $(TARGET) $(BINDIR)

clean:
	rm -rf build