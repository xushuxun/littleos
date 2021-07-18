#include "stdarg.h"
#include "screen.h"
#include "common.h"

int vprintf(const char *fmt, va_list ap)
{
	const char *hex = "0123456789abcdef";
	char buf[11];
	char *s;
	unsigned u;
	int ret = 0, i, c;

	while ((c = *fmt++)) {
		if (c == '%') {
			c = *fmt++;
			switch (c) {
			case 'c':
				screen_putchar(va_arg(ap, int));
				ret++;
				continue;
			case 's':
				for (s = va_arg(ap, char *); *s; s++) {
					screen_putchar(*s);
					ret++;
				}
				continue;
			case 'd':
				i = va_arg(ap, int);
				u = (i < 0 ? -i : i);
				s = buf;
				do {
					*s++ = '0' + u % 10U;
				} while (u /= 10U);
				if (i < 0)
					*s++ = '-';
				goto dumpbuf;
			case 'u':
				u = va_arg(ap, unsigned);
				s = buf;
				do {
					*s++ = '0' + u % 10U;
				} while (u /= 10U);
				goto dumpbuf;
			case 'x':
				u = va_arg(ap, unsigned);
				s = buf;
				do {
					*s++ = hex[u & 0xfu];
				} while (u >>= 4);
			dumpbuf:
				while (--s >= buf) {
					screen_putchar(*s);
					ret++;
				}
				continue;
			}
		}
		screen_putchar(c);
		ret++;
	}

	return (ret);
}


int printf(const char *fmt, ...)
{
	va_list ap;
	int ret;

	va_start(ap, fmt);
	ret = vprintf(fmt, ap);
	va_end(ap);

	return (ret);
}

void panic(const char *fmt, ...)
{
	printf("\nKernel panic!\n");
	
	va_list ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	for (;;) {
		
	}
}

void memset(uint8_t *dest, uint8_t val, uint32_t len)
{
    uint8_t *temp = (uint8_t *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}
