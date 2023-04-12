# C String
Dynamic string implementation in C, designed to be fast, flexible and easy-to-use.  
The library contains many functions for using and manipulating strings.  
Characters can easily be accessed using the `[]` operator.  
Compatible with C++.  

## Basic Usage
Creating strings:
```c
string str1 = str_create(); // Creates an empty string.
string str2 = str_create_from_str("Hello, World!"); // Creates a string with the given input.

// The "string" type is really just a char pointer and can be treated as such.
printf("%s\n", str2); // Prints out "Hello, World!"
```

Freeing strings:
```c
str_free(str); // Frees the allocated memory of the string.
```

Accessing characters:
```c
// Characters can be accessed using the [] operator. Note: This does not check if the index is within the string's range.
char c = str[0];
str[1] = 'A';

// You can also use str_get/str_set to read and write individual characters. These functions contain boundary checks.
char c = str_get(str, 0);
str_set(str, 1, 'A');
```

Adding/removing characters:
```c
str_add(str, "Hello"); // Appends "Hello" to the end of the string.
str_add(str1, str2); // Appends str2 at the end of str1.
str_insert(str, 4, "Hello"); // Inserts "Hello" at index 4 of the string.
str_delete(str, 4, 5); // Removes 5 characters from the string, starting from index 4.
str_clear(str); // Clears the entire string and sets its length to 0.

// There are also similar functions for adding individual characters:
str_add_char(str, 'I'); // Appends the character 'I' to the end of the string.
str_insert_char(str, 0, 'H'); // Inserts the character 'H' at index 0 of the string.

// Strings will reallocate its capacity if necessary.
```

Substrings:
```c
string substr = str_substr(str, 4, 8); // Copies 8 characters starting at index 4 and returns a new string.

int pos1 = str_find(str, "Hello"); // Finds the first occurrence of "Hello" and returns its position. Returns -1 if no are found.
int pos2 = str_find_from(str, "World", 5); // Finds the first occurrence of "World", starting from index 5, and returns its position. Returns -1 if no are found.

// Similar functions for individual characters also exist:
str_find_char(str, 'H'); // Finds the first occurrence character 'H'. Returns -1 if no are found.
str_find_char_from(str, 'W', 5); // Finds the first occurrence of 'W' starting from index 5. Returns -1 if no are found.

str_replace_first(str, "Hello", "Hey"); // Replaces the first occurrence of "Hello" with "Hey".
str_replace_all(str, "Hello", "Hey"); // Replaces the all occurrences of "Hello" with "Hey".

size_t count1 = str_count(str, "World"); // Returns the total number times "World" appears in the string.
size_t count2 = str_count_char(str, 'A'); // Returns the total number of times the character 'A' appears in the string.

```

Resizing strings:
```c
str_resive(str, 8); // Resizes the string to be 8 characters long. If expanded, any new memory will be uninitialized.
str_reserve(str, 16); // Reserves enough memory to contain at least 16 characters + the null terminator. Length will stay the same.
str_shrink(str) // Shrinks the string's capacity to its length + the null terminator.
```

Filling strings:
```c
str_fill(str, 'A'); // Fills the entire string with the character 'A'.
str_fill_range(str, 8, 4, 'B'); // Fills 4 characters of the string with the character 'B' starting from index 8.
```

Other functions:
```c
str_reverse(str); // Reverses the characters in the given string.
string clone = str_clone(str); // Clones the given string and returns a pointer to it.
```

## Function List
```c
str_create(str);
str_create_from_str(str);
str_free(str);
str_length(str);
str_size(str);
str_capacity(str);
str_empty(str);
str_compare(str1, str2);
str_get(str, index);
str_set(str, index, chr);
str_add(dst, src);
str_add_char(dst, chr);
str_insert(dst, index, src);
str_insert_char(dst, index, chr);
str_delete(str, index, num_chars);
str_clear(str);
str_reverse(str);
str_fill(str, chr);
str_fill_range(str, index, num_chars, chr);
str_clone(str);
str_substr(str, index, num_chars);
str_find(str, substr);
str_find_char(str, chr);
str_find_from(str, substr, index);
str_find_char_from(str, chr, index);
str_replace_all(str, substr, new_substr);
str_replace_first(str, substr, new_substr);
str_count(str, substr);
str_count_char(str, chr);
str_resize(str, num_chars);
str_reserve(str, num_chars);
str_shrink(str);
```

## Memory Layout
The memory of strings is layed out like so:
```
+-----------------+---------------+---------------------+
| size_t capacity | size_t length | char data[capacity] |
+-----------------+---------------+---------------------+
                                  ^
                                  |
                      Pointer given to the user.
```
