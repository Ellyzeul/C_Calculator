#ifndef __ELLYZ__C_CALCULATOR_DYNSTRING__
#define __ELLYZ__C_CALCULATOR_DYNSTRING__

#include <stdlib.h>

struct stringNode {
    short isString;
    union {
        char ch;
        char* str;
    };
    struct stringNode *prev;
    struct stringNode *next;
};
typedef struct stringNode CalcStringNode;
typedef struct {
    CalcStringNode *head;
    CalcStringNode *last;
    CalcStringNode *actual;
    int length;
} CalcDynString;

CalcDynString* allocCalcDynString();

_Bool str_append_char(CalcDynString *dynStr, char ch);
_Bool str_append_string(CalcDynString *dynStr, char *str);

_Bool str_clear_entry(CalcDynString *dynStr);
_Bool str_clear_all(CalcDynString *dynStr);

char* CalcDynString_to_CString(CalcDynString *dynStr);

#endif // __ELLYZ__C_CALCULATOR_DYNSTRING__
