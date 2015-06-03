#include "elfReader.h"

void ElfReader::printElfRelSym()
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
	
	//段表字符串表开始地址, 文件映射首地址为start
	char *str = start + elf_section[str_index].sh_offset;

	int rel_struct_size = sizeof(Elf32_Rel);
	
	int tab_width = 8;

	Elf32_Rel *rel_addr = NULL;
	Elf32_Sym *sym_addr = NULL;
	int rel_entry = 0;  //符号表的项数

	//默认字符表总是段表中的最后一个段
	//字符表首地址 strtab_addr
	//默认符号表在倒数第二个段
	char *strtab_addr = (char*)(this->start + elf_section[SectionNumber-1].sh_offset);
	sym_addr = (Elf32_Sym *)(this->start + elf_section[SectionNumber-2].sh_offset);

	for(int i=1; i<SectionNumber; i++)
	{

		if(strstr(str + elf_section[i].sh_name, ".rel") != NULL)
		{
			rel_entry = elf_section[i].sh_size / rel_struct_size;
			printf("Relocation section '%s' at offset 0x%x contains %d entries:\n", str + elf_section[i].sh_name, elf_section[i].sh_offset, rel_entry);
		
			printf("Offset     Info    Type            Sym.Value  Sym. Name\n");
			rel_addr = (Elf32_Rel *)(this->start + elf_section[i].sh_offset);	
			for(int j=0; j<rel_entry; j++)
			{
				printf("%08x  %08x ",rel_addr[j].r_offset, rel_addr[j].r_info);
				
				tab_width = 17;
				switch(ELF32_R_TYPE(rel_addr[j].r_info))
				{
					case 1:
						printf("%-*s", tab_width, "R_386_32");
						break;
					case 2:
						printf("%-*s", tab_width, "R_386_PC32");
						break;
					case 6:
						printf("%-*s", tab_width, "R_386_GLOB_DAT");
						break;
					case 7:
						printf("%-*s", tab_width, "R_386_JUMP_SLOT");
						break;
				}

				tab_width = 10;

				printf("%08x  ", sym_addr[ELF32_R_SYM(rel_addr[j].r_info)].st_value);
				if( ELF32_ST_TYPE(sym_addr[ELF32_R_SYM(rel_addr[j].r_info)].st_info) == STT_SECTION)
				{
					int index = sym_addr[ELF32_R_SYM(rel_addr[j].r_info)].st_shndx;
					printf("%-*s \n", tab_width, start + elf_section[elf_header.e_shstrndx].sh_offset + elf_section[index].sh_name);
				}
				else
				{
					printf("%-*s \n",tab_width, strtab_addr + sym_addr[ELF32_R_SYM(rel_addr[j].r_info)].st_name);			  
					printf("\n");
				}
				tab_width  = 8;

			}
		}
	}
}

