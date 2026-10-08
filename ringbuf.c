#include <stdio.h>
#include <stdint.h>

// Buffer size is 8 bytes as given in assignment
#define BUFFER_SIZE 8

// Structure for Ring Buffer
typedef struct
{
    uint8_t buffer[BUFFER_SIZE]; // Array to store data
    uint8_t head;               // Next write position
    uint8_t tail;               // Next read position
    uint8_t count;              // Number of bytes currently stored
} RingBuffer;

// Function to initialize buffer
void initialize(RingBuffer *rb)
{
    rb->head = 0;  // Start write position from 0
    rb->tail = 0;  // Start read position from 0
    rb->count = 0; // Buffer initially empty
}

// Function to write one byte into buffer
int writeData(RingBuffer *rb, uint8_t data)
{
    // Check if buffer is already full
    if(rb->count == BUFFER_SIZE)
    {
        return -1; // Return error
    }

    // Store data at current head position
    rb->buffer[rb->head] = data;

    // Move head to next position
    // Using & instead of % because BUFFER_SIZE = 8
    // Bitwise AND is faster than division/modulo on many MCUs
    // Some microcontrollers do not have a hardware divider
    // This works only when BUFFER_SIZE is a power of 2 (8,16,32...)
    rb->head = (rb->head + 1) & (BUFFER_SIZE - 1);

    // Increase stored byte count
    rb->count++;

    return 0; // Success
}

// Function to read one byte from buffer
int readData(RingBuffer *rb, uint8_t *data)
{
    // Check if buffer is empty
    if(rb->count == 0)
    {
        return -1; // Return error
    }

    // Read data from current tail position
    *data = rb->buffer[rb->tail];

    // Move tail to next position
    // Using & instead of % because BUFFER_SIZE = 8
    // Bitwise AND is faster than division/modulo on many MCUs
    // Some microcontrollers do not have a hardware divider
    // This works only when BUFFER_SIZE is a power of 2 (8,16,32...)
    rb->tail = (rb->tail + 1) & (BUFFER_SIZE - 1);

    // Decrease count because one byte is removed
    rb->count--;

    return 0; // Success
}

int main()
{
    RingBuffer rb;
    uint8_t data;
    int i;

    // Initialize buffer
    initialize(&rb);

    // First 8 bytes given in assignment
    uint8_t arr1[8] =
    {
        0x41,0x42,0x43,0x44,
        0x45,0x46,0x47,0x48
    };

    // Write first 8 bytes
    for(i=0;i<8;i++)
    {
        if(writeData(&rb,arr1[i]) == 0)
        {
            printf("[WRITE] 0x%02X -> OK (count=%d)",arr1[i],rb.count);

            // Check if buffer became full
            if(rb.count == BUFFER_SIZE)
            {
                printf(" FULL");
            }

            printf("\n");
        }
    }

    // Try writing one more byte
    if(writeData(&rb,0x99) == -1)
    {
        printf("[WRITE] 0x99 -> FAIL (buffer full)\n");
    }

    // Read first 3 bytes
    for(i=0;i<3;i++)
    {
        if(readData(&rb,&data) == 0)
        {
            printf("[READ] -> 0x%02X (count=%d)\n",data,rb.count);
        }
    }

    // New bytes to test wrap around
    uint8_t arr2[3] = {0x49,0x4A,0x4B};

    // Write 3 more bytes
    for(i=0;i<3;i++)
    {
        if(writeData(&rb,arr2[i]) == 0)
        {
            printf("[WRITE] 0x%02X -> OK (count=%d)\n",arr2[i],rb.count);
        }
    }

    // Read all remaining bytes
    while(rb.count != 0)
    {
        if(readData(&rb,&data) == 0)
        {
            printf("[READ] -> 0x%02X (count=%d)\n",data,rb.count);
        }
    }

    // Try reading from empty buffer
    if(readData(&rb,&data) == -1)
    {
        printf("[READ] (empty) -> FAIL (buffer empty)\n");
    }

    return 0;
}