#include "../project/inc/ft_printf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>

/*
 * ============================================================
 * CONFIG
 * ============================================================
 */

#define BUFFER_SIZE 16384

static int	g_total;
static int	g_passed;
static int	g_failed;

/*
 * ============================================================
 * CAPTURA DE STDOUT
 * ============================================================
 *
 * Guarda stdout, lo redirige a un fichero temporal y permite
 * recuperar posteriormente la salida generada.
 *
 * No usamos ft_vprintf().
 * ============================================================
 */

static int	start_capture(FILE **file, int *saved_stdout)
{
	*file = tmpfile();
	if (*file == NULL)
		return (0);

	fflush(stdout);

	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdout == -1)
	{
		fclose(*file);
		return (0);
	}

	if (dup2(fileno(*file), STDOUT_FILENO) == -1)
	{
		close(*saved_stdout);
		fclose(*file);
		return (0);
	}

	return (1);
}

static int	stop_capture(FILE *file, int saved_stdout,
	char *buffer, size_t buffer_size)
{
	size_t	len;

	fflush(stdout);

	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
	{
		close(saved_stdout);
		fclose(file);
		return (-1);
	}

	close(saved_stdout);

	rewind(file);

	len = fread(buffer, 1, buffer_size - 1, file);
	buffer[len] = '\0';

	fclose(file);

	return ((int)len);
}

/*
 * ============================================================
 * COMPARADOR
 * ============================================================
 */

static void	print_pass(const char *name)
{
	g_passed++;
	printf("\033[32m[PASS]\033[0m %s\n", name);
}

static void	print_fail(const char *name,
	const char *expected,
	const char *got,
	int expected_ret,
	int got_ret)
{
	g_failed++;

	printf("\033[31m[FAIL]\033[0m %s\n", name);

	if (expected_ret != got_ret)
	{
		printf("       return esperado : %d\n", expected_ret);
		printf("       return obtenido : %d\n", got_ret);
	}

	if (strcmp(expected, got) != 0)
	{
		printf("       esperado: [");
		printf("%s", expected);
		printf("]\n");

		printf("       obtenido: [");
		printf("%s", got);
		printf("]\n");
	}
}

/*
 * ============================================================
 * TEST MACROS
 * ============================================================
 *
 * TEST0:
 *   Para formatos sin argumentos.
 *
 * TEST:
 *   Para formatos con uno o más argumentos.
 *
 * Cada función se ejecuta independientemente:
 *
 *   1. printf()
 *   2. ft_printf()
 *
 * Se comparan:
 *
 *   - salida
 *   - número de caracteres retornados
 *
 * ============================================================
 */

#define TEST0(NAME, FORMAT)                                      \
	do                                                           \
	{                                                            \
		FILE		*file;                                      \
		int			saved;                                      \
		int			expected_ret;                               \
		int			got_ret;                                    \
		int			expected_len;                               \
		int			got_len;                                    \
		char		expected[BUFFER_SIZE];                      \
		char		got[BUFFER_SIZE];                           \
		const char	*fmt;                                      \
                                                                 \
		g_total++;                                               \
		fmt = FORMAT;                                            \
                                                                 \
		if (!start_capture(&file, &saved))                       \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: capture\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		expected_ret = printf("%s", fmt);                        \
		expected_len = stop_capture(file, saved,                \
			expected, sizeof(expected));                         \
                                                                 \
		if (expected_len < 0)                                    \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: restore\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		if (!start_capture(&file, &saved))                       \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: capture\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		got_ret = ft_printf("%s", fmt);                          \
		got_len = stop_capture(file, saved,                     \
			got, sizeof(got));                                   \
                                                                 \
		if (got_len < 0)                                         \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: restore\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		if (expected_ret == got_ret                             \
			&& expected_len == got_len                           \
			&& strcmp(expected, got) == 0)                       \
			print_pass(NAME);                                    \
		else                                                     \
			print_fail(NAME, expected, got,                      \
				expected_ret, got_ret);                          \
	} while (0)


