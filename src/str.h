/*

    string.h
    Copyright (c) 2023 Zekronz - MIT License

*/

#ifndef __STRING_H
#define __STRING_H

#ifdef __cplusplus
extern "C" {
#endif

typedef char* string;

typedef struct __string {
    size_t cap;
    size_t len;
    char data[];
} __string;

string __string_create();
string __string_create_from_string(string _str);
int __string_free(string _str);
__string* __string_struct(string _str);
__string* __string_realloc(__string* _str, size_t _data_size);
int __string_calc_capacity(size_t* _cap, size_t _dest);
size_t __string_length(string _str);
size_t __string_capacity(string _str);
int __string_inc(string* _str, size_t _count);
int __string_add(string* _dst, char* _src);
int __string_add_char(string* _dst, char _chr);
int __string_insert(string* _dst, size_t _index, char* _src);
int __string_insert_char(string* _dst, size_t _index, char _chr);
int __string_delete(string* _str, size_t _index, size_t _num_chars);

#define str_create(str) __string_create()
#define str_create_from_str(str) __string_create_from_string(str)
#define str_free(str) __string_free(str)
#define str_length(str) __string_length(str)
#define str_capacity(str) __string_capacity(str)
#define str_size(str) __string_length(str)
#define str_add(dst, src) __string_add(&dst, src)
#define str_add_char(dst, chr) __string_add_char(&dst, chr)
#define str_insert(dst, index, src) __string_insert(&dst, index, src)
#define str_insert_char(dst, index, chr) __string_insert_char(&dst, index, chr)
#define str_delete(str, index, num_chars) __string_delete(&str, index, num_chars)

#ifdef __cplusplus
}
#endif

#endif