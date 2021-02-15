#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C_CalculatorDynString.h"


CalcDynString* allocCalcDynString() {
    CalcDynString *dynStr = calloc(1, sizeof(CalcDynString));
    CalcStringNode *node = calloc(1, sizeof(CalcStringNode));
    node->isString = 0;
    node->ch = '\0';
    node->prev = node->next = NULL;

    dynStr->head = dynStr->last = dynStr->actual = node;
    dynStr->length = 0;

    return(dynStr);
}

_Bool calcDynString_append_node(CalcDynString *dynStr, CalcStringNode *node) {
    CalcStringNode *lastPrev;

    if(dynStr->length == 0) {
        dynStr->head = node;
        node->next = dynStr->last;
        dynStr->last->prev = node;

        return(1);
    }
    lastPrev = dynStr->last->prev;
    node->next = dynStr->last;
    lastPrev->next = node;
    node->prev = lastPrev;
    dynStr->last->prev = node;

    dynStr->length++;

    return(1);
}
_Bool str_append_char(CalcDynString *dynStr, char ch) {
    CalcStringNode *node = calloc(1, sizeof(CalcStringNode));
    node->isString = 0;
    node->ch = ch;
    node->prev = node->next = NULL;

    return(calcDynString_append_node(dynStr, node));
}
_Bool str_append_string(CalcDynString *dynStr, char *str) {
    CalcStringNode *node = calloc(1, sizeof(CalcStringNode));
    node->isString = 1;
    node->str = str;
    node->prev = node->next = NULL;

    return(calcDynString_append_node(dynStr, node));
}

_Bool str_clear_entry(CalcDynString *dynStr) {
    CalcStringNode *toFree = dynStr->last->prev;

    toFree->prev->next = dynStr->last;
    dynStr->last->prev = toFree->prev;

    free(toFree);
    dynStr->length--;

    return(1);
}
_Bool str_clear_all(CalcDynString *dynStr) {
    CalcStringNode *toFree;
    if(dynStr->last->isString == 0 && dynStr->last->prev == NULL) {
        dynStr->head = dynStr->last;
        dynStr->length = 0;
        return(1);
    }
    toFree = dynStr->last->prev;
    dynStr->last->prev = toFree->prev;
    free(toFree);
    str_clear_all(dynStr);
}

char* CalcDynString_to_CString(CalcDynString *dynStr) {
    char str[dynStr->length];
    int i = 0;
    CalcStringNode *actual = dynStr->head;

    strcpy(str, "");
    while(actual != NULL) {
        if(actual->isString == 1) {
            strcat(str, actual->str);
            i += strlen(actual->str);
            actual = actual->next;
            continue;
        }
        str[i++] = actual->ch;
        actual = actual->next;
    }

    return(str);
}
