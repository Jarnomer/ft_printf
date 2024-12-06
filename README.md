<h1 align="center">
  <img src="assets/ft_printf.png" alt="ft_printf" width="400">
</h1>

<p align="center">
	<b><i>Recreation of original printf, limited ft_edition.</i></b><br>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Score-100%2F100-lightgreen?style=for-the-badge" alt="score">
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

The goal of the project is to replicate limited functionality of original `printf`.

It includes the modified `put_fd` functions from [libft](https://github.com/Jarnomer/libft) to keep track of written bytes.

Project `passes` many of the 42 `testers`, including [franzinette](https://github.com/xicodomingues/francinette) `strict`.

Struct is used to manage write results including `-1` in case of `error`.

```c
typedef struct s_print
{
	int result;
	int length;
}	t_print;
```

## 🛠️ Build

GNU `make`, `gcc` and `ar` are required to build, compile and archive the project.

```bash
git clone https://github.com/Jarnomer/ft_printf.git ft_printf
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
  ft_printf("Percent: %s\n", NULL);
  return 0;
}
```

```bash
gcc main.c libftprintf.a -o ft_printf
```

## 🚀 Details

Function utilizes `va_list` from standard library. Following `specifiers` are handled.

| **Specifier** | **Description**                                                                 |
|---------------|---------------------------------------------------------------------------------|
| `%c`          | Prints a single character.                                                     |
| `%s`          | Prints a string.                       |
| `%p`          | Prints a pointer in hexadecimal format.                |
| `%d`          | Prints a decimal number.                                             |
| `%i`          | Prints an integer number.                                                  |
| `%u`          | Prints an unsigned integer number.                                   |
| `%x`          | Prints a hexadecimal number in lowercase.                     |
| `%X`          | Prints a hexadecimal number in uppercase.                     |
| `%%`          | Prints a percent sign.                                                        |

Following utility `macros` are included in the header.

```c
# define HEXUPP "0123456789ABCDEF"
# define HEXLOW "0123456789abcdef"
# define SPECS  "cspdiuxX%"
```

As an example, `recursive` implementation of hexadecimal printing.

```c
void format_hex(t_print *output, unsigned long hex, char spec)
{
  if (hex >= 16)
    format_hex(output, hex / 16, spec);
  if (spec == 'p' && hex < 16)
    format_str(output, "0x");
  if (output->length == -1)
    return ;
  if (spec == 'x' || spec == 'p')
    format_chr(output, HEXLOW[hex %= 16]);
  else
    format_chr(output, HEXUPP[hex %= 16]);
}
```

## ♻️ Resources

[franzinette](https://github.com/xicodomingues/francinette) amazing unit test framework for `ft_printf` and other 42 projects.

## 4️⃣2️⃣ Footer

For my other 42 projects and general information, please refer the [Hive42 page](https://github.com/Jarnomer/Hive42).

I have also created error handling [unit testers](https://github.com/Jarnomer/42Testers) for `pipex`, `so_long` and `cub3D`.

### Cheers and good luck! 🥳