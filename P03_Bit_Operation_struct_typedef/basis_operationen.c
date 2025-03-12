#include <stdlib.h>
#include <stdio.h>

int main() {
    unsigned int number = 0x75;
    unsigned int bit = 3; // bit at position 3

    // Setting a bit: Use bitwise OR to ensure the bit at the given position is set to 1
    // (1 << bit) shifts 1 to the left by 'bit' positions, creating a mask with only that bit set.
    // Applying OR (|) keeps all other bits unchanged while setting the target bit to 1.
    number = number | (1 << bit);

    // Clearing a bit: Use bitwise AND with NOT to ensure the bit at the given position is cleared to 0
    // (1 << bit) shifts 1 to the left, and ~ (bitwise NOT) inverts all bits.
    // Applying AND (&) ensures the target bit is 0 while leaving all other bits unchanged.
    bit = 1;
    number = number & ~(1 << bit);

    // Toggling a bit: Use bitwise XOR to flip the bit at the given position
    // (1 << bit) creates a mask for the target bit.
    // XOR (^) inverts the bit (0 becomes 1, 1 becomes 0) while leaving all other bits unchanged.
    bit = 0;
    number = number ^ (1 << bit);

    (void) printf("number = 0x%02X\n", number);

    return EXIT_SUCCESS;
}
