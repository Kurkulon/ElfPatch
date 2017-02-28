#ifndef ELF_H__23_02_2016__22_59
#define ELF_H__23_02_2016__22_59

#pragma once


#include "types.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// Attention! Platform depended definitions.
typedef u16	Elf_Half;
typedef u32	Elf_Word;
typedef i32	Elf_Sword;
typedef u64	Elf_Xword;
typedef i64	Elf_Sxword;

typedef u32	Elf32_Addr;
typedef u32	Elf32_Off;
typedef u64	Elf64_Addr;
typedef u64	Elf64_Off;

#define Elf32_Half Elf_Half
#define Elf64_Half Elf_Half
#define Elf32_Word Elf_Word
#define Elf64_Word Elf_Word
#define Elf32_Sword Elf_Sword
#define Elf64_Sword Elf_Sword

///////////////////////
// ELF Header Constants

// File type
#define ET_NONE        0
#define ET_REL         1
#define ET_EXEC        2
#define ET_DYN         3
#define ET_CORE        4
#define ET_LOOS   0xFE00
#define ET_HIOS   0xFEFF
#define ET_LOPROC 0xFF00
#define ET_HIPROC 0xFFFF


#define EM_NONE          0   // No machine
#define EM_M32           1   // AT&T WE 32100
#define EM_SPARC         2   // SUN SPARC
#define EM_386           3   // Intel 80386
#define EM_68K           4   // Motorola m68k family
#define EM_88K           5   // Motorola m88k family
#define EM_486           6   // Intel 80486// Reserved for future use
#define EM_860           7   // Intel 80860
#define EM_MIPS          8   // MIPS R3000 (officially, big-endian only)
#define EM_S370          9   // IBM System/370
#define EM_MIPS_RS3_LE   10  // MIPS R3000 little-endian (Oct 4 1999 Draft) Deprecated
#define EM_res011        11  // Reserved
#define EM_res012        12  // Reserved
#define EM_res013        13  // Reserved
#define EM_res014        14  // Reserved
#define EM_PARISC        15  // HPPA
#define EM_res016        16  // Reserved
#define EM_VPP550        17  // Fujitsu VPP500
#define EM_SPARC32PLUS   18  // Sun's "v8plus"
#define EM_960           19  // Intel 80960
#define EM_PPC           20  // PowerPC
#define EM_PPC64         21  // 64-bit PowerPC
#define EM_S390          22  // IBM S/390
#define EM_SPU           23  // Sony/Toshiba/IBM SPU
#define EM_res024        24  // Reserved
#define EM_res025        25  // Reserved
#define EM_res026        26  // Reserved
#define EM_res027        27  // Reserved
#define EM_res028        28  // Reserved
#define EM_res029        29  // Reserved
#define EM_res030        30  // Reserved
#define EM_res031        31  // Reserved
#define EM_res032        32  // Reserved
#define EM_res033        33  // Reserved
#define EM_res034        34  // Reserved
#define EM_res035        35  // Reserved
#define EM_V800          36  // NEC V800 series
#define EM_FR20          37  // Fujitsu FR20
#define EM_RH32          38  // TRW RH32
#define EM_MCORE         39  // Motorola M*Core // May also be taken by Fujitsu MMA
#define EM_RCE           39  // Old name for MCore
#define EM_ARM           40  // ARM
#define EM_OLD_ALPHA     41  // Digital Alpha
#define EM_SH            42  // Renesas (formerly Hitachi) / SuperH SH
#define EM_SPARCV9       43  // SPARC v9 64-bit
#define EM_TRICORE       44  // Siemens Tricore embedded processor
#define EM_ARC           45  // ARC Cores
#define EM_H8_300        46  // Renesas (formerly Hitachi) H8/300
#define EM_H8_300H       47  // Renesas (formerly Hitachi) H8/300H
#define EM_H8S           48  // Renesas (formerly Hitachi) H8S
#define EM_H8_500        49  // Renesas (formerly Hitachi) H8/500
#define EM_IA_64         50  // Intel IA-64 Processor
#define EM_MIPS_X        51  // Stanford MIPS-X
#define EM_COLDFIRE      52  // Motorola Coldfire
#define EM_68HC12        53  // Motorola M68HC12
#define EM_MMA           54  // Fujitsu Multimedia Accelerator
#define EM_PCP           55  // Siemens PCP
#define EM_NCPU          56  // Sony nCPU embedded RISC processor
#define EM_NDR1          57  // Denso NDR1 microprocesspr
#define EM_STARCORE      58  // Motorola Star*Core processor
#define EM_ME16          59  // Toyota ME16 processor
#define EM_ST100         60  // STMicroelectronics ST100 processor
#define EM_TINYJ         61  // Advanced Logic Corp. TinyJ embedded processor
#define EM_X86_64        62  // Advanced Micro Devices X86-64 processor
#define EM_PDSP          63  // Sony DSP Processor
#define EM_PDP10         64  // Digital Equipment Corp. PDP-10
#define EM_PDP11         65  // Digital Equipment Corp. PDP-11
#define EM_FX66          66  // Siemens FX66 microcontroller
#define EM_ST9PLUS       67  // STMicroelectronics ST9+ 8/16 bit microcontroller
#define EM_ST7           68  // STMicroelectronics ST7 8-bit microcontroller
#define EM_68HC16        69  // Motorola MC68HC16 Microcontroller
#define EM_68HC11        70  // Motorola MC68HC11 Microcontroller
#define EM_68HC08        71  // Motorola MC68HC08 Microcontroller
#define EM_68HC05        72  // Motorola MC68HC05 Microcontroller
#define EM_SVX           73  // Silicon Graphics SVx
#define EM_ST19          74  // STMicroelectronics ST19 8-bit cpu
#define EM_VAX           75  // Digital VAX
#define EM_CRIS          76  // Axis Communications 32-bit embedded processor
#define EM_JAVELIN       77  // Infineon Technologies 32-bit embedded cpu
#define EM_FIREPATH      78  // Element 14 64-bit DSP processor
#define EM_ZSP           79  // LSI Logic's 16-bit DSP processor
#define EM_MMIX          80  // Donald Knuth's educational 64-bit processor
#define EM_HUANY         81  // Harvard's machine-independent format
#define EM_PRISM         82  // SiTera Prism
#define EM_AVR           83  // Atmel AVR 8-bit microcontroller
#define EM_FR30          84  // Fujitsu FR30
#define EM_D10V          85  // Mitsubishi D10V
#define EM_D30V          86  // Mitsubishi D30V
#define EM_V850          87  // NEC v850
#define EM_M32R          88  // Renesas M32R (formerly Mitsubishi M32R)
#define EM_MN10300       89  // Matsushita MN10300
#define EM_MN10200       90  // Matsushita MN10200
#define EM_PJ            91  // picoJava
#define EM_OPENRISC      92  // OpenRISC 32-bit embedded processor
#define EM_ARC_A5        93  // ARC Cores Tangent-A5
#define EM_XTENSA        94  // Tensilica Xtensa Architecture
#define EM_VIDEOCORE     95  // Alphamosaic VideoCore processor
#define EM_TMM_GPP       96  // Thompson Multimedia General Purpose Processor
#define EM_NS32K         97  // National Semiconductor 32000 series
#define EM_TPC           98  // Tenor Network TPC processor
#define EM_SNP1K         99  // Trebia SNP 1000 processor
#define EM_ST200         100 // STMicroelectronics ST200 microcontroller
#define EM_IP2K          101 // Ubicom IP2022 micro controller
#define EM_MAX           102 // MAX Processor
#define EM_CR            103 // National Semiconductor CompactRISC
#define EM_F2MC16        104 // Fujitsu F2MC16
#define EM_MSP430        105 // TI msp430 micro controller
#define EM_BLACKFIN      106 // ADI Blackfin
#define EM_SE_C33        107 // S1C33 Family of Seiko Epson processors
#define EM_SEP           108 // Sharp embedded microprocessor
#define EM_ARCA          109 // Arca RISC Microprocessor
#define EM_UNICORE       110 // Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University
#define EM_EXCESS        111 // eXcess: 16/32/64-bit configurable embedded CPU
#define EM_DXP           112 // Icera Semiconductor Inc. Deep Execution Processor
#define EM_ALTERA_NIOS2  113 // Altera Nios II soft-core processor
#define EM_CRX           114 // National Semiconductor CRX
#define EM_XGATE         115 // Motorola XGATE embedded processor
#define EM_C166          116 // Infineon C16x/XC16x processor
#define EM_M16C          117 // Renesas M16C series microprocessors
#define EM_DSPIC30F      118 // Microchip Technology dsPIC30F Digital Signal Controller
#define EM_CE            119 // Freescale Communication Engine RISC core
#define EM_M32C          120 // Renesas M32C series microprocessors
#define EM_res121        121 // Reserved
#define EM_res122        122 // Reserved
#define EM_res123        123 // Reserved
#define EM_res124        124 // Reserved
#define EM_res125        125 // Reserved
#define EM_res126        126 // Reserved
#define EM_res127        127 // Reserved
#define EM_res128        128 // Reserved
#define EM_res129        129 // Reserved
#define EM_res130        130 // Reserved
#define EM_TSK3000       131 // Altium TSK3000 core
#define EM_RS08          132 // Freescale RS08 embedded processor
#define EM_res133        133 // Reserved
#define EM_ECOG2         134 // Cyan Technology eCOG2 microprocessor
#define EM_SCORE         135 // Sunplus Score
#define EM_SCORE7        135 // Sunplus S+core7 RISC processor
#define EM_DSP24         136 // New Japan Radio (NJR) 24-bit DSP Processor
#define EM_VIDEOCORE3    137 // Broadcom VideoCore III processor
#define EM_LATTICEMICO32 138 // RISC processor for Lattice FPGA architecture
#define EM_SE_C17        139 // Seiko Epson C17 family
#define EM_TI_C6000      140 // Texas Instruments TMS320C6000 DSP family
#define EM_TI_C2000      141 // Texas Instruments TMS320C2000 DSP family
#define EM_TI_C5500      142 // Texas Instruments TMS320C55x DSP family
#define EM_res143        143 // Reserved
#define EM_res144        144 // Reserved
#define EM_res145        145 // Reserved
#define EM_res146        146 // Reserved
#define EM_res147        147 // Reserved
#define EM_res148        148 // Reserved
#define EM_res149        149 // Reserved
#define EM_res150        150 // Reserved
#define EM_res151        151 // Reserved
#define EM_res152        152 // Reserved
#define EM_res153        153 // Reserved
#define EM_res154        154 // Reserved
#define EM_res155        155 // Reserved
#define EM_res156        156 // Reserved
#define EM_res157        157 // Reserved
#define EM_res158        158 // Reserved
#define EM_res159        159 // Reserved
#define EM_MMDSP_PLUS    160 // STMicroelectronics 64bit VLIW Data Signal Processor
#define EM_CYPRESS_M8C   161 // Cypress M8C microprocessor
#define EM_R32C          162 // Renesas R32C series microprocessors
#define EM_TRIMEDIA      163 // NXP Semiconductors TriMedia architecture family
#define EM_QDSP6         164 // QUALCOMM DSP6 Processor
#define EM_8051          165 // Intel 8051 and variants
#define EM_STXP7X        166 // STMicroelectronics STxP7x family
#define EM_NDS32         167 // Andes Technology compact code size embedded RISC processor family
#define EM_ECOG1         168 // Cyan Technology eCOG1X family
#define EM_ECOG1X        168 // Cyan Technology eCOG1X family
#define EM_MAXQ30        169 // Dallas Semiconductor MAXQ30 Core Micro-controllers
#define EM_XIMO16        170 // New Japan Radio (NJR) 16-bit DSP Processor
#define EM_MANIK         171 // M2000 Reconfigurable RISC Microprocessor
#define EM_CRAYNV2       172 // Cray Inc. NV2 vector architecture
#define EM_RX            173 // Renesas RX family
#define EM_METAG         174 // Imagination Technologies META processor architecture
#define EM_MCST_ELBRUS   175 // MCST Elbrus general purpose hardware architecture
#define EM_ECOG16        176 // Cyan Technology eCOG16 family
#define EM_CR16          177 // National Semiconductor CompactRISC 16-bit processor
#define EM_ETPU          178 // Freescale Extended Time Processing Unit
#define EM_SLE9X         179 // Infineon Technologies SLE9X core
#define EM_L1OM          180 // Intel L1OM
#define EM_INTEL181      181 // Reserved by Intel
#define EM_INTEL182      182 // Reserved by Intel
#define EM_res183        183 // Reserved by ARM
#define EM_res184        184 // Reserved by ARM
#define EM_AVR32         185 // Atmel Corporation 32-bit microprocessor family
#define EM_STM8          186 // STMicroeletronics STM8 8-bit microcontroller
#define EM_TILE64        187 // Tilera TILE64 multicore architecture family
#define EM_TILEPRO       188 // Tilera TILEPro multicore architecture family
#define EM_MICROBLAZE    189 // Xilinx MicroBlaze 32-bit RISC soft processor core
#define EM_CUDA          190 // NVIDIA CUDA architecture 
#define EM_TILEGX        191 // Tilera TILE-Gx multicore architecture family
#define EM_CLOUDSHIELD   192 // CloudShield architecture family
#define EM_COREA_1ST     193 // KIPO-KAIST Core-A 1st generation processor family
#define EM_COREA_2ND     194 // KIPO-KAIST Core-A 2nd generation processor family
#define EM_ARC_COMPACT2  195 // Synopsys ARCompact V2
#define EM_OPEN8         196 // Open8 8-bit RISC soft processor core
#define EM_RL78          197 // Renesas RL78 family
#define EM_VIDEOCORE5    198 // Broadcom VideoCore V processor
#define EM_78KOR         199 // Renesas 78KOR family
#define EM_56800EX       200 // Freescale 56800EX Digital Signal Controller (DSC)
#define EM_BA1           201 // Beyond BA1 CPU architecture
#define EM_BA2           202 // Beyond BA2 CPU architecture
#define EM_XCORE         203 // XMOS xCORE processor family
#define EM_MCHP_PIC      204 // Microchip 8-bit PIC(r) family
#define EM_INTEL205      205 // Reserved by Intel
#define EM_INTEL206      206 // Reserved by Intel
#define EM_INTEL207      207 // Reserved by Intel
#define EM_INTEL208      208 // Reserved by Intel
#define EM_INTEL209      209 // Reserved by Intel
#define EM_KM32          210 // KM211 KM32 32-bit processor
#define EM_KMX32         211 // KM211 KMX32 32-bit processor
#define EM_KMX16         212 // KM211 KMX16 16-bit processor
#define EM_KMX8          213 // KM211 KMX8 8-bit processor
#define EM_KVARC         214 // KM211 KVARC processor
#define EM_CDP           215 // Paneve CDP architecture family
#define EM_COGE          216 // Cognitive Smart Memory Processor
#define EM_COOL          217 // iCelero CoolEngine
#define EM_NORC          218 // Nanoradio Optimized RISC
#define EM_CSR_KALIMBA   219 // CSR Kalimba architecture family
#define EM_Z80           220 // Zilog Z80
#define EM_VISIUM        221 // Controls and Data Services VISIUMcore processor
#define EM_FT32          222 // FTDI Chip FT32 high performance 32-bit RISC architecture
#define EM_MOXIE         223 // Moxie processor family
#define EM_AMDGPU        224 // AMD GPU architecture
#define EM_RISCV         243 // RISC-V
#define EM_LANAI         244 // Lanai processor
#define EM_CEVA          245 // CEVA Processor Architecture Family
#define EM_CEVA_X2       246 // CEVA X2 Processor Family
#define EM_BPF           247 // Linux BPF – in-kernel virtual machine

