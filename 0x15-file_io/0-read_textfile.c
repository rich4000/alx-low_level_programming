#include <fcntl.h>
#include "main.h"

/**
 * read_textfile - Reads and prints a text file to standard output.
 * @filename: Name of the file to read.
 * @letters: The number of letters to read and print.
 * Return: The actual number of letters read and printed. 0 on failure.
 */
ssize_t read_textfile(const char *filename, size_t letters)
{
    int file_descriptor;
    ssize_t bytes_read, bytes_written;
    char *buf;

    if (filename == NULL)
        return (0);

    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1)
        return (0);

    buf = malloc(sizeof(char) * letters);
    if (buf == NULL)
    {
        close(file_descriptor);
        return (0);
    }

    bytes_read = read(file_descriptor, buf, letters);
    if (bytes_read == -1)
    {
        free(buf);
        close(file_descriptor);
        return (0);
    }

    bytes_written = write(STDOUT_FILENO, buf, bytes_read);
    if (bytes_written == -1 || bytes_written != bytes_read)
    {
        free(buf);
        close(file_descriptor);
        return (0);
    }

    free(buf);
    close(file_descriptor);
    return (bytes_written);
}
