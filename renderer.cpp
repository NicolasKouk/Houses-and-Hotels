////normal screen fill, suggested color:0x00b0ff
//internal void
//clear_screen(u32 color) {
//	unsigned int* pixel = (u32*)render_state.memory;
//	for (int y = 0; y < render_state.height; y++) {
//		for (int x = 1; x < render_state.width; x++) {
//			*pixel++ = color;
//		}
//	}
//}

////spicy screen fill
//internal void
//clear_screen(u32 color) {
//	unsigned int* pixel = (u32*)render_state.memory;
//	for (int y = 0; y < render_state.height; y++) {
//		for (int x = 1; x < render_state.width; x++) {
//			*pixel++ = x * (x + y);
//		}
//	}
//}

//diagonal blue slices, suggested color: 0x2e42df
internal void
clear_screen(u32 color) {
	unsigned int* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		u32 color1 = color;
		for (int x = 1; x < render_state.width; x++) {
			*pixel++ = color1;
			color1+=256;
		}
	}
}


global_variable float render_scale = 0.01f;

internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {

	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;

	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

bool neg_num = false;

internal void
draw_number(int num, float x, float y, float size, u32 color) {
	int digit = 1;
	bool drew_number = false;
	if (num / 1000 > 1) draw_rect(x - (7.5 * size), y-(3 * size), .3 * size, .7 * size, color);
	if (num / 1000000 >= 1) draw_rect(x - (16.5 * size), y-(3 * size), .3 * size, .7 * size, color);
	if (num < 0) {
		neg_num = true;
		num *= -1;
	}
	while (num != 0 || !drew_number) {
		digit = num % 10;
		num = num / 10;
		switch (digit) {
		case 0: {
			draw_rect(x, y - (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x - (.75 * size), y + (1.25 * size), .5 * size, 1.25 * size, color);
			draw_rect(x + (.75 * size), y - (1.25 * size), .5 * size, 1.25 * size, color);
			draw_rect(x + (.75 * size), y + (1.25 * size), .5 * size, 1.25 * size, color);
			draw_rect(x - (.75 * size), y - (1.25 * size), .5 * size, 1.25 * size, color);
			x -= 3 * size;
		} break;
		case 1: {
			draw_rect(x + (.5 * size), y, .5 * size, 3 * size, color);
			x -= 1.75 * size;
		} break;
		case 2: {
			draw_rect(x, y - (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x, y, 1.25 * size, .5 * size, color);
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x - (.75 * size), y - (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x + (.75 * size), y + (1.25 * size), .5 * size, .75 * size, color);
			x -= 3 * size;
		} break;
		case 3: {
			draw_rect(x + (1 * size), y, .5 * size, 3 * size, color);
			draw_rect(x, y - (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x + (.1 * size), y, 1 * size, .5 * size, color);
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			x -= 3 * size;
		} break;
		case 4: {
			draw_rect(x + (1 * size), y, .5 * size, 3 * size, color);
			draw_rect(x, y, 1.5 * size, .5 * size, color);
			draw_rect(x - (1 * size), y + (1.5 * size), .5 * size, 1.5 * size, color);
			x -= 3.3 * size;
		} break;

		case 5: {
			draw_rect(x, y - (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x, y, 1.25 * size, .5 * size, color);
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x - (.75 * size), y + (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x + (.75 * size), y - (1.25 * size), .5 * size, .75 * size, color);
			x -= 3 * size;
		} break;
		case 6: {
			draw_rect(x, y - (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x, y, 1.25 * size, .5 * size, color);
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x - (.75 * size), y + (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x + (.75 * size), y - (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x - (.75 * size), y - (1.25 * size), .5 * size, .75 * size, color);
			x -= 3 * size;
		} break;
		case 7: {
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x + (1 * size), y, .5 * size, 3 * size, color);
			x -= 3 * size;
		} break;
		case 8: {
			draw_rect(x, y - (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x, y, 1.25 * size, .5 * size, color);
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x - (.75 * size), y + (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x + (.75 * size), y - (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x + (.75 * size), y + (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x - (.75 * size), y - (1.25 * size), .5 * size, .75 * size, color);
			x -= 3 * size;
		} break;
		case 9: {
			draw_rect(x, y - (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x, y, 1.25 * size, .5 * size, color);
			draw_rect(x, y + (2.5 * size), 1.25 * size, .5 * size, color);
			draw_rect(x - (.75 * size), y + (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x + (.75 * size), y - (1.25 * size), .5 * size, .75 * size, color);
			draw_rect(x + (.75 * size), y + (1.25 * size), .5 * size, .75 * size, color);
			x -= 3 * size;
		} break;
		}
		drew_number = true;
	}
	if (neg_num) {
		draw_rect(x, y, .7, .25, 0x000000);
		neg_num = false;
	}
}

const char* letters[][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"0",
	"0",
	"0",
	"0",
	"0",
	"",
	"0",

	" 0",
	"0 0",
	"  0",
	" 0",
	" 0",
	"",
	" 0",

	"",
	"  0",
	" 0 0",
	" 00",
	"0 0 0",
	"0  0",
	" 00 0",
	
};

internal void
draw_text(const char* text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 63) letter = letters[27];
			else if (*text == 33) letter = letters[26];
			else if (*text == 38) letter = letters[28];
			else letter = letters[*text - 'A'];
			float original_x = x;

			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) {
					if (*row == '0') {
						draw_rect(x, y, half_size, half_size, color);
					}
					x += size;
					row++;
				}
				y -= size;
				x = original_x;
			}
		}
		text++;
		x += size * 6.f;
		y = original_y;
	}
}


string letters2[28][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	" 000",
	"0",
	"0",
	"0",
	"0",
	"0",
	" 000",

	"000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0",

	" 000",
	"0",
	"0",
	"0 00",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	" 000",
	"   0",
	"   0",
	"   0",
	"0  0",
	"0  0",
	" 000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	"0",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0000",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	" 000 ",
	"0   0",
	"0   0",
	"0   0",
	"0 0 0",
	"0  0 ",
	" 00 0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"0  0",

	" 000",
	"0",
	"0 ",
	" 00",
	"   0",
	"   0",
	"000 ",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	" 00",

	"0   0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"",
	"",
	"",
	"",
	"",
	"",
	"0",

	"   0",
	"  0",
	"  0",
	" 0",
	" 0",
	"0",
	"0",
};


internal void
draw_text2(string text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;
	int k = 0; //the letters being typed

	while (k < text.size()) {
		if (int(text[k]) != 32) {
			int letter_index;  // the index of the letters2 matrix which indicate which letter is to be used
			if (int(text[k]) == 47) letter_index = 27;
			else if (int(text[k]) == 46) letter_index = 26;
			else letter_index = int(text[k]) - 'A';
			float original_x = x;

			for (int i = 0; i < 7; i++) {
				string row = letters2[letter_index][i];
				int j = 0;
				while (row[j]) {
					if (row[j] == '0') {
						draw_rect(x, y, half_size, half_size, color);
					}
					x += size;
					j++;
				}
				y -= size;
				x = original_x;
			}
		}
		if (text[k] == '.' || text[k] == ' ') x -= size * 2.f;
		x += size * 6.f;
		y = original_y;
		k++;
	}
}



internal void 
draw_dice(float x, float y, int num) {
	draw_rect(x, y, 4, 4, 0xffffff);
	switch (num) {
	case 1: {
		draw_rect(x, y, .75, .75, 0x000000);
	} break;
	case 2: {
		draw_rect(x+2, y+2, .75, .75, 0x000000);
		draw_rect(x-2, y-2, .75, .75, 0x000000);
	} break;
	case 3: {
		draw_rect(x, y, .75, .75, 0x000000);
		draw_rect(x + 2, y + 2, .75, .75, 0x000000);
		draw_rect(x - 2, y - 2, .75, .75, 0x000000);
	} break;
	case 4: {
		draw_rect(x + 2, y + 2, .75, .75, 0x000000);
		draw_rect(x - 2, y - 2, .75, .75, 0x000000);
		draw_rect(x + 2, y - 2, .75, .75, 0x000000);
		draw_rect(x - 2, y + 2, .75, .75, 0x000000);
	} break;
	case 5: {
		draw_rect(x, y, .75, .75, 0x000000);
		draw_rect(x + 2, y + 2, .75, .75, 0x000000);
		draw_rect(x - 2, y - 2, .75, .75, 0x000000);
		draw_rect(x + 2, y - 2, .75, .75, 0x000000);
		draw_rect(x - 2, y + 2, .75, .75, 0x000000);
	} break;
	case 6: {
		draw_rect(x + 2, y + 2, .75, .75, 0x000000);
		draw_rect(x - 2, y - 2, .75, .75, 0x000000);
		draw_rect(x + 2, y - 2, .75, .75, 0x000000);
		draw_rect(x - 2, y + 2, .75, .75, 0x000000);
		draw_rect(x + 2, y, .75, .75, 0x000000);
		draw_rect(x - 2, y, .75, .75, 0x000000);
	} break;
	}
}


internal void
draw_logo(float x, float y, float size) {
	for (float y1 = -22.3; y1 <= 22.3; y1 += .1) {
		draw_rect(x, y + y1, sqrt(1000 - 2 * y1 * y1), .05, 0x72ADC5);
	}
	if (y < 20) {
		draw_number(0, 0, 0, 1, 0x000000);
	}
	draw_text("H&H", x - 19, y + 12, 2.5, 0xffffff);
	draw_text("HOUSES", x - 19.5, y - 6, .5, 0xffffff);
	draw_text("N HOTELS", x - 19.5, y - 10.5, .5, 0xffffff);
	draw_rect(x + 10, y - 8, 2.5, 3.5, 0x179C0B);
	draw_rect(x + 13.5, y - 7, 1, 2.5, 0x096301);
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 4.5, y + y1 - 22.5, (y - y1) / 2, .05, 0x096301);
	}
	/*	for (float y1 = y; y1 <= y+2; y1 += .1) {
			draw_rect(x + y1/2 + 2.5, y + y1 - 31.5, (y1 - y) / 2, .05, 0x096301);
		}*/
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 2.5, y + y1 - 24.5, (y1 - y) / 2, .05, 0x38F927);
	}
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 - .5, y + y1 - 22.5, (y - y1) / 2, .05, 0x38F927);
	}
	draw_rect(x + 11, y - 3.5, 1.6, 1, 0x38F927);

	draw_rect(x + 13, y - 11, 2.5, 3.5, 0x179C0B);
	draw_rect(x + 16.5, y - 10, 1, 2.5, 0x096301);
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 7.5, y + y1 - 25.5, (y - y1) / 2, .05, 0x096301);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 5.5, y + y1 - 34.5, (y1 - y) / 2, .05, 0x096301);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 5.5, y + y1 - 27.5, (y1 - y) / 2, .05, 0x38F927);
	}
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 2.5, y + y1 - 25.5, (y - y1) / 2, .05, 0x38F927);
	}
	draw_rect(x + 14, y - 6.5, 1.6, 1, 0x38F927);

	draw_rect(x + 20, y - 7, 2.5, 5.5, 0xFF1E1E);
	draw_rect(x + 23.5, y - 6, 1, 4.5, 0xC01A1A);
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 14.5, y + y1 - 19.5, (y - y1) / 2, .05, 0xC01A1A);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 12.5, y + y1 - 32.5, (y1 - y) / 2, .05, 0xC01A1A);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 12.5, y + y1 - 21.5, (y1 - y) / 2, .05, 0xFF3333);
	}
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 9.5, y + y1 - 19.5, (y - y1) / 2, .05, 0xFF3333);
	}
	draw_rect(x + 21, y - .5, 1.6, 1, 0xFF3333);

}

