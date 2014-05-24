#ifndef RO_WIND_H
#define RO_WIND_H

#define RW_DIRECTION_INDEX 1
#define RW_SPEED_INDEX 3
#define RW_VALID_INDEX 5

typedef struct _wind {
    double direction;
    double speed;
    int valid;
} Wind;

/*
 * get_wind: Return current wind data from the sensor.
 *
 * wind->direction (double):  The direction of the wind in the range of 0.0-359.9.
 * wind->speed (double): The speed of the wind in knots.
 * wind->valid (int): 0 if the data from the sensor is valid and the checksum
 * passed.
 *
 * ro_fd: file descriptor of the serial port used by the sensor. Use
 * get_rowind_fd to correctly set the configuration.
 */
Wind* get_wind(int ro_fd);

/*
 * update_wind: Updates a Wind struct with new data from the sensor
 */
void update_wind(int ro_fd, Wind* wind);

/*
 * get_rowind_fd: Configures the serial port and returns a file descriptor.
 *
 * portname: a string containing the path to the serial device. Probably
 * /dev/ttyUSBX.
 */
int get_rowind_fd(char* portname);

#endif