// File version
#define EV_NONE    0
#define EV_CURRENT 1

// Identification index
#define EI_MAG0        0
#define EI_MAG1        1
#define EI_MAG2        2
#define EI_MAG3        3
#define EI_CLASS       4
#define EI_DATA        5
#define EI_VERSION     6
#define EI_OSABI       7
#define EI_ABIVERSION  8
#define EI_PAD         9
#define EI_NIDENT     16

// Magic number
#define ELFMAG0 0x7F
#define ELFMAG1  'E'
#define ELFMAG2  'L'
#define ELFMAG3  'F'

// File class
#define ELFCLASSNONE 0
#define ELFCLASS32   1
#define ELFCLASS64   2

// Encoding
#define ELFDATANONE 0
#define ELFDATA2LSB 1
#define ELFDATA2MSB 2

// OS extensions
#define ELFOSABI_NONE     0 // No extensions or unspecified
#define ELFOSABI_HPUX     1 // Hewlett-Packard HP-UX
#define ELFOSABI_NETBSD   2 // NetBSD
#define ELFOSABI_LINUX    3 // Linux
#define ELFOSABI_SOLARIS  6 // Sun Solaris
#define ELFOSABI_AIX      7 // AIX
#define ELFOSABI_IRIX     8 // IRIX
#define ELFOSABI_FREEBSD  9 // FreeBSD
#define ELFOSABI_TRU64   10 // Compaq TRU64 UNIX
#define ELFOSABI_MODESTO 11 // Novell Modesto
#define ELFOSABI_OPENBSD 12 // Open BSD
#define ELFOSABI_OPENVMS 13 // Open VMS
#define ELFOSABI_NSK     14 // Hewlett-Packard Non-Stop Kernel
#define ELFOSABI_AROS    15 // Amiga Research OS
#define ELFOSABI_FENIXOS 16 // The FenixOS highly scalable multi-core OS
//                       64-255 Architecture-specific value range


