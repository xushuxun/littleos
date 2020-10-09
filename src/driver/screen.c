#include "screen.h"
#include "io.h"
#include "common.h"


#define DEFAULT_ATTR_BYTE ((0/* black */ << 4) | (15/* white */ & 0x0F))
#define BLANK_CHAR        (0x20/* space */ | (DEFAULT_ATTR_BYTE << 8))

#define WIDTH  80                                    // 屏幕宽高
#define HEIGHT 25
static uint16_t *video_memory = (uint16_t *)0xB8000; // 显存起始地址
static uint8_t cursor_x = 0;                         // 光标坐标
static uint8_t cursor_y = 0;


void move_cursor()
{
	uint16_t cl = cursor_y * WIDTH + cursor_x;
	outb(0x3D4, 14);
	outb(0x3D5, cl >> 8);
	outb(0x3D4, 15);
	outb(0x3D5, cl);
}


void scroll()
{
	int i, w = WIDTH, h = HEIGHT;

	if (cursor_y >= h) {
		for (i = 0; i < w * (h - 1); i++)
			video_memory[i] = video_memory[i + w];
		for (i = w * (h - 1); i < w * h; i++)
			video_memory[i] = BLANK_CHAR;
		cursor_y = (h - 1);
	}
}


void screen_putchar(char c)
{
	uint8_t back_color = 0, fore_color = 2;

	uint8_t attr_byte = (back_color << 4) | (fore_color & 0x0F);
	uint16_t attr = attr_byte << 8;
	uint16_t *location;

	if (c == '\n') {
		cursor_x = 0;
		cursor_y++;
	} else if (c >= ' ') {
		location = video_memory + (cursor_x++ + WIDTH * cursor_y);
		*location = c | attr;
	}

	if (cursor_x >= WIDTH) {
		cursor_x = 0;
		cursor_y++;
	}
	scroll();
	move_cursor();
}


void screen_clear()
{
	int i;

	for (i = 0; i < WIDTH * HEIGHT; i++)
		video_memory[i] = BLANK_CHAR;
	cursor_x = cursor_y = 0;
	move_cursor();
}

void screen_putchars(char *s) {
    while (*s) {
        screen_putchar(*s++);
    }
}