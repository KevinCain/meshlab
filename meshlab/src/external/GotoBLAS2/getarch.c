/*********************************************************************/
/*                                                                   */
/*             Optimized BLAS libraries                              */
/*                     By Kazushige Goto <kgoto@tacc.utexas.edu>     */
/*                                                                   */
/* Copyright (c) The University of Texas, 2009. All rights reserved. */
/* UNIVERSITY EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES CONCERNING  */
/* THIS SOFTWARE AND DOCUMENTATION, INCLUDING ANY WARRANTIES OF      */
/* MERCHANTABILITY, FITNESS FOR ANY PARTICULAR PURPOSE,              */
/* NON-INFRINGEMENT AND WARRANTIES OF PERFORMANCE, AND ANY WARRANTY  */
/* THAT MIGHT OTHERWISE ARISE FROM COURSE OF DEALING OR USAGE OF     */
/* TRADE. NO WARRANTY IS EITHER EXPRESS OR IMPLIED WITH RESPECT TO   */
/* THE USE OF THE SOFTWARE OR DOCUMENTATION.                         */
/* Under no circumstances shall University be liable for incidental, */
/* special, indirect, direct or consequential damages or loss of     */
/* profits, interruption of business, or related expenses which may  */
/* arise from use of Software or Documentation, including but not    */
/* limited to those resulting from defects in Software and/or        */
/* Documentation, or loss or inaccuracy of data of any kind.         */
/*********************************************************************/

#if defined(__WIN32__) || defined(__WIN64__) || defined(__CYGWIN32__) || defined(__CYGWIN64__)
#define OS_WINDOWS
#endif

#include <stdio.h>
#include <string.h>
#ifdef OS_WINDOWS
#include <windows.h>
#endif
#if defined(__FreeBSD__) || defined(__APPLE__)
#include <sys/types.h>
#include <sys/sysctl.h>
#endif
#ifdef linux
#include <sys/sysinfo.h>
#endif

/* #define FORCE_P2		*/
/* #define FORCE_KATMAI		*/
/* #define FORCE_COPPERMINE	*/
/* #define FORCE_NORTHWOOD	*/
/* #define FORCE_PRESCOTT	*/
/* #define FORCE_BANIAS		*/
/* #define FORCE_YONAH		*/
/* #define FORCE_CORE2		*/
/* #define FORCE_PENRYN		*/
/* #define FORCE_DUNNINGTON	*/
/* #define FORCE_NEHALEM	*/
/* #define FORCE_ATHLON		*/
/* #define FORCE_OPTERON	*/
/* #define FORCE_OPTERON_SSE3	*/
/* #define FORCE_BARCELONA	*/
/* #define FORCE_SHANGHAI	*/
/* #define FORCE_ISTANBUL	*/
/* #define FORCE_SSE_GENERIC	*/
/* #define FORCE_VIAC3		*/
/* #define FORCE_NANO		*/
/* #define FORCE_POWER3		*/
/* #define FORCE_POWER4		*/
/* #define FORCE_POWER5		*/
/* #define FORCE_POWER6		*/
/* #define FORCE_PPCG4		*/
/* #define FORCE_PPC970		*/
/* #define FORCE_PPC970MP	*/
/* #define FORCE_PPC440		*/
/* #define FORCE_PPC440FP2	*/
/* #define FORCE_CELL		*/
/* #define FORCE_SICORTEX	*/
/* #define FORCE_ITANIUM2	*/
/* #define FORCE_GENERIC	*/
/* #define FORCE_SPARC		*/
/* #define FORCE_SPARCV7	*/

#ifdef FORCE_P2
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "PENTIUM2"
#define ARCHCONFIG   "-DPENTIUM2 " \
		     "-DL1_DATA_SIZE=16384 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=512488 -DL2_LINESIZE=32 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX"
#define LIBNAME   "p2"
#define CORENAME  "P5"
#endif

#ifdef FORCE_COPPERMINE
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "PENTIUM3"
#define ARCHCONFIG   "-DPENTIUM3 " \
		     "-DL1_DATA_SIZE=16384 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=262144 -DL2_LINESIZE=32 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE "
#define LIBNAME   "coppermine"
#define CORENAME  "COPPERMINE"
#endif

#ifdef FORCE_KATMAI
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "PENTIUM3"
#define ARCHCONFIG   "-DPENTIUM3 " \
		     "-DL1_DATA_SIZE=16384 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=524288 -DL2_LINESIZE=32 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE "
#define LIBNAME   "katmai"
#define CORENAME  "KATMAI"
#endif

#ifdef FORCE_NORTHWOOD
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "PENTIUM4"
#define ARCHCONFIG   "-DPENTIUM4 " \
		     "-DL1_DATA_SIZE=8192 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=524288 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 "