#define TEST(NAME, FORMAT, ...)                                  \
	do                                                           \
	{                                                            \
		FILE		*file;                                      \
		int			saved;                                      \
		int			expected_ret;                               \
		int			got_ret;                                    \
		int			expected_len;                               \
		int			got_len;                                    \
		char		expected[BUFFER_SIZE];                      \
		char		got[BUFFER_SIZE];                           \
		const char	*fmt;                                      \
                                                                 \
		g_total++;                                               \
		fmt = FORMAT;                                            \
                                                                 \
		if (!start_capture(&file, &saved))                       \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: capture\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		expected_ret = printf(fmt, __VA_ARGS__);                 \
		expected_len = stop_capture(file, saved,                \
			expected, sizeof(expected));                         \
                                                                 \
		if (expected_len < 0)                                    \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: restore\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		if (!start_capture(&file, &saved))                       \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: capture\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		got_ret = ft_printf(fmt, __VA_ARGS__);                   \
		got_len = stop_capture(file, saved,                     \
			got, sizeof(got));                                   \
                                                                 \
		if (got_len < 0)                                         \
		{                                                        \
			printf("\033[31m[ERROR]\033[0m %s: restore\n",       \
				(NAME));                                         \
			g_failed++;                                          \
			break;                                               \
		}                                                        \
                                                                 \
		if (expected_ret == got_ret                             \
			&& expected_len == got_len                           \
			&& strcmp(expected, got) == 0)                       \
			print_pass(NAME);                                    \
		else                                                     \
			print_fail(NAME, expected, got,                      \
				expected_ret, got_ret);                          \
	} while (0)

/*
 * ============================================================
 * BASIC / %
 * ============================================================
 */

static void	test_basic(void)
{
	printf("\n\033[1;36m=== BASIC ===\033[0m\n");

	TEST0("plain text",
		"Hello world!\n");

	TEST0("empty format",
		"");

	TEST0("newline",
		"hello\nworld\n");

	TEST0("percent",
		"100%%\n");

	TEST0("multiple percent",
		"%%%%\n");

	TEST0("percent surrounded",
		"abc %% def\n");

	TEST0("special chars",
		"!@#$%^&*()_+-=[]{};:',.<>/?\n");
}


/*
 * ============================================================
 * %c
 * ============================================================
 */

static void	test_char(void)
{
	printf("\n\033[1;36m=== %%c ===\033[0m\n");

	TEST("char A",
		"%c\n", 'A');

	TEST("char Z",
		"%c\n", 'Z');

	TEST("char 0",
		"%c\n", 0);

	TEST("char space",
		"%c\n", ' ');

	TEST("char newline",
		"%c\n", '\n');

	TEST("char 127",
		"%c\n", 127);

	TEST("multiple chars",
		"%c%c%c%c\n", 'a', 'b', 'c', 'd');

	TEST("mixed chars",
		"[%c][%c][%c]\n", 'A', 0, 'Z');
}


/*
 * ============================================================
 * %s
 * ============================================================
 */

static char	*get_null_string(void)
{
	return (NULL);
}

static void	test_string(void)
{
	printf("\n\033[1;36m=== %%s ===\033[0m\n");

	TEST("simple",
		"%s\n", "hello");

	TEST("empty",
		"%s\n", "");

	TEST("one char",
		"%s\n", "A");

	TEST("spaces",
		"%s\n", "hello world");

	TEST("long string",
		"%s\n",
		"This is a long string used to test ft_printf.");

	TEST("special chars",
		"%s\n",
		"!@#$%^&*()_+-=[]{};:',.<>/?");

	TEST("newline in string",
		"%s\n",
		"hello\nworld");

	TEST("NULL",
		"%s\n", get_null_string());

	TEST("multiple",
		"%s %s %s\n",
		"one", "two", "three");

	TEST("mixed",
		"[%s][%s][%s]\n",
		"", "hello", get_null_string());
}


/*
 * ============================================================
 * %p
 * ============================================================
 */

