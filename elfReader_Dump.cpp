#include "elfReader.h"


void ElfReader::printElfDumpProgram()
{
	int SectionNumber = elf_header.e_shnum;		
	//段表符号表的索引
	int str_index	  = elf_header.e_shstrndx;

	try{

		this->elf_section =(Elf32_Shdr*)(this->start + elf_header.e_shoff);
	}
	catch(exception& e)
	{
		cout << e.what() << "\n";
	}

	int tab_width = 17;
	
	//字符串表开始地址, 文件映射首地址为start
	char *str = start + elf_section[str_index].sh_offset;
	
	int sym_struct_size = sizeof(Elf32_Sym);
	Elf32_Sym *sym_addr = NULL;
	int sym_entry = 0;  //符号表的项数

	//默认字符表总是段表中的最后一个段
	//字符表首地址 strtab_addr
	char *strtab_addr = (char*)(start + elf_section[SectionNumber-1].sh_offset);
	
	Elf32_Addr prog_addr = 0;
	Elf32_Word prog_size = 0;
	
	int i;
	for(i=1; i<SectionNumber; i++)
	{

		if( ! strcmp(str + elf_section[i].sh_name, ".text"))
		{
			prog_addr = elf_section[i].sh_offset; // start + elf_section[i].sh_offset
			prog_size = elf_section[i].sh_size;
			break;  //查找到就跳出循环,总觉得好像直接.text总是在第二个段。。。
		}
	}
	
	if(i == SectionNumber)
	{
		printf("No .text Section\n");
		exit(-1);
	}
	
	/* ------------------开始从二进制到汇编的翻译--------------- */	
	printf("%-*s\n", tab_width, "Disassembly of section .text:\n");	


	//从符号表中查找是func段属性的段进行翻译
	//char *sub_prog_addr 函数的地址
	//unsigned int sub_prog_size 函数的字节数,10进制大小
	for(i=1; i<SectionNumber; i++)
	{

		if(strstr(str + elf_section[i].sh_name, "sym") != NULL)
		{
			sym_entry = elf_section[i].sh_size / sym_struct_size;
			sym_addr = (Elf32_Sym*)(this->start + elf_section[i].sh_offset);
			break;
		}
	}

	Elf32_Addr sub_prog_addr = 0;
	Elf32_Word sub_prog_size = 0;

	for(int j=0; j<sym_entry; j++)
	{
		if( STT_FUNC == ELF32_ST_TYPE(sym_addr[j].st_info)) //函数
		{
			sub_prog_size = sym_addr[j].st_size;
			sub_prog_addr = sym_addr[j].st_value;
			printf("\n%08x <%-s>:\n", sub_prog_addr, strtab_addr + sym_addr[j].st_name);
			printf("%08x 开始翻译啦。。。。。\n", sub_prog_size);

			Elf32_Addr sub_addr_offset = 0x0000000; //记录已翻译指令字节的个数 + 函数的偏移地址;
			sub_addr_offset += sub_prog_size;



		}
	}
		
	/* ------------------二进制到汇编的翻译结束----------------- */	
	

}



