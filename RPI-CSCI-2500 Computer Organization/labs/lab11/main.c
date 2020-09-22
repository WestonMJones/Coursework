#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <math.h>



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
    return splice2;
}


/*
 Given the index values, determine the number of slots in your cache.
 */
uint32_t slot_count(uint32_t idx_start, uint32_t idx_end)
{
    // assert() calls are great to ensure your logic is valid!
    assert(idx_start < idx_end);
    
    uint32_t dif = idx_end - idx_start;
    uint32_t ans = pow(2,dif);
    return ans;
}

/*
 Given an address and range of bits in the index (start-end, inclusive)
 return the index.  Example:
 
 Given the address below, start of 4, and end of 11
 
    2    1    3    5    C    6    9    0
 0010 0001 0011 0101 1100 0110 1001 0000
                          ^       ^
                          e       s
 
 this function should return 0110 1001 or 0x69 or 105 in decimal.
 */
uint32_t get_index(uint32_t address, uint32_t idx_start, uint32_t idx_end)
{
    // assert() calls are great to ensure your logic is valid!
    assert(idx_start < idx_end);

    uint32_t ans = bit_twiddling(address,idx_start,idx_end);

    
    return ans;
}

/*
 Utilizing slide 34 as a reference, calculate the total BITS in the cache
 LINE including data, tag, and valid bits.  Assume 32-bit addressing.
 The bob argument should be the leftmost bit number of the BOB,
 e.g., 3 means bits 0-3 (inclusive) are used for the BOB.
 */
uint32_t get_cache_line_size(uint32_t idx_start, uint32_t idx_end, uint32_t bob)
{
    // assert() calls are great to ensure your logic is valid!
    assert(bob + 1 == idx_start);
    assert(idx_start < idx_end);

    uint32_t size = 0;

    size = 1 + (32-idx_end) + (pow(2,bob+1)*8);

    
    return size;
}

int main()
{
    // This should return 256
    printf("slot_count(4, 11) returned %d\n\n",
           slot_count(4, 11));
    
    printf("slot_count(5, 13) returned %d\n\n",
           slot_count(5, 13));
    
    // This should return 105
    printf("get_index(0x2135C690, 4, 11) returned %d\n\n",
           get_index(0x2135C690, 4, 11));
    
    printf("get_index(0x2135C690, 5, 17) returned %d\n\n",
           get_index(0x2135C690, 5, 17));
    
    // This should return 49
    printf("get_cache_line_size(2, 16, 1) returned %d\n\n",
           get_cache_line_size(2, 16, 1));
    
    printf("get_cache_line_size(4, 15, 3) returned %d\n\n",
           get_cache_line_size(4, 15, 3));
    
    
    return 0;
}