static void	test_pointer(void)
{
	int		a;
	int		b;
	char	c;

	printf("\n\033[1;36m=== %%p ===\033[0m\n");

	a = 42;
	b = -42;
	c = 'A';

	TEST("pointer int",
		"%p\n", (void *)&a);

	TEST("pointer second int",
		"%p\n", (void *)&b);

	TEST("pointer char",
		"%p\n", (void *)&c);

	TEST("multiple pointers",
		"%p %p %p\n",
		(void *)&a,
		(void *)&b,
		(void *)&c);

	TEST("same pointer",
		"[%p][%p][%p]\n",
		(void *)&a,
		(void *)&a,
		(void *)&a);

	/*
	 * IMPORTANTE:
	 *
	 * El comportamiento visual de printf("%p", NULL) puede ser
	 * "(nil)" en libc/glibc, mientras que muchos ft_printf
	 * de 42 esperan "0x0".
	 *
	 * Por eso NO lo usamos como comparación automática.
	 *
	 * Si tu implementación sigue exactamente la libc de tu
	 * sistema, puedes descomentar:
	 *
	 * TEST("NULL pointer", "%p\n", (void *)NULL);
	 */
}


/*
 * ============================================================
 * %d
 * ============================================================
 */

static void	test_decimal(void)
{
	printf("\n\033[1;36m=== %%d ===\033[0m\n");

	TEST("zero",
		"%d\n", 0);

	TEST("one",
		"%d\n", 1);

	TEST("minus one",
		"%d\n", -1);

	TEST("42",
		"%d\n", 42);

	TEST("minus 42",
		"%d\n", -42);

	TEST("100",
		"%d\n", 100);

	TEST("large positive",
		"%d\n", 123456789);

	TEST("large negative",
		"%d\n", -123456789);

	TEST("INT_MAX",
		"%d\n", INT_MAX);

	TEST("INT_MIN",
		"%d\n", INT_MIN);

	TEST("multiple",
		"%d %d %d %d\n",
		INT_MIN, -1, 0, INT_MAX);
}


/*
 * ============================================================
 * %i
 * ============================================================
 */

static void	test_integer(void)
{
	printf("\n\033[1;36m=== %%i ===\033[0m\n");

	TEST("zero",
		"%i\n", 0);

	TEST("positive",
		"%i\n", 42);

	TEST("negative",
		"%i\n", -42);

	TEST("INT_MAX",
		"%i\n", INT_MAX);

	TEST("INT_MIN",
		"%i\n", INT_MIN);

	TEST("multiple",
		"%i %i %i %i\n",
		INT_MIN, -42, 0, INT_MAX);
}


/*
 * ============================================================
 * %u
 * ============================================================
 */

static void	test_unsigned(void)
{
	printf("\n\033[1;36m=== %%u ===\033[0m\n");

	TEST("zero",
		"%u\n", 0u);

	TEST("one",
		"%u\n", 1u);

	TEST("42",
		"%u\n", 42u);

	TEST("100",
		"%u\n", 100u);

	TEST("large",
		"%u\n", 4000000000u);

	TEST("UINT_MAX",
		"%u\n", UINT_MAX);

	TEST("multiple",
		"%u %u %u %u\n",
		0u, 1u, 42u, UINT_MAX);
}


/*
 * ============================================================
 * %x / %X
 * ============================================================
 */

static void	test_hex(void)
{
	printf("\n\033[1;36m=== %%x / %%X ===\033[0m\n");

	TEST("x zero",
		"%x\n", 0u);

	TEST("x one",
		"%x\n", 1u);

	TEST("x 10",
		"%x\n", 10u);

	TEST("x 15",
		"%x\n", 15u);

	TEST("x 16",
		"%x\n", 16u);

	TEST("x 42",
		"%x\n", 42u);

	TEST("x 255",
		"%x\n", 255u);

	TEST("x UINT_MAX",
		"%x\n", UINT_MAX);

	TEST("X zero",
		"%X\n", 0u);

	TEST("X 42",
		"%X\n", 42u);

	TEST("X 255",
		"%X\n", 255u);

	TEST("X UINT_MAX",
		"%X\n", UINT_MAX);

	TEST("mixed hex",
		"%x %X %x %X\n",
		42u, 42u, 255u, 255u);
}


