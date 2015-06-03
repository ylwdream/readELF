#include "elfReader.h"

void ElfReader::printElfSection()
{
	
	//段表的总个数
	int SectionNumber = elf_header.e_shnum;		
	//段表符号表的索引
	int str_index	  = elf_header.e_shstrndx;
	//段表的开始地址	
	//	Elf32_Shdr *SectionAddr = (Elf32_Shdr*)(start + elf_header.e_shoff); 


	try{

		//this->elf_section = new Elf32_Shdr[SectionNumber];
		this->elf_section =(Elf32_Shdr*)(this->start + elf_header.e_shoff);
	}
	catch(exception& e)
	{
		cout << e.what() << "\n";
	}

	//memcpy(elf_section, (start+elf_header.e_shoff), SectionSize*SectionNumber);


	int tab_width = 17;

	printf("There are %d section headers, starting at offset 0x%x:\n\n", SectionNumber, elf_header.e_shoff);
	
	printf("Section Headers:\n");

	printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
	printf("  [ 0]                   NULL            00000000 000000 000000 00      0   0  0\n");
	
	//字符串表开始地址, 文件映射首地址为start
	char *str = start + elf_section[str_index].sh_offset;

	for(int i=1; i<SectionNumber; i++)
	{

		printf("  [%2d] %-*s ", i,tab_width, str + elf_section[i].sh_name);

		
		tab_width = 16;
		switch(elf_section[i].sh_type)
		{
			case 0:
				printf("%-*s",tab_width, "NULL");
				break;
			case 1:
				printf("%-*s",tab_width, "PROGRAMS");
				break;
			case 2:
				printf("%-*s",tab_width, "SYMTAB");
				break;
			case 3:
				printf("%-*s",tab_width, "STRTAB");
				break;
			case 4:
				printf("%-*s",tab_width, "RELA");
				break;
			case 5:
				printf("%-*s",tab_width, "SHT_HASH");
				break;
			case 6:
				printf("%-*s",tab_width, "DYNAMIC");
				break;
			case 7:
				printf("%-*s",tab_width, "DOTE");
				break;
			case 8:
				printf("%-*s",tab_width, "DOBITS");
				break;
			case 9:
				printf("%-*s",tab_width, "REL");
				break;
			case 10:
				printf("%-*s",tab_width, "SHLIB");
				break;
			case 11:
				printf("%-*s",tab_width, "DYNSYM");
				break;
			case 14:
				printf("%-*s",tab_width, "INIT_ARRAY");
				break;
			case 15:
				printf("%-*s",tab_width, "FINI_ARRAY");
				break;
			case 16:
				printf("%-*s",tab_width, "PREINIT_ARRAY");
					break;
			case 17:
				printf("%-*s",tab_width, "GROUP");
				break;
			case 18:
				printf("%-*s",tab_width, "SYMTAB_SHNDX");
				break;
			case 19:
				printf("%-*s",tab_width, "NUM");
				break;
			case 20:
				printf("%-*s",tab_width, "LOOS");
				break;
			case SHT_GNU_verdef:
				printf("%-*s",tab_width, "VERDEF");
				break;
			case SHT_GNU_verneed:
				printf("%-*s",tab_width, "VERNEED");
				break;
			case SHT_GNU_versym:
				printf("%-*s",tab_width, "VERSYM");
				break;
				
		}			
		printf("%08x ", elf_section[i].sh_addr);
		printf("%06x ", elf_section[i].sh_offset);
		printf("%06x ", elf_section[i].sh_size);
		printf("%02x  ",elf_section[i].sh_entsize);

		tab_width = 2;
		switch(elf_section[i].sh_flags)
		{
			case 1:
				printf("%*s", tab_width, "W");
				break;
			case 2:
				printf("%*s", tab_width, "A");
				break;
			case 3:
				printf("%*s", tab_width, "WA");
				break;
			case 4:
				printf("%*s", tab_width, "X");
				break;
			case 5:
				printf("%*s", tab_width, "WX");
				break;
			case 6:
				printf("%*s", tab_width, "AX");
				break;
			case 7:
				printf("%*s", tab_width, "WAX");
				break;
			case 16:
				printf("%*s", tab_width, "M");
				break;
			case 17:
				printf("%*s", tab_width, "MW");
				break;
			case 18:
				printf("%*s", tab_width, "MA");
				break;
			case 20:
				printf("%*s", tab_width, "ME");
				break;
			case 48:
				printf("%-*s",tab_width, "MS");
				break;
			case SHF_INFO_LINK:
				printf("%*s", tab_width, "S");
				break;

			default:
				printf("%*s", tab_width, "  ");
				break;

		}
		printf(" ");
		
		printf("%2d ", elf_section[i].sh_link);
		printf("%3d ", elf_section[i].sh_info);
		
		printf("%2d ", elf_section[i].sh_addralign);

		tab_width = 17;
		printf("\n");
	}
	
	printf("Key to Flags:\n W (write), A (alloc), X (execute), M (merge), S (strings) \n I (info), L (link order), G (group), x (unknown) \n O (extra OS processing required) o (OS specific), p (processor specific)\n\n");
}

