#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * create_file - Creates a file with specific permissions and writes text to it.
 * @filename: Name of the file to create.
 * @text_content: The text to write to the file.
 * Return: 1 on success, -1 on failure.
 */
int create_file(const char *filename, char *text_content)
{
    int file_descriptor, write_status;
    ssize_t text_len;

    if (filename == NULL)
        return (-1);

    file_descriptor = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
    if (file_descriptor == -1)
        return (-1);

    if (text_content == NULL)
    {
        close(file_descriptor);
        return (1);
    }

    text_len = 0;
    while (text_content[text_len])
        text_len++;

    write_status = write(file_descriptor, text_content, text_len);
    close(file_descriptor);

    if (write_status == -1 || write_status != text_len)
        return (-1);

    return (1);
}