internal void
draw_logo2(float x, float y, float size) {
	size = .5;
	for (float y1 = -22.3; y1 <= 22.3; y1 += .1) {
		draw_rect(x, y + y1, sqrt(1000 - 2 * y1 * y1), .05, 0x72ADC5);
	}
	draw_text("H&H", x - 19, y + 12, 2.5, 0xffffff);
	draw_text("HOUSES", x - 19.5, y - 6, .5, 0xffffff);
	draw_text("N HOTELS", x - 19.5, y - 10.5, .5, 0xffffff);
	draw_rect(x + 10, y - 8, 2.5, 3.5, 0x179C0B);
	draw_rect(x + 13.5, y - 7, 1, 2.5, 0x096301);
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 13, y + y1 - 5.5, (y - y1) / 2, .05, 0x096301);
	}
	/*	for (float y1 = y; y1 <= y+2; y1 += .1) {
			draw_rect(x + y1/2 + 2.5, y + y1 - 31.5, (y1 - y) / 2, .05, 0x096301);
		}*/
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 11, y + y1 - 7.5, (y1 - y) / 2, .05, 0x38F927);
	}
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 8, y + y1 - 5.5, (y - y1) / 2, .05, 0x38F927);
	}
	draw_rect(x + 11, y - 3.5, 1.6, 1, 0x38F927);

	draw_rect(x + 13, y - 11, 2.5, 3.5, 0x179C0B);
	draw_rect(x + 16.5, y - 10, 1, 2.5, 0x096301);
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 16, y + y1 - 8.5, (y - y1) / 2, .05, 0x096301);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 14, y + y1 - 17.5, (y1 - y) / 2, .05, 0x096301);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 14, y + y1 - 10.5, (y1 - y) / 2, .05, 0x38F927);
	}
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 11, y + y1 - 8.5, (y - y1) / 2, .05, 0x38F927);
	}
	draw_rect(x + 14, y - 6.5, 1.6, 1, 0x38F927);

	draw_rect(x + 20, y - 7, 2.5, 5.5, 0xFF1E1E);
	draw_rect(x + 23.5, y - 6, 1, 4.5, 0xC01A1A);
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 23, y + y1 - 2.5, (y - y1) / 2, .05, 0xC01A1A);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 21, y + y1 - 15.5, (y1 - y) / 2, .05, 0xC01A1A);
	}
	for (float y1 = y; y1 <= y + 2; y1 += .1) {
		draw_rect(x + y1 / 2 + 21, y + y1 - 4.5, (y1 - y) / 2, .05, 0xFF3333);
	}
	for (float y1 = y - 2; y1 <= y; y1 += .1) {
		draw_rect(x + y1 / 2 + 18, y + y1 - 2.5, (y - y1) / 2, .05, 0xFF3333);
	}
	draw_rect(x + 21, y - .5, 1.6, 1, 0xFF3333);

}


