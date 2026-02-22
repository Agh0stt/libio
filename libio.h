// libio.h - header for libio
// copyright - (c) - Abhigyan Ghosh 2026 - present
// Lisenced under MIT Lisence
#ifndef LIBSMALL_H
#define LIBSMALL_H

// custom types
typedef unsigned char bool;
#define true 1
#define false 0

typedef char* string;
typedef char char_t;
typedef int int_t;
typedef float float_t;
typedef double double_t;

// I/O functions
void print(const char* fmt, ...);
void print(const char* fmt, ...);
int_t get_int(const char* prompt);
float_t get_float(const char* prompt);
double_t get_double(const char* prompt);
bool get_bool(const char* prompt);
char_t get_char(const char* prompt);
string get_string(const char* prompt);

// string functions
string string_cat(string s1, string s2);
string string_intpol(const char* fmt, ...);
int_t string_len(string s);
int_t string_cmp(string s1, string s2);
string string_copy(string src);
string string_to_lower(string s);

// math functions
int_t math_max(int_t a, int_t b);
int_t math_min(int_t a, int_t b);
float_t math_fmax(float_t a, float_t b);
float_t math_fmin(float_t a, float_t b);

#endif
