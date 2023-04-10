/*

    string.c
    Copyright (c) 2023 Zekronz - MIT License

*/

#include <stdlib.h>
#include <stdio.h> //@TODO: Remove this.
#include <string.h>
#include "str.h"

#define __STRING_MAX_CAPACITY (size_t)-1

string __string_create(){
    __string* str = (__string*)malloc(sizeof(__string) + 1);
    if(str == NULL) return NULL;

    str->cap = 1;
    str->len = 0;

    return (string)(&str->data);
}

string __string_create_from_string(string _str){
    size_t len = strlen(_str);
    size_t cap = 0;
    if(!__string_calc_capacity(&cap, len + 1)) return NULL;

    __string* str = (__string*)malloc(sizeof(__string) + cap);
    if(str == NULL) return NULL;

    str->cap = cap;
    str->len = len;

    for(size_t i = 0; i < len; ++i) str->data[i] = _str[i];
    str->data[len] = '\0';

    return (string)(&str->data);
}

int __string_free(string _str){
    if(_str == NULL) return 0;
    free(__string_struct(_str));
    return 1;
}

__string* __string_struct(string _str){
    if(_str == NULL) return NULL;
    return ((__string*)_str) - 1;
}

__string* __string_realloc(__string* _str, size_t _data_size){
    if(_str == NULL) return NULL;

    __string* new_str = (__string*)realloc(_str, sizeof(__string) + _data_size);
    if(new_str == NULL) return NULL;
    
    return new_str;
}

int __string_calc_capacity(size_t* _cap, size_t _dest){
    (*_cap) = 0;
    if(_dest == 0){ printf("Capacity %u\n", 1);return 1; }//@TODO: Remove this.

    size_t new_cap = 1;
    size_t prev_cap;
    while(new_cap < _dest){
        prev_cap = new_cap;
        new_cap *= 2;

        if(new_cap < prev_cap){
            new_cap = __STRING_MAX_CAPACITY;
            break;
        }
    }

    if(new_cap < _dest) return 0; //Overflow.

    (*_cap) = new_cap;
    printf("Capacity %I64u\n", new_cap); //@TODO: Remove this.
    return 1;
}

size_t __string_length(string _str){
    if(_str == NULL) return 0;
    return __string_struct(_str)->len;
}

size_t __string_capacity(string _str){
    if(_str == NULL) return 0;
    return __string_struct(_str)->cap;
}

int __string_inc(string* _str, size_t _count){
    if(_str == NULL || _count == 0) return 0;
    if((*_str) == NULL) return 0;

    __string* str = __string_struct(*_str);

    size_t new_len = str->len + _count;
    if(new_len < str->len) return 0; //Overflow.

    if(new_len + 1 > str->cap){
        size_t new_cap = 0;
        if(!__string_calc_capacity(&new_cap, new_len + 1)) return 0; //Overflow.

        __string* new_str = __string_realloc(str, new_cap);
        if(new_str == NULL) return 0;

        str = new_str;
        str->cap = new_cap;
        *_str = (string)(&str->data);
    }

    str->len = new_len;

    return 1;
}

int __string_add(string* _dst, char* _src){
    if(_dst == NULL) return 0;
    if((*_dst) == NULL) return 0;
    if((*_src) == '\0') return 1;

    __string* str = __string_struct(*_dst);

    size_t src_len = strlen(_src);
    size_t old_len = str->len;

    if(!__string_inc(_dst, src_len)) return 0;
    str = __string_struct(*_dst);

    size_t end = old_len + src_len;
    for(size_t i = old_len; i < end; ++i) str->data[i] = _src[i - old_len];
    str->data[str->len] = '\0';

    return 1;
}

int __string_add_char(string* _dst, char _chr){
    if(_dst == NULL) return 0;
    if((*_dst) == NULL) return 0;
    if(_chr == '\0') return 0;

    __string* str = __string_struct(*_dst);
    if(!__string_inc(_dst, 1)) return 0;
    str = __string_struct(*_dst);

    str->data[str->len - 1] = _chr;
    str->data[str->len] = '\0';

    return 1;
}

int __string_insert(string* _dst, size_t _index, char* _src){
    if(_dst == NULL) return 0;
    if((*_dst) == NULL) return 0;

    __string* str = __string_struct(*_dst);
    if(_index > str->len) return 0;

    if((*_src) == '\0') return 1;

    size_t old_len = str->len;
    size_t src_len = strlen(_src);
    if(!__string_inc(_dst, src_len)) return 0;
    str = __string_struct(*_dst);

    if(_index < old_len) memmove(str->data + _index + src_len, str->data + _index, (old_len - _index));

    size_t end = _index + src_len;
    for(size_t i = _index; i < end; ++i) str->data[i] = _src[i - _index];
    str->data[str->len] = '\0';

    return 1;
}

int __string_insert_char(string* _dst, size_t _index, char _chr){
    if(_dst == NULL) return 0;
    if((*_dst) == NULL) return 0;
    if(_chr == '\0') return 0;

    __string* str = __string_struct(*_dst);
    if(_index > str->len) return 0;

    size_t old_len = str->len;
    if(!__string_inc(_dst, 1)) return 0;
    str = __string_struct(*_dst);

    if(_index < old_len) memmove(str->data + _index + 1, str->data + _index, (old_len - _index));

    str->data[_index] = _chr;
    str->data[str->len] = '\0';

    return 1;
}

int __string_delete(string* _str, size_t _index, size_t _num_chars){
    if(_str == NULL || _num_chars == 0) return 0;
    if((*_str) == NULL) return 0;

    __string* str = __string_struct(*_str);

    if(_index >= str->len) return 0;
    if(_index + _num_chars - 1 < _index) return 0; //Overflow.
    if(_index + _num_chars - 1 >= str->len) _num_chars = (str->len - _index);

    size_t new_len = str->len - _num_chars;
    size_t old_cap = str->cap;
    size_t new_cap = 0;
    if(!__string_calc_capacity(&new_cap, new_len + 1)) return 0; //Overflow.

    if(_index + _num_chars - 1 < str->len - 1){
        //memmove(_str + _index - 1, _str + _index + _num_chars - 1, str->len - (_index + _num_chars));
    }

    if(old_cap != new_cap){
        __string* new_str = __string_realloc(str, new_cap);
        if(new_str == NULL) return 0;
        
        str = new_str;
        *_str = (string)(&str->data);
    }

    str->len = new_len;
    str->cap = new_cap;

    str->data[new_len] = '\0';

    return 1;
}