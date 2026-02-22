// libio.c - C implementation of libio
// Copyright - (c) - Abhigyan Ghosh 2026 - present
// Lisenced under MIT Lisence
#include "include/libio.h"
#include <unistd.h>   // for read/write
#include <stdarg.h>   // for va_list in print

// ---------------- Output ----------------
void print(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    // expanded %s, %i, %f, %c, %b support for interpolation
    char buffer[512];
    int b = 0;
    for (int i = 0; fmt[i] != '\0' && b < 511; i++)
    {
        if (fmt[i] == '%' && fmt[i+1] != '\0')
        {
            i++;
            if (fmt[i] == 's') {
                char* s = va_arg(args, char*);
                for (int j = 0; s[j] != '\0' && b < 511; j++) buffer[b++] = s[j];
            } else if (fmt[i] == 'i') {
                int_t n = va_arg(args, int_t);
                // simple int -> string
                char tmp[20];
                int k = 0;
                if (n == 0) tmp[k++]='0';
                else {
                    bool neg = n<0; if(neg) n=-n;
                    while(n>0){ tmp[k++]= (n%10)+'0'; n/=10; }
                    if(neg) tmp[k++]='-';
                    // reverse
                    for(int t=0; t<k/2; t++){ char x=tmp[t]; tmp[t]=tmp[k-1-t]; tmp[k-1-t]=x; }
                }

                for(int t=0;t<k && b<511;t++) buffer[b++]=tmp[t];

  } else if (fmt[i] == 'f') {
    double f = va_arg(args, double);           // ← changed to double
    // now convert double → your float_t if you really want, but usually just work with double
    // (or keep as double for printing)
    int_t int_part = (int_t)f;
    double frac_part = f - int_part;           // ← use double here
    if (frac_part < 0) frac_part = -frac_part;

    // int part (same as before, but using double → int_t cast)
    char tmp[32];  // bigger to be safe
    int k = 0;
    bool neg = f < 0.0;
    int_t n_abs = neg ? -(int_t)f : (int_t)f;
    if (n_abs == 0) tmp[k++] = '0';
    else {
        while (n_abs > 0) { tmp[k++] = (n_abs % 10) + '0'; n_abs /= 10; }
        if (neg) tmp[k++] = '-';
        // reverse
        for (int t = 0; t < k/2; t++) {
            char x = tmp[t]; tmp[t] = tmp[k-1-t]; tmp[k-1-t] = x;
        }
    }
    for (int t = 0; t < k && b < 511; t++) buffer[b++] = tmp[t];

    buffer[b++] = '.';

    // fractional part - 6 digits (using double)
    for (int d = 0; d < 6; d++) {
        frac_part *= 10.0;
        int_t digit = (int_t)frac_part;
        buffer[b++] = digit + '0';
        frac_part -= digit;
    }

} else if (fmt[i] == 'c') {
    int c_promoted = va_arg(args, int);        // ← changed to int
    buffer[b++] = (char_t)c_promoted;          // cast back if you want

} else if (fmt[i] == 'b') {
    int bb_promoted = va_arg(args, int);       // ← changed to int
    bool bb = (bb_promoted != 0);              // treat 0 as false, nonzero as true
    char* bs = bb ? "true" : "false";
    for (int j = 0; bs[j] != '\0' && b < 511; j++) buffer[b++] = bs[j];
            }
            continue;
        }
        buffer[b++] = fmt[i];
    }
    buffer[b] = '\0';
    va_end(args);

    // calculate length
    int len = 0;
    while(buffer[len] != '\0') len++;
    write(1, buffer, len);
    write(1, "\n", 1);
}
// ---------------- Error Output ----------------
void print_error(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    char buffer[512];
    int b = 0;

    // Same formatting logic as print() — supports %s, %i, %f, %c, %b (copy your existing logic)
    for (int i = 0; fmt[i] != '\0' && b < 511; i++)
    {
        if (fmt[i] == '%' && fmt[i+1] != '\0')
        {
            i++;
            if (fmt[i] == 's') {
                char* s = va_arg(args, char*);
                for (int j = 0; s[j] != '\0' && b < 511; j++) buffer[b++] = s[j];
            } else if (fmt[i] == 'i') {
                int_t n = va_arg(args, int_t);
                char tmp[20];
                int k = 0;
                if (n == 0) tmp[k++] = '0';
                else {
                    bool neg = n < 0; if (neg) n = -n;
                    while (n > 0) { tmp[k++] = (n % 10) + '0'; n /= 10; }
                    if (neg) tmp[k++] = '-';
                    for (int t = 0; t < k/2; t++) {
                        char x = tmp[t]; tmp[t] = tmp[k-1-t]; tmp[k-1-t] = x;
                    }
                }
                for (int t = 0; t < k && b < 511; t++) buffer[b++] = tmp[t];
            } else if (fmt[i] == 'f') {
                double f = va_arg(args, double);
                // Reuse / copy  full %f logic from print() here
                // (int part + '.' + 6 fractional digits – paste it from your existing code)
                int_t int_part = (int_t)f;
                double frac_part = f - int_part;
                if (frac_part < 0) frac_part = -frac_part;

                char tmp[32];
                int k = 0;
                bool neg = f < 0.0;
                int_t n_abs = neg ? -(int_t)f : (int_t)f;
                if (n_abs == 0) tmp[k++] = '0';
                else {
                    while (n_abs > 0) { tmp[k++] = (n_abs % 10) + '0'; n_abs /= 10; }
                    if (neg) tmp[k++] = '-';
                    for (int t = 0; t < k/2; t++) {
                        char x = tmp[t]; tmp[t] = tmp[k-1-t]; tmp[k-1-t] = x;
                    }
                }
                for (int t = 0; t < k && b < 511; t++) buffer[b++] = tmp[t];

                buffer[b++] = '.';

                for (int d = 0; d < 6; d++) {
                    frac_part *= 10.0;
                    int_t digit = (int_t)frac_part;
                    buffer[b++] = digit + '0';
                    frac_part -= digit;
                }
            } else if (fmt[i] == 'c') {
                int c = va_arg(args, int);
                buffer[b++] = (char)c;
            } else if (fmt[i] == 'b') {
                int bb_promoted = va_arg(args, int);
                bool bb = (bb_promoted != 0);
                char* bs = bb ? "true" : "false";
                for (int j = 0; bs[j] != '\0' && b < 511; j++) buffer[b++] = bs[j];
            }
            continue;
        }
        buffer[b++] = fmt[i];
    }
    buffer[b] = '\0';
    va_end(args);

    // Write to stderr (fd = 2)
    int len = 0;
    while (buffer[len] != '\0') len++;
    write(2, buffer, len);
    write(2, "\n", 1);
}
// ---------------- Input ----------------
string get_string(const char* prompt)
{
    if(prompt) print(prompt);
    static char buffer[256];
    int i=0;
    char c;
    while(1)
    {
        int n=read(0,&c,1);
        if(n!=1) continue;
        if(c=='\n'){ buffer[i]='\0'; return buffer; }
        if(i<255) buffer[i++]=c;
    }
}

