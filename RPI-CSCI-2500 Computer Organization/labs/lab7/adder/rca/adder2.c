#include <stdio.h>

/* 
   Use d0, d1, and carry_in to compute a return value.
   If necessary, use the carry_out pointer to return additional information
*/
int add_two_bits(int d0, int d1, int carry_in, int *carry_out)
{
  // The Boolean logic for the sum (in this case S) will be A'B+AB' whereas for carry (C) will be AB.
  int sum = d0 + d1 + carry_in;
  printf("Adding %d + %d + %d = %d\n",d0,d1,carry_in,sum);
  if (sum==3) {
      *carry_out = 1;
      return 1;
  } else if (sum==2) {
      *carry_out = 1;
      return 0;
  } else if (sum==1) {
      return 1;
  } else {
      return 0;
  }
  
}

int main()
{
  int i;
  int d0[4];
  int d1[4];
  int ci[5];
  int sum[4];
  int c_out = 0;

  ci[0]=0;

  for (i=3;i>=0;i--) {
    printf("Enter binary digit for d0[%d]: ",c_out);
    scanf("%d", &d0[i]);
    /* Clean the user-generated input */
    d0[i] = !!d0[i];
    c_out++;
  }

  c_out = 0;

  for (i=3;i>=0;i--) {
    printf("Enter binary digit for d1[%d]: ",c_out);
    scanf("%d", &d1[i]);
    /* Clean the user-generated input */
    d1[i] = !!d1[i];
    c_out++;
  }

  c_out=0;

  /* Call add_two_bits multiple times */
  for (i=0;i<4;i++) {
    c_out = 0;
    sum[i]=add_two_bits(d0[i],d1[i],ci[i],&c_out);
    ci[i+1] = c_out;
  }

  for (i=3;i>=0;i--) {
    printf("%d",d0[i]);
  }

  printf(" + ");

  for (i=3;i>=0;i--) {
    printf("%d",d1[i]);
  }
  
  printf(" = ");

  for (i=3;i>=0;i--) {
    printf("%d",sum[i]);
  }

  if (ci[4]==1) {
    printf(" with a carry\n");
  } else {
    printf(" without a carry\n");
  }

  
  return 0;
}