/*
 * ============================================================
 * WIDTH
 * ============================================================
 */

static void	test_width(void)
{
	printf("\n\033[1;36m=== WIDTH ===\033[0m\n");

	TEST("char width 5",
		"%5c\n", 'A');

	TEST("char width 10",
		"%10c\n", 'A');

	TEST("string width 5",
		"%5s\n", "abc");

	TEST("string width 10",
		"%10s\n", "abc");

	TEST("string exact width",
		"%3s\n", "abc");

	TEST("string smaller width",
		"%2s\n", "abc");

	TEST("decimal width 5",
		"%5d\n", 42);

	TEST("decimal width 10",
		"%10d\n", 42);

	TEST("negative width decimal",
		"%10d\n", -42);

	TEST("unsigned width",
		"%10u\n", 42u);

	TEST("hex width",
		"%10x\n", 42u);

	TEST("HEX width",
		"%10X\n", 42u);
}


/*
 * ============================================================
 * FLAG -
 * ============================================================
 */

static void	test_minus(void)
{
	printf("\n\033[1;36m=== FLAG - ===\033[0m\n");

	TEST("left char",
		"%-5c\n", 'A');

	TEST("left string",
		"%-10s\n", "abc");

	TEST("left decimal",
		"%-10d\n", 42);

	TEST("left negative",
		"%-10d\n", -42);

	TEST("left unsigned",
		"%-10u\n", 42u);

	TEST("left hex",
		"%-10x\n", 42u);

	TEST("left HEX",
		"%-10X\n", 42u);

	TEST("left exact",
		"%-3s\n", "abc");

	TEST("left smaller",
		"%-2s\n", "abc");
}


/*
 * ============================================================
 * FLAG 0
 * ============================================================
 */

static void	test_zero(void)
{
	printf("\n\033[1;36m=== FLAG 0 ===\033[0m\n");

	TEST("zero decimal",
		"%05d\n", 42);

	TEST("zero negative",
		"%05d\n", -42);

	TEST("zero large",
		"%010d\n", 123456);

	TEST("zero unsigned",
		"%010u\n", 42u);

	TEST("zero hex",
		"%010x\n", 42u);

	TEST("zero HEX",
		"%010X\n", 42u);

	TEST("zero width exact",
		"%03d\n", 123);

	TEST("zero width smaller",
		"%02d\n", 123);

	TEST("zero INT_MIN",
		"%015d\n", INT_MIN);
}


/*
 * ============================================================
 * PRECISION
 * ============================================================
 */

static void	test_precision(void)
{
	printf("\n\033[1;36m=== PRECISION ===\033[0m\n");

	/*
	 * Strings
	 */

	TEST("string precision 0",
		"%.0s\n", "hello");

	TEST("string precision 1",
		"%.1s\n", "hello");

	TEST("string precision 2",
		"%.2s\n", "hello");

	TEST("string precision 3",
		"%.3s\n", "hello");

	TEST("string precision 5",
		"%.5s\n", "hello");

	TEST("string precision 10",
		"%.10s\n", "hello");

	TEST("string precision 0 empty",
		"%.0s\n", "");

	/*
	 * Decimal
	 */

	TEST("decimal precision 0",
		"%.0d\n", 42);

	TEST("decimal precision 1",
		"%.1d\n", 42);

	TEST("decimal precision 3",
		"%.3d\n", 42);

	TEST("decimal precision 5",
		"%.5d\n", 42);

	TEST("decimal precision 10",
		"%.10d\n", 42);

	TEST("decimal precision zero",
		"%.5d\n", 0);

	TEST("decimal precision negative",
		"%.5d\n", -42);

	/*
	 * Unsigned
	 */

	TEST("unsigned precision",
		"%.5u\n", 42u);

	TEST("unsigned precision zero",
		"%.5u\n", 0u);

	TEST("unsigned precision large",
		"%.10u\n", UINT_MAX);

	/*
	 * Hex
	 */

	TEST("hex precision",
		"%.5x\n", 42u);

	TEST("HEX precision",
		"%.5X\n", 42u);

	TEST("hex precision zero",
		"%.5x\n", 0u);

	TEST("hex precision large",
		"%.10x\n", UINT_MAX);

	/*
	 * Width + precision
	 */

	TEST("width precision d",
		"%10.5d\n", 42);

	TEST("width precision negative",
		"%10.5d\n", -42);

	TEST("width precision s",
		"%10.3s\n", "hello");

	TEST("width precision x",
		"%10.5x\n", 42u);
}