internal void 
draw_table(int lefta[], const char* names[], const char* prop_names[]) {
	draw_rect(0, 0, 45, 45, 0xffef95);
	draw_logo2(0, 3, .5);
	draw_text("MADE BY CAPTAIN KOUK", -23, -20, .4, 0x000000);
	draw_rect(-32, 0, .35, 45, 0x000000);
	draw_rect(+32, 0, .35, 45, 0x000000);
	draw_rect(0, +32, 45, .35, 0x000000);
	draw_rect(0, -32, 45, .35, 0x000000);

	draw_rect(-3.55, 38.5, .25, 6.5, 0x000000);
	draw_rect(3.55, 38.5, .25, 6.5, 0x000000);
	draw_rect(-17.75, 38.5, .25, 6.5, 0x000000);
	draw_rect(-10.65, 38.5, .25, 6.5, 0x000000);
	draw_rect(-24.85, 38.5, .25, 6.5, 0x000000);
	draw_rect(+17.75, 38.5, .25, 6.5, 0x000000);
	draw_rect(+10.65, 38.5, .25, 6.5, 0x000000);
	draw_rect(+24.85, 38.5, .25, 6.5, 0x000000);

	draw_rect(-3.55, -38.5, .25, 6.5, 0x000000);
	draw_rect(3.55, -38.5, .25, 6.5, 0x000000);
	draw_rect(-17.75, -38.5, .25, 6.5, 0x000000);
	draw_rect(-10.65, -38.5, .25, 6.5, 0x000000);
	draw_rect(-24.85, -38.5, .25, 6.5, 0x000000);
	draw_rect(+17.75, -38.5, .25, 6.5, 0x000000);
	draw_rect(+10.65, -38.5, .25, 6.5, 0x000000);
	draw_rect(+24.85, -38.5, .25, 6.5, 0x000000);

	draw_rect(-38.5, -3.55, 6.5, .25, 0x000000);
	draw_rect(-38.5, 3.55, 6.5, .25, 0x000000);
	draw_rect(-38.5, -17.75, 6.5, .25, 0x000000);
	draw_rect(-38.5, -10.65, 6.5, .25, 0x000000);
	draw_rect(-38.5, -24.85, 6.5, .25, 0x000000);
	draw_rect(-38.5, 17.75, 6.5, .25, 0x000000);
	draw_rect(-38.5, 10.65, 6.5, .25, 0x000000);
	draw_rect(-38.5, 24.85, 6.5, .25, 0x000000);

	draw_rect(38.5, -3.55, 6.5, .25, 0x000000);
	draw_rect(38.5, 3.55, 6.5, .25, 0x000000);
	draw_rect(38.5, -17.75, 6.5, .25, 0x000000);
	draw_rect(38.5, -10.65, 6.5, .25, 0x000000);
	draw_rect(38.5, -24.85, 6.5, .25, 0x000000);
	draw_rect(38.5, 17.75, 6.5, .25, 0x000000);
	draw_rect(38.5, 10.65, 6.5, .25, 0x000000);
	draw_rect(38.5, 24.85, 6.5, .25, 0x000000);

	draw_text("P", -40, 41.5, .8, 0xff0000);
	draw_text("PARKING", -43.5, 35, .25, 0xff0000);
	draw_text("GO TO", 35, 41, .3, 0x000000);
	draw_text("JAIL", 36, 37, .3, 0x000000);
	draw_text("GO", 37, -36, .6, 0xff0000);
	draw_rect(40, -42, 4, .5, 0xff0000);
	draw_rect(36, -42, .1, .7, 0xff0000);
	draw_rect(35.8, -42, .1, .6, 0xff0000);
	draw_rect(35.6, -42, .1, .5, 0xff0000);
	draw_rect(35.4, -42, .1, .4, 0xff0000);
	draw_rect(35.2, -42, .1, .3, 0xff0000);
	draw_rect(35, -42, .1, .2, 0xff0000);
	draw_rect(34.8, -42, .1, .1, 0xff0000);
	draw_rect(-37, -36.9, 4.55, 4.55, 0xff6400);
	draw_rect(-37, -36.9, 2, 2, 0xffffff);
	draw_rect(-38, -36.9, .15, 2, 0x000000);
	draw_rect(-37, -36.9, .15, 2, 0x000000);
	draw_rect(-36, -36.9, .15, 2, 0x000000);
	draw_rect(-39, -36.9, .2, 2, 0x000000);
	draw_rect(-35, -36.9, .2, 2, 0x000000);
	draw_rect(-37, -39, 2, .2, 0x000000);
	draw_rect(-37, -35, 2, .2, 0x000000);
	draw_text("JAIL", -39, -33, .2, 0x000000);
	draw_text("JUST VISITING", -44, -43, .15, 0x000000);

	/*bottom row */ {
		draw_rect(28.4, -33.25, 3.3, 1, 0x5d0b0b);
		draw_text("INDO", 26, -37, .18, 0x000000);
		draw_text("NESIA", 25.5, -40, .18, 0x000000);
		draw_rect(14.2, -33.25, 3.3, 1, 0x5d0b0b);
		draw_text("PHILIP", 11.3, -37, .18, 0x000000);
		draw_text("PINES", 11.5, -40, .18, 0x000000);
		draw_text("SYDNEY", -2.5, -37, .16, 0x000000);
		draw_text("AIRPORT", -3, -40, .16, 0x000000);
		draw_rect(-7.1, -33.25, 3.3, 1, 0x0099ff);
		draw_text(prop_names[7], -9.5, -38.5, .18, 0x000000);
		draw_rect(-21.3, -33.25, 3.3, 1, 0x0099ff);
		draw_text(prop_names[9], -24, -38.5, .17, 0x000000);
		draw_rect(-28.4, -33.25, 3.3, 1, 0x0099ff);
		draw_text(prop_names[10], -31, -38.5, .18, 0x000000);
		draw_text("TAX", 4.8, -38, .3, 0x000000);
		draw_text("?", -15, -36, .9, 0xff00b9);
		draw_text("COMM", 19.5, -37, .18, 0x000000);
		draw_text("CHEST", 19, -40, .18, 0x000000);
	}

	/*top row*/ {
		draw_rect(-28.4, 33.25, 3.3, 1, 0xff0000);
		draw_text(prop_names[22], -31.8, 38.5, .13, 0x000000);
		draw_rect(-14.2, 33.25, 3.3, 1, 0xff0000);
		draw_text("NEW", -15.5, 40, .17, 0x000000);
		draw_text("ZEALAND", -17.5, 37, .17, 0x000000);
		draw_rect(-7.1, 33.25, 3.3, 1, 0xff0000);
		draw_text(prop_names[25], -9.5, 38.5, .18, 0x000000);
		draw_text("HANEDA", -2.7, 40, .16, 0x000000);
		draw_text("AIRPORT", -3, 37, .16, 0x000000);
		draw_rect(7.1, 33.25, 3.3, 1, 0xf4fb00);
		draw_text("MADA", 5, 40, .17, 0x000000);
		draw_text("GASCAR", 4, 37, .17, 0x000000);
		draw_rect(14.2, 33.25, 3.3, 1, 0xf4fb00);
		draw_text(prop_names[28], 11, 38.5, .15, 0x000000);
		draw_rect(28.4, 33.25, 3.3, 1, 0xf4fb00);
		draw_text("SEY", 27, 40, .16, 0x000000);
		draw_text("CHELLES", 25.25, 37, .16, 0x000000);
		draw_text("?", -22, 41, .9, 0x00a4ff);
		draw_text("WATER", 19, 40, .16, 0x000000);
		draw_text("WORKS", 19, 37, .16, 0x000000);
	}

	/*right row*/ {
		draw_rect(33.25, -14.2, 1, 3.3, 0x040065);
		draw_text("KOUK", 35, -28, .2, 0x000000);
		draw_text("ISLANDS", 35, -30, .2, 0x000000);
		draw_text("TAX", 35, -20.5, .3, 0x000000);
		draw_rect(33.25, -28.4, 1, 3.3, 0x040065);
		draw_text(prop_names[38], 35, -16, .2, 0x000000);
		draw_text("HEATHROW", 33, .7, .2, 0x000000);
		draw_text("AIRPORT", 33, -1.5, .2, 0x000000);
		draw_rect(33.25, 7.1, 1, 3.3, 0x0a6900);
		draw_text(prop_names[35], 35, 5.3, .18, 0x000000);
		draw_rect(33.25, 21.3, 1, 3.3, 0x0a6900);
		draw_text(prop_names[32], 35, 26.5, .2, 0x000000);
		draw_rect(33.25, 28.35, 1, 3.3, 0x0a6900);
		draw_text(prop_names[33], 35, 19.5, .18, 0x000000);
		draw_text("?", 38, -5.2, .7, 0xff0000);
		draw_text("COMM CHEST", 33, 12.2, .17, 0x000000);
	}

	/*left row*/ {
		draw_rect(-33.25, -7.1, 1, 3.3, 0xff00b9);
		draw_text(prop_names[12], -43, -30, .18, 0x000000);
		draw_rect(-33.25, -14.2, 1, 3.3, 0xff00b9);
		draw_text(prop_names[14], -42, -15.8, .18, 0x000000);
		draw_rect(-33.25, -28.4, 1, 3.3, 0xff00b9);
		draw_text(prop_names[15], -41, -9, .18, 0x000000);
		draw_text("JOSE MARTI", -45, .2, .18, 0x000000);
		draw_text("AIRPORT", -41.7, -1.5, .18, 0x000000);
		draw_rect(-33.25, 7.1, 1, 3.3, 0xff7700);
		draw_text("G BRITAIN", -43.5, 5.5, .17, 0x000000);
		draw_rect(-33.25, 21.3, 1, 3.3, 0xff7700);
		draw_text(prop_names[19], -42, 19.4, .18, 0x000000);
		draw_rect(-33.25, 28.35, 1, 3.3, 0xff7700);
		draw_text(prop_names[20], -42, 26.6, .18, 0x000000);
		draw_text("ELECTRIC", -43, -21, .18, 0x000000);
		draw_text("COMPANY", -42, -23, .18, 0x000000);
		draw_text("COMM CHEST", -44, 13, .17, 0x000000);
	}

	draw_text(names[1], -64.1, 43, .3, 0x000000);
	draw_number(lefta[1], -48.5, 38, .8, 0x000000);
	draw_text(names[2], -64.1, 32, .3, 0x000000);
	draw_number(lefta[2], -48.5, 27, .8, 0x000000);
	if (lefta[3] > 0) {
		draw_text(names[3], -64.1, 21, .3, 0x000000);
		draw_number(lefta[3], -48.5, 16, .8, 0x000000);
		if (lefta[4] > 0) {
			draw_text(names[4], -64.1, 10, .3, 0x000000);
			draw_number(lefta[4], -48.5, 5, .8, 0x000000);
			if (lefta[5] > 0) {
				draw_text(names[5], -64.1, -1, .3, 0x000000);
				draw_number(lefta[5], -48.5, -6, .8, 0x000000);
				if (lefta[6] > 0) {
					draw_text(names[6], -64.1, -10, .3, 0x000000);
					draw_number(lefta[6], -48.5, -15, .8, 0x000000);
				}
			}
		}
	}

}