// ELF file header
struct Elf32_Ehdr {
    unsigned char e_ident[EI_NIDENT];
    Elf_Half    e_type;
    Elf_Half    e_machine;
    Elf_Word    e_version;
    Elf32_Addr  e_entry;
    Elf32_Off   e_phoff;
    Elf32_Off   e_shoff;
    Elf_Word    e_flags;
    Elf_Half    e_ehsize;
    Elf_Half    e_phentsize;
    Elf_Half    e_phnum;
    Elf_Half    e_shentsize;
    Elf_Half    e_shnum;
    Elf_Half    e_shstrndx;
};

struct Elf64_Ehdr {
    unsigned char e_ident[EI_NIDENT];
    Elf_Half    e_type;
    Elf_Half    e_machine;
    Elf_Word    e_version;
    Elf64_Addr  e_entry;
    Elf64_Off   e_phoff;
    Elf64_Off   e_shoff;
    Elf_Word    e_flags;
    Elf_Half    e_ehsize;
    Elf_Half    e_phentsize;
    Elf_Half    e_phnum;
    Elf_Half    e_shentsize;
    Elf_Half    e_shnum;
    Elf_Half    e_shstrndx;
};


// Section header
struct Elf32_Shdr {
    Elf_Word   sh_name;
    Elf_Word   sh_type;
    Elf_Word   sh_flags;
    Elf32_Addr sh_addr;
    Elf32_Off  sh_offset;
    Elf_Word   sh_size;
    Elf_Word   sh_link;
    Elf_Word   sh_info;
    Elf_Word   sh_addralign;
    Elf_Word   sh_entsize;
};

