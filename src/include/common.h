#ifndef COMMON_H
#define COMMON_H

typedef unsigned int	uint32_t;
typedef int		        int32_t;

typedef unsigned short	uint16_t;
typedef short		    int16_t;

typedef unsigned char	uint8_t;
typedef char		    int8_t;

typedef unsigned long	size_t;

int	 printf(const char *fmt, ...);
void panic(const char *fmt, ...);

#endif