int drawn_pos_x[41], drawn_pos_y[41];

internal void
draw_house(float x, float y) {
	draw_rect(x, y, .5, .5, 0x21a908);
	draw_rect(x - .5, y, .1, .5, 0x000000);
	draw_rect(x + .5, y, .1, .5, 0x000000);
	draw_rect(x, y+.5, .5, .1, 0x000000);
	draw_rect(x, y-.5, .5, .1, 0x000000);
}

internal void
draw_hotel(float x, float y) {
	draw_rect(x, y, .8, .8, 0xff0000);
	draw_rect(x - .8, y, .1, .8, 0x000000);
	draw_rect(x + .8, y, .1, .8, 0x000000);
	draw_rect(x, y + .8, .8, .1, 0x000000);
	draw_rect(x, y - .8, .8, .1, 0x000000);
}

internal void 
draw_player(int k, int theseis[], bool isInJail[], int hhtablo[], u32 color) {
	drawn_pos_x[1] = 37; drawn_pos_y[1] = -40;
	drawn_pos_x[2] = 28; drawn_pos_y[2] = -40;
	drawn_pos_x[3] = 21; drawn_pos_y[3] = -40;
	drawn_pos_x[4] = 14; drawn_pos_y[4] = -40;
	drawn_pos_x[5] = 7; drawn_pos_y[5] = -40;
	drawn_pos_x[6] = 0; drawn_pos_y[6] = -40;
	drawn_pos_x[7] = -7.6; drawn_pos_y[7] = -40;
	drawn_pos_x[8] = -14.7; drawn_pos_y[8] = -40;
	drawn_pos_x[9] = -21.8; drawn_pos_y[9] = -40;
	drawn_pos_x[10] = -28.9; drawn_pos_y[10] = -40;
	drawn_pos_x[11] = -43; drawn_pos_y[11] = -43;
	drawn_pos_x[12] = -40; drawn_pos_y[12] = -28.9;
	drawn_pos_x[13] = -40; drawn_pos_y[13] = -21.8;
	drawn_pos_x[14] = -40; drawn_pos_y[14] = -14.7;
	drawn_pos_x[15] = -40; drawn_pos_y[15] = -7.6;
	drawn_pos_x[16] = -40; drawn_pos_y[16] = -0.5;
	drawn_pos_x[17] = -40; drawn_pos_y[17] = 7;
	drawn_pos_x[18] = -40; drawn_pos_y[18] = 14;
	drawn_pos_x[19] = -40; drawn_pos_y[19] = 21;
	drawn_pos_x[20] = -40; drawn_pos_y[20] = 28;
	drawn_pos_x[21] = -38; drawn_pos_y[21] = 40;
	drawn_pos_x[22] = -28.3; drawn_pos_y[22] = 40;
	drawn_pos_x[23] = -21; drawn_pos_y[23] = 40;
	drawn_pos_x[24] = -14; drawn_pos_y[24] = 40;
	drawn_pos_x[25] = -7; drawn_pos_y[25] = 40;
	drawn_pos_x[26] = 0; drawn_pos_y[26] = 40;
	drawn_pos_x[27] = 7.6; drawn_pos_y[27] = 40;
	drawn_pos_x[28] = 14.7; drawn_pos_y[28] = 40;
	drawn_pos_x[29] = 21.8; drawn_pos_y[29] = 40;
	drawn_pos_x[30] = 28.9; drawn_pos_y[30] = 40;
	drawn_pos_x[31] = 40; drawn_pos_y[31] = 40;
	drawn_pos_x[32] = 40; drawn_pos_y[32] = 28.9;
	drawn_pos_x[33] = 40; drawn_pos_y[33] = 21;
	drawn_pos_x[34] = 40; drawn_pos_y[34] = 14;
	drawn_pos_x[35] = 40; drawn_pos_y[35] = 7;
	drawn_pos_x[36] = 40; drawn_pos_y[36] = 0;
	drawn_pos_x[37] = 40; drawn_pos_y[37] = -7.6;
	drawn_pos_x[38] = 40; drawn_pos_y[38] = -14.7;
	drawn_pos_x[39] = 40; drawn_pos_y[39] = -21.8;
	drawn_pos_x[40] = 40; drawn_pos_y[40] = -28.9;

	int counter = 0;
	float x, y;

	//player positioning
	if (theseis[k] != 11) {
		for (int m = 1; m < k; m++) {
			if (theseis[m] == theseis[k]) counter++;
		}
		if (counter == 0) {
			x = drawn_pos_x[theseis[k]];
			y = drawn_pos_y[theseis[k]];
		}
		else if (counter == 1) {
			x = drawn_pos_x[theseis[k]] + 2;
			y = drawn_pos_y[theseis[k]];
		}
		else if (counter == 2) {
			x = drawn_pos_x[theseis[k]];
			y = drawn_pos_y[theseis[k]] + 2;
		}
		else if (counter == 3) {
			x = drawn_pos_x[theseis[k]] + 2;
			y = drawn_pos_y[theseis[k]] + 2;
		}
		else if (counter == 4) {
			x = drawn_pos_x[theseis[k]] - 2; 
			y = drawn_pos_y[theseis[k]];
		}
		else if (counter == 5) {
			x = drawn_pos_x[theseis[k]];
			y = drawn_pos_y[theseis[k]] - 2;
		}
	}
	else if (theseis[k] == 11) {
		for (int m = 1; m < k; m++) {
			if (theseis[m] == theseis[k] && isInJail[k] == isInJail[m]) counter++;
		}
		if (isInJail[k]) {
			if (counter == 0) {
				x = drawn_pos_x[theseis[k]] + 5;
				y = drawn_pos_y[theseis[k]] + 5;
			}
			else if (counter == 1) {
				x = drawn_pos_x[theseis[k]] + 7;
				y = drawn_pos_y[theseis[k]] + 5;
			}
			else if (counter == 2) {
				x = drawn_pos_x[theseis[k]] + 5;
				y = drawn_pos_y[theseis[k]] + 7;
			}
			else if (counter == 3) {
				x = drawn_pos_x[theseis[k]] + 7;
				y = drawn_pos_y[theseis[k]] + 7;
			}
			else if (counter == 4) {
				x = drawn_pos_x[theseis[k]] + 3;
				y = drawn_pos_y[theseis[k]] + 5;
			}
			else if (counter == 5) {
				x = drawn_pos_x[theseis[k]] + 5;
				y = drawn_pos_y[theseis[k]] + 3;
			}
		}
		else if (!isInJail[k]) {
			if (counter == 0) {
				x = drawn_pos_x[theseis[k]];
				y = drawn_pos_y[theseis[k]];
			}
			else if (counter == 1) {
				x = drawn_pos_x[theseis[k]] + 2;
				y = drawn_pos_y[theseis[k]];
			}
			else if (counter == 2) {
				x = drawn_pos_x[theseis[k]];
				y = drawn_pos_y[theseis[k]] + 2;
			}
			else if (counter == 3) {
				x = drawn_pos_x[theseis[k]] + 4;
				y = drawn_pos_y[theseis[k]];
			}
			else if (counter == 4) {
				x = drawn_pos_x[theseis[k]];
				y = drawn_pos_y[theseis[k]] + 4;
			}
			else if (counter == 5) {
				x = drawn_pos_x[theseis[k]] + 6;
				y = drawn_pos_y[theseis[k]];
			}
		}
	}

	//player rendering
	draw_rect(x, y, .7, .7, color);
	u32 bcolor;
	if (color == 0x000000) bcolor = 0x888888;
	else bcolor = 0x000000;
	draw_rect(x-.7, y, .08, .7, bcolor);
	draw_rect(x+.7, y, .08, .7, bcolor);
	draw_rect(x, y-.7, .7, .08, bcolor);
	draw_rect(x, y+.7, .7, .08, bcolor);

	// and houses and hotels
	for (int k = 1; k <= 40; k++) {
		if (hhtablo[k] <= 4 && hhtablo[k] > 0) {
			for (int m = 1; m <= hhtablo[k]; m++) {
				if (k < 11 && k > 1) {
					draw_house(drawn_pos_x[k] - 3 + (1.25 * m), drawn_pos_y[k] + 6.75);
				}
				if (k < 21 && k > 11) {
					draw_house(drawn_pos_x[k] + 6.75, drawn_pos_y[k] - 3.5 + (1.25 * m));
				}
				if (k < 31 && k > 21) {
					draw_house(drawn_pos_x[k] - 3 + (1.25 * m), drawn_pos_y[k] - 6.75);
				}
				if (k < 41 && k > 31) {
					draw_house(drawn_pos_x[k] - 6.75, drawn_pos_y[k] - 3.5 + (1.25 * m));
				}
			}
		}
		else if (hhtablo[k] == 5) {
			if (k < 11 && k > 1) {
				draw_hotel(drawn_pos_x[k], drawn_pos_y[k] + 6.75);
			}
			if (k < 21 && k > 11) {
				draw_hotel(drawn_pos_x[k] + 6.75, drawn_pos_y[k]);
			}
			if (k < 31 && k > 21) {
				draw_hotel(drawn_pos_x[k], drawn_pos_y[k] - 6.75);
			}
			if (k < 41 && k > 31) {
				draw_hotel(drawn_pos_x[k] - 6.75, drawn_pos_y[k]);
			}
		}
	}

}

