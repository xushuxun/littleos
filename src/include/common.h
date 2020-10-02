#ifndef COMMON_H
#define COMMON_H

#include <types.h>

void		outb(uint16_t port, uint8_t value); /* write a byte out to port */
uint8_t		inb(uint16_t port); /* read a byte out from port */
uint16_t	inw(uint16_t port); /* read two bytes out from port */


#endif /* ndef COMMON_H */
