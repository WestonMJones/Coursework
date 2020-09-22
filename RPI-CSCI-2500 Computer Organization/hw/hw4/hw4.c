#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// This function converts a hexadecimal number into an array of 64 bits representing
// that number in binary
int* hex_to_bit_array(long hex) {
	int *bit_array = calloc(64,sizeof(int));
	for (int i = 0; i < 64; i++) {
    	bit_array[i] = hex & 1;
    	hex >>= 1;
	}
	return bit_array;
}

// This function inverts a bit array representing a binary number for subtraction
void invert_bit_array(int* bit_array) {
	for (int i=0;i<64;i++) {
		// if value = 1, then change to 0
		if (bit_array[i]==1) {
			bit_array[i]=0;
		} else {
			// if value = 0, then change to 1
			bit_array[i]=1;
		}
	}
}

// This function converts a bit array into a char array of 0s and 1s for easily displaying
char* bit_array_to_bin(int*bit_array) {
	char * bin = calloc(65,sizeof(char));
	for (int i=0;i<64;i++) {

		// append 0s and 1s to generate the string
		if (bit_array[i]==1) {
			bin[63-i] = '1';
		} else {
			bin[63-i] = '0';
		}
	}

	return bin;
}

int main()
{

	long in1, in2, sum; // longs to hold hex numbers
	int op; // int to hold operation code (add / subtract)

	// Pointers to the bit arrays holding A, B, and their sum.
	int *A; 
	int *B; 
	int *S;

	// pointers to the char arrays hold easily printable representations of A, B, and their sum
	char* A_out;
	char* B_out;
	char* S_out;

	// Query the user
    printf("Enter A (hex): \n");
    scanf("%lx", &in1);
    printf("Enter B (hex): \n");
    scanf("%lx", &in2);
    printf("Add (0) or subtract (1): \n");
    scanf("%d", &op);

    printf("\n");
    printf("A is %016lx or %ld\n",in1,in1);
    printf("B is %016lx or %ld\n",in2,in2);

    // Convert user given hex values to bit arrays
    A = hex_to_bit_array(in1);
    B = hex_to_bit_array(in2);

    // Convert bit array to char array
    A_out = bit_array_to_bin(A);

    // If subtracting, invert B before converting to char array
    if (op==1) {
    	// Invert Code
    	printf("Inverting %ld\n",in2);
    	invert_bit_array(B);
    	B_out = bit_array_to_bin(B); 

    	printf("B (bin) : %s \n",B_out);
    } else {
    	B_out = bit_array_to_bin(B);
    }

    // Begin the CLA Process

 	// 1. Calculate gi and pi for all i. (1 gate delay)

    int * g = calloc(64,sizeof(int));
    int * p = calloc(64,sizeof(int));

    for (int i=0;i<64;i++) {
    	g[i] = (A[i] & B[i]);
    	p[i] = (A[i] | B[i]);
    }

	// 2. Calculate ggj and gpj for all j using gi and pi. (2 gate delays)

	// ggj = gi+3 + pi+3gi+2 + pi+3pi+2gi+1 + pi+3pi+2pi+1gi
	// gpj = pi+3pi+2pi+1pi

    int * gg = calloc(16,sizeof(int));
    int * gp = calloc(16,sizeof(int));

    for (int j=0;j<16;j++) {

    	int i = j*4;
    	gg[j] = ( (g[i+3]) | (p[i+3] & g[i+2]) | (p[i+3] & p[i+2] & g[i+1]) | (p[i+3] & p[i+2] & p[i+1] & g[i]) );
    	gp[j] = (p[i+3] & p[i+2] & p[i+1] & p[i]);

    }

	// 3. Calculate sgk and spk for all k using ggj and gpj. (2 gate delays) Note, it is at this point, we
	// 	can shift to computing the top-level sectional carries. This is because the number of sections
	// 	is less than or equal the block size which is 4 bits.

	// sgk = ggj+3 + gpj+3ggj+2 + gpj+3gpj+2ggj+1 + gpj+3gpj+2gpj+1ggj
	// spk = gpj+3gpj+2gpj+1gpj

    int * sg = calloc(4,sizeof(int));
    int * sp = calloc(4,sizeof(int));

    for (int k=0;k<4;k++) {
    	int j=k*4;
    	sg[k] = ((gg[j+3]) | (gp[j+3] & gg[j+2]) | (gp[j+3] & gp[j+2] & gg[j+1]) | (gp[j+3] & gp[j+2] & gp[j+1] & gg[j])  );
    	sp[k] = ((gp[j+3]) & gp[j+2] & gp[j+1] & gp[j] );
    }

	// 4. Calculate sck using sgk and spk for all k and 0 for sci−1. (2 gate delays)
	/*sck = sgk + spksck−1
	sck+1 = sgk+1 + spk+1sck
	sck+2 = sgk+2 + spk+2sck+1
	sck+3 = sgk+3 + spk+3sck+2*/

    int * sc = calloc(4,sizeof(int));

    sc[0] = (sg[0] | (sp[0] & op));
    for (int k=1;k<4;k++) {
    	sc[k] = (sg[k] | (sp[k] & sc[k-1]));
    }

	// 5. Calculate gcj using ggj, gpj and correct sck, k = (j div 4) as sectional carry-in for all j. (2 gate delays)
 	// gcj = ggj + gpjgcj−1
	// gcj+1 = ggj+1 + gpj+1gcj
	// gcj+2 = ggj+2 + gpj+2gcj+1
	// gcj+3 = ggj+3 + gpj+3gcj+2

	int * gc = calloc(16,sizeof(int));

	for (int j=0;j<16;j++) {
		int k = j/4;
		gc[j] = ((gg[j]) | (gp[j] & sc[k]));
	}

	// 6. Calculate ci using gi, pi and correct gcj, j = (i div 4) as group carry-in for all i. (2 gate delays)
	// ci = gi + pici−1
	// ci+1 = gi+1 + pi+1ci
	// ci+2 = gi+2 + pi+2ci+1
	// ci+3 = gi+3 + pi+3ci+2
	
	int * c = calloc(64,sizeof(int));

	for (int i=0;i<64;i++) {
		int j = i/4;
		c[i] = (g[i] | (p[i] & gc[j]));
	}

	// 7. Calculate sumi using ai and bi and ci−1 for all i. (2 gate delays)

	S = calloc(64,sizeof(int));

	S[0] = (A[0] ^ B[0] ^ op);
	for (int i=1;i<64;i++) {
		S[i] = (A[i] ^ B[i] ^ c[i-1]);
	}

	// Convert Sum bit array to easily printable binary string
	S_out = bit_array_to_bin(S);

	// Convert the sum bit array to long for easily converting to hex
	sum = 0;
	for (int i=0;i<64;i++) {
		sum = sum + (S[i]*pow(2,i));
	}

	printf("\nCalculate sum, S:\n\n");

    printf("A (bin) : %s \n",A_out);
    printf("B (bin) : %s \n",B_out);
    printf("S (bin) : %s \n",S_out);

    printf("\nS is %016lx or %ld\n",sum,sum);
    return 0;

}