#include "main.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * copy_file - Copies the content of one file to another.
 * @file_from: The source file to copy from.
 * @file_to: The destination file to copy to.
 * Return: 0 on success, -1 on failure.
 */
int copy_file(const char *file_from, const char *file_to)
{
    int fd_from, fd_to;
    char buffer[1024];
    ssize_t bytes_read, bytes_written;
    mode_t file_permissions;

    if (file_from == NULL || file_to == NULL)
        return (-1);

    fd_from = open(file_from, O_RDONLY);
    if (fd_from == -1)
        return (-1);

    fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd_to == -1)
    {
        close(fd_from);
        return (-1);
    }

    while ((bytes_read = read(fd_from, buffer, sizeof(buffer))) > 0)
    {
        bytes_written = write(fd_to, buffer, bytes_read);
        if (bytes_written == -1 || bytes_written != bytes_read)
        {
            close(fd_from);
            close(fd_to);
            return (-1);
        }
    }

    if (bytes_read == -1)
    {
        close(fd_from);
        close(fd_to);
        return (-1);
    }

    file_permissions = fchmod(fd_to, 0664);
    if (file_permissions == -1)
    {
        close(fd_from);
        close(fd_to);
        return (-1);
    }

    if (close(fd_from) == -1 || close(fd_to) == -1)
        return (-1);

    return (0);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        dprintf(2, "Usage: %s file_from file_to\n", argv[0]);
        exit(97);
    }

    if (copy_file(argv[1], argv[2]) == -1)
    {
        dprintf(2, "Error: Can't read from file %s\n", argv[1]);
        exit(98);
    }

    return (0);
}
