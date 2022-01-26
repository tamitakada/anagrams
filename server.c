#include "networking.h"
#include <time.h>

int main() {
    srand(time(NULL));

    int sd = server_setup();
    server_connect(sd);
}
