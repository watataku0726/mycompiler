#include <stdio.h>

union val {
    unsigned long long int ival;
    unsigned long long int uval;
};

int main() {
    long long int val = 0;
    val = 0xffffffffL + 0xffffffffL;
    printf("%llx\n", val);
    printf("%x\n", (int)val);

    union val a, b;
    a.uval = 0xffffffffffffffff;
    b.ival = -1;
    printf("%llx\n", a.uval);
    printf("%d\n", a.ival);
    printf("%d\n", -1 < 0xffffffffffffffff);
    return 0;
}



