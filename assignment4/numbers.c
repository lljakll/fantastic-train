// Jackie A. Adair
// CST 221
// Topic 5 Memory Management
// 20 Jan 2019
// This code gathers input from the user and performs the described actions

#include <stdio.h>
#include <limits.h>

// Converts the decimal to binary
void printInBinary(long num, int bit){

    // if the number is completely converted, return
    if ( bit >= 8*sizeof(num) )
    {
       return;
    }

    // recursively convert to binary
    printInBinary(num/2, bit+1);
    printf("%ld", num%2);

    // split into 8 bit segments
    if ( bit%8 == 0 )
    {
       printf(" ");
    }
    if ( bit == 0 )
    {
       printf("\n");
    }
}

// convert the decimal to a hex and print
void printInHex(long num){
    printf("ox%032lx\n\n", num);
}

// perform multiple operations IAW the assignment
void finalCow(long num){
    long shiftedNum = num << 16;
    //printf("%ld shifted 16 bits to the left\n%ld\n", num, shiftedNum);
    long maskedNum = shiftedNum & ~0xFFFF;
    //printf("%ld with bottom 16 bits masked\n%ld\n", shiftedNum, maskedNum);
    long hexAddedNum = maskedNum | 0x07FF;
    //printf("%ld with 0x07ff added\n%ld\n", maskedNum, hexAddedNum);
    printf("%ld Shifted 16 bits to the left, lower 16 bits masked, and 0x07FF added:\n", num);
    printf("%ld\n",hexAddedNum);
    printInBinary(hexAddedNum,0);
    printInHex(hexAddedNum);
    printf("\n");
}



int main()
{
    long number;
    do{

        printf("Enter a number between 0 and 4095: ");
        scanf("%ld", &number);
        printf("\n");
    }while(number > 4095 || number < 0);

    printf("Printing %ld in 32-bit binary with the least significant bit on the right: \n", number);
    printInBinary(number, 0);
    printf("\n");

    printf("Printing %ld in 32-bit hexadecimal: \n", number);
    printInHex(number);

    finalCow(number);

}