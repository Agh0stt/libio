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
void print_error(const char* fmt, ...);
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

// ---------------- File I/O ----------------

typedef struct {
    int fd;
    bool eof;
    bool error;
} FILE_t;

// File open modes
#define FILE_READ   1
#define FILE_WRITE  2
#define FILE_APPEND 3

FILE_t* file_open(const char* path, int mode);
int_t file_close(FILE_t* f);

int_t file_read(void* ptr, int_t size, int_t count, FILE_t* f);
int_t file_write(const void* ptr, int_t size, int_t count, FILE_t* f);

char_t* file_gets(char_t* buffer, int_t size, FILE_t* f);

int_t file_flush(FILE_t* f);

bool file_remove(const char* path);
bool file_rename(const char* oldname, const char* newname);

// ---------------- Character I/O ----------------

int_t put_char(char_t c);
int_t get_char_raw(void);

int_t put_string(const char* s);


#endif
