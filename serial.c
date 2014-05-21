#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int set_serial_options (int fd) {
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0) {
                return -1;
        }

        cfsetospeed (&tty, B4800);
        cfsetispeed (&tty, B4800);

        tty.c_iflag &= ~IGNBRK;
        tty.c_lflag = 0;
        tty.c_cc[VMIN]  = 0;
        tty.c_cc[VTIME] = 50;

        tty.c_iflag &= ~(IXON | IXOFF | IXANY);

        tty.c_cflag |= (CLOCAL | CREAD);
        tty.c_cflag &= ~(PARENB | PARODD);
        tty.c_cflag |= B4800;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0) {
                return -2;
        }
        return 0;
}

int main() {
    char *portname = "/dev/ttyUSB0";
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        return 1;
    }

    set_serial_options(fd);
    char c;
    int n = 1;
    while (n >= 1) {
        n = read (fd, &c, 1);
        printf(&c);
    }
    return 1;
}
