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
IMAGE_SECTION_HEADER sects[2];
IMAGE_FILE_HEADER fh;
IMAGE_IMPORT_DESCRIPTOR idt[2];
 
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
    nth.FileHeader.NumberOfSections                 = 2;
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
    nth.OptionalHeader.SizeOfImage                  = 0x3000;
    nth.OptionalHeader.SizeOfHeaders                = 0x0200;
    nth.OptionalHeader.Subsystem                    = 3;
    nth.OptionalHeader.SizeOfStackReserve           = 0x100000;
    nth.OptionalHeader.SizeOfStackCommit            = 0x001000;
    nth.OptionalHeader.SizeOfHeapReserve            = 0x100000;
    nth.OptionalHeader.SizeOfHeapCommit             = 0x001000;
    nth.OptionalHeader.NumberOfRvaAndSizes          = 16;

    nth.OptionalHeader.DataDirectory[1].VirtualAddress = 0x00002000;
    nth.OptionalHeader.DataDirectory[1].Size           = 0x00001000;

    strncpy((char *)sects[0].Name, ".text", 8);
    sects[0].Misc.VirtualSize   = 0x34;
    sects[0].VirtualAddress     = 0x1000;
    sects[0].SizeOfRawData      = 0x0200;
    sects[0].PointerToRawData   = 0x0200;
    sects[0].Characteristics    = 0x60000020;

    strncpy((char *)sects[1].Name, ".idata", 16);
    sects[1].Misc.VirtualSize   = 0x54;
    sects[1].VirtualAddress     = 0x2000;
    sects[1].SizeOfRawData      = 0x0200;
    sects[1].PointerToRawData   = 0x0400;
    sects[1].Characteristics    = 0xc0300040;

    idt[0].OriginalFirstThunk = 0x2028;
    idt[0].Name               = 0x2048;
    idt[0].FirstThunk         = 0x2030;
    /* strcpy((char*)idt[0].Name, "prtnum"); */

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
    BYTE text[] = { 0x6a, 0x41, 0xff, 0x15, 0x30, 0x20, 0x40, 0x00, 0x58, 0xc3 };
    fwrite(text, sizeof(text), 1, f);
    align(f, nth.OptionalHeader.FileAlignment);

    fwrite(&idt, sizeof(idt), 1, f);

    DWORD ilt[] = { 0x2038, 0 };
    fwrite(ilt, sizeof(ilt), 1, f);

    DWORD iat[] = { 0x2038, 0 };
    fwrite(iat, sizeof(iat), 1, f);

    WORD hint = 0;
    const char *func = "putchar";
    fwrite(&hint, sizeof(hint), 1, f);
    fwrite(func, strlen(func) + 1, 1, f);
    fwrite(&hint, sizeof(hint), 1, f);

    DWORD unused[] = { 0x2000 };
    fwrite(unused, sizeof(unused), 1, f);

    const char *dll = "msvcrt.dll";
    fwrite(dll, strlen(dll) + 1, 1, f);

    align(f, nth.OptionalHeader.FileAlignment);

    fclose(f);

    return 0;
}