internal void
draw_props(int i, int tablo[], u32 colors[]) {
	for (int m = 1; m <= 40; m++) {
		if (tablo[m] > 0 && tablo[m] < 9) {
			if (m < 11 && m > 1) {
				draw_rect(drawn_pos_x[m], drawn_pos_y[m] + 8.5, 3.5, .4, colors[tablo[m]]);
			}
			else if (m < 21 && m > 11) {
				draw_rect(drawn_pos_x[m] + 8.5, drawn_pos_y[m], .4, 3.5, colors[tablo[m]]);
			}
			else if (m < 31 && m > 21) {
				draw_rect(drawn_pos_x[m], drawn_pos_y[m] - 8.5, 3.5, .4, colors[tablo[m]]);
			}
			else if (m < 41 && m > 31) {
				draw_rect(drawn_pos_x[m] - 8.5, drawn_pos_y[m], .4, 3.5, colors[tablo[m]]);
			}
		}
	}
}

internal void
draw_card(int pos, const char* prop_names[],int axies[], int enoikia[], int enoikia1h[], int enoikia2h[], int enoikia3h[], int enoikia4h[], int enoikiahot[]) {
//	pos = 22;
	draw_rect(68, 20, 18, 26, 0xffffff);
	draw_rect(68, 45, 17, .15, 0x000000);
	draw_rect(80, -5, 5, .15, 0x000000);
	draw_rect(56, -5, 5, .15, 0x000000);
	draw_rect(51, 20, .15, 25, 0x000000);
	draw_rect(85, 20, .15, 25, 0x000000);
	draw_text("CAPTAIN KOUK", 64.2, -4.5, .15, 0x000000);
	draw_number(20, 63.3, -5, .2, 0x000000);
	draw_number(20, 62, -5, .2, 0x000000);
	if (pos % 10 == 6) {
		draw_text("AIRPORT", 62, 40, .3, 0x000000);
		if (pos < 10) {
			draw_text("KINGSFORD SMITH", 55, 37, .3, 0x000000);
			draw_text("SYDNEY", 62.5, 34, .3, 0x000000);
			draw_text("AUSTRALIA", 60, 31, .3, 0x000000);
		}
		else if (pos < 20) {
			draw_text("JOSE MARTI", 59, 37, .3, 0x000000);
			draw_text("HAVANA", 62.5, 34, .3, 0x000000);
			draw_text("CUBA", 64.25, 31, .3, 0x000000);
		}
		else if (pos < 30) {
			draw_text("HANEDA KUKO", 58, 37, .3, 0x000000);
			draw_text("TOKYO", 63.5, 34, .3, 0x000000);
			draw_text("JAPAN", 63.5, 31, .3, 0x000000);
		}
		else {
			draw_text("HEATHROW", 60.5, 37, .3, 0x000000);
			draw_text("LONDON", 62.5, 34, .3, 0x000000);
			draw_text("UNITED KINGDOM", 55.5, 31, .3, 0x000000);
		}
		draw_text("RENT", 53, 22, .25, 0x000000);
		draw_text("FOR THE OWNER", 53, 19, .25, 0x000000);
		draw_text("OF  AIRPORTS", 53, 16.5, .25, 0x000000);
		draw_number(2, 57, 15.75, .3, 0x000000);
		draw_text("FOR THE OWNER", 53, 13.5, .25, 0x000000);
		draw_text("OF  AIRPORTS", 53, 11, .25, 0x000000);
		draw_number(3, 57, 10.25, .3, 0x000000);
		draw_text("FOR THE OWNER", 53, 8, .25, 0x000000);
		draw_text("OF  AIRPORTS", 53, 5.5, .25, 0x000000);
		draw_number(4, 57, 4.75, .3, 0x000000);

		draw_number(250000, 82.5, 21, .3, 0x000000);
		draw_number(500000, 82.5, 15.75, .3, 0x000000);
		draw_number(1000000, 82.5, 10.25, .3, 0x000000);
		draw_number(2000000, 82.5, 4.75, .3, 0x000000);

		draw_text("MORTGAGE VALUE", 53, -1.5, .25, 0x000000);
		draw_number(1000000, 82.5, -2, .3, 0x000000);
	}
	else if (pos == 13 || pos == 29) {
		if (pos == 13) draw_text(prop_names[pos], 54, 38, .3, 0x000000);
		else draw_text(prop_names[pos], 57, 38, .35, 0x000000);
		draw_text("FOR THE OWNER OF A", 57.5, 30, .2, 0x000000);
		draw_text("COMMUNITY SERVICE THE", 55.5, 28, .2, 0x000000);
		draw_text("RENT IS  TIMES THE", 57.5, 26, .2, 0x000000);
		draw_text("NUMBER OF THE DICE", 57.5, 24, .2, 0x000000);
		draw_text("MULITPLIED BY", 58, 22, .2, 0x000000);
		draw_number(10000, 77.5, 21.5, .25, 0x000000);
		draw_number(4, 67, 25.5, .25, 0x000000);

		draw_text("FOR THE OWNER OF TWO", 56, 17, .2, 0x000000);
		draw_text("COMMUNITY SERVICE THE", 55.5, 15, .2, 0x000000);
		draw_text("RENT IS  TIMES THE", 57.5, 13, .2, 0x000000);
		draw_text("NUMBER OF THE DICE", 57.5, 11, .2, 0x000000);
		draw_text("MULITPLIED BY", 58, 9, .2, 0x000000);
		draw_number(10000, 77.5, 8.5, .25, 0x000000);
		draw_number(10, 67, 12.5, .25, 0x000000);

		draw_text("MORGAGE VALUE", 53, 0, .25, 0x000000);
		draw_number(750000, 80, -.55, .3, 0x000000);
	}
	else {
		if (pos < 5) draw_rect(68, 38.5, 16, 6, 0x781515);
		else if (pos < 11) draw_rect(68, 38.5, 16, 6, 0x0099ff);
		else if (pos < 16) draw_rect(68, 38.5, 16, 6, 0xff00b9);
		else if (pos < 21) draw_rect(68, 38.5, 16, 6, 0xff7700);
		else if (pos < 26) draw_rect(68, 38.5, 16, 6, 0xff0000);
		else if (pos < 31) draw_rect(68, 38.5, 16, 6, 0xf4fb00);
		else if (pos < 36) draw_rect(68, 38.5, 16, 6, 0x0a6900);
		else draw_rect(68, 38.5, 16, 6, 0x100b80);
		draw_text(prop_names[pos], 58, 39.5, .3, 0x000000);
		draw_text("RENT", 52.5, 32, .2, 0x000000);
		draw_text("WITHOUT HOUSE", 52.5, 30, .2, 0x000000);
		draw_text("WITH  HOUSE", 52.5, 28, .2, 0x000000);
		draw_text("WITH  HOUSES", 52.5, 26, .2, 0x000000);
		draw_text("WITH  HOUSES", 52.5, 24, .2, 0x000000);
		draw_text("WITH  HOUSES", 52.5, 22, .2, 0x000000);
		draw_text("WITH HOTEL", 52.5, 20, .2, 0x000000);
		draw_number(1, 58.5, 27.5, .25, 0x000000);
		draw_number(2, 58.5, 25.5, .25, 0x000000);
		draw_number(3, 58.5, 23.5, .25, 0x000000);
		draw_number(4, 58.5, 21.5, .25, 0x000000);

		draw_number(enoikia[pos], 83.5, 29.5, .25, 0x000000);
		draw_number(enoikia1h[pos], 83.5, 27.5, .25, 0x000000);
		draw_number(enoikia2h[pos], 83.5, 25.5, .25, 0x000000);
		draw_number(enoikia3h[pos], 83.5, 23.5, .25, 0x000000);
		draw_number(enoikia4h[pos], 83.5, 21.5, .25, 0x000000);
		draw_number(enoikiahot[pos], 83.5, 19.5, .25, 0x000000);

		draw_rect(68, 18, 16, .15, 0x000000);

		draw_text("IF A PLAYER OWNS ALL", 56.5, 17, .2, 0x000000);
		draw_text("THE PROPERTIES OF THE", 55.5, 15, .2, 0x000000);
		draw_text("SAME COLOR THEN THE RENT", 54, 13, .2, 0x000000);
		draw_text("IS DOUBLED FOR THE", 57.5, 11, .2, 0x000000);
		draw_text("PROPERTIES WITHOUT A HOUSE", 52.5, 9, .2, 0x000000);
	
		draw_rect(68, 6.75, 16, .15, 0x000000);

		draw_text("HOUSE PRICE", 52.5, 5.5, .2, 0x000000);
		draw_text("HOTEL PRICE", 52.5, 3.5, .2, 0x000000);
		int houseval;
		if (pos < 11) houseval = 500000;
		else if (pos < 21) houseval = 1000000;
		else if (pos < 11) houseval = 1500000;
		else houseval = 2000000;
		draw_number(houseval, 77, 5, .25, 0x000000);
		draw_number(houseval, 77, 3, .25, 0x000000);
		draw_text("EACH", 79, 5.5, .2, 0x000000);
		draw_text("EACH", 79, 3.5, .2, 0x000000);
		draw_text("PLUS  HOUSES", 69.5, 1.5, .2, 0x000000);
		draw_number(4, 75.5, 1, .25, 0x000000);

		draw_text("MORTGAGE VALUE", 52.5, -2, .2, 0x000000);
		draw_number(axies[pos] / 2, 82.5, -2.5, .25, 0x000000);

	}
}


