#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
 
#define I8K_SET_FAN      _IOWR('i', 0x87, size_t)
#define I8K_GET_SPEED    _IOWR('i', 0x85, size_t)
#define I8K_FAN_CPU_0	 0
#define I8K_FAN_CPU_1	 1
#define I8K_FAN_SYS_0    2
#define I8K_FAN_SYS_1    3
#define I8K_FAN_SYS_2    4
#define I8K_FAN_REAR_0   5
#define I8K_FAN_REAR_1   6

#define I8K_PROC         "/proc/i8k"

#define I8K_FAN_OFF      0
#define I8K_FAN_LOW      1
#define I8K_FAN_HIGH     2

static int i8k_fd;

int
i8k_get_fan_speed(int fan)
{
    int args[1];
    int rc;

    args[0] = fan;
    if ((rc=ioctl(i8k_fd, I8K_GET_SPEED, &args)) < 0) {
	return rc;
    }

    return args[0];
}

int
fan_speed()
{
    int cpu0 = i8k_get_fan_speed(I8K_FAN_CPU_0);
    int cpu1 = i8k_get_fan_speed(I8K_FAN_CPU_1);
    int sys0 = i8k_get_fan_speed(I8K_FAN_SYS_0);
    int sys1 = i8k_get_fan_speed(I8K_FAN_SYS_1);
    int sys2 = i8k_get_fan_speed(I8K_FAN_SYS_2);
    int rear0 = i8k_get_fan_speed(I8K_FAN_REAR_0);
    int rear1 = i8k_get_fan_speed(I8K_FAN_REAR_1);

    printf("cpu0:%d\n", cpu0);
    printf("cpu1:%d\n", cpu1);
    printf("sys0:%d\n", sys0);
    printf("sys1:%d\n", sys1);
    printf("sys2:%d\n", sys2);
    printf("rear0:%d\n", rear0);
    printf("rear1:%d\n", rear1);
    return 0;
}

int
i8k_set_fan_by_id(int fan, int speed)
{
    int args[2];
    int rc;

    args[0] = fan;
    args[1] = speed;
    if ((rc=ioctl(i8k_fd, I8K_SET_FAN, &args)) < 0) {
	return rc;
    }

    return args[0];
}

int
i8k_set_rear(int speed)
{
    i8k_set_fan_by_id(I8K_FAN_REAR_0, speed);
    i8k_set_fan_by_id(I8K_FAN_REAR_1, speed);
}

int
i8k_set_sys(int speed)
{
    i8k_set_fan_by_id(I8K_FAN_SYS_0, speed);
    i8k_set_fan_by_id(I8K_FAN_SYS_1, speed);
    i8k_set_fan_by_id(I8K_FAN_SYS_2, speed);
}

int
i8k_set_cpu(int speed)
{
    i8k_set_fan_by_id(I8K_FAN_CPU_0, speed);
    i8k_set_fan_by_id(I8K_FAN_CPU_1, speed);
}

int main(int argc, char **argv)
{
    i8k_fd = open(I8K_PROC, O_RDONLY);
    if (argc<3) {
        fan_speed();
        close(i8k_fd);
        return 0;
    }

    char * fanBank = argv[1];
    char * fanSpeed = argv[2];

    printf("Parsed arguments: \n");
    printf("Fan bank: %s\n", fanBank);
    printf("Speed:    %s\n", fanSpeed);

    int i8kFanSpeed = 1;
    if (strcmp(fanSpeed,"low")==0) {
       i8kFanSpeed = 1;
    } else if (strcmp(fanSpeed,"high")==0) {
       i8kFanSpeed = 2;
    } else {
       // safely fall back to low, at least fan is running.
       i8kFanSpeed = 1;
    }

    if (strcmp(fanBank,"rear")==0) {
        printf("Setting rear fan speed of %d\n",i8kFanSpeed);
        i8k_set_rear(i8kFanSpeed);
    } else if (strcmp(fanBank,"sys")==0) {
        printf("Setting sys fan speed of %d\n",i8kFanSpeed);
        i8k_set_sys(i8kFanSpeed);
    } else if (strcmp(fanBank,"cpu")==0) {
       printf("Setting CPU fan speed of %d\n", i8kFanSpeed);
       i8k_set_cpu(i8kFanSpeed);
    } else {
        printf("Not changing any fan speed\n");
    }
    close(i8k_fd);
    return 0;
}
