#include "randlib.h"
#include <stdio.h>
#include <stdlib.h>

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

__attribute__ ((__constructor__)) //added constructor


/* Initialize the software rand64 implementation.  */
static void
software_rand64_init (void)
{
    urandstream = fopen ("/dev/urandom", "r");
    if (! urandstream)
        abort ();
}

/* Return a random value, using software operations.  */
extern unsigned long long
software_rand64 (void)
{
    unsigned long long int x;
    if (fread (&x, sizeof x, 1, urandstream) != 1)
        abort ();
    return x;
}



__attribute__ ((__destructor__))  //added destructor



/* Finalize the software rand64 implementation.  */
static void
software_rand64_fini (void)
{
    fclose (urandstream);
}
