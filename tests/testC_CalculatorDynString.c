#include "../src/C_CalculatorDynString.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void) {
    CalcDynString *dynStr = allocCalcDynString();
    char *str1;

    str_append_char(dynStr, 'A');
    str1 = CalcDynString_to_CString(dynStr);
    printf("Test 1 - %s\n", (strcmp(str1, "A") ? "Approved" : "Failed" ));

    str_append_string(dynStr, "BC");
    printf("Test 2 - %s\n", (strcmp(CalcDynString_to_CString(dynStr), "ABC") ? "Approved" : "Failed" ));

    system("Pause");
    return(0);
}
