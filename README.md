<h1 align="center">
  <img src="assets/ft_printf.png" alt="ft_printf" width="400">
</h1>

<p align="center">
	<b><i>Recreation of original printf, limited 4️⃣2️⃣ edition.</i></b><br>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-125%2F100-lightgreen?style=for-the-badge" alt="score">
  <img src="https://img.shields.io/github/languages/top/Jarnomer/ft_printf?style=for-the-badge&logo=c&label=%20&labelColor=gray&color=lightblue" alt="GitHub top language">
	<img src="https://img.shields.io/github/languages/code-size/Jarnomer/ft_printf?style=for-the-badge&color=lightyellow" alt="GitHub code size in bytes">
  <img src="https://img.shields.io/github/directory-file-count/Jarnomer/ft_printf/sources?style=for-the-badge&label=sources&color=pink" alt="GitHub repo file or directory count (in path)">
</p>

<p align="center">
    <img src="https://img.shields.io/badge/Type-Solo-violet?style=for-the-badge" alt="type">
  <img src="https://img.shields.io/github/last-commit/Jarnomer/ft_printf/main?style=for-the-badge&color=red" alt="GitHub last commit (branch)">
</p>

<div align="center">

## Table of Contents
[📝 General](#-general)
[🛠️ Build](#️-build)
[⚡ Usage](#-usage)
[🚀 Details](#-details)
[♻️ Resources](#️-resources)

</div>

## 📝 General

The goal of the project is to replicate the functionality of the original `printf` function with limited features.

Project `passes` many of the 42 `testers`, including [franzinette](https://github.com/xicodomingues/francinette) `strict`.

Only the functions necessary for the project are included within `libft`.

## 🛠️ Build

GNU `make`, `gcc` and `ar` are required to build, compile and archive the project.

```bash
git clone https://github.com/Jarnomer/ft_printf.git
```

```bash
cd ft_printf && make all
```

## ⚡ Usage

Build creates binary `libftprintf.a` into `root` directory and it should be `compiled` with your project.

```c
#include "./include/ft_printf.h"

int main(void)
{
  int number = 42;
  unsigned int hex = 255;
  char *text = "Hello, world!";
  void *ptr = &number;

  ft_printf("Integer: %i\n", number);
  ft_printf("Hexadecimal: %X\n", hex);
  ft_printf("Pointer: %p\n", ptr);
  ft_printf("String: %s\n", text);
  ft_printf("Percent: %%\n");
  
  // With flags and formatting
  ft_printf("Left-aligned: %-10s\n", text);
  ft_printf("With precision: %.5s\n", text);
  ft_printf("Zero-padded: %05d\n", number);
  ft_printf("With sign: %+d\n", number);
  ft_printf("With space: % d\n", number);
  ft_printf("With hash: %#x\n", hex);
  
  return 0;
}
```

```bash
gcc main.c libftprintf.a -o ft_printf
```

## 🚀 Details

The function utilizes `va_list` from the standard library. The following `specifiers` and `flags` are handled:

| **Specifier** | **Description**                                                             |
|---------------|-----------------------------------------------------------------------------|
| `%c`          | Prints a single character.                                                  |
| `%s`          | Prints a string.                                                            |
| `%p`          | Prints a pointer in hexadecimal format.                                     |
| `%d`          | Prints a decimal number.                                                    |
| `%i`          | Prints an integer number.                                                   |
| `%u`          | Prints an unsigned integer number.                                          |
| `%x`          | Prints a hexadecimal number in lowercase.                                   |
| `%X`          | Prints a hexadecimal number in uppercase.                                   |
| `%%`          | Prints a percent sign.                                                      |

| **Flag**      | **Description**                                                             |
|---------------|-----------------------------------------------------------------------------|
| `-`           | Left-aligns the result within the field width.                              |
| `0`           | Pads numbers with leading zeros instead of spaces.                          |
| `#`           | Adds "0x" or "0X" prefix to hexadecimal format values.                      |
| ` `         | Adds a space before positive numbers.                                       |
| `+`           | Forces displaying the sign for positive numbers.                            |

| **Format**    | **Description**                                                             |
|---------------|-----------------------------------------------------------------------------|
| Width         | `%10s` - Reserves 10 characters for the output.                             |
| Precision     | `%.5s` - For strings: Limits to 5 characters.                               |
|               | `%.5d` - For integers: Ensures at least 5 digits (zero-padding).            |
|               | `%.5x` - For hex: Ensures at least 5 digits (zero-padding).                 |
|               | `%.0d` - With value 0: Prints nothing (suppresses zero value).              |
| Combined      | `%10.5s` - 10 character field with 5 character precision.                   |
| Special       | `%.*s` - Precision is specified as a parameter in the arguments list.       |
|               | `%*s` - Width is specified as a parameter in the arguments list.            |

Following utility `macros` are included in the header:

```c
# define HEXUPP "0123456789ABCDEF"
# define HEXLOW "0123456789abcdef"
# define SPECS  "cspdiuxX%"
# define FLAGS  "-0# +"
```

Struct manages formatting, flags, precision, width and write results including `-1` in case of `error`:

```c
typedef struct s_print
{
  bool error;
  int  length;

  ...
} t_print;
```

The project follows a modular design with separate files for each format type:

- `ft_printf.c` - Main function and parsing
- `ft_printf_chr.c` - Character formatting
- `ft_printf_str.c` - String formatting
- `ft_printf_nbr.c` - Integer number formatting
- `ft_printf_hex.c` - Hexadecimal formatting
- `ft_printf_utils.c` - Utility functions

Each format function handles:

1. Parsing any prefixes or special cases
2. Setting up the string representation
3. Calculating padding and alignment
4. Handling justification (left or right)
5. Writing to standard output

## ♻️ Resources

[franzinette](https://github.com/xicodomingues/francinette) amazing unit test framework for `ft_printf` and other 42 projects.

[printfTester](https://github.com/Tripouille/printfTester) excellent baseline tester for mandatory and bonus, tests leaks.

[ft_printf_test](https://github.com/cacharle/ft_printf_test) a very comprehensive tester, does not test leaks.

## 4️⃣2️⃣ Footer

For my other 42 projects and general information, please refer the [Hive42](https://github.com/Jarnomer/Hive42) page.

I have also created error handling [unit testers](https://github.com/Jarnomer/42Testers) for `pipex`, `so_long` and `cub3D`.

### Cheers and good luck! 🥳