#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>


int bit_twiddling(int val, int lsb, int msb)
{

    int mask1;
    if (msb==31) {
        mask1 = 1 << 31;
    } else {
        mask1 = 1 << (msb+1);
    }
    int mask2 = mask1 - 1;
    int splice1 = mask2 & val;
    int splice2 = splice1 >> lsb;

   


    return splice2;
}


void print_stuff(unsigned int address) {

    int BOB = 3;
    int index_bits = 2;
    int index, tag;



    int address_copy = address >> BOB;

    int mask = 1 << (index_bits);
    mask = mask - 1;
    index = mask & address_copy;


    tag = address_copy >> index_bits;



    printf("Address %x: Tag= %x, Index=%d \n",address,tag,index);

}



int main()
{
    print_stuff(0x400074); //Address 400074: Tag= 20003, Index= 2 
    print_stuff(0x400018); // Address 400018: Tag= 20000, Index= 3
    print_stuff(0x10010178); // Address 10010178: Tag= 80080b, Index= 3
    print_stuff(0x400200); // Address 400200: Tag= 20010, Index= 0 
    print_stuff(0x4001f4); //Address 4001f4: Tag= 2000f, Index= 2 

 


    return 0;
}