char_t get_char(const char* prompt)
{
    if(prompt) print(prompt);
    char c;
    while(1)
    {
        int n=read(0,&c,1);
        if(n==1 && c!='\n') return c;
    }
}

int_t get_int(const char* prompt)
{
    string s = get_string(prompt);
    int_t val = 0, sign=1;
    int i=0;
    if(s[0]=='-'){ sign=-1; i=1; }
    for(; s[i]!='\0'; i++){ val = val*10 + (s[i]-'0'); }
    return val*sign;
}

float_t get_float(const char* prompt)
{
    string s = get_string(prompt);
    float_t val = 0.0f, sign=1.0f;
    int i=0, dec=0; float_t frac=0.1f;
    if(s[0]=='-'){ sign=-1.0f; i=1; }
    for(; s[i]!='\0'; i++)
    {
        if(s[i]=='.'){ dec=1; i++; }
        if(dec){
            val += (s[i]-'0')*frac;
            frac*=0.1f;
        } else val = val*10 + (s[i]-'0');
    }
    return val*sign;
}

double_t get_double(const char* prompt)
{
    string s = get_string(prompt);
    double_t val = 0.0, sign=1.0;
    int i=0, dec=0; double_t frac=0.1;
    if(s[0]=='-'){ sign=-1.0; i=1; }
    for(; s[i]!='\0'; i++)
    {
        if(s[i]=='.'){ dec=1; i++; }
        if(dec){
            val += (s[i]-'0')*frac;
            frac*=0.1;
        } else val = val*10 + (s[i]-'0');
    }
    return val*sign;
}

bool get_bool(const char* prompt)
{
    string s = get_string(prompt);
    if(s[0]=='1'||s[0]=='t'||s[0]=='T'||s[0]=='y'||s[0]=='Y') return true;
    return false;
}