internal void
draw_police_van_up(float x, float y, bool isSirenOn) {
	draw_rect(x, y, 1.5, 2.5, 0x000000);
	draw_rect(x, y + 1.2, 1, .4, 0x888888);
	draw_rect(x, y + .1, 1, .2, 0xffffff);
	if (isSirenOn) {
		draw_rect(x-.6, y + .1, .35, .2, 0x0b00ff);
		draw_rect(x+.6, y + .1, .35, .2, 0xff0000);
		draw_rect(x-.6, y-2.4, .6, .12, 0x0b00ff);
		draw_rect(x+.6, y-2.4, .6, .12, 0xff0000);
	}
	else {
		draw_rect(x - .6, y + .1, .35, .2, 0x5458B4);
		draw_rect(x + .6, y + .1, .35, .2, 0xB45454);
	}
	draw_rect(x - 1.6, y + 1, .25, .15, 0x000000);
	draw_rect(x+1.6, y+1, .25, .15, 0x000000);
	draw_rect(x - 1.2, y, .1, .5, 0x888888);
	draw_rect(x + 1.2, y, .1, .5, 0x888888);
	draw_rect(x - 1.2, y-1.25, .1, .5, 0x888888);
	draw_rect(x + 1.2, y-1.25, .1, .5, 0x888888);
}

