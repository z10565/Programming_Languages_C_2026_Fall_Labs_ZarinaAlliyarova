#include <stdio.h>

long long factorial(int n) {
    long long answer = 1;
    for (int i = 2; i <= n; i++) {
        answer *= i;
    }
    return answer;
}

int main(void) {
    int n;

    printf("Enter a non-negative integer n: ");
    if (scanf("%d", &n) != 1) {
        printf("Error: please enter an integer\n");
        return 1;
    }

    if (n < 0) {
        printf("Error: please enter a non-negative number\n");
    } else {
        long long result = factorial(n);
        printf("%d! = %lld\n", n, result);
    }

    return 0;
}