#define LIBNAME   "northwood"
#define CORENAME  "NORTHWOOD"
#endif

#ifdef FORCE_PRESCOTT
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "PENTIUM4"
#define ARCHCONFIG   "-DPENTIUM4 " \
		     "-DL1_DATA_SIZE=16384 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3"
#define LIBNAME   "prescott"
#define CORENAME  "PRESCOTT"
#endif

#ifdef FORCE_BANIAS
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "BANIAS"
#define ARCHCONFIG   "-DPENTIUMM " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 "
#define LIBNAME   "banias"
#define CORENAME  "BANIAS"
#endif

#ifdef FORCE_YONAH
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "YONAH"
#define ARCHCONFIG   "-DPENTIUMM " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 "
#define LIBNAME   "yonah"
#define CORENAME  "YONAH"
#endif

#ifdef FORCE_CORE2
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "CONRORE"
#define ARCHCONFIG   "-DCORE2 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=256 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3 -DHAVE_SSSE3"
#define LIBNAME   "core2"
#define CORENAME  "CORE2"
#endif

#ifdef FORCE_PENRYN
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "PENRYN"
#define ARCHCONFIG   "-DPENRYN " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=256 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3 -DHAVE_SSSE3 -DHAVE_SSE4_1"
#define LIBNAME   "penryn"
#define CORENAME  "PENRYN"
#endif

#ifdef FORCE_DUNNINGTON
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "DUNNINGTON"
#define ARCHCONFIG   "-DDUNNINGTON " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DL3_SIZE=16777216 -DL3_LINESIZE=64 " \
		     "-DDTB_ENTRIES=256 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3 -DHAVE_SSSE3 -DHAVE_SSE4_1"
#define LIBNAME   "dunnington"
#define CORENAME  "DUNNINGTON"
#endif

#ifdef FORCE_NEHALEM
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "NEHALEM"
#define ARCHCONFIG   "-DNEHALEM " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=262144 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3 -DHAVE_SSSE3 -DHAVE_SSE4_1 -DHAVE_SSE4_2"
#define LIBNAME   "nehalem"
#define CORENAME  "NEHALEM"
#endif

#ifdef FORCE_ATOM
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "ATOM"
#define ARCHCONFIG   "-DATOM " \
		     "-DL1_DATA_SIZE=24576 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=524288 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=4 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3 -DHAVE_SSSE3"
#define LIBNAME   "atom"
#define CORENAME  "ATOM"
#endif

#ifdef FORCE_ATHLON
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "ATHLON"
#define ARCHCONFIG   "-DATHLON " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=32 -DDTB_SIZE=4096 -DHAVE_3DNOW  " \
		     "-DHAVE_3DNOWEX -DHAVE_MMX -DHAVE_SSE "
#define LIBNAME   "athlon"
#define CORENAME  "ATHLON"
#endif

#ifdef FORCE_OPTERON
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "OPTERON"
#define ARCHCONFIG   "-DOPTERON " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=32 -DDTB_SIZE=4096 -DHAVE_3DNOW " \
		     "-DHAVE_3DNOWEX -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 "
#define LIBNAME   "opteron"
#define CORENAME  "OPTERON"
#endif

#ifdef FORCE_OPTERON_SSE3
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "OPTERON"
#define ARCHCONFIG   "-DOPTERON " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=32 -DDTB_SIZE=4096 -DHAVE_3DNOW " \
		     "-DHAVE_3DNOWEX -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3"
#define LIBNAME   "opteron"
#define CORENAME  "OPTERON"
#endif

#if defined(FORCE_BARCELONA) || defined(FORCE_SHANGHAI) || defined(FORCE_ISTANBUL)
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "BARCELONA"
#define ARCHCONFIG   "-DBARCELONA " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=524288 -DL2_LINESIZE=64  -DL3_SIZE=2097152 " \
		     "-DDTB_ENTRIES=48 -DDTB_SIZE=4096 -DHAVE_3DNOW " \
		     "-DHAVE_3DNOWEX -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3 " \
		     "-DHAVE_SSE4A -DHAVE_MISALIGNSSE -DHAVE_128BITFPU -DHAVE_FASTMOVU"
#define LIBNAME   "barcelona"
#define CORENAME  "BARCELONA"
#endif

#ifdef FORCE_SSE_GENERIC
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "GENERIC"
#define ARCHCONFIG   "-DGENERIC " \
		     "-DL1_DATA_SIZE=16384 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=524288 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2"
#define LIBNAME   "generic"
#define CORENAME  "GENERIC"
#endif

#ifdef FORCE_VIAC3
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "VIAC3"
#define ARCHCONFIG   "-DVIAC3 " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=65536 -DL2_LINESIZE=32 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 " \
		     "-DHAVE_MMX -DHAVE_SSE "
