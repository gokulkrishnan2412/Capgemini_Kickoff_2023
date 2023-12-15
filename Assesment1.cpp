#include <stdio.h>
int array_process(unsigned char *ptr, int size, unsigned char no_bits);

int main() {
    int size;
    unsigned char no_bits;
    unsigned char array[size];

    printf("Enter size of array: ");
    scanf("%d", &size);
    if(size<0){
        printf("Invalid array size.Operation unsuccessful!");
    }
    
    //user input of array elements
    printf("Enter %d elements for the array:\n", size);
    for (int i = 0; i < size; i++) {
        scanf("%hhu", &array[i]);
    }

    printf("Enter number of bits to reverse (1-8): ");
    scanf("%hhu",&no_bits);

    int result = array_process(array, size, no_bits);

    //final result validation
    if (result) {
        printf("Reversal operation successful. New array: ");
        for (int i = 0; i < size; i++) {
            printf("\n%hhu ", array[i]);
        }
        printf("\n");
    } else {
        printf("Operation unsuccessful. Invalid number of bits.\n");
    }

    return 0;
}
int array_process(unsigned char *ptr, int size, unsigned char no_bits) {
    //for invalid reversal bits
    if (no_bits < 0 || no_bits > 8) {
        return -1; 
    }

    for (int i = 0; i < size; i++) {
        
        // Bit selection pattern for reversing specific bits
        unsigned char pattern = (0xFF << no_bits) - 1; 
        unsigned char reverse = 0;

        // reversing the bits to be reversed 
        int j = 0;
        while (j < no_bits) 
        {
            reverse <<= 1;
            reverse |= (ptr[i] & 1);
            ptr[i] >>= 1;
            j++;
        }
        
        ptr[i] = (ptr[i] << no_bits) | (reverse & pattern);
    }

    return 1; // for Successful operation
}
