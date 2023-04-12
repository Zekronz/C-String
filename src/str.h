/*

    str.h
    Copyright (c) 2023 Zekronz - MIT License
    
    https://github.com/Zekronz/C-String

*/

#ifndef __ZEKRONZ_STRING_H
#define __ZEKRONZ_STRING_H

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
int __string_empty(string _str);
int __string_compare(string str1, string str2);
int __string_inc(string* _str, size_t _count);
char __string_get(string _str, size_t _index);
int __string_set(string _str, size_t _index, char _chr);
int __string_add(string* _dst, char* _src);
int __string_add_char(string* _dst, char _chr);
int __string_insert(string* _dst, size_t _index, char* _src);
int __string_insert_char(string* _dst, size_t _index, char _chr);
int __string_delete(string* _str, size_t _index, size_t _num_chars);
int __string_clear(string* _str);
int __string_reverse(string _str);
int __string_fill(string _str, char _chr);
int __string_fill_range(string _str, size_t _index, size_t _num_chars, char _chr);
string __string_substr(string _str, size_t _index, size_t _num_chars);
string __string_clone(string _str);
int __string_find_from(string _str, char* _substr, size_t _index);
int __string_find_char_from(string _str, char _chr, size_t _index);
int __string_replace(string* _str, char* _substr, char* _new_substr, int _first);
size_t __string_count(string _str, char* _substr);
size_t __string_count_char(string _str, char _chr);
int __string_resize(string* _str, size_t _num_chars);
int __string_reserve(string* _str, size_t _num_chars);
int __string_shrink(string* _str);

#define str_create(str) __string_create()
#define str_create_from_str(str) __string_create_from_string(str)
#define str_free(str) __string_free(str)
#define str_length(str) __string_length(str)
#define str_size(str) __string_length(str)
#define str_capacity(str) __string_capacity(str)
#define str_empty(str) __string_empty(str)
#define str_compare(str1, str2) __string_compare(str1, str2)
#define str_get(str, index) __string_get(str, index)
#define str_set(str, index, chr) __string_set(str, index, chr)
#define str_add(dst, src) __string_add(&dst, src)
#define str_add_char(dst, chr) __string_add_char(&dst, chr)
#define str_insert(dst, index, src) __string_insert(&dst, index, src)
#define str_insert_char(dst, index, chr) __string_insert_char(&dst, index, chr)
#define str_delete(str, index, num_chars) __string_delete(&str, index, num_chars)
#define str_clear(str) __string_clear(&str)
#define str_reverse(str) __string_reverse(str)
#define str_fill(str, chr) __string_fill(str, chr)
#define str_fill_range(str, index, num_chars, chr) __string_fill_range(str, index, num_chars, chr)
#define str_clone(str) __string_clone(str)
#define str_substr(str, index, num_chars) __string_substr(str, index, num_chars)
#define str_find(str, substr) __string_find_from(str, substr, 0)
#define str_find_char(str, chr) __string_find_char_from(str, chr, 0)
#define str_find_from(str, substr, index) __string_find_from(str, substr, index)
#define str_find_char_from(str, chr, index) __string_find_char_from(str, chr, index)
#define str_replace_all(str, substr, new_substr) __string_replace(&str, substr, new_substr, 0)
#define str_replace_first(str, substr, new_substr) __string_replace(&str, substr, new_substr, 1)
#define str_count(str, substr) __string_count(str, substr)
#define str_count_char(str, chr) __string_count_char(str, chr)
#define str_resize(str, num_chars) __string_resize(&str, num_chars)
#define str_reserve(str, num_chars) __string_reserve(&str, num_chars)
#define str_shrink(str) __string_shrink(&str)

#ifdef __cplusplus
}
#endif

#endif