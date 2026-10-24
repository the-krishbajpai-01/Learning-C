# C Arrays Notes

My learning journey with arrays in C.

# Table of Contents
1. [What is an array](#1-what-is-an-array)
2. [Declaration and initialization](#2-declaration-and-initialization)
3. [Input, output and traversal](#3-input-output-and-traversal)
4. [Common operations](#4-common-operations)
5. [Arrays and functions](#5-arrays-and-functions)
6. [Strings (character arrays)](#6-strings-character-arrays)
7. [2D arrays](#7-2d-arrays)
8. [Array of structures](#8-array-of-structures)
9. [File handling with arrays](#9-file-handling-with-arrays)
10. [Dynamic arrays (intro)](#10-dynamic-arrays-intro)
11. [Common mistakes](#11-common-mistakes)
12. [Quick reference](#12-quick-reference)
13. [Repository structure](#13-repository-structure)
14. [How to compile and run](#14-how-to-compile-and-run)

---

## 1. What is an array

An array is a collection of **elements of the same data type** stored in **continuous memory locations**, accessed using an **index**.

```
int a[5] = {10, 20, 30, 40, 50};

index :    0    1    2    3    4
value :   10   20   30   40   50
address: 1000 1004 1008 1012 1016   (int = 4 bytes)
```

Key points:
- Index starts at **0**. The last valid index is `size - 1`.
- All elements have the **same type**.
- Size is **fixed** once declared (for normal arrays).
- Access by index is fast: `address = base + index * sizeof(type)`.
- C does **not** check bounds. `a[5]` on a size-5 array is a bug (undefined behavior).

---

## 2. Declaration and initialization

```c
int a[5];                       // declared, contains garbage values (local array)
int b[5] = {1, 2, 3, 4, 5};     // full initialization
int c[5] = {1, 2};              // rest become 0 -> {1, 2, 0, 0, 0}
int d[] = {4, 5, 6};            // size decided by compiler = 3
int e[100] = {0};               // all elements 0
```

Finding the number of elements:

```c
int n = sizeof(d) / sizeof(d[0]);   // works only where the array is declared
```

Rules:
- Local arrays are **not** auto-initialized. Always initialize them.
- Global and static arrays are automatically set to 0.
- Size must be a positive integer.

---

## 3. Input, output and traversal

```c
#include <stdio.h>

int main(void) {
    int n;
    printf("Enter size: ");
    scanf("%d", &n);

    int a[100];                          // fixed maximum size
    if (n < 1 || n > 100) {
        printf("Invalid size\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {        // input
        printf("a[%d] = ", i);
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < n; i++)          // output
        printf("%d ", a[i]);

    return 0;
}
```

Remember: `scanf` needs `&` for array elements (`&a[i]`), but not for strings.

---

## 4. Common operations

### Sum and average
```c
int sum = 0;
for (int i = 0; i < n; i++) sum += a[i];
float avg = (float)sum / n;
```

### Maximum and minimum
```c
int max = a[0], min = a[0];
for (int i = 1; i < n; i++) {
    if (a[i] > max) max = a[i];
    if (a[i] < min) min = a[i];
}
```

### Linear search
```c
int pos = -1;
for (int i = 0; i < n; i++) {
    if (a[i] == key) { pos = i; break; }
}
```

### Reverse
```c
for (int l = 0, r = n - 1; l < r; l++, r--) {
    int t = a[l]; a[l] = a[r]; a[r] = t;
}
```

### Insert at a position
```c
// array must have spare space
for (int i = n; i > pos; i--) a[i] = a[i - 1];   // shift right
a[pos] = value;
n++;
```

### Delete from a position
```c
for (int i = pos; i < n - 1; i++) a[i] = a[i + 1];   // shift left
n--;
```

### Bubble sort
```c
for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - 1 - i; j++)
        if (a[j] > a[j + 1]) {
            int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
        }
```

### Frequency counting (small known range)
```c
int freq[10] = {0};                  // for digits 0-9
for (int i = 0; i < n; i++) freq[a[i]]++;
```

### Time complexity summary

| Operation | Time |
|---|---|
| Access by index | O(1) |
| Search (unsorted) | O(n) |
| Insert / delete in middle | O(n) |
| Insert at end (space available) | O(1) |
| Bubble / selection sort | O(n^2) |

---

## 5. Arrays and functions

An array is passed to a function **by address**, so changes inside the function affect the original array. Always pass the size separately.

```c
void display(int a[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");
}

void doubleAll(int a[], int n) {
    for (int i = 0; i < n; i++) a[i] *= 2;     // changes original
}

int main(void) {
    int a[] = {1, 2, 3};
    doubleAll(a, 3);
    display(a, 3);        // 2 4 6
    return 0;
}
```

Important:
- `int a[]` and `int *a` mean the same in a parameter.
- `sizeof(a)` inside the function gives the **pointer size**, not the array size.
- Use `const int a[]` if the function must not modify the array.
- A function cannot return a local array. Pass an output array as a parameter instead.

### Array name and pointers
```c
int a[3] = {10, 20, 30};
printf("%d", *(a + 1));    // 20, same as a[1]
```
`a[i]` is the same as `*(a + i)`.

---

## 6. Strings (character arrays)

A string is a `char` array that ends with the null character `'\0'`.

```c
char s1[10] = "Hello";               // stored: H e l l o \0
char s2[] = "World";                 // size 6 (5 letters + \0)
```

A `char s[50]` can hold at most **49 characters** plus `'\0'`.

### Taking input safely
```c
char name[50];
fgets(name, sizeof(name), stdin);          // reads spaces too
name[strcspn(name, "\n")] = '\0';          // remove newline

scanf("%49s", name);                       // one word only
scanf(" %49[^\n]", name);                  // whole line
```
Never use `gets()`. It is unsafe and removed from modern C.

### Useful functions (`<string.h>`)

| Function | Purpose |
|---|---|
| `strlen(s)` | length (without `\0`) |
| `strcpy(dest, src)` | copy string |
| `strcat(dest, src)` | append string |
| `strcmp(a, b)` | 0 if equal, negative/positive otherwise |
| `strrev` | not standard C, write your own |

Character functions (`<ctype.h>`): `isalpha`, `isdigit`, `isupper`, `islower`, `toupper`, `tolower`.

### Example: palindrome check
```c
int isPalindrome(char s[]) {
    int l = 0, r = strlen(s) - 1;
    while (l < r) {
        if (s[l++] != s[r--]) return 0;
    }
    return 1;
}
```

---

## 7. 2D arrays

An array of arrays, used for tables, matrices, grids and boards.

```c
int m[3][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12}
};
```

Access: `m[row][col]`. Stored in memory **row by row** (row-major order).

### Traversal
```c
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++)
        printf("%d ", m[i][j]);
    printf("\n");
}
```

### Passing to functions
All dimensions except the first are required:
```c
void show(int m[][4], int rows);
```

### Common matrix programs
- Addition: `c[i][j] = a[i][j] + b[i][j]`
- Transpose: `t[j][i] = m[i][j]`
- Multiplication:
```c
for (int i = 0; i < r1; i++)
    for (int j = 0; j < c2; j++) {
        res[i][j] = 0;
        for (int k = 0; k < c1; k++)
            res[i][j] += a[i][k] * b[k][j];
    }
```
(needs `c1 == r2`)
- Diagonal sum: `m[i][i]`
- Row and column sums.

### Real-world uses
Tic-tac-toe board, seating chart, marks table (students x subjects), game maps, image pixels.

---

## 8. Array of structures

Real data has many fields. Use a `struct` and make an array of it.

```c
#define MAX 100

typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

Student s[MAX];
int count = 0;                      // how many are actually used

s[count].roll = 1;
strcpy(s[count].name, "Krish");
s[count].marks = 88.5;
count++;
```

Notes:
- `MAX` is the capacity. `count` is the real number of records.
- Always check `count < MAX` before adding.
- Strings in a struct are assigned with `strcpy`, not `=`.
- Sorting works the same as with numbers, but swap whole structs:
```c
Student temp = s[j]; s[j] = s[j + 1]; s[j + 1] = temp;
```

### Menu-driven program pattern
```c
int choice;
do {
    printf("\n1.Add 2.View 3.Search 4.Delete 0.Exit\nChoice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: /* add */    break;
        case 2: /* view */   break;
        case 3: /* search */ break;
        case 4: /* delete */ break;
        case 0: printf("Bye\n"); break;
        default: printf("Invalid choice\n");
    }
} while (choice != 0);
```

---

## 9. File handling with arrays

Save data so it is not lost when the program closes.

### Text file
```c
FILE *f = fopen("numbers.txt", "w");
if (f == NULL) { printf("Error\n"); return 1; }
for (int i = 0; i < n; i++) fprintf(f, "%d\n", a[i]);
fclose(f);
```

Reading back:
```c
FILE *f = fopen("numbers.txt", "r");
int n = 0;
while (n < MAX && fscanf(f, "%d", &a[n]) == 1) n++;
fclose(f);
```

### Binary file (easy for struct arrays)
```c
void save(Student s[], int count) {
    FILE *f = fopen("data.bin", "wb");
    if (!f) return;
    fwrite(&count, sizeof(int), 1, f);
    fwrite(s, sizeof(Student), count, f);
    fclose(f);
}

int load(Student s[]) {
    FILE *f = fopen("data.bin", "rb");
    if (!f) return 0;
    int count = 0;
    fread(&count, sizeof(int), 1, f);
    fread(s, sizeof(Student), count, f);
    fclose(f);
    return count;
}
```
Always check that `fopen` succeeded and always `fclose`.

---

## 10. Dynamic arrays (intro)

Use when the size is only known at runtime.

```c
#include <stdlib.h>

int *a = malloc(n * sizeof(int));       // uninitialized
if (a == NULL) { printf("No memory\n"); return 1; }

int *z = calloc(n, sizeof(int));        // zero-initialized

int *tmp = realloc(a, newSize * sizeof(int));   // resize
if (tmp != NULL) a = tmp;

free(a);
free(z);
```

Rules: always check for `NULL`, always `free` what you `malloc`, never use memory after freeing it.

---

## 11. Common mistakes

| Mistake | Fix |
|---|---|
| Looping `i <= n` | use `i < n` |
| Forgetting `&` in `scanf("%d", &a[i])` | add `&` |
| Using `sizeof(arr)` inside a function | pass `n` as a parameter |
| Reading a string with `scanf("%s")` and expecting spaces | use `fgets` |
| Comparing strings with `==` | use `strcmp` |
| Assigning strings with `=` | use `strcpy` |
| Uninitialized local array | initialize with `= {0}` |
| Very large local array (stack overflow) | declare it globally or use `malloc` |
| Forgetting `'\0'` space in a string | size = characters + 1 |
| Leftover newline after `scanf` breaks `fgets` | use `" %[^\n]"` or clear the buffer |
| Memory leak | `free` after `malloc` |

Tip: compile with `-Wall -Wextra` to catch many mistakes early.

---

## 12. Quick reference

```c
int a[n];                 // declare
a[i]                      // access
sizeof(a)/sizeof(a[0])    // element count (same scope only)
void f(int a[], int n)    // pass to function
char s[50];               // string, max 49 characters
int m[r][c];              // 2D array
Student s[MAX];           // array of structs
```

---

## 13. Repository structure

```
c-arrays/
├── README.md
├── 01-basics/
├── 02-manipulation/
├── 03-strings/
├── 04-2d-arrays/
├── 05-structs-and-files/
└── projects/
    ├── student-record-manager/
    ├── contact-book/
    ├── inventory-system/
    ├── tic-tac-toe/
    └── expense-tracker/
```

| Folder | What is inside |
|---|---|
| `01-basics` | input/output, sum, max/min, search, reverse |
| `02-manipulation` | insert, delete, merge, rotate, sorting |
| `03-strings` | palindrome, anagram, vowels, cipher |
| `04-2d-arrays` | matrix operations, marks table, Pascal's triangle |
| `05-structs-and-files` | struct arrays, menus, file save/load |
| `projects` | complete mini projects |

---

## 14. How to compile and run

```bash
gcc program.c -o program -Wall -Wextra
./program            # Linux / macOS
program.exe          # Windows
```

---

## Progress tracker

- [ ] Basics (programs 1-10)
- [ ] Manipulation (programs 11-19)
- [ ] Strings (programs 20-28)
- [ ] 2D arrays (programs 29-37)
- [ ] Structs and files (programs 38-45)
- [ ] Student Record Manager
- [ ] Contact Book
- [ ] Inventory System
- [ ] Tic-Tac-Toe
- [ ] Expense Tracker

## What I learned
_Update this section after each stage._