struct Elf64_Shdr {
    Elf_Word   sh_name;
    Elf_Word   sh_type;
    Elf_Xword  sh_flags;
    Elf64_Addr sh_addr;
    Elf64_Off  sh_offset;
    Elf_Xword  sh_size;
    Elf_Word   sh_link;
    Elf_Word   sh_info;
    Elf_Xword  sh_addralign;
    Elf_Xword  sh_entsize;
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static struct class_table_t {
    const char  key;
    const char* str;
} class_table [] = 
{
    { ELFCLASS32, "ELF32" },
    { ELFCLASS64, "ELF64" },
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static struct endian_table_t {
    const char  key;
    const char* str;
} endian_table [] = 
{
    { ELFDATANONE, "None"          },
    { ELFDATA2LSB, "Little endian" },
    { ELFDATA2MSB, "Big endian"    },
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static struct version_table_t {
    const Elf64_Word key;
    const char*      str;
} version_table [] = 
{
    { EV_NONE   , "None"    },
    { EV_CURRENT, "Current" },
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static struct type_table_t {
    const Elf32_Half key;
    const char*      str;
} type_table [] = 
{
    { ET_NONE, "No file type"       },
    { ET_REL , "Relocatable file"   },
    { ET_EXEC, "Executable file"    },
    { ET_DYN , "Shared object file" },
    { ET_CORE, "Core file"          },
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static struct machine_table_t {
    const Elf64_Half key;
    const char*      str;
} machine_table [] = 
{
    { EM_NONE         , "No machine"                                                              },
    { EM_M32          , "AT&T WE 32100"                                                           },
    { EM_SPARC        , "SUN SPARC"                                                               },
    { EM_386          , "Intel 80386"                                                             },
    { EM_68K          , "Motorola m68k family"                                                    },
    { EM_88K          , "Motorola m88k family"                                                    },
    { EM_486          , "Intel 80486// Reserved for future use"                                   },
    { EM_860          , "Intel 80860"                                                             },
    { EM_MIPS         , "MIPS R3000 (officially, big-endian only)"                                },
    { EM_S370         , "IBM System/370"                                                          },
    { EM_MIPS_RS3_LE  , "MIPS R3000 little-endian (Oct 4 1999 Draft) Deprecated"                  },
    { EM_res011       , "Reserved"                                                                },
    { EM_res012       , "Reserved"                                                                },
    { EM_res013       , "Reserved"                                                                },
    { EM_res014       , "Reserved"                                                                },
    { EM_PARISC       , "HPPA"                                                                    },
    { EM_res016       , "Reserved"                                                                },
    { EM_VPP550       , "Fujitsu VPP500"                                                          },
    { EM_SPARC32PLUS  , "Sun's v8plus"                                                            },
    { EM_960          , "Intel 80960"                                                             },
    { EM_PPC          , "PowerPC"                                                                 },
    { EM_PPC64        , "64-bit PowerPC"                                                          },
    { EM_S390         , "IBM S/390"                                                               },
    { EM_SPU          , "Sony/Toshiba/IBM SPU"                                                    },
    { EM_res024       , "Reserved"                                                                },
    { EM_res025       , "Reserved"                                                                },
    { EM_res026       , "Reserved"                                                                },
    { EM_res027       , "Reserved"                                                                },
    { EM_res028       , "Reserved"                                                                },
    { EM_res029       , "Reserved"                                                                },
    { EM_res030       , "Reserved"                                                                },
    { EM_res031       , "Reserved"                                                                },
    { EM_res032       , "Reserved"                                                                },
    { EM_res033       , "Reserved"                                                                },
    { EM_res034       , "Reserved"                                                                },
    { EM_res035       , "Reserved"                                                                },
    { EM_V800         , "NEC V800 series"                                                         },
    { EM_FR20         , "Fujitsu FR20"                                                            },
    { EM_RH32         , "TRW RH32"                                                                },
    { EM_MCORE        , "Motorola M*Core // May also be taken by Fujitsu MMA"                     },
 //   { EM_RCE          , "Old name for MCore"                                                      },
    { EM_ARM          , "ARM"                                                                     },
    { EM_OLD_ALPHA    , "Digital Alpha"                                                           },
    { EM_SH           , "Renesas (formerly Hitachi) / SuperH SH"                                  },
    { EM_SPARCV9      , "SPARC v9 64-bit"                                                         },
    { EM_TRICORE      , "Siemens Tricore embedded processor"                                      },
    { EM_ARC          , "ARC Cores"                                                               },
    { EM_H8_300       , "Renesas (formerly Hitachi) H8/300"                                       },
    { EM_H8_300H      , "Renesas (formerly Hitachi) H8/300H"                                      },
    { EM_H8S          , "Renesas (formerly Hitachi) H8S"                                          },
    { EM_H8_500       , "Renesas (formerly Hitachi) H8/500"                                       },
    { EM_IA_64        , "Intel IA-64 Processor"                                                   },
    { EM_MIPS_X       , "Stanford MIPS-X"                                                         },
    { EM_COLDFIRE     , "Motorola Coldfire"                                                       },
    { EM_68HC12       , "Motorola M68HC12"                                                        },
    { EM_MMA          , "Fujitsu Multimedia Accelerator"                                          },
    { EM_PCP          , "Siemens PCP"                                                             },
    { EM_NCPU         , "Sony nCPU embedded RISC processor"                                       },
    { EM_NDR1         , "Denso NDR1 microprocesspr"                                               },
    { EM_STARCORE     , "Motorola Star*Core processor"                                            },
    { EM_ME16         , "Toyota ME16 processor"                                                   },
    { EM_ST100        , "STMicroelectronics ST100 processor"                                      },
    { EM_TINYJ        , "Advanced Logic Corp. TinyJ embedded processor"                           },
    { EM_X86_64       , "Advanced Micro Devices X86-64 processor"                                 },
    { EM_PDSP         , "Sony DSP Processor"                                                      },
    { EM_PDP10        , "Digital Equipment Corp. PDP-10"                                          },
    { EM_PDP11        , "Digital Equipment Corp. PDP-11"                                          },
    { EM_FX66         , "Siemens FX66 microcontroller"                                            },
    { EM_ST9PLUS      , "STMicroelectronics ST9+ 8/16 bit microcontroller"                        },
    { EM_ST7          , "STMicroelectronics ST7 8-bit microcontroller"                            },
    { EM_68HC16       , "Motorola MC68HC16 Microcontroller"                                       },
    { EM_68HC11       , "Motorola MC68HC11 Microcontroller"                                       },
    { EM_68HC08       , "Motorola MC68HC08 Microcontroller"                                       },
    { EM_68HC05       , "Motorola MC68HC05 Microcontroller"                                       },
    { EM_SVX          , "Silicon Graphics SVx"                                                    },
    { EM_ST19         , "STMicroelectronics ST19 8-bit cpu"                                       },
    { EM_VAX          , "Digital VAX"                                                             },
    { EM_CRIS         , "Axis Communications 32-bit embedded processor"                           },
    { EM_JAVELIN      , "Infineon Technologies 32-bit embedded cpu"                               },
    { EM_FIREPATH     , "Element 14 64-bit DSP processor"                                         },
    { EM_ZSP          , "LSI Logic's 16-bit DSP processor"                                        },
    { EM_MMIX         , "Donald Knuth's educational 64-bit processor"                             },
    { EM_HUANY        , "Harvard's machine-independent format"                                    },
    { EM_PRISM        , "SiTera Prism"                                                            },
    { EM_AVR          , "Atmel AVR 8-bit microcontroller"                                         },
    { EM_FR30         , "Fujitsu FR30"                                                            },
    { EM_D10V         , "Mitsubishi D10V"                                                         },
    { EM_D30V         , "Mitsubishi D30V"                                                         },
    { EM_V850         , "NEC v850"                                                                },
    { EM_M32R         , "Renesas M32R (formerly Mitsubishi M32R)"                                 },
    { EM_MN10300      , "Matsushita MN10300"                                                      },
    { EM_MN10200      , "Matsushita MN10200"                                                      },
    { EM_PJ           , "picoJava"                                                                },
    { EM_OPENRISC     , "OpenRISC 32-bit embedded processor"                                      },
    { EM_ARC_A5       , "ARC Cores Tangent-A5"                                                    },
    { EM_XTENSA       , "Tensilica Xtensa Architecture"                                           },
    { EM_VIDEOCORE    , "Alphamosaic VideoCore processor"                                         },
    { EM_TMM_GPP      , "Thompson Multimedia General Purpose Processor"                           },
    { EM_NS32K        , "National Semiconductor 32000 series"                                     },
    { EM_TPC          , "Tenor Network TPC processor"                                             },
    { EM_SNP1K        , "Trebia SNP 1000 processor"                                               },
    { EM_ST200        , "STMicroelectronics ST200 microcontroller"                                },
    { EM_IP2K         , "Ubicom IP2022 micro controller"                                          },
    { EM_MAX          , "MAX Processor"                                                           },
    { EM_CR           , "National Semiconductor CompactRISC"                                      },
    { EM_F2MC16       , "Fujitsu F2MC16"                                                          },
    { EM_MSP430       , "TI msp430 micro controller"                                              },
    { EM_BLACKFIN     , "ADI Blackfin"                                                            },
    { EM_SE_C33       , "S1C33 Family of Seiko Epson processors"                                  },
    { EM_SEP          , "Sharp embedded microprocessor"                                           },
    { EM_ARCA         , "Arca RISC Microprocessor"                                                },
    { EM_UNICORE      , "Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University" },
    { EM_EXCESS       , "eXcess: 16/32/64-bit configurable embedded CPU"                          },
    { EM_DXP          , "Icera Semiconductor Inc. Deep Execution Processor"                       },
    { EM_ALTERA_NIOS2 , "Altera Nios II soft-core processor"                                      },
    { EM_CRX          , "National Semiconductor CRX"                                              },
    { EM_XGATE        , "Motorola XGATE embedded processor"                                       },
    { EM_C166         , "Infineon C16x/XC16x processor"                                           },
    { EM_M16C         , "Renesas M16C series microprocessors"                                     },
    { EM_DSPIC30F     , "Microchip Technology dsPIC30F Digital Signal Controller"                 },
    { EM_CE           , "Freescale Communication Engine RISC core"                                },
    { EM_M32C         , "Renesas M32C series microprocessors"                                     },
    { EM_res121       , "Reserved"                                                                },
    { EM_res122       , "Reserved"                                                                },
    { EM_res123       , "Reserved"                                                                },
    { EM_res124       , "Reserved"                                                                },
    { EM_res125       , "Reserved"                                                                },
    { EM_res126       , "Reserved"                                                                },
    { EM_res127       , "Reserved"                                                                },
    { EM_res128       , "Reserved"                                                                },
    { EM_res129       , "Reserved"                                                                },
    { EM_res130       , "Reserved"                                                                },
    { EM_TSK3000      , "Altium TSK3000 core"                                                     },
    { EM_RS08         , "Freescale RS08 embedded processor"                                       },
    { EM_res133       , "Reserved"                                                                },
    { EM_ECOG2        , "Cyan Technology eCOG2 microprocessor"                                    },
    { EM_SCORE        , "Sunplus Score"                                                           },
    { EM_SCORE7       , "Sunplus S+core7 RISC processor"                                          },
    { EM_DSP24        , "New Japan Radio (NJR) 24-bit DSP Processor"                              },
    { EM_VIDEOCORE3   , "Broadcom VideoCore III processor"                                        },
    { EM_LATTICEMICO32, "RISC processor for Lattice FPGA architecture"                            },
    { EM_SE_C17       , "Seiko Epson C17 family"                                                  },
    { EM_TI_C6000     , "Texas Instruments TMS320C6000 DSP family"                                },
    { EM_TI_C2000     , "Texas Instruments TMS320C2000 DSP family"                                },
    { EM_TI_C5500     , "Texas Instruments TMS320C55x DSP family"                                 },
    { EM_res143       , "Reserved"                                                                },
    { EM_res144       , "Reserved"                                                                },
    { EM_res145       , "Reserved"                                                                },
    { EM_res146       , "Reserved"                                                                },
    { EM_res147       , "Reserved"                                                                },
    { EM_res148       , "Reserved"                                                                },
    { EM_res149       , "Reserved"                                                                },
    { EM_res150       , "Reserved"                                                                },
    { EM_res151       , "Reserved"                                                                },
    { EM_res152       , "Reserved"                                                                },
    { EM_res153       , "Reserved"                                                                },
    { EM_res154       , "Reserved"                                                                },
    { EM_res155       , "Reserved"                                                                },
    { EM_res156       , "Reserved"                                                                },
    { EM_res157       , "Reserved"                                                                },
    { EM_res158       , "Reserved"                                                                },
    { EM_res159       , "Reserved"                                                                },
    { EM_MMDSP_PLUS   , "STMicroelectronics 64bit VLIW Data Signal Processor"                     },
    { EM_CYPRESS_M8C  , "Cypress M8C microprocessor"                                              },
    { EM_R32C         , "Renesas R32C series microprocessors"                                     },
    { EM_TRIMEDIA     , "NXP Semiconductors TriMedia architecture family"                         },
    { EM_QDSP6        , "QUALCOMM DSP6 Processor"                                                 },
    { EM_8051         , "Intel 8051 and variants"                                                 },
    { EM_STXP7X       , "STMicroelectronics STxP7x family"                                        },
    { EM_NDS32        , "Andes Technology compact code size embedded RISC processor family"       },
    { EM_ECOG1        , "Cyan Technology eCOG1X family"                                           },
    { EM_ECOG1X       , "Cyan Technology eCOG1X family"                                           },
    { EM_MAXQ30       , "Dallas Semiconductor MAXQ30 Core Micro-controllers"                      },
    { EM_XIMO16       , "New Japan Radio (NJR) 16-bit DSP Processor"                              },
    { EM_MANIK        , "M2000 Reconfigurable RISC Microprocessor"                                },
    { EM_CRAYNV2      , "Cray Inc. NV2 vector architecture"                                       },
    { EM_RX           , "Renesas RX family"                                                       },
    { EM_METAG        , "Imagination Technologies META processor architecture"                    },
    { EM_MCST_ELBRUS  , "MCST Elbrus general purpose hardware architecture"                       },
    { EM_ECOG16       , "Cyan Technology eCOG16 family"                                           },
    { EM_CR16         , "National Semiconductor CompactRISC 16-bit processor"                     },
    { EM_ETPU         , "Freescale Extended Time Processing Unit"                                 },
    { EM_SLE9X        , "Infineon Technologies SLE9X core"                                        },
    { EM_L1OM         , "Intel L1OM"                                                              },
    { EM_INTEL181     , "Reserved by Intel"                                                       },
    { EM_INTEL182     , "Reserved by Intel"                                                       },
    { EM_res183       , "Reserved by ARM"                                                         },
    { EM_res184       , "Reserved by ARM"                                                         },
    { EM_AVR32        , "Atmel Corporation 32-bit microprocessor family"                          },
    { EM_STM8         , "STMicroeletronics STM8 8-bit microcontroller"                            },
    { EM_TILE64       , "Tilera TILE64 multicore architecture family"                             },
    { EM_TILEPRO      , "Tilera TILEPro multicore architecture family"                            },
    { EM_MICROBLAZE   , "Xilinx MicroBlaze 32-bit RISC soft processor core"                       },
    { EM_CUDA         , "NVIDIA CUDA architecture "                                               },
}; 




#endif // ELF_H__23_02_2016__22_59
