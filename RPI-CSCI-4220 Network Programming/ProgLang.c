#include <stdio.h>

typedef struct {
	int *i;
	char c;

} huge_record;

void const_is_shallow(const huge_record* const r) {
	int *x = r->i;
	*x = 0;
}

int main(int argc, char **argv) {

	printf("BLAH\n");
	return 0;

}