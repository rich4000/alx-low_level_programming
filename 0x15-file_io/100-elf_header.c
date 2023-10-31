#include "main.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <string.h>

/**
 * print_magic - Prints the ELF magic numbers.
 * @e_ident: ELF identification array.
 */
void print_magic(unsigned char e_ident[])
{
    int i;

    printf("  Magic:   ");
    for (i = 0; i < EI_NIDENT; i++)
    {
        printf("%02x", e_ident[i]);
        if (i < EI_NIDENT - 1)
            printf(" ");
    }
    printf("\n");
}

/**
 * print_elf_header - Prints the ELF header information.
 * @ehdr: ELF header structure.
 */
void print_elf_header(Elf64_Ehdr ehdr)
{
    printf("ELF Header:\n");
    print_magic(ehdr.e_ident);
    printf("  Class:                             ");
    switch (ehdr.e_ident[EI_CLASS])
    {
        case ELFCLASS32:
            printf("ELF32\n");
            break;
        case ELFCLASS64:
            printf("ELF64\n");
            break;
        default:
            printf("<unknown: %x>\n", ehdr.e_ident[EI_CLASS]);
            break;
    }

    printf("  Data:                              ");
    switch (ehdr.e_ident[EI_DATA])
    {
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;
        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;
        default:
            printf("<unknown: %x>\n", ehdr.e_ident[EI_DATA]);
            break;
    }

    printf("  Version:                           %d (current)\n", ehdr.e_ident[EI_VERSION]);
    printf("  OS/ABI:                            ");
    switch (ehdr.e_ident[EI_OSABI])
    {
        case ELFOSABI_SYSV:
            printf("UNIX - System V\n");
            break;
        case ELFOSABI_HPUX:
            printf("HP-UX\n");
            break;
        case ELFOSABI_NETBSD:
            printf("NetBSD\n");
            break;
        case ELFOSABI_LINUX:
            printf("Linux\n");
            break;
        case ELFOSABI_SOLARIS:
            printf("UNIX - Solaris\n");
            break;
        case ELFOSABI_IRIX:
            printf("IRIX\n");
            break;
        case ELFOSABI_FREEBSD:
            printf("FreeBSD\n");
            break;
        case ELFOSABI_TRU64:
            printf("TRU64\n");
            break;
        case ELFOSABI_ARM:
            printf("ARM\n");
            break;
        case ELFOSABI_STANDALONE:
            printf("Standalone App\n");
            break;
        default:
            printf("<unknown: %x>\n", ehdr.e_ident[EI_OSABI]);
            break;
    }

    printf("  ABI Version:                       %d\n", ehdr.e_ident[EI_ABIVERSION]);

    printf("  Type:                              ");
    switch (ehdr.e_type)
    {
        case ET_REL:
            printf("REL (Relocatable file)\n");
            break;
        case ET_EXEC:
            printf("EXEC (Executable file)\n");
            break;
        case ET_DYN:
            printf("DYN (Shared object file)\n");
            break;
        case ET_CORE:
            printf("CORE (Core file)\n");
            break;
        default:
            printf("<unknown: %x>\n", ehdr.e_type);
            break;
    }

    printf("  Entry point address:               0x%lx\n", ehdr.e_entry);
}

/**
 * main - Entry point.
 * @ac: The number of arguments.
 * @av: An array of argument strings.
 * Return: 0 on success, 98 on failure.
 */
int main(int ac, char **av)
{
    int fd;
    Elf64_Ehdr ehdr;

    if (ac != 2)
    {
        dprintf(2, "Usage: %s elf_filename\n", av[0]);
        exit(98);
    }

    fd = open(av[1], O_RDONLY);
    if (fd == -1)
    {
        dprintf(2, "Error: Can't open file %s\n", av[1]);
        exit(98);
    }

    if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) != sizeof(Elf64_Ehdr))
    {
        dprintf(2, "Error: Can't read file %s\n", av[1]);
        close(fd);
        exit(98);
    }

    print_elf_header(ehdr);
    close(fd);
    return (0);
}