#define LIBNAME   "viac3"
#define CORENAME  "VIAC3"
#endif

#ifdef FORCE_NANO
#define FORCE
#define FORCE_INTEL
#define ARCHITECTURE    "X86"
#define SUBARCHITECTURE "NANO"
#define ARCHCONFIG   "-DNANO " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1048576 -DL2_LINESIZE=64 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 " \
		     "-DHAVE_CMOV -DHAVE_MMX -DHAVE_SSE -DHAVE_SSE2 -DHAVE_SSE3 -DHAVE_SSSE3"
#define LIBNAME   "nano"
#define CORENAME  "NANO"
#endif

#ifdef FORCE_POWER3
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "POWER3"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPOWER3 " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=2097152 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=256 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "power3"
#define CORENAME  "POWER3"
#endif

#ifdef FORCE_POWER4
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "POWER4"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPOWER4 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=1509949 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=6 "
#define LIBNAME   "power4"
#define CORENAME  "POWER4"
#endif

#ifdef FORCE_POWER5
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "POWER5"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPOWER5 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=1509949 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=6 "
#define LIBNAME   "power5"
#define CORENAME  "POWER5"
#endif

#ifdef FORCE_POWER6
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "POWER6"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPOWER6 " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=4194304 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "power6"
#define CORENAME  "POWER6"
#endif

#ifdef FORCE_PPCG4
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "PPCG4"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPPCG4 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=262144 -DL2_LINESIZE=32 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "ppcg4"
#define CORENAME  "PPCG4"
#endif

#ifdef FORCE_PPC970
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "PPC970"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPPC970 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=512488 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "ppc970"
#define CORENAME  "PPC970"
#endif

#ifdef FORCE_PPC970MP
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "PPC970"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPPC970 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=1024976 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "ppc970mp"
#define CORENAME  "PPC970"
#endif

#ifdef FORCE_PPC440
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "PPC440"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPPC440 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=16384 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=16 "
#define LIBNAME   "ppc440"
#define CORENAME  "PPC440"
#endif

#ifdef FORCE_PPC440FP2
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "PPC440FP2"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DPPC440FP2 " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=16384 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=64 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=16 "
#define LIBNAME   "ppc440FP2"
#define CORENAME  "PPC440FP2"
#endif

#ifdef FORCE_CELL
#define FORCE
#define ARCHITECTURE    "POWER"
#define SUBARCHITECTURE "CELL"
#define SUBDIRNAME      "power"
#define ARCHCONFIG   "-DCELL " \
		     "-DL1_DATA_SIZE=262144 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=512488 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "cell"
#define CORENAME  "CELL"
#endif

#ifdef FORCE_SICORTEX
#define FORCE
#define ARCHITECTURE    "MIPS"
#define SUBARCHITECTURE "SICORTEX"
#define SUBDIRNAME      "mips"
#define ARCHCONFIG   "-DSICORTEX " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=32 " \
		     "-DL2_SIZE=512488 -DL2_LINESIZE=32 " \
		     "-DDTB_ENTRIES=32 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "mips"
#define CORENAME  "sicortex"
#endif

#ifdef FORCE_ITANIUM2
#define FORCE
#define ARCHITECTURE    "IA64"
#define SUBARCHITECTURE "ITANIUM2"
#define SUBDIRNAME      "ia64"
#define ARCHCONFIG   "-DITANIUM2 " \
		     "-DL1_DATA_SIZE=262144 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=1572864 -DL2_LINESIZE=128 -DDTB_SIZE=16384 -DDTB_ENTRIES=128 "
#define LIBNAME   "itanium2"
#define CORENAME  "itanium2"
#endif

#ifdef FORCE_SPARC
#define FORCE
#define ARCHITECTURE    "SPARC"
#define SUBARCHITECTURE "SPARC"
#define SUBDIRNAME      "sparc"
#define ARCHCONFIG   "-DSPARC -DV9 " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1572864 -DL2_LINESIZE=64 -DDTB_SIZE=8192 -DDTB_ENTRIES=64 "
#define LIBNAME   "sparc"
#define CORENAME  "sparc"
#endif

#ifdef FORCE_SPARCV7
#define FORCE
#define ARCHITECTURE    "SPARC"
#define SUBARCHITECTURE "SPARC"
#define SUBDIRNAME      "sparc"
#define ARCHCONFIG   "-DSPARC -DV7 " \
		     "-DL1_DATA_SIZE=65536 -DL1_DATA_LINESIZE=64 " \
		     "-DL2_SIZE=1572864 -DL2_LINESIZE=64 -DDTB_SIZE=8192 -DDTB_ENTRIES=64 "
