#include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <fcntl.h>

#ifdef __OpenBSD__
#include <machine/apmvar.h>
#endif


int main(void)
{
    int batt_life;
    int batt_charging;
    #ifdef __OpenBSD__
    struct apm_power_info inf;
    int fd;
    int ioresult;
    fd = open("/dev/apm", O_RDONLY);
    ioresult = ioctl(fd, APM_IOC_GETPOWER, &inf);

    batt_life = inf.battery_life;
    batt_charging = (inf.ac_state == APM_AC_ON);
    #elif __linux__
    #include <string.h>
    char *charging = "Charging\n";
    char charge_buf[10] = {};
    FILE *fd = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (!fd)
        return 1;

    fscanf(fd, "%d", &batt_life);
    fclose(fd);
    fd = fopen("/sys/class/power_supply/BAT0/status", "r");
    if (!fd)
        return 1;
    fread(charge_buf, 1, 9, fd);
    fclose(fd);
    batt_charging = !strcmp(charge_buf, charging);

    #else
    #error "Only openbsd supported right now"
    #endif

    printf("%d%% %s\n", batt_life, batt_charging ? "⌁" : " ");

    return 0;
}
