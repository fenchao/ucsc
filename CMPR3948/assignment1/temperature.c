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
/*    Assignment Number: 1                                              */
/*                                                                      */
/*    Topic: Introduction to C Programming                              */
/*                                                                      */
/*    file name: temperature.c                                          */ 
/*                                                                      */
/*    Date: 07/08/2017                                                  */
/*                                                                      */
/*    Objective: Convert temperature between Celsius and Fahrenheit     */
/*                                                                      */
/*    Comments:                                                         */
/*                                                                      */
/************************************************************************/ 

#include <stdio.h>

int main ()
{
    int deg;
    char type;

    printf("enter the value of temperature and the type of degrees\n");
    scanf("%d deg %c", &deg, &type);
    if (type == 'C') {
        printf("%d deg C = %d deg F\n", deg, (deg*9/5)+32);
    } else if (type =='F') {
        printf("%d deg F = %d deg C\n", deg, (deg-32)*5/9);
    } else {
        printf("invalid input\n");
    }

    return 0;
}
