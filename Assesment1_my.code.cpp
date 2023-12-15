#include <stdio.h>
#include <stdlib.h> // Include the necessary header file for malloc
#define MAXVAL 8
#define MINVAL 1
#define SUCCESS 1
#define UNSUCCESS -1
 
int array_process(unsigned char *input_ptr, unsigned char *output_ptr, int size, unsigned char no_bits); // Function Declaration
 
int main() {
    int size;
    unsigned char no_bits;
 
    printf("Enter size of array: ");
    scanf("%d", &size);
 
    if (size <= 0) {
        printf("Invalid array size. Operation unsuccessful!\n");
        return 1;
    }
 
    // Dynamically allocate memory for input_array
    unsigned char *input_array = (unsigned char *)malloc(size * sizeof(unsigned char));
    if (input_array == NULL) {
        printf("Memory allocation failed for input_array. Exiting program.\n");
        return 1;
    }
 
    // Dynamically allocate memory for reversed_array
    unsigned char *reversed_array = (unsigned char *)malloc(size * sizeof(unsigned char));
    if (reversed_array == NULL) {
        free(input_array); // Free previously allocated memory
        printf("Memory allocation failed for reversed_array. Exiting program.\n");
        return 1;
    }
 
    // User input of array elements
    printf("Enter %d elements for the array:\n", size);
   
    for (int i = 0; i < size; i++) {
    int temp;
    printf("Element %d: ", i + 1);
    scanf("%d", &temp);
 
    if (temp < 0 || temp > 255) {
        printf("Invalid input. Please enter a value between 0 and 255.\n");
        // Handle the invalid input, ask the user to input again, etc.
        i--; // Decrement i to re-enter the current element
    } else {
        input_array[i] = (unsigned char)temp;
    }
}
 
    printf("Enter number of bits to reverse (1-8): ");
    scanf("%hhu", &no_bits);
    printf("Input arrays:");
    for (int i = 0; i < size; i++) {
        printf("%hhu ", input_array[i]);
    }
 
    int result = array_process(input_array, reversed_array, size, no_bits);
 
    // Final result validation
    if (result == 1) {
        printf("\nReversal operation successful. \nNew array: ");
        for (int i = 0; i < size; i++) {
            printf("%hhu ", reversed_array[i]);
        }
        printf("\n");
    } else {
        printf("Operation unsuccessful. Invalid number of bits.\n");
    }
 
    // Free dynamically allocated memory before exiting
    free(input_array);
    free(reversed_array);
 
    return 0;
}
 
int array_process(unsigned char *input_ptr, unsigned char *output_ptr, int size, unsigned char no_bits) {
    // For invalid reversal bits
    if (no_bits < MINVAL || no_bits > MAXVAL){
        return -1;
    }
 
    for (int i = 0; i < size; i++) {
        // Bit selection pattern for reversing specific bits
        unsigned char mask = (1 << no_bits) - 1;
        unsigned char reverse = 0;
 
        // Reversing the specified number of bits
        for (int j = 0; j < no_bits; j++) {
            reverse <<= 1;
            reverse |= (input_ptr[i] & 1);
            input_ptr[i] >>= 1;
        }
 
        output_ptr[i] = (input_ptr[i] << (8 - no_bits)) | (reverse & mask);
    }
 
    return 1; // Successful operation
}