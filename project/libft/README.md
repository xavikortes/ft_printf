*This project has been created as part of 42 curriculum by jcortes.*

# Libft

## Description

**Libft** is a custom C library containing a collection of general-purpose functions that are commonly used in C programming.

The goal of this project is to recreate several standard C library functions and develop additional utility functions for working with strings, memory, characters, and linked lists.

This library will serve as a foundation for future projects at 42, allowing these functions to be reused instead of rewritten each time.

`libft` is compiled into a static library (`libft.a`) containing three main functional groups:

### 1. Libc Functions
Standard C library re-implementations following their respective manual pages:
* **Character classification & conversion:** `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower`.
* **String inspection & manipulation:** `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strncmp`, `ft_strnstr`, `ft_atoi`.
* **Raw memory operations:** `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`.
* **Dynamic memory allocation:** `ft_calloc`, `ft_strdup`.

### 2. Additional Functions
Utility functions for advanced string handling and file descriptor output:
* `ft_substr`: Extracts a substring from a string.
* `ft_strjoin`: Concatenates two strings into a newly allocated string.
* `ft_strtrim`: Trims specified characters from the start and end of a string.
* `ft_split`: Splits a string into an array of substrings using a delimiter.
* `ft_itoa`: Converts an integer into its string representation.
* `ft_strmapi`: Applies a function by index to every character in a string, creating a new string.
* `ft_striteri`: Applies a function by index to modify characters in place.
* `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd`: Write formatted output to a specified file descriptor using `write`.

### 3. Linked List Functions
Data structures designed to manage singly linked lists using the `t_list` structure:
* `ft_lstnew`: Creates a new list element.
* `ft_lstadd_front`: Adds an element to the beginning of the list.
* `ft_lstsize`: Counts the number of elements in the list.
* `ft_lstlast`: Returns the last element of the list.
* `ft_lstadd_back`: Adds an element to the end of the list.
* `ft_lstdelone`: Frees a node's content using a provided delete function and frees the node itself.
* `ft_lstclear`: Deletes and frees an entire list.
* `ft_lstiter`: Applies a function across elements in the list.
* `ft_lstmap`: Creates a new list resulting from applying a function to each node.

## Instructions

### Compiling

To compile the library and generate `libft.a`, run:

```bash
make
```

### Makefile Rules

The Makefile contains the following rules:

- `make` — Compile the library.
- `make clean` — Remove all object files.
- `make fclean` — Remove all object files and the library.
- `make re` — Recompile the library from scratch.

## Usage

In order to use the compiled library in your project:

* Compile it following the steps above.
* Include the `libft.h` file.
	```
	#include "libft.h"
	```
* Compile your project with the libraries flags & `lft`:
	```
	cc -Wall -Wextra -Werror your_source.c -L. -lft -o your_program
	```

## Resources

This project only use AI tools to check the exhaustiveness of the tests and received some guidance to write this `README.md`.
