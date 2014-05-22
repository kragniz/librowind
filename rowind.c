#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
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
        tty.c_cc[VMIN]  = 1;
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

int get_rowind_fd(char* portname) {
    int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (fd < 0) {
        return -1;
    }

    set_serial_options(fd);
    return fd;
}

char* get_IIMWV(int ro_fd, char* line) {
    char c;
    int n = 1;
    while (n >= 1) {
        n = read (ro_fd, &c, 1);
        printf(&c);
    }
}

int main() {
    int ro_fd = get_rowind_fd("/dev/ttyUSB0");
    char* line = malloc(30);
    puts(get_IIMWV(ro_fd, line));
}
