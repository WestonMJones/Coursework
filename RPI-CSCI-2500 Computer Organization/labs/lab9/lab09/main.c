#include <stdio.h>
#include <stdint.h>

/*
 * If zeroOrOne is 1, append 1 to bitbucket and return that value.
 * Likewise for 0.
 */
uint32_t push_bits(uint32_t bitbucket, uint32_t zeroOrOne)
{
    
    return (bitbucket << 1) | zeroOrOne;
}

/*
 * Extract the least significant bit from the value pointed to by bitbucket.
 * Remove this bit from the pointed-to value and return it.
 */
uint32_t pop_bits(uint32_t *bitbucket)
{

    uint32_t temp = *bitbucket & 1;
    *bitbucket = *bitbucket >> 1;
    return temp;
}

/*
 * Print out a 32-bit binary string
 */
void print_b32(uint32_t s)
{
    uint32_t binaryString[32];
    
    for (int i = 0; i < 32; i++) {
        binaryString[i] = pop_bits(&s);
    }
    
    for (int i = 31; i >= 0; i--) {
        printf("%d", binaryString[i]);
    }
    printf("\n");
}

/*
 * Bit twiddling
 * Pass in an integer.  Also pass in two numbers to construct
 * the range of bits you are interested in viewing.  For example,
 * passing 3 and 5 should return the value of ONLY BITS 3 THROUGH
 * 5 (inclusive) of the integer you pass in.
 * As an example, passing in 123 for val, 1 for lsb, and 4 for msb
 * should generate the value 13.
 * (Why? 123 = 01111011 and between the values between the pointers
 *                ^  ^
 * yields 1101 or 8+4+0+1 or 13.
 */
uint32_t bit_twiddling(uint32_t val, uint32_t lsb, uint32_t msb)
{

    uint32_t mask1;
    if (msb==31) {
        mask1 = 1 << 31;
    } else {
        mask1 = 1 << (msb+1);
    }
    uint32_t mask2 = mask1 - 1;
    uint32_t splice1 = mask2 & val;
    uint32_t splice2 = splice1 >> lsb;

    printf("Splicing %d between %d and %d\n",val,lsb,msb);
    print_b32(val);
    print_b32(mask1);
    print_b32(mask2);
    print_b32(splice1);
    print_b32(splice2);



    return splice2;
}

/*
 * This function should decode the instruction:
 * 1) determine the instruction opcode and, based on that,
 * 2) return the appropriate funct code (or zero if not applicable)
 * This function should support:
 *    add
 *    slt
 *    sub
 *    j
 *    beq
 */
uint32_t decode(uint32_t inst)
{




    uint32_t opcode = bit_twiddling(inst,26,31);
    uint32_t funct_code = bit_twiddling(inst,0,5);

    /*print_b32(inst);
    print_b32(opcode);
    print_b32(funct_code);
    printf("\n");*/

    if (opcode==0) {
        return funct_code;
    } else {
        return 0;
    }
}

int main()
{

    uint32_t test = 15;
    uint32_t test2 = bit_twiddling(test,2,3);
    print_b32(test2);





    // //////////// CHECKPOINT 1 ////////////
    // printf("looping over pop_bits(13):\n");
    // uint32_t temp = 13;
    // print_b32(temp);
    
    // uint32_t x = push_bits(13, 1);
    // printf("push_bits(13,1) is %d\n", x);
    
    // printf("in binary:\n");
    // print_b32(x);
    
    // //////////// CHECKPOINT 2 ////////////
    // uint32_t val = bit_twiddling(123, 1, 4);
    // printf("val is %d\n", val);
    
    // //////////// CHECKPOINT 3 ////////////
    // uint32_t inst[] =
    // {
    //     45459490, 66803754, 273938261, 12965920, 137929722
    // };
    
    // for (int i = 0; i < 5; i++) {
    //     if (decode(inst[i])) {
    //         printf("R type\n");
    //     }
    //     else {
    //         printf("Non-R type\n");
    //     }
    // }
    
    return 0;
}