internal void
draw_police_van_right(float x, float y, bool isSirenOn) {
	draw_rect(x, y, 2.5, 1.5, 0x000000);
	draw_rect(x+1.2, y, .4, 1, 0x888888);
	draw_rect(x+.1, y, .2, 1, 0xffffff);
	if (isSirenOn) {
		draw_rect(x+.1, y +.65, .2, .35, 0x0b00ff);
		draw_rect(x +.1, y - .65, .2, .35, 0xff0000);
		draw_rect(x - 2.4, y + .6, .12, .6, 0x0b00ff);
		draw_rect(x - 2.4, y - .6, .12, .6, 0xff0000);
	}
	else {
		draw_rect(x + .1, y + .65, .2, .35, 0x5458B4);
		draw_rect(x + .1, y - .65, .2, .35, 0xB45454);
	}
	draw_rect(x + 1, y - 1.6, .15, .25, 0x000000);
	draw_rect(x + 1, y + 1.6, .15, .25, 0x000000);
	draw_rect(x, y-1.2, .5, .1, 0x888888);
	draw_rect(x, y+1.2, .5, .1, 0x888888);
	draw_rect(x - 1.25, y - 1.2, .5, .1, 0x888888);
	draw_rect(x - 1.25, y + 1.2, .5, .1, 0x888888);
}

internal void
draw_police_van_down(float x, float y, bool isSirenOn) {
	draw_rect(x, y, 1.5, 2.5, 0x000000);
	draw_rect(x, y - 1.2, 1, .4, 0x888888);
	draw_rect(x, y - .1, 1, .2, 0xffffff);
	if (isSirenOn) {
		draw_rect(x + .6, y - .1, .35, .2, 0x0b00ff);
		draw_rect(x - .6, y - .1, .35, .2, 0xff0000);
		draw_rect(x + .6, y + 2.4, .6, .12, 0x0b00ff);
		draw_rect(x - .6, y + 2.4, .6, .12, 0xff0000);
	}
	else {
		draw_rect(x + .6, y - .1, .35, .2, 0x5458B4);
		draw_rect(x - .6, y - .1, .35, .2, 0xB45454);
	}
	draw_rect(x + 1.6, y - 1, .25, .15, 0x000000);
	draw_rect(x - 1.6, y - 1, .25, .15, 0x000000);
	draw_rect(x + 1.2, y, .1, .5, 0x888888);
	draw_rect(x - 1.2, y, .1, .5, 0x888888);
	draw_rect(x + 1.2, y + 1.25, .1, .5, 0x888888);
	draw_rect(x - 1.2, y + 1.25, .1, .5, 0x888888);
}

