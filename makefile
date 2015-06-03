CC=g++
OBJES=elfReader.o elfReader_header.o elfReader_Dump.o \
	  elfReader_RelSym.o elfReader_Section.o elfReader_Symbol.o
Flags= -Wall


all:elfReader
.PHONY:all clean

elfReader:$(OBJES)
	$(CC) -o $@ $^ 
elfReader.o:elfReader.cpp elfReader.h
	$(CC) -c $<
elfReader_header.o:elfReader_header.cpp elfReader.h
	$(CC) -c $<
elfReader_Dump.o:elfReader_Dump.cpp elfReader.h
	$(CC) -c $<
elfReader_RelSym.o:elfReader_RelSym.cpp elfReader.h
	$(CC) -c $<
elfReader_Section.o:elfReader_Section.cpp elfReader.h
	$(CC) -c $<
elfReader_Symbol.o:elfReader_Symbol.cpp elfReader.h
	$(CC) -c $<

clean:
	rm *.o