/*
 * ============================================================
 * BONUS: #
 * ============================================================
 */

static void	test_hash(void)
{
	printf("\n\033[1;36m=== BONUS # ===\033[0m\n");

	TEST("hash x",
		"%#x\n", 42u);

	TEST("hash X",
		"%#X\n", 42u);

	TEST("hash x 255",
		"%#x\n", 255u);

	TEST("hash X 255",
		"%#X\n", 255u);

	TEST("hash x zero",
		"%#x\n", 0u);

	TEST("hash X zero",
		"%#X\n", 0u);

	TEST("hash x width",
		"%#10x\n", 42u);

	TEST("hash X width",
		"%#10X\n", 42u);

	TEST("hash x zero padding",
		"%#010x\n", 42u);

	TEST("hash X zero padding",
		"%#010X\n", 42u);

	TEST("hash x left",
		"%-#10x\n", 42u);

	TEST("hash X left",
		"%-#10X\n", 42u);

	TEST("hash x precision",
		"%#.8x\n", 42u);

	TEST("hash X precision",
		"%#.8X\n", 42u);
}


/*
 * ============================================================
 * BONUS: +
 * ============================================================
 */

static void	test_plus(void)
{
	printf("\n\033[1;36m=== BONUS + ===\033[0m\n");

	TEST("plus positive",
		"%+d\n", 42);

	TEST("plus negative",
		"%+d\n", -42);

	TEST("plus zero",
		"%+d\n", 0);

	TEST("plus INT_MAX",
		"%+d\n", INT_MAX);

	TEST("plus INT_MIN",
		"%+d\n", INT_MIN);

	TEST("plus width",
		"%+10d\n", 42);

	TEST("plus zero padding",
		"%+010d\n", 42);

	TEST("plus precision",
		"%+.10d\n", 42);

	TEST("plus width precision",
		"%+10.5d\n", 42);
}


/*
 * ============================================================
 * BONUS: SPACE
 * ============================================================
 */

static void	test_space(void)
{
	printf("\n\033[1;36m=== BONUS SPACE ===\033[0m\n");

	TEST("space positive",
		"% d\n", 42);

	TEST("space negative",
		"% d\n", -42);

	TEST("space zero",
		"% d\n", 0);

	TEST("space INT_MAX",
		"% d\n", INT_MAX);

	TEST("space INT_MIN",
		"% d\n", INT_MIN);

	TEST("space width",
		"% 10d\n", 42);

	TEST("space zero padding",
		"% 010d\n", 42);

	TEST("space precision",
		"% .10d\n", 42);
}


/*
 * ============================================================
 * BONUS: COMBINACIONES
 * ============================================================
 */

static void	test_combinations(void)
{
	printf("\n\033[1;36m=== BONUS COMBINATIONS ===\033[0m\n");

	/*
	 * -
	 */

	TEST("- + d",
		"%-+10d\n", 42);

	TEST("- + negative",
		"%-+10d\n", -42);

	TEST("- space d",
		"%- 10d\n", 42);

	/*
	 * #
	 */

	TEST("- # x",
		"%-#10x\n", 255u);

	TEST("- # X",
		"%-#10X\n", 255u);

	TEST("# width precision x",
		"%#10.5x\n", 255u);

	TEST("# width precision X",
		"%#10.5X\n", 255u);

	/*
	 * +
	 */

	TEST("+ width precision",
		"%+10.5d\n", 42);

	TEST("+ width precision negative",
		"%+10.5d\n", -42);

	TEST("+ zero width",
		"%+010d\n", 42);

	/*
	 * space
	 */

	TEST("space width precision",
		"% 10.5d\n", 42);

	TEST("space width precision negative",
		"% 10.5d\n", -42);

	/*
	 * Combined bonus
	 */

	TEST("all relevant flags x",
		"%-#10.5x\n", 255u);

	TEST("all relevant flags X",
		"%-#10.5X\n", 255u);

	TEST("plus minus precision",
		"%-+10.5d\n", 42);

	TEST("plus minus precision negative",
		"%-+10.5d\n", -42);
}