internal void
draw_police_van_left(float x, float y, bool isSirenOn) {
	draw_rect(x, y, 2.5, 1.5, 0x000000);
	draw_rect(x - 1.2, y, .4, 1, 0x888888);
	draw_rect(x - .1, y, .2, 1, 0xffffff);
	if (isSirenOn) {
		draw_rect(x - .1, y - .65, .2, .35, 0x0b00ff);
		draw_rect(x - .1, y + .65, .2, .35, 0xff0000);
		draw_rect(x + 2.4, y - .6, .12, .6, 0x0b00ff);
		draw_rect(x + 2.4, y + .6, .12, .6, 0xff0000);
	}
	else {
		draw_rect(x - .1, y - .65, .2, .35, 0x5458B4);
		draw_rect(x - .1, y + .65, .2, .35, 0xB45454);
	}
	draw_rect(x - 1, y + 1.6, .15, .25, 0x000000);
	draw_rect(x - 1, y - 1.6, .15, .25, 0x000000);
	draw_rect(x, y + 1.2, .5, .1, 0x888888);
	draw_rect(x, y + 1.2, .5, .1, 0x888888);
	draw_rect(x + 1.25, y + 1.2, .5, .1, 0x888888);
	draw_rect(x + 1.25, y - 1.2, .5, .1, 0x888888);
}

//
//internal void
//draw_island() {
//	int x = -70;
//	float length;
//	for (int y = 1; y < 50; y++) {
//		length = sqrt(y) * 5;
//		draw_rect(x, y*.1-40, length * .5, .1, 0xFFFC6E);
//	}
//	for (int y = 50; y < 100; y++) {
//		length = 35 - (y - 50) * (y - 50) / 50;
//		draw_rect(x, y * .1-40, length * .5, .1, 0xFFFC6E);
//	}
//	float x1, x2;
//	for (int y = 10; y < 250; y++) {
//		x1 = sqrt(y) /2.3 -50;
//		x2 = sqrt(y-50) / 3-50;
//		draw_rect((x1 + x2)/2-23, y*.1 -40, (x1-x2) * .5, .1, 0x8D2222);
//	}
//	//float y1, y2;
//	//for (int x = 10; x < 20; x++) {
//	//	y1 = x*x / (-10) - .2*x;
//	//	y2 = -.35*x * x - .2*x;
//	//	draw_rect(x*.1-70, (y1+y2)/2*.1-15, .1, (y1-y2)/2*.1, 0x1DBB00);
//	//}
//	for (int y = 1; y < 50; y++) {
//		length = sqrt(y) * 5;
//		x = sqrt(y) * 2;
//		draw_rect(x*.1, y * .1 - 40, length * .5, .1, 0x000000);
//	}
//	for (int y = -50; y < -10; y++) {
//		x1 = sqrt(-1*y) * 2.5 - 50;
//		x2 = sqrt(-1*y) * 1.7 - 48;
//		draw_rect((x1 + x2) / 2 - 33, y * .1 - 10, (x1 - x2) * .5, .1, 0x1DBB00);
//	}
//
//}


internal void
draw_money(float x, float y) {
	draw_rect(x, y, 2, 1, 0x65b343);
	draw_rect(x+1.6, y, .15, .8, 0x2d9300);
	draw_rect(x-1.6, y, .15, .8, 0x2d9300);
	draw_rect(x, y-.7, 1.6, .15, 0x2d9300);
	draw_rect(x, y+.7, 1.6, .15, 0x2d9300);
	draw_rect(x, y, .4, .3, 0x2d9300);
	draw_rect(x, y, .25, 1.1, 0x888888);
}


internal  void 
draw_balloon(float x, float y, float size, u32 color) {
	if (color == 0x888888) color = 0x545454;
	
	draw_rect(x, y, 15*size, 15*size, color);
	draw_rect(x, y, 17*size, 10*size, color);
	draw_rect(x, y-1*size, 13*size, 18*size, color);
	draw_rect(x, y-1.2*size, 11.5*size, 20*size, color);
	draw_rect(x, y-1.4*size, 9*size, 22*size, color);
	draw_rect(x, y-1.6*size, 5*size, 23.5*size, color);
	draw_rect(x, y-24.5*size, 2*size, 2*size, color);

	u32 rcolor;
	if (color == 0xffffff) rcolor = 0xff0000;
	else rcolor = 0xffffff;

	draw_rect(x, y - 36*size, 1*size, 10*size, rcolor);
	draw_rect(x+1, y - 50*size, 1*size, 8*size, rcolor);
	draw_rect(x, y - 64*size, 1*size, 10*size, rcolor);

	draw_text("WINNER", x-10*size, y, .6*size, rcolor);

}

const char* gr_letters[][7] = {
	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	"0  0",
	"0  0",
	"000",
	"0  0",
	"0  0",
	"000",

	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 000",
	"  0",
	"  0",
	"  0",

	" 00",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	"0000",
	"0",
	"0",
	"000",
	"0",
	"0",
	"0000",

	"  0",
	" 000",
	"0 0 0",
	"0 0 0",
	" 000",
	"  0",
	"  0",

	"00000",
	"0",
	"0",
	"0",
	"0",
	"0",
	"0",

	"0  0",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	"0  0",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	"000",

	"0000",
	"",
	"",
	"0000",
	"",
	"",
	"0000",

	"0  0",
	"0  0",
	"0 0",
	"00",
	"0 0",
	"0  0",
	"0  0",

	" 00",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",

	"00 00",
	"0 0 0",
	"0 0 0",
	"0   0",
	"0   0",
	"0   0",
	"0   0",

	"00  0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	"0  00",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0000",

	"0000",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",
	"0  0",

	"",
	"",
	"",
	"",
	"",
	"",
	"",

	" 000",
	"0  0",
	"0  0",
	"000",
	"0",
	"0",
	"0",

	"0000",
	"0",
	" 0 ",
	" 00",
	" 0",
	"0",
	" 000",

	"000",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",
	" 0",

	" 00",
	"0  0",
	"0  0",
	"0000",
	"0  0",
	"0  0",
	" 00",

	" 000",
	"0   0",
	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"00000",

	"0   0 ",
	"0   0",
	"0   0",
	"0 0 0",
	"0 0 0",
	"0 0 0",
	" 0 0 ",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	" 0 0",
	"0   0",
	"0   0",

	"0   0",
	"0   0",
	" 0 0",
	"  0",
	"  0",
	"  0",
	"  0",

	"0000",
	"   0",
	"  0",
	" 0",
	"0",
	"0",
	"0000",

	"0",
	"0",
	"0",
	"0",
	"0",
	"",
	"0",

	" 0",
	"0 0",
	"  0",
	" 0",
	" 0",
	"",
	" 0",
};

// for '?' call '/' and for '!' call '.'
internal void
draw_gr_text(const char* text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
		if (*text != 32) {
			const char** letter;
			if (*text == 47) letter = gr_letters[27];
			else if (*text == 46) letter = gr_letters[26];
			else letter = gr_letters[*text - 'A'];
			float original_x = x;

			for (int i = 0; i < 7; i++) {
				const char* row = letter[i];
				while (*row) {
					if (*row == '0') {
						draw_rect(x, y, half_size, half_size, color);
					}
					x += size;
					row++;
				}
				y -= size;
				x = original_x;
			}
		}
		text++;
		x += size * 6.f;
		y = original_y;
	}
}

