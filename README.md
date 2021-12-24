# USB DFU

A bootloader for AVR microcontrollers with USB hardware.

## New Board

### [`Board/Board.h`](Board/Board.h)

## Development Environment Setup

### Linux

```bash
apt install -y gcc-avr avr-libc
```

### Windows

These Makefiles expect a bunch of standard linux tools to be available.
They normally aren't on Windows.

#### Manual Method

Zak publishes recent [AVR-GCC builds](https://blog.zakkemble.net/avr-gcc-builds/). These include `avrdude` and `make`, which are quite handy.

But other tools need to be installed and available on the PATH as well...
For that, we recommend the use of Cygwin.

##### Needed tools on path

- `printf` provided by `coreutils` package
- `grep`
- `hostname` Windows's works
