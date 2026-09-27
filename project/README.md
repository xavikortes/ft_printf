*This project has been created as part of 42 curriculum by jcortes.*

# ft\_printf

## Description

**ft_printf** is a custom implementation of the standard C printf function.

The goal of this project is to recreate the core behavior of printf, handling formatted output and multiple conversion specifiers while respecting the restrictions and requirements of the 42 curriculum.

The project is compiled into a static library (libftprintf.a) that can be included and linked with other C projects.

*ft_printf* supports the following conversion specifiers:

* **Characters**: `%c`
* **Strings**: `%s`
* **Pointers**: `%p`
* **Decimals**: `%d`
* **Integers**: `%i`
* **Unsigned integers**: `%u`
* **Hexadecimal (lowercase)**: `%x`
* **Hexadecimal (uppercase)**: `%X`

It also supports multiple flags:

* **#**: Prepend prefix (0x) to hexadecimal values
* **+**: Always print a sign in positive numbers
* **' '**: Prints an space before a positive number
* **-**: Right adjust the printed string
* **0**: Zero pad numbers

Also support both minimun width and precision.

## Instructions

### Compiling

To compile the library and generate `libftprintf.a`, run:

```bash
make
```

### Makefile Rules

The Makefile contains the following rules:

- `make` — Compile the library.
- `make bonus` — Compile the library with the complementary part.
- `make clean` — Remove all object files.
- `make fclean` — Remove all object files and the library.
- `make re` — Recompile the library from scratch.

## Usage

In order to use the compiled library in your project:

* Compile it following the steps above.
* Include the `ft_printf.h` file.
	```
	#include "ft_printf.h"
	```
* Compile your project with the library:
	```
	cc -Wall -Wextra -Werror your_source.c libftprintf.a -o your_program
	```

## Resources

This project only use AI tools to check the exhaustiveness of the tests and received some guidance to write this `README.md`.
