#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int fd;
    
    fd = open("output.txt", O_WRONLY | O_CREAT, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    
    /* Redirect output to output.txt */
    if (dup2(fd, STDOUT_FILENO) < 0) {
        perror("Error duplicating file descriptor");
        return 1;
    }
    
    /* Output will now be written to output.txt */
    printf("This will be written to output.txt\n");
    
    /* Redirect output back to standard output */
    if (dup2(STDOUT_FILENO, fd) < 0) {
        perror("Error duplicating file descriptor");
        return 1;
    }
    
    /* Output will now be written to standard output */
    printf("This will be written to standard output\n");
    
    return 0;
}