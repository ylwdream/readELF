#include "elfReader.h"

void ElfReader::printElfHeader() const
{
	int pos = 0;
	memcpy(start, this->start, ELF_LENHT);
	
	printf("ELF Header:\n");
	/* ------------Magic begin---------- */	
	printf("  Magic: ");
	for(pos = 0; pos < 16; pos++)
		printf("%02x ", start[pos]);
	printf("\n");
	
	int tab_width = 35;

	printf("  %-*s", tab_width, "Class:");
	switch(start[EI_CLASS])
	{
		case 0:
			printf("Invalid\n");
			break;
		case 1:
			printf("ELF32\n");
			break;
		case 2:
			printf("ELF64\n");
			break;
	}

	printf("  %-*s", tab_width, "Data:");
	switch(start[EI_DATA])
	{
		case 0:
			printf("Invalid\n");
			break;
		case 1:
			printf("2's complement, little endian\n");
			break;
		case 2:
			printf("2's complement, big endian\n");
			break;
	}

	printf("  %-*s", tab_width, "Version:");
	switch(start[EI_VERSION])
	{
		case EV_CURRENT:
			printf("1 (Current)\n");
			break;
		default:
			printf("Invalid\n");
			break;
	}

	printf("  %-*s", tab_width, "OS/ABI:");
	switch(start[EI_OSABI])
	{
		case 0:
			printf("UNIX System V ABI\n");
			break;
		case 1:
			printf("HP-UX\n");
			break;
		case 2:
			printf("NetBSD\n");
			break;
		case 3:
			printf("Linux \n");
			break;
		case 6:
			printf("Sun Solaris\n");
			break;
		case 7:
			printf("IBM AIX\n");
			break;
			
	}
	/* ------------Magic end---------- */	
	
	printf("  %-*s", tab_width, "Type:");
	switch(elf_header.e_type)
	{
		case 0:
			printf("No file type\n");
			break;
		case 1:
			printf("Relocatable file\n");
			break;
		case 2:
			printf("Executable file\n");
			break;
		case 3:
			printf("Shared object file\n");
			break;
		case 4:
			printf("Core file\n");
			break;
	}

	printf("  %-*s", tab_width, "Machine:");
	switch(elf_header.e_machine)
	{
		case 0:
			printf("no machine\n");
			break;
		case 1:
			printf("AT&T WE 32100\n");
			break;
		case 2:
			printf("SUN SPARC\n");
			break;
		case 3:
			printf("Intel 80386\n");
			break;
		case 4:
			printf("Motorola m68k family\n");
			break;
		case 7:
			printf("Intel 80860\n");
			break;
	}
	
	printf("  %-*s", tab_width, "Version:");
	switch(elf_header.e_version)
	{
		case 0:
			printf("Invalid Version\n");
			break;
		case 1:
			printf("0x1 Current\n");
			break;
	}

	printf("  %-*s", tab_width, "Entry point address:");
	printf("0x"); printf("%x\n", elf_header.e_entry);

	printf("  %-*s", tab_width, "Start of program headers:");
	printf("%d (bytes into file)\n", elf_header.e_phoff);

	printf("  %-*s", tab_width, "Start of section headers:");
	printf("%d (bytes into file)\n", elf_header.e_shoff);

	printf("  %-*s", tab_width, "Flags:");
	printf("0x"); printf("%x\n", elf_header.e_flags);

	printf("  %-*s", tab_width, "Size of this header:");
	printf("%d (bytes)\n", elf_header.e_ehsize);

	printf("  %-*s", tab_width, "Size of Program header:");
	printf("%d (bytes)\n", elf_header.e_phentsize);

	printf("  %-*s", tab_width, "Number of program headers:");
	printf("%d\n", elf_header.e_phnum);

	printf("  %-*s", tab_width, "Size of Section headers:");
	printf("%d (bytes)\n", elf_header.e_shentsize);

	printf("  %-*s", tab_width, "Number of Section headers:");
	printf("%d\n", elf_header.e_shnum);

	printf("  %-*s", tab_width, "Section header string table index:");
	printf("%d\n", elf_header.e_shstrndx);
}

