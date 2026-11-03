# Strings in C: Notes, Programs and Mini Projects

Notes from my learning journey with strings in C, from the basics to building small text-based projects.

## Table of Contents
1. [What is a string](#1-what-is-a-string)
2. [Declaration and initialization](#2-declaration-and-initialization)
3. [Input and output](#3-input-and-output)
4. [Traversing a string](#4-traversing-a-string)
5. [String functions (string.h)](#5-string-functions-stringh)
6. [Character functions (ctype.h)](#6-character-functions-ctypeh)
7. [Writing your own string functions](#7-writing-your-own-string-functions)
8. [Common string programs](#8-common-string-programs)
9. [Array of strings (2D char array)](#9-array-of-strings-2d-char-array)
10. [Strings and functions](#10-strings-and-functions)
11. [Strings and pointers](#11-strings-and-pointers)
12. [String conversion functions](#12-string-conversion-functions)
13. [Strings in structs and files](#13-strings-in-structs-and-files)
14. [Common mistakes](#14-common-mistakes)
15. [Quick reference](#15-quick-reference)
16. [Practice programs and projects](#16-practice-programs-and-projects)
17. [How to compile and run](#17-how-to-compile-and-run)

---

## 1. What is a string

C has **no built-in string type**. A string is a **character array that ends with the null character `'\0'`**.

```
char s[] = "Hello";

index : 0   1   2   3   4   5
value : H   e   l   l   o   \0
```

Key points:
- `'\0'` (ASCII value 0) marks the end of the string. All string functions depend on it.
- A string of 5 letters needs an array of **at least 6** elements.
- `char s[50]` can hold at most **49 characters** plus `'\0'`.
- `'A'` (single quotes) is a **character**. `"A"` (double quotes) is a **string** with 2 bytes: `'A'` and `'\0'`.

---

## 2. Declaration and initialization

```c
char a[10] = "Hello";                  // H e l l o \0 and the rest are \0
char b[] = "World";                    // size 6, decided by compiler
char c[6] = {'H', 'e', 'l', 'l', 'o', '\0'};   // character by character
char d[50];                            // uninitialized, contains garbage
char e[50] = "";                       // empty string
char f[50] = {0};                      // all zeros, safe empty string
```

Wrong:
```c
char x[5] = "Hello";     // no room for '\0', not a valid string
char y[10];
y = "Hello";             // ERROR: cannot assign to an array with =
```

To assign later, use `strcpy(y, "Hello");`

### sizeof vs strlen
```c
char s[20] = "Hello";
sizeof(s);     // 20  (total array size)
strlen(s);     // 5   (characters before '\0')
```

---

## 3. Input and output

### Output
```c
printf("%s\n", s);       // print string
puts(s);                 // prints string and adds newline automatically
putchar(s[0]);           // print one character
printf("%c\n", s[0]);
```

### Input

| Method | Reads spaces? | Safe? | Notes |
|---|---|---|---|
| `scanf("%s", s)` | No (stops at space) | No, unless width given | no `&` needed |
| `scanf("%49s", s)` | No | Yes | limits to 49 characters |
| `scanf(" %49[^\n]", s)` | Yes | Yes | reads the whole line |
| `fgets(s, size, stdin)` | Yes | Yes | **best option**, keeps `'\n'` |
| `gets(s)` | Yes | **No** | removed from modern C, never use |

### fgets (recommended)
```c
char name[50];
printf("Enter name: ");
fgets(name, sizeof(name), stdin);
name[strcspn(name, "\n")] = '\0';      // remove trailing newline
```

### The newline problem
After `scanf("%d", &n);` a `'\n'` stays in the input buffer, so the next `fgets` reads an empty line.

Fixes:
```c
scanf("%d", &n);
getchar();                              // eat the leftover '\n'
fgets(name, sizeof(name), stdin);

// or
scanf("%d ", &n);                       // space after %d is risky, prefer below
scanf(" %49[^\n]", name);               // leading space skips whitespace
```

### Reading character by character
```c
int ch;
while ((ch = getchar()) != '\n' && ch != EOF) {
    // process ch
}
```

---

## 4. Traversing a string

Because every string ends with `'\0'`, you do not need the length to loop:

```c
for (int i = 0; s[i] != '\0'; i++) {
    printf("%c ", s[i]);
}
```

Using a pointer:
```c
for (char *p = s; *p != '\0'; p++) {
    printf("%c ", *p);
}
```

Count characters manually:
```c
int len = 0;
while (s[len] != '\0') len++;
```

Tip: calling `strlen(s)` inside the loop condition makes the loop slower, because it recounts every time. Store it first: `int n = strlen(s);`

---

## 5. String functions (string.h)

```c
#include <string.h>
```

| Function | Purpose | Example |
|---|---|---|
| `strlen(s)` | length without `'\0'` | `strlen("Hi")` is 2 |
| `strcpy(dest, src)` | copy src into dest | `strcpy(a, "Hello");` |
| `strncpy(dest, src, n)` | copy at most n characters | does not always add `'\0'` |
| `strcat(dest, src)` | append src to end of dest | `strcat(a, " World");` |
| `strncat(dest, src, n)` | append at most n characters | always adds `'\0'` |
| `strcmp(a, b)` | compare two strings | 0 if equal |
| `strncmp(a, b, n)` | compare first n characters | |
| `strchr(s, c)` | first occurrence of char | returns pointer or `NULL` |
| `strrchr(s, c)` | last occurrence of char | |
| `strstr(s, sub)` | find substring | returns pointer or `NULL` |
| `strspn`, `strcspn` | count matching / non-matching prefix | `strcspn(s, "\n")` finds the newline |
| `strtok(s, delim)` | split into tokens | modifies the original string |
| `memset(s, 0, n)` | fill memory | clear a buffer |

### strcmp return value
```c
strcmp("apple", "apple");    //  0   equal
strcmp("apple", "banana");   // <0   first is smaller
strcmp("banana", "apple");   // >0   first is greater
```
Never compare strings with `==`. That compares **addresses**, not content.

```c
if (strcmp(a, b) == 0) printf("Same\n");
```

### Safe copying with strncpy
```c
char dest[10];
strncpy(dest, src, sizeof(dest) - 1);
dest[sizeof(dest) - 1] = '\0';          // guarantee termination
```

### Safe formatted copy with snprintf
```c
snprintf(dest, sizeof(dest), "%s", src);      // always terminated, never overflows
snprintf(buf, sizeof(buf), "Roll %d: %s", roll, name);
```

### strstr example
```c
char *p = strstr("I love programming", "love");
if (p != NULL) printf("Found at index %ld\n", p - "I love programming");
```
For a variable `s`: `index = p - s`.

### strtok example (split a sentence into words)
```c
char s[] = "one two three";
char *word = strtok(s, " ");
while (word != NULL) {
    printf("%s\n", word);
    word = strtok(NULL, " ");
}
```
`strtok` changes the original string, so work on a copy if you need the original.

---

## 6. Character functions (ctype.h)

```c
#include <ctype.h>
```

| Function | Checks / does |
|---|---|
| `isalpha(c)` | letter (A-Z, a-z) |
| `isdigit(c)` | digit 0-9 |
| `isalnum(c)` | letter or digit |
| `isupper(c)` / `islower(c)` | case check |
| `isspace(c)` | space, tab, newline |
| `ispunct(c)` | punctuation |
| `toupper(c)` / `tolower(c)` | convert case, returns the converted char |

Without the library, using ASCII values:
```
'A' = 65 ... 'Z' = 90
'a' = 97 ... 'z' = 122
'0' = 48 ... '9' = 57
Difference between lowercase and uppercase = 32
```

```c
if (c >= 'a' && c <= 'z') c = c - 32;      // to uppercase
int digit = ch - '0';                      // '7' becomes 7
char letter = 'a' + 3;                     // 'd'
```

---

## 7. Writing your own string functions

Good practice for the logic behind the library.

### Length
```c
int my_strlen(const char s[]) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}
```

### Copy
```c
void my_strcpy(char dest[], const char src[]) {
    int i = 0;
    while ((dest[i] = src[i]) != '\0') i++;
}
```

### Concatenate
```c
void my_strcat(char dest[], const char src[]) {
    int i = 0, j = 0;
    while (dest[i] != '\0') i++;                       // go to end of dest
    while ((dest[i++] = src[j++]) != '\0');
}
```

### Compare
```c
int my_strcmp(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && a[i] == b[i]) i++;
    return (unsigned char)a[i] - (unsigned char)b[i];
}
```

### Reverse
```c
void my_strrev(char s[]) {
    int l = 0, r = strlen(s) - 1;
    while (l < r) {
        char t = s[l]; s[l] = s[r]; s[r] = t;
        l++; r--;
    }
}
```

---

## 8. Common string programs

### Palindrome check
```c
int isPalindrome(const char s[]) {
    int l = 0, r = strlen(s) - 1;
    while (l < r) {
        if (s[l] != s[r]) return 0;
        l++; r--;
    }
    return 1;
}
```
Better version: skip non-letters and ignore case (`tolower`), so "A man, a plan, a canal: Panama" works.

### Count vowels, consonants, digits, spaces
```c
int v = 0, c = 0, d = 0, sp = 0;
for (int i = 0; s[i] != '\0'; i++) {
    char ch = tolower(s[i]);
    if (isalpha(ch)) {
        if (ch=='a' || ch=='e' || ch=='i' || ch=='o' || ch=='u') v++;
        else c++;
    } else if (isdigit(ch)) d++;
    else if (isspace(ch)) sp++;
}
```

### Count words
```c
int words = 0, inWord = 0;
for (int i = 0; s[i] != '\0'; i++) {
    if (!isspace(s[i]) && !inWord) { inWord = 1; words++; }
    else if (isspace(s[i])) inWord = 0;
}
```

### Convert case
```c
for (int i = 0; s[i]; i++) s[i] = toupper(s[i]);
```

### Character frequency (lowercase letters)
```c
int freq[26] = {0};
for (int i = 0; s[i]; i++)
    if (isalpha(s[i])) freq[tolower(s[i]) - 'a']++;

for (int i = 0; i < 26; i++)
    if (freq[i] > 0) printf("%c : %d\n", 'a' + i, freq[i]);
```
This frequency array idea is useful in many problems.

### Anagram check
Two strings are anagrams if they have the same letters with the same counts.
```c
int isAnagram(const char a[], const char b[]) {
    int freq[26] = {0};
    for (int i = 0; a[i]; i++) if (isalpha(a[i])) freq[tolower(a[i]) - 'a']++;
    for (int i = 0; b[i]; i++) if (isalpha(b[i])) freq[tolower(b[i]) - 'a']--;
    for (int i = 0; i < 26; i++) if (freq[i] != 0) return 0;
    return 1;
}
```

### Remove spaces
```c
int w = 0;
for (int r = 0; s[r]; r++)
    if (s[r] != ' ') s[w++] = s[r];
s[w] = '\0';
```
The `w` / `r` pair (write and read position) is a handy pattern for removing characters in place.

### Remove duplicate characters
```c
int seen[256] = {0};
int w = 0;
for (int r = 0; s[r]; r++) {
    unsigned char ch = s[r];
    if (!seen[ch]) { seen[ch] = 1; s[w++] = ch; }
}
s[w] = '\0';
```

### Caesar cipher
```c
void encrypt(char s[], int key) {
    for (int i = 0; s[i]; i++) {
        if (isupper(s[i])) s[i] = (s[i] - 'A' + key) % 26 + 'A';
        else if (islower(s[i])) s[i] = (s[i] - 'a' + key) % 26 + 'a';
    }
}
// decrypt: encrypt(s, 26 - key);
```

### Reverse each word / reverse word order
Reverse the whole string, then reverse each word again.
```c
void rev(char s[], int l, int r) {
    while (l < r) { char t = s[l]; s[l++] = s[r]; s[r--] = t; }
}
void reverseWords(char s[]) {
    int n = strlen(s);
    rev(s, 0, n - 1);
    int start = 0;
    for (int i = 0; i <= n; i++) {
        if (s[i] == ' ' || s[i] == '\0') {
            rev(s, start, i - 1);
            start = i + 1;
        }
    }
}
```

### Largest word / longest word
Use `strtok` or manual traversal, tracking the length of the current word and the best so far.

### Check if a string contains only digits
```c
int allDigits(const char s[]) {
    if (s[0] == '\0') return 0;
    for (int i = 0; s[i]; i++) if (!isdigit(s[i])) return 0;
    return 1;
}
```

### Substring search (without strstr)
```c
int find(const char s[], const char sub[]) {
    int n = strlen(s), m = strlen(sub);
    for (int i = 0; i + m <= n; i++) {
        int j = 0;
        while (j < m && s[i + j] == sub[j]) j++;
        if (j == m) return i;
    }
    return -1;
}
```

---

## 9. Array of strings (2D char array)

```c
char names[5][30];               // 5 strings, each up to 29 characters
```

### Input and output
```c
for (int i = 0; i < 5; i++) {
    printf("Name %d: ", i + 1);
    fgets(names[i], sizeof(names[i]), stdin);
    names[i][strcspn(names[i], "\n")] = '\0';
}

for (int i = 0; i < 5; i++) printf("%s\n", names[i]);
```

### Initialize directly
```c
char days[3][10] = {"Mon", "Tue", "Wed"};
```

### Sort names alphabetically
```c
char temp[30];
for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++)
        if (strcmp(names[j], names[j + 1]) > 0) {
            strcpy(temp, names[j]);
            strcpy(names[j], names[j + 1]);
            strcpy(names[j + 1], temp);
        }
```

### Search a name
```c
for (int i = 0; i < n; i++)
    if (strcmp(names[i], key) == 0) { printf("Found at %d\n", i); break; }
```

### Array of pointers (strings that never change)
```c
const char *months[] = {"Jan", "Feb", "Mar"};
printf("%s\n", months[1]);       // Feb
```
Good for fixed lookup tables. Each string is stored as a read-only literal, so you cannot modify it.

---

## 10. Strings and functions

A string is passed **by address** (as a `char` pointer), so the function can change the original.

```c
void toUpper(char s[]) {                 // modifies original
    for (int i = 0; s[i]; i++) s[i] = toupper(s[i]);
}

int countChar(const char s[], char c) {  // const: only reads
    int count = 0;
    for (int i = 0; s[i]; i++) if (s[i] == c) count++;
    return count;
}
```

Notes:
- You do **not** need to pass the length, because `'\0'` marks the end.
- Use `const char s[]` when the function must not change the string.
- When a function writes into a buffer (copy, concatenate), pass the **buffer size** too, so it cannot overflow.
- A function cannot return a local array. Either pass an output buffer as a parameter, or use `malloc`.

```c
void getInitials(const char name[], char out[], int outSize);
```

---

## 11. Strings and pointers

```c
char arr[] = "Hello";        // array: a modifiable copy stored in your variable
char *ptr = "Hello";         // pointer to a string literal (read-only memory)
```

| | `char arr[] = "Hello"` | `char *ptr = "Hello"` |
|---|---|---|
| Can modify characters | Yes | **No** (undefined behavior) |
| Can reassign | No | Yes (`ptr = "Bye";`) |
| `sizeof` | 6 | pointer size (8) |

Better to write `const char *ptr = "Hello";` so the compiler warns you if you try to modify it.

Pointer arithmetic on strings:
```c
char s[] = "Hello";
printf("%c", *(s + 1));       // e
printf("%s", s + 2);          // llo   (string starting from index 2)
```

---

## 12. String conversion functions

```c
#include <stdlib.h>
#include <stdio.h>
```

### String to number
```c
int n = atoi("123");                // simple, no error checking
double d = atof("3.14");

char *end;
long x = strtol("123abc", &end, 10);    // end points to "abc", safer
```

### Number to string
```c
char buf[20];
sprintf(buf, "%d", 456);                 // buf = "456"
snprintf(buf, sizeof(buf), "%.2f", 3.14159);   // buf = "3.14", safer
```

### Manual conversion (a good exercise)
```c
int value = 0;
for (int i = 0; s[i]; i++) value = value * 10 + (s[i] - '0');
```

### Reading a number safely
Read the line with `fgets`, then convert with `strtol`. This avoids infinite loops when the user types letters into `scanf("%d")`.

---

## 13. Strings in structs and files

### Strings inside a struct
```c
typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

Student s;
strcpy(s.name, "Krish");          // not s.name = "Krish"
```

### Search records by name
```c
for (int i = 0; i < count; i++)
    if (strcmp(students[i].name, key) == 0) { /* found */ }
```

### Case-insensitive search
Convert both strings to lowercase copies, then compare. (`strcasecmp` exists on Linux/macOS but is not standard C.)

### Write strings to a file
```c
FILE *f = fopen("names.txt", "w");
if (f == NULL) { printf("Error\n"); return 1; }
fprintf(f, "%s\n", name);
fclose(f);
```

### Read lines from a file
```c
FILE *f = fopen("names.txt", "r");
char line[100];
while (fgets(line, sizeof(line), f) != NULL) {
    line[strcspn(line, "\n")] = '\0';
    printf("%s\n", line);
}
fclose(f);
```

### Saving records with spaces in names
Use a delimiter and `fprintf`/`fgets` with `strtok`, or write the struct in binary with `fwrite`.
```c
fprintf(f, "%d,%s,%.2f\n", s.roll, s.name, s.marks);
```

---

## 14. Common mistakes

| Mistake | Fix |
|---|---|
| Forgetting space for `'\0'` | array size = characters + 1 |
| `if (a == b)` to compare strings | `strcmp(a, b) == 0` |
| `a = "text";` to assign a string | `strcpy(a, "text");` |
| `scanf("%s", name)` for names with spaces | `fgets` or `scanf(" %49[^\n]", name)` |
| `scanf("%s", &name)` | no `&` for arrays |
| Using `gets()` | use `fgets()` |
| Leftover `'\n'` after `scanf("%d")` | `getchar()` or `" %[^\n]"` |
| Newline at the end of `fgets` input | remove with `strcspn` |
| `strcpy` into a too-small buffer | check sizes, use `snprintf` or `strncpy` |
| `strncpy` not adding `'\0'` | set the last character to `'\0'` yourself |
| Modifying a string literal (`char *p = "Hi"; p[0] = 'h';`) | use `char p[] = "Hi";` |
| `strlen` in loop condition on long strings | store length in a variable |
| Using an uninitialized `char` array as a string | initialize with `= {0}` |
| `strtok` destroying your original string | copy first |
| `toupper`/`tolower` on a negative `char` | cast to `unsigned char` when handling non-ASCII input |
| Comparing `'a'` with `"a"` | single quotes for char, double quotes for string |
| Returning a local array from a function | pass in an output buffer |

Compile with `-Wall -Wextra -fsanitize=address,undefined` during practice to catch overflows early.

---

## 15. Quick reference

```c
char s[50];                          // string of up to 49 characters
fgets(s, sizeof(s), stdin);          // read a line
s[strcspn(s, "\n")] = '\0';          // strip newline
strlen(s)                            // length
strcpy(d, s)                         // copy
strcat(d, s)                         // append
strcmp(a, b) == 0                    // equal?
strstr(s, "sub")                     // find substring
toupper(c), tolower(c)               // case
c - '0'                              // digit char to int
'a' + i                              // int to letter
snprintf(buf, sizeof(buf), "%d", n)  // number to string
```

---

## 16. Practice programs and projects

### Basic
1. Print a string character by character
2. Find length without `strlen`
3. Copy a string without `strcpy`
4. Concatenate two strings without `strcat`
5. Compare two strings without `strcmp`
6. Reverse a string

### Intermediate
7. Palindrome check
8. Count vowels, consonants, digits, spaces
9. Count words in a sentence
10. Convert uppercase to lowercase and back
11. Toggle the case of each letter
12. Character frequency
13. Anagram check
14. Remove spaces / remove duplicate characters
15. Find the first non-repeating character
16. Replace a character in a string
17. Count occurrences of a substring

### Advanced
18. Reverse words in a sentence
19. Longest word in a sentence
20. Caesar cipher (encrypt and decrypt)
21. Sort names alphabetically (2D char array)
22. Check if a string is a valid number
23. Run-length encoding (`aaabb` becomes `a3b2`)
24. Capitalize the first letter of each word
25. Check if two strings are rotations of each other

### Mini projects
- **Password strength checker**: length, uppercase, lowercase, digit, special character, with a score
- **Text analyzer**: characters, words, sentences, most common letter, longest word
- **Contact book**: names and phone numbers, with search by name and save to file
- **Simple login system**: usernames and passwords stored in arrays or a file
- **Hangman game**: secret word, guessed letters, remaining lives
- **Caesar cipher tool**: menu with encrypt, decrypt, and brute force
- **Word counter / find-and-replace tool** on a text file

---

## 17. How to compile and run

```bash
gcc program.c -o program -Wall -Wextra
./program            # Linux / macOS
program.exe          # Windows
```

---

## Progress tracker

- [ ] String basics: declare, input, output, traverse
- [ ] string.h functions
- [ ] ctype.h functions
- [ ] Own versions of strlen, strcpy, strcat, strcmp
- [ ] Palindrome, vowels, word count, frequency, anagram
- [ ] Array of strings and sorting names
- [ ] Strings in structs and files
- [ ] Password strength checker
- [ ] Text analyzer
- [ ] Hangman or Caesar cipher tool

## What I learned
_Update this section after each stage._

