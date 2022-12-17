#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;

    // Open the file for writing
    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // if (fd < 0) {
    //     perror("open");
    //     return 1;
    // }

    // // Redirect stdout to the file
    // close(STDOUT_FILENO);
    // if (dup2(fd, STDOUT_FILENO) < 0) {
    //     perror("dup2");
    //     return 1;
    // }

    // Close the original file descriptor
    close(fd);

    // Any output written to stdout will now be written to the file
    // printf("heellooooo\n");
    while (1)
    {
        /* code */
    }
    
    return 0;
}