/*
 * ============================================================
 * EDGE CASES
 * ============================================================
 */

static void	test_edge_cases(void)
{
	printf("\n\033[1;36m=== EDGE CASES ===\033[0m\n");

	TEST("zero precision d",
		"%.0d\n", 0);

	TEST("zero precision u",
		"%.0u\n", 0u);

	TEST("zero precision x",
		"%.0x\n", 0u);

	TEST("zero precision X",
		"%.0X\n", 0u);

	TEST("precision one zero",
		"%.1d\n", 0);

	TEST("precision ten zero",
		"%.10d\n", 0);

	TEST("precision twenty zero",
		"%.20d\n", 0);

	TEST("negative precision value",
		"%.10d\n", -42);

	TEST("large width",
		"%50d\n", 42);

	TEST("large width string",
		"%50s\n", "hello");

	TEST("large width hex",
		"%50x\n", 42u);

	TEST("large precision",
		"%.30d\n", 42);

	TEST("large string precision",
		"%.30s\n", "hello");

	TEST("width precision zero",
		"%010.5d\n", 42);

	TEST("minus width precision",
		"%-10.5d\n", 42);

	TEST("negative width precision",
		"%10.8d\n", -42);

	TEST("INT_MIN padded",
		"%020d\n", INT_MIN);

	TEST("INT_MAX padded",
		"%020d\n", INT_MAX);

	TEST("UINT_MAX padded",
		"%020u\n", UINT_MAX);

	TEST("UINT_MAX hex",
		"%020x\n", UINT_MAX);
}


/*
 * ============================================================
 * MULTIPLE CONVERSIONS
 * ============================================================
 */

static void	test_multiple(void)
{
	printf("\n\033[1;36m=== MULTIPLE CONVERSIONS ===\033[0m\n");

	TEST("all mandatory",
		"%c %s %p %d %i %u %x %X %%\n",
		'A',
		"hello",
		(void *)&g_total,
		42,
		-42,
		42u,
		42u,
		42u);

	TEST("many decimals",
		"%d %d %d %d %d\n",
		INT_MIN,
		-1,
		0,
		1,
		INT_MAX);

	TEST("many unsigned",
		"%u %u %u %u\n",
		0u,
		1u,
		42u,
		UINT_MAX);

	TEST("many hex",
		"%x %x %x %X %X %X\n",
		0u,
		42u,
		UINT_MAX,
		0u,
		42u,
		UINT_MAX);

	TEST("mixed everything",
		"c=%c s=%s p=%p d=%d i=%i u=%u x=%x X=%X %%\n",
		'A',
		"hello",
		(void *)&g_total,
		-123,
		456,
		789u,
		0xabcdefu,
		0xABCDEFu);

	TEST("adjacent decimals",
		"%d%d%d%d%d\n",
		1, 2, 3, 4, 5);

	TEST("adjacent strings",
		"%s%s%s\n",
		"a", "b", "c");

	TEST("adjacent hex",
		"%x%x%x%x\n",
		10u, 11u, 12u, 13u);
}


/*
 * ============================================================
 * RETURN VALUES
 * ============================================================
 *
 * Los tests normales YA comprueban el return value.
 * Aquí añadimos casos específicos.
 * ============================================================
 */

static void	test_return_values(void)
{
	printf("\n\033[1;36m=== RETURN VALUES ===\033[0m\n");

	TEST0("return plain",
		"hello");

	TEST("return char",
		"%c", 'A');

	TEST("return string",
		"%s", "hello");

	TEST("return decimal",
		"%d", 12345);

	TEST("return negative",
		"%d", -12345);

	TEST("return unsigned",
		"%u", 12345u);

	TEST("return hex",
		"%x", 0xabcdefu);

	TEST0("return percent",
		"%%");

	TEST("return mixed",
		"[%c][%s][%d][%x][%%]",
		'A',
		"hello",
		42,
		255u);
}


