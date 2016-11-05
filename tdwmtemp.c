#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int temp;
    #ifdef __linux__
    char buf[6] = {};
    FILE *fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!fp)
        exit(1);
    fscanf(fp, "%d", &temp);
    fclose(fp);
    temp /= 1000;
    #endif

    printf("%dC\n", temp);
}
