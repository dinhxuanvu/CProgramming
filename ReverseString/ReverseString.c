//
//  ReverseString.c
//  
//
//  Created by Vu Dinh on 9/21/14.
//
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ReverseString.h"

/*
 * Accept a character pointer of a string as a parameter.
 * Then reverse the original string with return anything to the function.
 */
void string_reverse1(char *string)
{
    int length = strlen(string);
    char temp;
    char *reverseString;
    int i;
    
    /* Check if the string is empty or points to null. */
    if (string == 0 || *string == 0)
    {
        return;
    }
    
    reverseString = string + length - 1;
    
    /* Reverse the original string. */
    for (i = 0; i < (length/2); i++)
    {
        temp = *reverseString;
        *reverseString = *string;
        *string = temp;
        string++;
        reverseString--;
    }
}

/*
 * Accept a constant character pointer as a parameter.
 * Then return back a character pointer which points to reversed string.
 * The original string is not modified since it is constant.
 */
char *string_reverse2(const char *string)
{
    int length = strlen(string);
    int i;
    char *reverseString;
    char *tempString;
    char temp;
    
    /* Check if the string is empty or points to null. */
    if (string == NULL || *string == 0)
    {
        return NULL;
    }
    
    reverseString = malloc(sizeof(length+1));
    
    /* Copy the original string to a new string. */
    strcpy(reverseString, string);
    tempString = reverseString + length - 1;
    
    /* Reverse the new string. */
    for (i = 0; i < length/2; i++)
    {
        temp = *tempString;
        *tempString = *reverseString;
        *reverseString = temp;
        tempString--;
        reverseString++;
    }
    
    /* Move the pointer back to the first character of the new string. */
    reverseString = reverseString - length/2;
    
    /* Return the pointer which points to reversed string. */
    return reverseString;
}

/*
 * Main function to test both functions.
 */
int main()
{
    char string1[] = "dooG";
    const char string2[] = "!gninrom";
    
    char *reverse;
    
    /* Reverse the first string and print out the reversed (original) string. */
    string_reverse1(string1);
    printf("%s",string1);
    
    /* Reverse the second string and print out the reversed (new) string. */
    reverse = string_reverse2(string2);
    printf(" %s\n",reverse);
    
    return 0;
}