/*
 * ============================================================
 * STRESS
 * ============================================================
 */

static void	test_stress(void)
{
	int		i;
	char	name[128];

	printf("\n\033[1;36m=== STRESS ===\033[0m\n");

	/*
	 * Muchos valores decimales.
	 */

	for (i = -100; i <= 100; i++)
	{
		snprintf(name, sizeof(name),
			"stress %%d: %d", i);

		TEST(name, "%d\n", i);
	}

	/*
	 * Muchos valores hexadecimales.
	 */

	for (i = 0; i <= 255; i++)
	{
		snprintf(name, sizeof(name),
			"stress %%x: %d", i);

		TEST(name, "%x\n", (unsigned int)i);
	}
}


/*
 * ============================================================
 * BONUS EXTRA
 * ============================================================
 *
 * Estas pruebas no añaden nuevas conversiones, sino que
 * combinan las características del bonus.
 * ============================================================
 */

static void	test_bonus_extra(void)
{
	printf("\n\033[1;36m=== BONUS EXTRA ===\033[0m\n");

	TEST("hash + width + precision",
		"%#15.8x\n", 0x1234u);

	TEST("hash + minus + width + precision",
		"%-#15.8x\n", 0x1234u);

	TEST("hash + zero + width",
		"%#015x\n", 0x1234u);

	TEST("hash + precision",
		"%#.10x\n", 0x1234u);

	TEST("hash uppercase",
		"%#15.8X\n", 0x1234u);

	TEST("plus + width + precision",
		"%+15.8d\n", 1234);

	TEST("plus + minus + width",
		"%-+15d\n", 1234);

	TEST("plus + zero + width",
		"%+015d\n", 1234);

	TEST("space + width + precision",
		"% 15.8d\n", 1234);

	TEST("space + minus + width",
		"%- 15d\n", 1234);

	TEST("space + zero + width",
		"% 015d\n", 1234);

	TEST("negative plus zero",
		"%+015d\n", -1234);

	TEST("negative space zero",
		"% 015d\n", -1234);

	TEST("negative plus precision",
		"%+15.8d\n", -1234);

	TEST("negative space precision",
		"% 15.8d\n", -1234);
}


/*
 * ============================================================
 * MAIN
 * ============================================================
 */

int	main(void)
{
	printf("\n");
	printf("\033[1;35m");
	printf("============================================================\n");
	printf("                 FT_PRINTF TESTER\n");
	printf("                  MANDATORY + BONUS\n");
	printf("============================================================\n");
	printf("\033[0m");

	if (1)
	{
	test_basic();
	test_char();
	test_string();
	test_pointer();
	}

	if (1)
	{
	test_decimal();
	test_integer();
	test_unsigned();
	test_hex();
	}

	if (1)
	{
	test_width();
	test_minus();
	test_precision();
	test_zero();
	}

	if (1)
	{
	test_hash();
	test_plus();
	test_space();
	test_combinations();
	}

	if (1)
	{
	test_edge_cases();
	test_multiple();
	test_return_values();
	test_bonus_extra();
	}

	if (1)
	{
		test_stress();
	}

	printf("\n");
	printf("\033[1;35m");
	printf("============================================================\n");
	printf("                         RESULTS\n");
	printf("============================================================\n");
	printf("\033[0m");

	printf("Total : %d\n", g_total);
	printf("\033[32mPassed: %d\033[0m\n", g_passed);
	printf("\033[31mFailed: %d\033[0m\n", g_failed);

	if (g_failed == 0)
	{
		printf("\n");
		printf("\033[1;32m");
		printf("              ALL TESTS PASSED! 🎉\n");
		printf("\033[0m\n");
		return (0);
	}

	printf("\n");
	printf("\033[1;31m");
	printf("              SOME TESTS FAILED.\n");
	printf("\033[0m\n");

	return (1);
}