#define LIBNAME   "sparcv7"
#define CORENAME  "sparcv7"
#endif

#ifdef FORCE_GENERIC
#define FORCE
#define ARCHITECTURE    "GENERIC"
#define SUBARCHITECTURE "GENERIC"
#define SUBDIRNAME      "generic"
#define ARCHCONFIG   "-DGENERIC " \
		     "-DL1_DATA_SIZE=32768 -DL1_DATA_LINESIZE=128 " \
		     "-DL2_SIZE=512488 -DL2_LINESIZE=128 " \
		     "-DDTB_ENTRIES=128 -DDTB_SIZE=4096 -DL2_ASSOCIATIVE=8 "
#define LIBNAME   "generic"
#define CORENAME  "generic"
#endif

#ifndef FORCE

#if defined(__powerpc__) || defined(__powerpc) || defined(powerpc) || \
    defined(__PPC__) || defined(PPC) || defined(_POWER) || defined(__POWERPC__)
#ifndef POWER
#define POWER
#endif
#endif

#if defined(__i386__) || (__x86_64__)
#include "cpuid_x86.c"
#endif

#ifdef __ia64__
#include "cpuid_ia64.c"
#endif

#ifdef __alpha
#include "cpuid_alpha.c"
#endif

#ifdef POWER
#include "cpuid_power.c"
#endif

#ifdef sparc
#include "cpuid_sparc.c"
#endif

#ifdef __mips__
#include "cpuid_mips.c"
#endif

#else

#endif

static int get_num_cores(void) {

#ifdef OS_WINDOWS
  SYSTEM_INFO sysinfo;
#elif defined(__FreeBSD__) || defined(__APPLE__)
  int m[2], count;
  size_t len;
#endif
  
#ifdef linux
  return get_nprocs();
  
#elif defined(OS_WINDOWS)

  GetSystemInfo(&sysinfo);
  return sysinfo.dwNumberOfProcessors;

#elif defined(__FreeBSD__) || defined(__APPLE__)
  m[0] = CTL_HW;
  m[1] = HW_NCPU;
  len = sizeof(int);
  sysctl(m, 2, &count, &len, NULL, 0);

  return count;
#else
  return 2;
#endif
}

int main(int argc, char *argv[]){

#ifdef FORCE
  char buffer[8192], *p, *q;
  int length;
#endif

  if (argc == 1) return 0;

  switch (argv[1][0]) {

  case '0' : /* for Makefile */

#ifdef FORCE
    printf("CORE=%s\n", CORENAME);
#else    
#if defined(__i386__) || defined(__x86_64__) || defined(POWER)
    printf("CORE=%s\n", get_corename());
#endif
#endif

#ifdef FORCE
    printf("LIBCORE=%s\n", LIBNAME);
#else
    printf("LIBCORE=");
    get_libname();
    printf("\n");
#endif

    printf("NUM_CORES=%d\n", get_num_cores());

#if defined(__i386__) || defined(__x86_64__)
#ifndef FORCE
    get_sse();
#else

    sprintf(buffer, "%s", ARCHCONFIG);

    p = &buffer[0];

    while (*p) {
      if ((*p == '-') && (*(p + 1) == 'D')) {
	p += 2;

	while ((*p != ' ') && (*p != '\0')) {

	  if (*p == '=') {
	    printf("=");
	    p ++;
	    while ((*p != ' ') && (*p != '\0')) {
	      printf("%c", *p);
	      p ++;
	    }
	  } else {
	    printf("%c", *p);
	    p ++;
	    if ((*p == ' ') || (*p =='\0')) printf("=1");
	  }
	}

	printf("\n");
      } else p ++;
    }
#endif
#endif

#ifndef OS_WINDOWS
    printf("MAKE += -j %d\n", get_num_cores());
#endif

    break;

  case '1' : /* For config.h */
#ifdef FORCE
    sprintf(buffer, "%s -DCORE_%s\n", ARCHCONFIG, CORENAME);

    p = &buffer[0];
    while (*p) {
      if ((*p == '-') && (*(p + 1) == 'D')) {
	p += 2;
	printf("#define ");

	while ((*p != ' ') && (*p != '\0')) {

	  if (*p == '=') {
	    printf(" ");
	    p ++;
	    while ((*p != ' ') && (*p != '\0')) {
	      printf("%c", *p);
	      p ++;
	    }
	  } else {
	    printf("%c", *p);
	    p ++;
	  }
	}

	printf("\n");
      } else p ++;
    }
#else
    get_cpuconfig();
#endif
 break;

  case '2' : /* SMP */
    if (get_num_cores() > 1) printf("SMP=1\n");
    break;
  }

  fflush(stdout);

  return 0;
}

