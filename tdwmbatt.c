 #include <stdio.h>
#include <stdlib.h>

#include <sys/ioctl.h>
#include <fcntl.h>

#ifdef __OpenBSD__
#include <machine/apmvar.h>
#endif


int main(void)
{
    // Does any laptop have more than 2 batteries?
    int batt_life[3];
    int batt_charging[3];
    int batteries = 0;
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
    char charge_buf[10] = {0};
    FILE *fd = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    if (fd) {

        fscanf(fd, "%d", &batt_life[0]);
        fclose(fd);
        fd = fopen("/sys/class/power_supply/BAT0/status", "r");
        if (!fd)
            return 1;
        batteries++;
        fread(charge_buf, 1, 9, fd);
        fclose(fd);
        batt_charging[0] = !strcmp(charge_buf, charging);
    }
    
    fd = fopen("/sys/class/power_supply/BAT1/capacity", "r");
    if (fd) {


        fscanf(fd, "%d", &batt_life[1]);
        fclose(fd);
        fd = fopen("/sys/class/power_supply/BAT1/status", "r");
        if (!fd)
            return 1;
        fread(charge_buf, 1, 9, fd);
        fclose(fd);
        batt_charging[1] = !strcmp(charge_buf, charging);
        batteries++;
    }
#else
#error "Only openbsd and linux supported right now"
#endif

    for (int i = 0; i < batteries; i++)
        printf("%d%% %s ", batt_life[i], batt_charging[i] ? "C" : " ");

    return 0;
}
