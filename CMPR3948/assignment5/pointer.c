/************************************************************************/
/****************                  prologue               ***************/ 
/*                                                                      */
/*              University of California Extension, Santa Cruz          */
/*                                                                      */
/*                          Advanced C Programming                      */
/*                                                                      */
/*                    Instructor: Rajainder A. Yeldandi                 */
/*                                                                      */
/*    Author: Fenchao Du                                                */
/*                                                                      */
/*    Assignment Number: 5                                              */
/*                                                                      */
/*    Topic: pointers                                                   */
/*                                                                      */
/*    file name: pointer.c                                              */ 
/*                                                                      */
/*    Date: 07/15/2017                                                  */
/*                                                                      */
/*    Objective: print val, address, play with pointers                 */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>

int main (void)
{
    int a = 25, *ap = &a;
    float b = 3.142, *bp = &b;
    double c = 1.73217, *cp = &c;
    const char *str = "Hello, C Programmer";
    char d = 'x', *dp = &d;

    printf("Val %d, Dereference-val %d, Address %p, Address of pointer %p\n", a, *ap, ap, &ap);
    printf("Val %f, Dereference-val %f, Address %p, Address of pointer %p\n", b, *bp, bp, &bp);
    printf("Val %f, Dereference-val %f, Address %p, Address of pointer %p\n", c, *cp, cp, &cp);
    printf("Val %s, Dereference-val %c, Address %p, Address of pointer %p\n", str, *str, str, &str);
    printf("Val %c, Dereference-val %c, Address %p, Address of pointer %p\n", d, *dp, dp, &dp);
    
    int *sp = ap;
    printf("Dereference-val %d\n", *sp);

    return 0;
}