// ---------------- String helpers ----------------
string string_cat(string s1, string s2)
{
    static char buffer[512];
    int i=0,j=0;
    while(s1[i]!='\0'){ buffer[i]=s1[i]; i++; }
    while(s2[j]!='\0'){ buffer[i++]=s2[j++]; }
    buffer[i]='\0';
    return buffer;
}

string string_intpol(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char buffer[512];
    int b=0;
    for(int i=0; fmt[i]!='\0' && b<511; i++)
    {
        if(fmt[i]=='%' && fmt[i+1]!='\0')
        {
            i++;
            if(fmt[i]=='s'){
                char* s=va_arg(args,char*);
                int j=0; while(s[j]!='\0' && b<511) buffer[b++]=s[j++];
            } else if(fmt[i]=='i'){
                int_t n=va_arg(args,int_t);
                char tmp[20]; int k=0;
                if(n==0) tmp[k++]='0';
                else { bool neg=n<0; if(neg)n=-n;
                    while(n>0){ tmp[k++]=n%10+'0'; n/=10; }
                    if(neg) tmp[k++]='-';
                    for(int t=0;t<k/2;t++){ char x=tmp[t]; tmp[t]=tmp[k-1-t]; tmp[k-1-t]=x; }
                }
                for(int t=0;t<k && b<511;t++) buffer[b++]=tmp[t];


   } else if (fmt[i] == 'f') {
    double f = va_arg(args, double);           // ← changed to double
    // now convert double → your float_t if you really want, but usually just work with double
    // (or keep as double for printing)
    int_t int_part = (int_t)f;
    double frac_part = f - int_part;           // ← use double here
    if (frac_part < 0) frac_part = -frac_part;

    // int part (same as before, but using double → int_t cast)
    char tmp[32];  // bigger to be safe
    int k = 0;
    bool neg = f < 0.0;
    int_t n_abs = neg ? -(int_t)f : (int_t)f;
    if (n_abs == 0) tmp[k++] = '0';
    else {
        while (n_abs > 0) { tmp[k++] = (n_abs % 10) + '0'; n_abs /= 10; }
        if (neg) tmp[k++] = '-';
        // reverse
        for (int t = 0; t < k/2; t++) {
            char x = tmp[t]; tmp[t] = tmp[k-1-t]; tmp[k-1-t] = x;
        }
    }
    for (int t = 0; t < k && b < 511; t++) buffer[b++] = tmp[t];

    buffer[b++] = '.';

    // fractional part - 6 digits (using double)
    for (int d = 0; d < 6; d++) {
        frac_part *= 10.0;
        int_t digit = (int_t)frac_part;
        buffer[b++] = digit + '0';
        frac_part -= digit;
    }

} else if (fmt[i] == 'c') {
    int c_promoted = va_arg(args, int);        // ← changed to int
    buffer[b++] = (char_t)c_promoted;          // cast back if you want

} else if (fmt[i] == 'b') {
    int bb_promoted = va_arg(args, int);       // ← changed to int
    bool bb = (bb_promoted != 0);              // treat 0 as false, nonzero as true
    char* bs = bb ? "true" : "false";
    for (int j = 0; bs[j] != '\0' && b < 511; j++) buffer[b++] = bs[j];
            }
            continue;
        }
        buffer[b++]=fmt[i];
    }
    buffer[b]='\0';
    va_end(args);
    return string_cat("",buffer);
}

int_t string_len(string s) {
    int_t len = 0;
    while (s[len] != '\0') len++;
    return len;
}

int_t string_cmp(string s1, string s2) {
    int i = 0;
    while (s1[i] != '\0' && s2[i] != '\0') {
        if (s1[i] != s2[i]) return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

string string_copy(string src) {
    static char buffer[512];
    int i = 0;
    while (src[i] != '\0' && i < 511) {
        buffer[i] = src[i];
        i++;
    }
    buffer[i] = '\0';
    return buffer;
}

string string_to_lower(string s) {
    static char buffer[512];
    int i = 0;
    while (s[i] != '\0' && i < 511) {
        if (s[i] >= 'A' && s[i] <= 'Z') {
            buffer[i] = s[i] + 32;
        } else {
            buffer[i] = s[i];
        }
        i++;
    }
    buffer[i] = '\0';
    return buffer;
}

// ---------------- Math helpers ----------------
int_t math_max(int_t a, int_t b) {
    return a > b ? a : b;
}

int_t math_min(int_t a, int_t b) {
    return a < b ? a : b;
}

float_t math_fmax(float_t a, float_t b) {
    return a > b ? a : b;
}

float_t math_fmin(float_t a, float_t b) {
    return a < b ? a : b;
}
