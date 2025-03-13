#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    int current_fd = 0;
    if ((current_fd = open("./new_file.txt", O_RDONLY | O_CREAT, 0644)) == -1) {
        perror("Error opening file\n");
        return EXIT_FAILURE;
    }

    const char* msg = "Hello file\n";
    const size_t msg_len = strlen(msg);

    ssize_t ret_val = 0;
    if ((ret_val = write(current_fd, msg, msg_len)) == -1) {
        fprintf(stderr, "%s: %s", sys_errlist[errno], "Error writing\n");
        return EXIT_FAILURE;
    } else if (ret_val < msg_len) {
        fprintf(stderr, "Not all bytes were written\n");
        return EXIT_FAILURE;
    }

    if ((ret_val = close(current_fd))) {
        fprintf(stderr, "errno: %d\n", errno);
        return EXIT_FAILURE;
    }


    return 0;
}