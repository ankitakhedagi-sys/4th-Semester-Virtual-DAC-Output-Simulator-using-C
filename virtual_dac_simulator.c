#include <stdio.h>
#include <math.h>

int binaryToDecimal(const int bits[], int n) {
    int value = 0;

    for (int i = 0; i < n; i++) {
        value = value * 2 + bits[i];
    }

    return value;
}

void decimalToBinary(int value, int bits[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        bits[i] = value & 1;
        value >>= 1;
    }
}

int main(void) {
    int n;
    double vref;
    int digitalCode;

    printf("=== VIRTUAL DAC OUTPUT SIMULATOR ===\\n");

    printf("Enter DAC resolution (bits): ");
    scanf("%d", &n);

    if (n <= 0 || n > 16) {
        printf("Resolution must be between 1 and 16 bits.\\n");
        return 1;
    }

    printf("Enter reference voltage (V): ");
    scanf("%lf", &vref);

    long levels = 1L << n;

    printf("Enter digital input code (0 to %ld): ", levels - 1);
    scanf("%d", &digitalCode);

    if (digitalCode < 0 || digitalCode >= levels) {
        printf("Invalid digital code.\\n");
        return 1;
    }

    int bits[16];
    decimalToBinary(digitalCode, bits, n);

    double lsb = vref / (levels - 1);
    double outputVoltage = digitalCode * lsb;

    printf("\\n--- DAC Parameters ---\\n");
    printf("Resolution       : %d bits\\n", n);
    printf("Number of levels : %ld\\n", levels);
    printf("Reference voltage: %.3f V\\n", vref);

    printf("Digital input    : ");
    for (int i = 0; i < n; i++) {
        printf("%d", bits[i]);
    }

    printf("\\nDecimal code     : %d\\n", digitalCode);
    printf("LSB size         : %.6f V\\n", lsb);
    printf("Analog output    : %.6f V\\n", outputVoltage);

    printf("\\nQuantization interval: %.6f V\\n", lsb);

    return 0;
}
