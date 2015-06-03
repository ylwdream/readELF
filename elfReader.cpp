
#include "elfReader.h"

bool ElfReader::readFile(const char *filename)
{

    struct stat sb;
    fd = open(filename, O_RDONLY);
    fstat(fd, &sb); /* 取得文件大小 */
    file_size = sb.st_size;
    start = (char*)mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(start == MAP_FAILED) /* 判断是否映射成功 */
        return false;

	return true;
}

ElfReader::ElfReader(const char *filename)
{
	if( !readFile(filename))
	{
		printf("can not mmap the file %s\n", filename);
		exit(0);
	}

	memcpy(&elf_header, this->start, ELF_LENHT);
}

ElfReader::~ElfReader()
{
    munmap(start, file_size); /* 解除映射 */
    close(fd);

}


unsigned int ElfReader::getFileSize() const
{
	return this->file_size;
}


int main(int argc, char *argv[])
{
	ElfReader *read = NULL;

	if(argc <= 1)
	{
		printf("input the filename!\n");
		exit(0);
	}

	if(argc == 2)
	{
		printf("please usage:\n");
		printf("-h filename \t dump the file header\n");
		printf("-s filename \t dump the Section\n");
		exit(0);
	}
	
	if(argc == 3)
	{
		read = new ElfReader(argv[2]);
		
		if(!strcmp(argv[1], "-h"))
			read->printElfHeader();
		if(!strcmp(argv[1], "-S"))
			read->printElfSection();
		if(!strcmp(argv[1], "-s"))
			read->printElfSymbol();
		if(!strcmp(argv[1], "-r"))
			read->printElfRelSym();
		if(!strcmp(argv[1], "-d"))
			read->printElfDumpProgram();
				
	}

	return 0;
}








