#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void check_elf(unsigned char *e_ident);
void print_magic(unsigned char *e_ident);
void print_class(unsigned char *e_ident);
void print_data(unsigned char *e_ident);
void print_version(unsigned char *e_ident);
void print_abi(unsigned char *e_ident);
void print_osabi(unsigned char *e_ident);
void print_type(unsigned int e_type, unsigned char *e_ident);
void close_elf(int elf);
void print_entry(unsigned long int e_entry, unsigned char *e_ident);

/**
 * check-elf - Checks if ELF file or not
 * @e_ident: pointer to array of magic numbers
 * Return: exit code 98 if not an elf file
 */

 void check_elf(unsigned char *e_ident)
{
	int index;

	for (index = 0; index < 4; index++)
	{
		if (e_ident[index] != 127 &&
				e_ident[index] != 'E' &&
				e_ident[index] != 'L' &&
				e_ident[index] != 'F')
		{
			dprintf(STDERR_FILENO, "Error: Not an ELF file\n");
			exit(98);
		}
	}
}

/**
 * print_magic - print elf magic header numbers
 * @e_ident: pointer to elf magic number array
 * Return: space separated magic numbers
 */
void print_magic(unsigned char *e_ident)
{
	int index;

	printf(" Magic:  ");

	for (index = 0; index < EI_NIDENT; index++)
	{
		printf("%02", e_ident[index]);

		if (index == EI_NIDENT - 1)
			printf("\n");
		else
			printf(" ");
	}
}
/**
 * print_class - prints the class of ELF header
 * @e_ident: pointer to an array containing class
 */
void print_class(unsigned char *e_ident)
{
	printf("  Class:             ");

	switch (e_ident[EI_CLASS])
	{
		case ELFCLASSNONE:
			printf("none\n");
			break;
		case ELFCLASS32:
			printf("ELF32\n");
			break;
		case ELFCLASS64:
			printf("ELF64\n");
			break;
		default:
			printf("<unknown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * print_data - prints data on ELF header
 * @e_ident: pointer to an array containing ELF class
 */
void print_data(unsigned char *e_ident)
{
	printf("  Data:                 ");

	switch (e_ident[EI_DATA])
	{
		case ELFDATANONE:
			printf("none\n");
			break;
		case ELFDATA2LSB:
			printf("2's compliment, little endian\n");
			break;
		case ELFDATA2MSB:
			printf("2's compliment, big endian\n");
			break;
		default:
			printf("<unkown: %x>\n", e_ident[EI_CLASS]);
	}
}

/**
 * print_version - versinon of an ELF header
 * @e_ident: pointer array
 */
void print_version(unsigned char *e_ident)
{
	printf(" Version:           %d",
			e_ident[EI_VERSION]);
	switch (e_ident[EI_VERSION])
	{
		case EV_CURRENT:
			printf(" (current)\n");
			break;
		default:
			printf("\n");
			break;
	}
}
/**
 * print_osabi - prints OS/ABI of ELF header
 * @e_ident: pointer array
 */
void print_osabi(unsigned char *e_ident)
{
	printf(" OS/ABI:       ");
	 switch (e_ident[EI_OSABI])
	 {
		 case ELFOSABI_NONE:
			 printf("UNIX - System V\n");
			 break;
		 case ELFOSABI_HPUX:
			 printf("UNIX - HP-UX\n");
			 break;
		 case ELFOSABI_NETBSD:
			 printf("UNIX - NetBSD\n");
			 break;
		 case ELFOSABI_LINUX:
			 printf("UNIX - LINUX\n");
			 break;
		 case ELFOSABI_SOLARIS:
			 printf("UNIX - SOLARIS\n");
			 break;
		 case ELFOSABI_IRIX:
			 printf("UNIX - IRIX\n");
			 break;
		 case ELFOSABI_FREEBSD:
			 printf("UNIX - FreeBSD\n");
			 break;
		 case ELFOSABI_TRU64:
			 printf("UNIX - TRU64\n");
			 break;
		 case ELFOSABI_ARM:
			 printf("ARM\n");
			 break;
		 case ELFOSABI_STANDALONE:
			 printf("Standalone App\n");
			 break;
		 default:
			 printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	 }
}

/**
 * print_abi - ABI version of ELF header
 * @e_ident: pointer array
 */
void print_abi(unsigned char *e_ident)
{
	printf("   ABI Version:              %d\n",
			e_ident[EI_ABIVERSION]);
}
/**
 * print_type - prints type of an ELF header
 * @e_type: ELF type
 * @e_ident: Poiinter array
 */

void print_type(unsigned int e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >> 8;

	printf("  Type:            ");

	switch (e_type)
	{
		case ET_NONE:
			printf("NONE (none)\n");
			break;
		case ET_REL:
			printf("REL (Relocatable file)\n");
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
			printf("<unknown: %x>\n", e_type);
	}
}

/**
 * print_entry - prints entry point of an ELF header
 * @e_entry: address of ELF entry point
 * @e_ident: pointer to an array
 */
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf("   Entry point address:         ");

	if ( e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) |
			((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}
	if (e_ident[EI_CLASS] == ELFCLASS32)
	{
		printf("%#x\n", (unsigned int)e_entry);
	}
	else
		printf("%#lx\n", e_entry);
}

/**
 * close_elf - Closes an ELF file
 * @elf: The file descriptor of the elf file
 * Description: if can't be closed - exit code 98
 */
void close_elf(int elf)
{
	if (close(elf) == -1)
	{
		dprintf(STDERR_FILENO,
				"Error: Can't close fd %d\n", elf);
		exit(98);
	}
}
/**
 * main - Displays info of ELF file
 * @argc: number of arguments to program
 * @argv: array of pointers to arguments
 * Return: 0 if pass
 * Description: if not ELF exit code 98
 */

int main(int __attribute__((__unused__)) argc, char *argv[])
{
	Elf64_Ehdr *header;
	int op, rd;

	op = open(argv[1], O_RDONLY);
	
	if (op == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	header = malloc(sizeof(El64_Ehdr));
	if (header == NULL)
	{
		close_elf(op);
		dprintf(STDERR_FILENO, "Error: Can't read file %s\n", argv[1]);
		exit(98);
	}
	rd = read(op, header, sizeof(Elf64_Ehdr));
	if (rd == -1)
	{
		free(header);
		close_elf(op);
		dprintf(STDERR_FILENO, "Error: '%s': No such file\n", argv[1]);
		exit(98);
	}
	check_elf(header->e_ident);
	printf("ELF Header:\n");
	print_magic(header->e_ident);
	print_class(header->e_ident);
	print_data(header->e_ident);
	print_version(header->e_ident);
	print_osabi(header->e_ident);
	print_abi(header->ident);
	print_type(header->e_type, header->e_ident);
	print_entry(header->e_entry, header->e_ident);

	free(header);
	close_elf(op);
	return (0);
}
