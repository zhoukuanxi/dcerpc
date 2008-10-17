/*
 * 
 * (c) Copyright 1990 OPEN SOFTWARE FOUNDATION, INC.
 * (c) Copyright 1990 HEWLETT-PACKARD COMPANY
 * (c) Copyright 1990 DIGITAL EQUIPMENT CORPORATION
 * To anyone who acknowledges that this file is provided "AS IS"
 * without any express or implied warranty:
 *                 permission to use, copy, modify, and distribute this
 * file for any purpose is hereby granted without fee, provided that
 * the above copyright notices and this notice appears in all source
 * code copies, and that none of the names of Open Software
 * Foundation, Inc., Hewlett-Packard Company, or Digital Equipment
 * Corporation be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.  Neither Open Software Foundation, Inc., Hewlett-
 * Packard Company, nor Digital Equipment Corporation makes any
 * representations about the suitability of this software for any
 * purpose.
 * 
 */
/*
 */
/*
**
**  NAME:
**
**      ndrchars.c
**
**  FACILITY:
**
**      IDL Stub Runtime Support
**
**  ABSTRACT:
**
**  NDR conversion utility routines, Stub support routines for strings.
**
**  VERSION: DCE 1.0
**
*/
#if HAVE_CONFIG_H
#include <config.h>
#endif


/* The ordering of the following 3 includes should NOT be changed! */
#include <dce/rpc.h>
#include <dce/stubbase.h>
#include <lsysdep.h>

/*
 *  ASCII <-> EBCDIC conversion tables
 */

globaldef rpc_trans_tab_t ndr_g_def_ascii_to_ebcdic = {
     0x00, 0x01, 0x02, 0x03, 0x37, 0x2D, 0x2E, 0x2F, /* 0x00 - 0x07 */
     0x16, 0x05, 0x25, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, /* 0x08 - 0x0F */
     0x10, 0x11, 0x12, 0x13, 0x3C, 0x3D, 0x32, 0x26, /* 0x10 - 0x17 */
     0x18, 0x19, 0x3F, 0x27, 0x1C, 0x1D, 0x1E, 0x1F, /* 0x18 - 0x1F */
     0x40, 0x4F, 0x7F, 0x7B, 0x5B, 0x6C, 0x50, 0x7D, /* 0x20 - 0x27 */
     0x4D, 0x5D, 0x5C, 0x4E, 0x6B, 0x60, 0x4B, 0x61, /* 0x28 - 0x2F */
     0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7, /* 0x30 - 0x37 */
     0xF8, 0xF9, 0x7A, 0x5E, 0x4C, 0x7E, 0x6E, 0x6F, /* 0x38 - 0x3F */
     0x7C, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, /* 0x40 - 0x47 */
     0xC8, 0xC9, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5, 0xD6, /* 0x48 - 0x4F */
     0xD7, 0xD8, 0xD9, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, /* 0x50 - 0x57 */
     0xE7, 0xE8, 0xE9, 0x4A, 0xE0, 0x5A, 0x5F, 0x6D, /* 0x58 - 0x5F */
     0x79, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, /* 0x60 - 0x67 */
     0x88, 0x89, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, /* 0x68 - 0x6F */
     0x97, 0x98, 0x99, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, /* 0x70 - 0x77 */
     0xA7, 0xA8, 0xA9, 0xC0, 0xBB, 0xD0, 0xA1, 0x07, /* 0x78 - 0x7F */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0x80 - 0x87 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0x88 - 0x8F */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0x90 - 0x97 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0x98 - 0x9F */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xA0 - 0xA7 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xA8 - 0xAF */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xB0 - 0xB7 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xB8 - 0xBF */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xC0 - 0xC7 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xC8 - 0xCF */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xD0 - 0xD7 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xD8 - 0xDF */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xE0 - 0xE7 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xE8 - 0xEF */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, /* 0xF0 - 0xF7 */
     0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0xFF  /* 0xF8 - 0xFF */
};

