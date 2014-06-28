#include <windows.h>
#include <stdio.h>
 
void align(FILE *f, int size) {
    int pos = ftell(f);
    int aligned = (pos + size - 1) / size * size;
    for (; pos < aligned; ++pos) {
        fwrite("\0", 1, 1, f);
    }
}
 
IMAGE_DOS_HEADER dosh;
IMAGE_NT_HEADERS32 nth;
IMAGE_SECTION_HEADER sects[1];
IMAGE_OPTIONAL_HEADER32 oph;
IMAGE_FILE_HEADER fh;
 
int main(void) {
    strncpy((char *)&dosh.e_magic, "MZ", 2);
    dosh.e_cblp     = 0x90;
    dosh.e_cp       = 3;
    dosh.e_cparhdr  = 4;
    dosh.e_maxalloc = 0xffff;
    dosh.e_sp       = 0xb8;
    dosh.e_lfarlc   = 0x40;
    dosh.e_lfanew   = 0x80;
    strncpy((char *)&nth.Signature, "PE", 4);
    nth.FileHeader.Machine                          = 0x014c;
    nth.FileHeader.NumberOfSections                 = 1;
    nth.FileHeader.TimeDateStamp                    = 0x4da65f9b;
    nth.FileHeader.SizeOfOptionalHeader             = sizeof(nth.OptionalHeader);
    nth.FileHeader.Characteristics                  = 0x0102;
    nth.OptionalHeader.Magic                        = 0x010b;
    nth.OptionalHeader.MajorLinkerVersion           = 0x0a;
    nth.OptionalHeader.SizeOfCode                   = 0x0200;
    nth.OptionalHeader.AddressOfEntryPoint          = 0x1000;
    nth.OptionalHeader.BaseOfCode                   = 0x1000;
    nth.OptionalHeader.BaseOfData                   = 0x2000;
    nth.OptionalHeader.ImageBase                    = 0x400000;
    nth.OptionalHeader.SectionAlignment             = 0x1000;
    nth.OptionalHeader.FileAlignment                = 0x0200;
    nth.OptionalHeader.MajorOperatingSystemVersion  = 5;
    nth.OptionalHeader.MinorOperatingSystemVersion  = 1;
    nth.OptionalHeader.MajorSubsystemVersion        = 5;
    nth.OptionalHeader.MinorSubsystemVersion        = 1;
    nth.OptionalHeader.SizeOfImage                  = 0x2000;
    nth.OptionalHeader.SizeOfHeaders                = 0x0200;
    nth.OptionalHeader.Subsystem                    = 2;
    nth.OptionalHeader.SizeOfStackReserve           = 0x100000;
    nth.OptionalHeader.SizeOfStackCommit            = 0x001000;
    nth.OptionalHeader.SizeOfHeapReserve            = 0x100000;
    nth.OptionalHeader.SizeOfHeapCommit             = 0x001000;
    nth.OptionalHeader.NumberOfRvaAndSizes          = 16;
    strncpy((char *)sects[0].Name, ".text", 8);
    sects[0].Misc.VirtualSize   = 1;
    sects[0].VirtualAddress     = 0x1000;
    sects[0].SizeOfRawData      = 0x0200;
    sects[0].PointerToRawData   = 0x0200;
    sects[0].Characteristics    = 0x60000020;

    fh.NumberOfSections = 2;

    oph.SizeOfImage                     = 300;
    oph.Subsystem                       = 3;
    oph.DataDirectory[1].VirtualAddress = 0x00002000;
    oph.DataDirectory[1].Size           = 0x00001000;
 
    FILE *f = fopen("test.exe", "wb");
    fwrite(&dosh, sizeof(dosh), 1, f);
    BYTE dos_stub[] = { 0x0e, 0x1f, 0xba, 0x0e, 0x00, 0xb4, 0x09, 0xcd, 0x21, 0xb8, 0x01, 0x4c, 0xcd, 0x21 };
    fwrite(dos_stub, sizeof(dos_stub), 1, f);
    char dos_msg[] = "This program cannot be run in DOS mode.\r\r\n$";
    fwrite(dos_msg, sizeof(dos_msg), 1, f);
    align(f, 8);
    fwrite(&nth, sizeof(nth), 1, f);
    fwrite(sects, sizeof(sects), 1, f);
    align(f, nth.OptionalHeader.FileAlignment);
    BYTE text[] = { 0xc3 };
    fwrite(text, sizeof(text), 1, f);
    align(f, nth.OptionalHeader.FileAlignment);
    fclose(f);

    return 0;
}
