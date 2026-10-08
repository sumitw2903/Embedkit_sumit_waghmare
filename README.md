# EmbedKit_SumitWaghmare

Name: Sumit Tanaji Waghmare

## Modules

### Ring Buffer (ringbuf.c)
Implementation of an 8-byte FIFO circular buffer using uint8_t. Supports write, read, buffer full detection, buffer empty detection, and wrap-around operation.

---

## Build Instructions

Compile the program:

```bash
gcc -Wall -std=c99 ringbuf.c -o ringbuf
```

Run the program:

```bash
./ringbuf
```

For Windows (PowerShell):

```powershell
.\ringbuf.exe
```

---

## Notes

- Uses fixed-width data types from `<stdint.h>`
- Uses FIFO (First In First Out) operation
- Uses `&(BUFFER_SIZE - 1)` optimization for index wrap-around
- Compiles with zero warnings using `gcc -Wall -std=c99`
