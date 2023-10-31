#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * append_text_to_file - Appends text to the end of a file.
 * @filename: Name of the file to append text to.
 * @text_content: The text to append to the file.
 * Return: 1 on success, -1 on failure.
 */
int append_text_to_file(const char *filename, char *text_content)
{
    int file_descriptor, write_status;
    ssize_t text_len;

    if (filename == NULL)
        return (-1);

    file_descriptor = open(filename, O_WRONLY | O_APPEND);
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
