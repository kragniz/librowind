#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "librowind.h"

void print_usage() {
    puts("Usage: rowind [test|<device name>]");
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
            print_usage();
            puts("rowind_client: Prints out the current readings from the RO Wind sensor");
        } else if (!strcmp(argv[1], "test")) {
            int ro_fd = get_rowind_fd("/dev/ttyUSB0");
            while (1) {
                Wind* wind = get_wind(ro_fd);
                printf("direction: %f speed: %f\n", wind->direction, wind->speed);
                free(wind);
                sleep(1);
            }
        } else {
            int ro_fd = get_rowind_fd(argv[1]);
            Wind* wind = get_wind(ro_fd);
            printf("{\"direction\": %f, \"speed\": %f, \"valid\": %s}\n",
                    wind->direction,
                    wind->speed,
                    wind->valid ? "true" : "false"
                  );
            return wind->valid;
        }
    } else {
        print_usage();
    }
    return 0;
}
