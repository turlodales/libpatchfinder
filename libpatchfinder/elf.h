//
//  elf.h
//  libpatchfinder
//
//  Created by tihmstar on 21.02.26.
//

#ifndef elf_h
#define elf_h

#include <stdint.h>

/*
 * ELF definitions common to all 32-bit architectures.
 */

typedef uint32_t    Elf32_Addr;
typedef uint16_t    Elf32_Half;
typedef uint32_t    Elf32_Off;
typedef int32_t     Elf32_Sword;
typedef uint32_t    Elf32_Word;
typedef uint64_t    Elf32_Lword;

/*
 * ELF definitions common to all 64-bit architectures.
 */

typedef uint64_t    Elf64_Addr;
typedef uint16_t    Elf64_Half;
typedef uint64_t    Elf64_Off;
typedef int32_t     Elf64_Sword;
typedef int64_t     Elf64_Sxword;
typedef uint32_t    Elf64_Word;
typedef uint64_t    Elf64_Lword;
typedef uint64_t    Elf64_Xword;

#define     EI_NIDENT 16
#define     EI_MAG0   0
#define     EI_MAG1   1
#define     EI_MAG2   2
#define     EI_MAG3   3
#define     EI_CLASS   4
#define     EI_DATA   5
#define     EI_VERSION   6
#define     EI_OSABI   7
#define     EI_ABIVERSION   8
#define     EI_PAD   9
#define     EI_NIDENT   16
#define     ELFCLASSNONE   0
#define     ELFCLASS32   1
#define     ELFCLASS64   2
#define     ELFDATANONE   0
#define     ELFDATA2LSB   1
#define     ELFDATA2MSB   2
#define     EV_NONE   0
#define     EV_CURRENT   1
typedef struct {
        unsigned char   e_ident[EI_NIDENT];
        Elf32_Half      e_type;
        Elf32_Half      e_machine;
        Elf32_Word      e_version;
        Elf32_Addr      e_entry;
        Elf32_Off       e_phoff;
        Elf32_Off       e_shoff;
        Elf32_Word      e_flags;
        Elf32_Half      e_ehsize;
        Elf32_Half      e_phentsize;
        Elf32_Half      e_phnum;
        Elf32_Half      e_shentsize;
        Elf32_Half      e_shnum;
        Elf32_Half      e_shstrndx;
} Elf32_Ehdr;

typedef struct {
        unsigned char   e_ident[EI_NIDENT];
        Elf64_Half      e_type;
        Elf64_Half      e_machine;
        Elf64_Word      e_version;
        Elf64_Addr      e_entry;
        Elf64_Off       e_phoff;
        Elf64_Off       e_shoff;
        Elf64_Word      e_flags;
        Elf64_Half      e_ehsize;
        Elf64_Half      e_phentsize;
        Elf64_Half      e_phnum;
        Elf64_Half      e_shentsize;
        Elf64_Half      e_shnum;
        Elf64_Half      e_shstrndx;
} Elf64_Ehdr;

struct Elf_Ehdr {
    union {
        Elf64_Ehdr e64;
        Elf32_Ehdr e32;
    };
};


/** ELF program header */
typedef struct {
       Elf32_Word p_type;
       Elf32_Off p_offset;
       Elf32_Addr p_vaddr;
       Elf32_Addr p_paddr;
       Elf32_Word p_filesz;
       Elf32_Word p_memsz;
       Elf32_Word p_flags;
       Elf32_Word p_align;
} Elf32_Phdr;

typedef struct{
  Elf64_Word    p_type;
  Elf64_Word    p_flags;
  Elf64_Off     p_offset;
  Elf64_Addr    p_vaddr;
  Elf64_Addr    p_paddr;
  Elf64_Xword   p_filesz;
  Elf64_Xword   p_memsz;
  Elf64_Xword   p_align;
} Elf64_Phdr;

#define PT_NULL        0        /* Program header table entry unused */
#define PT_LOAD        1        /* Loadable program segment */
#define PT_DYNAMIC    2        /* Dynamic linking information */
#define PT_INTERP    3        /* Program interpreter */
#define PT_NOTE        4        /* Auxiliary information */
#define PT_SHLIB    5        /* Reserved */
#define PT_PHDR        6        /* Entry for header table itself */
#define PT_TLS        7        /* Thread-local storage segment */
#define PT_NUM        8        /* Number of defined types */
#define PT_LOOS        0x60000000    /* Start of OS-specific */
#define PT_GNU_EH_FRAME    0x6474e550    /* GCC .eh_frame_hdr segment */
#define PT_GNU_STACK    0x6474e551    /* Indicates stack executability */
#define PT_GNU_RELRO    0x6474e552    /* Read-only after relocation */
#define PT_LOSUNW    0x6ffffffa
#define PT_SUNWBSS    0x6ffffffa    /* Sun Specific segment */
#define PT_SUNWSTACK    0x6ffffffb    /* Stack segment */
#define PT_HISUNW    0x6fffffff
#define PT_HIOS        0x6fffffff    /* End of OS-specific */
#define PT_LOPROC    0x70000000    /* Start of processor-specific */
#define PT_HIPROC    0x7fffffff    /* End of processor-specific */

#define PF_X        (1 << 0)    /* Segment is executable */
#define PF_W        (1 << 1)    /* Segment is writable */
#define PF_R        (1 << 2)    /* Segment is readable */
#define PF_MASKOS    0x0ff00000    /* OS-specific */
#define PF_MASKPROC    0xf0000000    /* Processor-specific */

#endif /* elf_h */