globaldef rpc_trans_tab_t ndr_g_def_ebcdic_to_ascii = {
     0x00, 0x01, 0x02, 0x03, 0x1A, 0x09, 0x1A, 0x7F, /* 0x00 - 0x07 */
     0x1A, 0x1A, 0x1A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, /* 0x08 - 0x0F */
     0x10, 0x11, 0x12, 0x13, 0x1A, 0x1A, 0x08, 0x1A, /* 0x10 - 0x17 */
     0x18, 0x19, 0x1A, 0x1A, 0x1C, 0x1D, 0x1E, 0x1F, /* 0x18 - 0x1F */
     0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x0A, 0x17, 0x1B, /* 0x20 - 0x27 */
     0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x05, 0x06, 0x07, /* 0x28 - 0x2F */
     0x1A, 0x1A, 0x16, 0x1A, 0x1A, 0x1A, 0x1A, 0x04, /* 0x30 - 0x37 */
     0x1A, 0x1A, 0x1A, 0x1A, 0x14, 0x15, 0x1A, 0x1A, /* 0x38 - 0x3F */
     0x20, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0x40 - 0x47 */
     0x1A, 0x1A, 0x5B, 0x2E, 0x3C, 0x28, 0x2B, 0x21, /* 0x48 - 0x4F */
     0x26, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0x50 - 0x57 */
     0x1A, 0x1A, 0x5D, 0x24, 0x2A, 0x29, 0x3B, 0x5E, /* 0x58 - 0x5F */
     0x2D, 0x2F, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0x60 - 0x67 */
     0x1A, 0x1A, 0x7C, 0x2C, 0x25, 0x5F, 0x3E, 0x3F, /* 0x68 - 0x6F */
     0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0x70 - 0x77 */
     0x1A, 0x60, 0x3A, 0x23, 0x40, 0x27, 0x3D, 0x22, /* 0x78 - 0x7F */
     0x1A, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, /* 0x80 - 0x87 */
     0x68, 0x69, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0x88 - 0x8F */
     0x1A, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, /* 0x90 - 0x97 */
     0x71, 0x72, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0x98 - 0x9F */
     0x1A, 0x7E, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, /* 0xA0 - 0xA7 */
     0x79, 0x7A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0xA8 - 0xAF */
     0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0xB0 - 0xB7 */
     0x1A, 0x1A, 0x1A, 0x7C, 0x1A, 0x1A, 0x1A, 0x1A, /* 0xB8 - 0xBF */
     0x7B, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, /* 0xC0 - 0xC7 */
     0x48, 0x49, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0xC8 - 0xCF */
     0x7D, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, /* 0xD0 - 0xD7 */
     0x51, 0x52, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0xD8 - 0xDF */
     0x5C, 0x1A, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, /* 0xE0 - 0xE7 */
     0x59, 0x5A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, /* 0xE8 - 0xEF */
     0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, /* 0xF0 - 0xF7 */
     0x38, 0x39, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A, 0xFF  /* 0xF8 - 0xFF */
};


/*
 * N D R _ C V T _ S T R I N G
 *
 * Called by stubs to copy and convert a string in one character
 * representation to another.
 */

void ndr_cvt_string
#ifdef IDL_PROTOTYPES
(
ndr_format_t src_drep,
ndr_format_t dst_drep,
char_p_t src,
char_p_t dst
)
#else
(src_drep, dst_drep, src, dst)
ndr_format_t src_drep;
ndr_format_t dst_drep;
char_p_t src;
char_p_t dst;
#endif
{
    if (src_drep.char_rep == dst_drep.char_rep)
        strcpy((char *) dst, (char *) src);
    else if (dst_drep.char_rep == ndr_c_char_ascii)
        while ((*dst++ = ndr_g_def_ebcdic_to_ascii[*src++]));
    else
        while ((*dst++ = ndr_g_def_ascii_to_ebcdic[*src++]));
}


/*
 *  r p c _ s s _ s t r s i z
 *
 *  Called by stubs to determine the size of a string.  This routine assumes
 *  that if the string is composed of multi-octet characters, the termination
 *  character must have the value NUL in all of its octets.  For multi-octet
 *  character strings, the number of *characters* (not octets) is returned.
 *  In all cases, the value returned includes the termination character.
 *
 *  NOTE: A NULL input value results in a returned size of zero.
 */

idl_ulong_int rpc_ss_strsiz
#ifdef IDL_PROTOTYPES
(
    idl_char        *s,
    idl_ulong_int   octets_per_char
)
#else
(s, octets_per_char)
    idl_char        *s;
    idl_ulong_int   octets_per_char;
#endif
{
    idl_ulong_int   i = 0, j;
    idl_char        *octet;

    if (s == NULL)
        return 0;

    for (;;)
    {
        while (s[i] != '\0')
            i += octets_per_char;

        /*
         * First octet is null, are the rest?
         */
        octet = &s[i];
        for (j = 1; j < octets_per_char && octet[j] == '\0'; j++)
            ;
        if (j == octets_per_char)
            return ((octet + j - s) / octets_per_char);

        /*
         * Not a full null char, update to next char and continue.
         */
        i += octets_per_char;
    }
}