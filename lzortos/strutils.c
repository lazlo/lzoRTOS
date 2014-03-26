/**
 * \file strutils.c
 * \brief string manipulation functions - implementation
 */

/* checkout http://www.jb.man.ac.uk/~slowe/cpp/itoa.html */

/**
 * strreverse
 */
/** Reverse character string.
 * \param *begin Pointer to where character string starts.
 * \param *end Pointer to where character string ends.
 */
void strreverse( char *begin, char *end )
{
        char aux;
        while(end>begin)
                aux = *end, *end--= *begin, *begin++= aux;
}

/**
 * itoa
 */
/** Transform integer to character string.
 *
 * \param value Integer value to convert.
 * \param *str Pointer to character string in which to write into.
 * \param base Base for conversion (e.g. 10).
 */
void itoa( int value, char *str, int base )
{
        static char num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
        char *wstr = str;
        int sign;
        if( base < 2 || base > 35) { *wstr = '\0'; return; }
        if( ( sign = value ) < 0 ) value = -value;

        do *wstr++ = num[ value % base ]; while ( value /= base );
        if( sign < 0 ) *wstr++='-';
        *wstr = '\0';
        strreverse( str, wstr-1 );
}


