#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

enum Gamemode {
	GM_MENU,
//	GM_PLAYER_NAMES,
	GM_COLORS,
	GM_ROLL_THE_DICE,
	GM_GAMEPLAY,
	GM_BUY_MENU,
	GM_AUCTION,
	GM_CANT_BUY,
	GM_SUCCESSFUL,
	GM_YOURS,
	GM_YOU_HAVE_TO_PAY,
	GM_TAX,
	GM_ANYTHING_ELSE,
	GM_WHAT_PROP_SM,
	GM_WHAT_PROP_AM,
	GM_WHAT_PROP_H,
	GM_WHAT_PROP_SELLH,
	GM_MY_PROPS,
	GM_CHANCE,
	GM_COMMUNITY_CHEST,
	GM_JAIL,
	GM_OUT_OF_JAIL,
	GM_END_OF_GAME,
	GM_GRAPHICS_POLICE,
	GM_GRAPHICS_MONEY,
};

Gamemode current_gamemode;
int hotButton = 2;

int tablo[41];      // the table of the game (what belongs to the players) - if a property is mortgaged then it's value is 10*i
int hhtablo[41];    // the table of the game (how many houses does a property have)
int theseis[7];     // the positions of the players
int lefta[7];       // money of each player
bool isInJail[7];
int doublesInJail[7];//how many doubles chances a player has missed before paying to get out of jail
u32 colors[7];       // the color of each player
int score[7];        // the score of the players at the end of the game

u32 selected_color;
bool ok;           // indicates if it's ok to pick a color
int dice1, dice2;
int i = 1;			// the current player
int nop;			// number of players
int doubles = 0;
float box_half_side = 0;          // the half side of the grey box at the auction menu
float box_half_side_speed = 140;
int current_price = 100000;   // the current bid the player wants to place
int last_bid = 100000;        // the last confirmed bid
int a = 1;                    // the current player who can place a bid
int current_bidder;
bool auction_live = false;    // indicates if the auction is live 
int chancesCounter = -1, commChestCounter = -1;
int outOfJailCard = 0, outOfJailCardPos;
int prop_chosen;
bool somethingPressed = false, somethingToBeViewed = false;
int propCounter = 0;
int fee;             // the money one has to pay to another player
int airportCounter = 0;
bool dontThrowDice = false;
int winner, maxpoints = 0;
int police_van_direction = 0; // up is 1, right is 2, down is 3, left is 4
bool isSirenOn;
float police_van_x = -42, police_van_y = -42, police_van_dx, total_time = 0;
bool arrested = false;
int money_direction = 0; // up is 1, right is 2, down is 3, left is 4
float money_x[10], money_y[10], money_dx;
float balloon1y=-100, balloon2y=-100, balloon3y=-100, balloondp=60;

int j;

int senders[7], receiver;

const char* names[7] = {
	"",
	"PLAYERONE",
	"PLAYERTWO",
	"PLAYERTHREE",
	"PLEYERFOUR",
	"PLAYERFIVE",
	"PLAYERSIX",
};

const char* prop_names[41] = {
	"",
	"",
	"INDONESIA",
	"",
	"PHILIPPINES",
	"",
	"SYDNEY AIRPORT",
	"CRETE",
	"",
	"CYPRUS",
	"MALTA",
	"",
	"SARDINIA",
	"ELECTRIC COMPANY",
	"CORSICA",
	"SICILY",
	"JOSE MARTI AIRPORT",
	"GREAT BRITAIN",
	"",
	"IRELAND",
	"ICELAND",
	"",
	"AUSTRALIA",
	"",
	"NEW ZEALAND",
	"JAPAN",
	"HANEDA AIRPORT",
	"MADAGASCAR",
	"MALDIVES",
	"WATER WORKS",
	"SEYCHELLES",
	"",
	"CUBA",
	"JAMAICA",
	"",
	"BAHAMAS",
	"HEATHROW AIRPORT",
	"",
	"HAWAII",
	"",
	"KOUK ISLANDS",
};

float drawn_money_pos[7] = { 0, 41.5, 30, 19, 8, -3, -12 };

bool canBuildHouse(int a) {
	if (a == 2 || a == 4) {
		if (tablo[2] == i && tablo[4] == i &&
			hhtablo[a] - hhtablo[2] < 1 &&
			hhtablo[a] - hhtablo[4] < 1) return true;
	}
	else if (a == 7 || a == 9 || a == 10) {
		if (tablo[7] == i && tablo[9] == i && tablo[10] == i &&
			hhtablo[a] - hhtablo[7] < 1 &&
			hhtablo[a] - hhtablo[9] < 1 &&
			hhtablo[a] - hhtablo[10] < 1) return true;
	}
	else if (a == 12 || a == 14 || a == 15) {
		if (tablo[12] == i && tablo[14] == i && tablo[15] == i &&
			hhtablo[a] - hhtablo[12] < 1 &&
			hhtablo[a] - hhtablo[14] < 1 &&
			hhtablo[a] - hhtablo[15] < 1) return true;
	}
	else if (a == 17 || a == 19 || a == 20) {
		if (tablo[17] == i && tablo[19] == i && tablo[20] == i &&
			hhtablo[a] - hhtablo[17] < 1 &&
			hhtablo[a] - hhtablo[19] < 1 &&
			hhtablo[a] - hhtablo[20] < 1) return true;
	}
	else if (a == 22 || a == 24 || a == 25) {
		if (tablo[22] == i && tablo[24] == i && tablo[25] == i &&
			hhtablo[a] - hhtablo[22] < 1 &&
			hhtablo[a] - hhtablo[24] < 1 &&
			hhtablo[a] - hhtablo[25] < 1) return true;
	}
	else if (a == 27 || a == 28 || a == 30) {
		if (tablo[27] == i && tablo[28] == i && tablo[30] == i &&
			hhtablo[a] - hhtablo[27] < 1 &&
			hhtablo[a] - hhtablo[28] < 1 &&
			hhtablo[a] - hhtablo[30] < 1) return true;
	}
	else if (a == 32 || a == 33 || a == 35) {
		if (tablo[32] == i && tablo[33] == i && tablo[35] == i &&
			hhtablo[a] - hhtablo[32] < 1 &&
			hhtablo[a] - hhtablo[33] < 1 &&
			hhtablo[a] - hhtablo[35] < 1) return true;
	}
	else if (a == 38 || a == 40) {
		if (tablo[38] == i && tablo[40] == i &&
			hhtablo[a] - hhtablo[38] < 1 &&
			hhtablo[a] - hhtablo[40] < 1) return true;
	}
	return false;
}

bool canSellHouse(int a) {
	if (hhtablo[a] == 0) return false;
	else if (tablo[a] == i){
		if (a == 2 || a == 4) {
			if (hhtablo[a] - hhtablo[2] > -1 &&
				hhtablo[a] - hhtablo[4] > -1) return true;
		}
		if (a == 7 || a == 9 || a == 10) {
			if (hhtablo[a] - hhtablo[7] > -1 &&
				hhtablo[a] - hhtablo[9] > -1 &&
				hhtablo[a] - hhtablo[10] > -1) return true;
		}
		if (a == 12 || a == 14 || a == 15) {
			if (hhtablo[a] - hhtablo[12] > -1 &&
				hhtablo[a] - hhtablo[14] > -1 &&
				hhtablo[a] - hhtablo[15] > -1) return true;
		}
		if (a == 17 || a == 19 || a == 20) {
			if (hhtablo[a] - hhtablo[17] > -1 &&
				hhtablo[a] - hhtablo[19] > -1 &&
				hhtablo[a] - hhtablo[20] > -1) return true;
		}
		if (a == 22 || a == 24 || a == 25) {
			if (hhtablo[a] - hhtablo[22] > -1 &&
				hhtablo[a] - hhtablo[24] > -1 &&
				hhtablo[a] - hhtablo[25] > -1) return true;
		}
		if (a == 27 || a == 28 || a == 30) {
			if (hhtablo[a] - hhtablo[27] > -1 &&
				hhtablo[a] - hhtablo[28] > -1 &&
				hhtablo[a] - hhtablo[30] > -1) return true;
		}
		if (a == 32 || a == 33 || a == 35) {
			if (hhtablo[a] - hhtablo[32] > -1 &&
				hhtablo[a] - hhtablo[33] > -1 &&
				hhtablo[a] - hhtablo[35] > -1) return true;
		}
		if (a == 38 || a == 40) {
			if (hhtablo[a] - hhtablo[38] > -1 &&
				hhtablo[a] - hhtablo[40] > -1) return true;
		}
	}
	return false;
}

internal void
calculate_scores(int axies[]) {
	for (i = 1; i <= nop; i++) {
		score[i] += lefta[i];
		for (int k = 1; k <= 40; k++) {
			if (tablo[k] == i) {
				score[i] += axies[k];
				for (int m = 1; m <= hhtablo[k]; m++) {
					score[i] += ((((k - 1) / 10) + 1) * 500000);
				}
			}
			else if (tablo[k] == 10 * i) /*mortgage*/{
				score[i] += (axies[k] / 2);
			}
		}
		score[i] /= 10000;
	}
}

internal void
menu(Input* input) {
	draw_rect(0, 0, 78, 50, 0xffffff);
	draw_logo(0, 20, .7);
	draw_text("MADE BY CAPTAIN KOUK", -30, -46, 0.5, 0x55A6C6);
	draw_text("HOW MANY PLAYERS?", -34, -10, .7, 0x888888);
	if (pressed(BUTTON_RIGHT)) {
		if (hotButton != 6) hotButton++;
		else hotButton = 2;
	}
	if (pressed(BUTTON_LEFT)) {
		if (hotButton != 2) hotButton--;
		else hotButton = 6;
	}
	if (pressed(BUTTON_ENTER)) {
		current_gamemode = GM_COLORS;
		nop = hotButton;
		for (int i = 1; i <= nop; i++) {
			lefta[i] = 15000000;
			isInJail[i] = false;
			doublesInJail[i] = 0;
			theseis[i] = 1;
		}
		hotButton = 0;
	}
	switch (hotButton) {
	case 2: {
		draw_number(2, -30, -30, 1, 0xff0000);
		draw_number(3, -15, -30, 1, 0x888888);
		draw_number(4, 0, -30, 1, 0x888888);
		draw_number(5, 15, -30, 1, 0x888888);
		draw_number(6, 29, -30, 1, 0x888888);
	} break;
	case 3: {
		draw_number(2, -30, -30, 1, 0x888888);
		draw_number(3, -15, -30, 1, 0xff0000);
		draw_number(4, 0, -30, 1, 0x888888);
		draw_number(5, 15, -30, 1, 0x888888);
		draw_number(6, 29, -30, 1, 0x888888);
	} break;
	case 4: {
		draw_number(2, -30, -30, 1, 0x888888);
		draw_number(3, -15, -30, 1, 0x888888);
		draw_number(4, 0, -30, 1, 0xff0000);
		draw_number(5, 15, -30, 1, 0x888888);
		draw_number(6, 29, -30, 1, 0x888888);
	} break;
	case 5: {
		draw_number(2, -30, -30, 1, 0x888888);
		draw_number(3, -15, -30, 1, 0x888888);
		draw_number(4, 0, -30, 1, 0x888888);
		draw_number(5, 15, -30, 1, 0xff0000);
		draw_number(6, 29, -30, 1, 0x888888);
	} break;
	case 6: {
		draw_number(2, -30, -30, 1, 0x888888);
		draw_number(3, -15, -30, 1, 0x888888);
		draw_number(4, 0, -30, 1, 0x888888);
		draw_number(5, 15, -30, 1, 0x888888);
		draw_number(6, 29, -30, 1, 0xff0000);
	} break;
	}
}

bool typing = true;
string written_text = "";
internal void
write_text(Input* input, float x, float y, float size, u32 color) {
	if (pressed(BUTTON_A)) written_text += "A";
	else if (pressed(BUTTON_B)) written_text += "B";
	else if (pressed(BUTTON_C)) written_text += "C";
	else if (pressed(BUTTON_D)) written_text += "D";
	else if (pressed(BUTTON_E)) written_text += "E";
	else if (pressed(BUTTON_F)) written_text += "F";
	else if (pressed(BUTTON_G)) written_text += "G";
	else if (pressed(BUTTON_H)) written_text += "H";
	else if (pressed(BUTTON_I)) written_text += "I";
	else if (pressed(BUTTON_J)) written_text += "J";
	else if (pressed(BUTTON_K)) written_text += "K";
	else if (pressed(BUTTON_L)) written_text += "L";
	else if (pressed(BUTTON_M)) written_text += "M";
	else if (pressed(BUTTON_N)) written_text += "N";
	else if (pressed(BUTTON_O)) written_text += "O";
	else if (pressed(BUTTON_P)) written_text += "P";
	else if (pressed(BUTTON_Q)) written_text += "Q";
	else if (pressed(BUTTON_R)) written_text += "R";
	else if (pressed(BUTTON_S)) written_text += "S";
	else if (pressed(BUTTON_T)) written_text += "T";
	else if (pressed(BUTTON_U)) written_text += "U";
	else if (pressed(BUTTON_V)) written_text += "V";
	else if (pressed(BUTTON_W)) written_text += "W";
	else if (pressed(BUTTON_X)) written_text += "X";
	else if (pressed(BUTTON_Y)) written_text += "Y";
	else if (pressed(BUTTON_Z)) written_text += "Z";
	else if (pressed(BUTTON_SPACE)) written_text += " ";
	else if (pressed(BUTTON_BACKSPACE) && written_text.length() > 0) written_text.pop_back();
	draw_text2(written_text, x, y, size, color);
}


internal void
colors_selection(Input* input) {
	if (i > nop) i = 1;
	if (hotButton < 1) hotButton = 1;
	draw_rect(0, 0, 78, 50, 0xffffff);
	draw_text(names[i], -15, 37, .7, 0x888888);
	draw_text("WHAT COLOR DO YOU PREFER?", -57, 30, .7, 0x888888);
	if (pressed(BUTTON_DOWN)) {
		hotButton++;
		if (hotButton > 12) hotButton = 1;
	}
	if (pressed(BUTTON_UP)) {
		hotButton--;
		if (hotButton <= 0) hotButton = 12;
	}
	if (pressed(BUTTON_ENTER)) {
		switch (hotButton) {
		case 1: {
			selected_color = 0xff0000;
		} break;
		case 2: {
			selected_color = 0x0031ff;
		} break;
		case 3: {
			selected_color = 0x127400;
		} break;
		case 4: {
			selected_color = 0x28ff00;
		} break;
		case 5: {
			selected_color = 0x000000;
		} break;
		case 6: {
			selected_color = 0xff4d00;
		} break;
		case 7: {
			selected_color = 0xffffff;
		} break;
		case 8: {
			selected_color = 0xfffb00;
		} break;
		case 9: {
			selected_color = 0x64260f;
		} break;
		case 10: {
			selected_color = 0x888888;
		} break;
		case 11: {
			selected_color = 0xf400ff;
		} break;
		case 12: {
			selected_color = 0x9800de;
		} break;
		}
		ok = true;
		for (int k = 1; k <= i - 1; k++) {
			if (colors[k] == selected_color) ok = false;
		}
		if (ok == true) {
			colors[i] = selected_color;
			i++;
			if (i > nop) {
				current_gamemode = GM_ROLL_THE_DICE;
				i = 1;
			}
			hotButton = 0;
		}
	}
	switch (hotButton) {
	case 1: {
		draw_text("RED", -8, 25, .55, 0xff0000);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 2: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -8, 20, .55, 0xff0000);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 3: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -8, 15, .55, 0xff0000);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 4: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -8, 10, .55, 0xff0000);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 5: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -8, 5, .55, 0xff0000);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 6: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -8, 0, .55, 0xff0000);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 7: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -8, -5, .55, 0xff0000);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 8: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -8, -10, .55, 0xff0000);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 9: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -8, -15, .55, 0xff0000);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 10: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -8, -20, .55, 0xff0000);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 11: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -8, -25, .55, 0xff0000);
		draw_text("PURPLE", -10, -30, .55, 0x888888);
	} break;
	case 12: {
		draw_text("RED", -10, 25, .55, 0x888888);
		draw_text("BLUE", -10, 20, .55, 0x888888);
		draw_text("GREEN", -10, 15, .55, 0x888888);
		draw_text("LIGHT GREEN", -10, 10, .55, 0x888888);
		draw_text("BLACK", -10, 5, .55, 0x888888);
		draw_text("ORANGE", -10, 0, .55, 0x888888);
		draw_text("WHITE", -10, -5, .55, 0x888888);
		draw_text("YELLOW", -10, -10, .55, 0x888888);
		draw_text("BROWN", -10, -15, .55, 0x888888);
		draw_text("GREY", -10, -20, .55, 0x888888);
		draw_text("PINK", -10, -25, .55, 0x888888);
		draw_text("PURPLE", -8, -30, .55, 0xff0000);
	} break;
	}
}

internal void
roll_the_dice(Input* input) {
	draw_text(names[i], 50, 20, .7, 0x000000);
	draw_text("ROLL THE", 50, 10, .7, 0x000000);
	draw_text("DICE", 57, 0, .7, 0x000000);
	draw_text("OK", 61.5, -12, .7, 0xff0000);
	if (pressed(BUTTON_ENTER)) {
		current_gamemode = GM_GAMEPLAY;
		mciSendString("open rolling_dice.mp3 type mpegvideo", NULL, 0, 0);
		mciSendString("play rolling_dice.mp3", NULL, 0, 0);
		Sleep(700);
		mciSendString("close rolling_dice.mp3", NULL, 0, NULL);
		hotButton = 0;
	}
}

internal void
buy_menu(Input* input, int axies[], int enoikia[], int enoikia1h[], int enoikia2h[], int enoikia3h[], int enoikia4h[], int enoikiahot[]) {
	draw_text(names[i], 47, -10, .4, 0x000000);
	draw_text("IS AVAILABLE", 47, -20, .4, 0x000000);
	draw_text(prop_names[theseis[i]], 47, -15, .4, 0x000000);
	draw_card(theseis[i], prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
	draw_dice(-88, 5, dice1);
	draw_dice(-82, 15, dice2);
	if (dice1 == dice2)	draw_text("DOUBLES!", -93, -2, .5, 0xfffb00);
	if (hotButton > 2 || hotButton < 0) hotButton = 0;
	if (pressed(BUTTON_UP)) {
		hotButton--;
		if (hotButton == -1) hotButton = 2;
	}
	if (pressed(BUTTON_DOWN)) {
		hotButton++;
		if (hotButton == 3) hotButton = 0;
	}

	if (pressed(BUTTON_ENTER)) {
		if (hotButton == 0) {
			if (axies[theseis[i]] > lefta[i]) {
				current_gamemode = GM_CANT_BUY;
			}
			else {
				lefta[i] -= axies[theseis[i]];
				tablo[theseis[i]] = i;
				current_gamemode = GM_SUCCESSFUL;
				mciSendString("open cash_register2.mp3 type mpegvideo", NULL, 0, 0);
				mciSendString("play cash_register2.mp3", NULL, 0, 0);
				Sleep(2000);
				mciSendString("close cash_register2.mp3", NULL, 0, NULL);
			}

		}
		else if (hotButton == 1) {
			current_gamemode = GM_AUCTION;
			last_bid = 0;
			current_price = 100000;
			a = i;
			current_bidder = 0;
			auction_live = true;
		}
		else {
			current_gamemode = GM_ANYTHING_ELSE;
		}
		hotButton = 0;
	}
	switch (hotButton) {
	case 0: {
		draw_text("BUY FOR", 47, -26, .4, 0xff0000);
		draw_number(axies[theseis[i]], 78, -28, .7, 0xff0000);
		draw_text("EUROS", 80, -26, .4, 0xff0000);
		draw_text("AUCTION", 47, -31, .4, 0x000000);
		draw_text("PASS", 47, -36, .4, 0x000000);
	} break;
	case 1: {
		draw_text("BUY FOR", 47, -26, .4, 0x000000);
		draw_number(axies[theseis[i]], 78, -28, .7, 0x000000);
		draw_text("EUROS", 80, -26, .4, 0x000000);
		draw_text("AUCTION", 47, -31, .4, 0xff0000);
		draw_text("PASS", 47, -36, .4, 0x000000);
	} break;
	case 2: {
		draw_text("BUY FOR", 47, -26, .4, 0x000000);
		draw_number(axies[theseis[i]], 78, -28, .7, 0x000000);
		draw_text("EUROS", 80, -26, .4, 0x000000);
		draw_text("AUCTION", 47, -31, .4, 0x000000);
		draw_text("PASS", 47, -36, .4, 0xff0000);
	} break;
	}

}

internal void
auctions_menu(Input* input, float dt, int axies[], int enoikia[], int enoikia1h[], int enoikia2h[], int enoikia3h[], int enoikia4h[], int enoikiahot[]) {
	if (box_half_side > 87) {
		draw_text("MADE BY CAPTAIN KOUK", -24, -46, .4, 0xffffff);
		if (auction_live) {
			if (hotButton > 1 || hotButton < 0) hotButton = 1;
			draw_rect(0, 0, 87, 50, 0x888888);
			draw_text("AUCTION MENU", -35, 35, 1, 0x000000);
			draw_text(names[a], -45, 20, .7, 0x000000);
			draw_text("PLACE A BID FOR", -45, 12, .7, 0x000000);
			draw_text(prop_names[theseis[i]], -45, 5, .7, 0x000000);
			draw_text("CURRENT BID", -45, -17, .7, 0x000000);
			draw_number(current_price, 25, -19, 1, 0x000000);
			draw_card(theseis[i], prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
			draw_text("EUROS", 30, -17, .7, 0x000000);

			if (pressed(BUTTON_UP)) {
				current_price += 100000;
			}
			if (pressed(BUTTON_DOWN)) {
				if (last_bid < current_price - 100000) {
					current_price -= 100000;
				}
			}
			if (pressed(BUTTON_LEFT)) hotButton = 0;
			if (pressed(BUTTON_RIGHT)) hotButton = 1;
			switch (hotButton) {
			case 0: {
				draw_text("OK", -35, -30, .7, 0xff0000);
				draw_text("CANCEL BID", -5, -30, .7, 0x000000);
			} break;
			case 1: {
				draw_text("OK", -35, -30, .7, 0x000000);
				draw_text("CANCEL BID", -5, -30, .7, 0xff0000);
			} break;
			}
			if (pressed(BUTTON_ENTER)) {
				if (hotButton == 0) {
					if (lefta[a] >= current_price && current_price > last_bid) {
						current_bidder = a;
						a++;
						if (a > nop) a = 1;
						last_bid = current_price;
					}
				}
				else {
					a++;
					if (a > nop) a = 1;
					current_price = last_bid;
					if (a == current_bidder || (a == i && last_bid == 0)) auction_live = false;
				}
			}
			draw_text(names[1], -70, 23, .3, 0x000000);
			draw_number(lefta[1], -54, 18, .8, 0x000000);
			draw_text(names[2], -70, 12, .3, 0x000000);
			draw_number(lefta[2], -54, 7, .8, 0x000000);
			if (lefta[3] > 0) {
				draw_text(names[3], -70, 1, .3, 0x000000);
				draw_number(lefta[3], -54, -4, .8, 0x000000);
				if (lefta[4] > 0) {
					draw_text(names[4], -70, -10, .3, 0x000000);
					draw_number(lefta[4], -54, -15, .8, 0x000000);
					if (lefta[5] > 0) {
						draw_text(names[5], -70, -21, .3, 0x000000);
						draw_number(lefta[5], -54, -26, .8, 0x000000);
						if (lefta[6] > 0) {
							draw_text(names[6], -70, -30, .3, 0x000000);
							draw_number(lefta[6], -54, -35, .8, 0x000000);
						}
					}
				}
			}
		}
		else {
			draw_rect(0, 0, 87, 50, 0x888888);
			draw_text("AUCTION COMPLETE", -50, 35, 1, 0x000000);
			if (last_bid != 0) {
				draw_text(names[i], -65, 20, .8, 0x000000);
				draw_text("HAS SUCCESSFULLY BOUGHT", -65, 10, .8, 0x000000);
				draw_text(prop_names[theseis[i]], -65, 0, .8, 0x000000);
				draw_text("FOR", -65, -10, .8, 0x000000);
				draw_number(current_price, -20, -12.5, 1, 0x000000);
				draw_text("EUROS", -16, -10, .8, 0x000000);
			}
			else {
				draw_text("NO BUYER WAS", -65, 17, .9, 0x000000);
				draw_text("FOUND FOR", -65, 7, .9, 0x000000);
				draw_text(prop_names[theseis[i]], -65, -3, .9, 0x000000);
			}
			draw_card(theseis[i], prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
			draw_text("OK", -10, -30, .8, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				tablo[theseis[i]] = current_bidder;
				lefta[current_bidder] -= last_bid;
				if (last_bid != 0) {
					mciSendString("open cash_register2.mp3 type mpegvideo", NULL, 0, 0);
					mciSendString("play cash_register2.mp3", NULL, 0, 0);
					Sleep(2000);
					mciSendString("close cash_register2.mp3", NULL, 0, NULL);
				}
				box_half_side = 0;
			}
		}

	}
	else {
		box_half_side += box_half_side_speed * dt;
		draw_rect(0, 0, box_half_side, 5 * box_half_side / 8, 0x888888);
	}
}

internal void
cant_buy_menu(Input* input) {
	draw_rect(0, 10, 38, 20, 0xffffff);
	draw_text("YOU CANT BUY IT!", -22, 20, .5, 0x888888);
	draw_text("OK", -3, 0, .5, 0xff0000);
	draw_dice(-88, 5, dice1);
	draw_dice(-82, 15, dice2);
	if (pressed(BUTTON_ENTER)) {
		current_gamemode = GM_ANYTHING_ELSE;
	}
}

internal void
successful(Input* input) {
	draw_text("TRANSACTION", 52, 0, .5, 0x000000);
	draw_text("COMPLETE", 56, -5, .5, 0x000000);
	draw_text("OK", 65, -15, .7, 0xff0000);
	draw_dice(-88, 5, dice1);
	draw_dice(-82, 15, dice2);
	if (pressed(BUTTON_ENTER)) {
		current_gamemode = GM_ANYTHING_ELSE;
	}
}

internal void
anything_else(Input* input) {
	draw_text(names[i], 47, 23, .55, 0x000000);
	draw_text("ANYTHING ELSE?", 47, 18, .55, 0x000000);
	draw_dice(-88, 5, dice1);
	draw_dice(-82, 15, dice2);
	if (hotButton == 0 || hotButton > 8) hotButton = 1;
	if (pressed(BUTTON_DOWN)) {
		if (hotButton == 8) hotButton = 1;
		else hotButton++;
	}
	if (pressed(BUTTON_UP)) {
		if (hotButton == 1) hotButton = 8;
		else hotButton--;
	}
	switch (hotButton) {
	case 1: {
		draw_text("CONTINUE", 47, 10, .55, 0xff0000);
		draw_text("MORTGAGE", 47, 5, .55, 0x000000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0x000000);
		draw_text("SELL", 47, -5, .55, 0x000000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0x000000);
		draw_text("OR HOTEL", 47, -15, .55, 0x000000);
		draw_text("SELL HOUSE", 47, -20, .55, 0x000000);
		draw_text("OR HOTEL", 47, -25, .55, 0x000000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0x000000);
		draw_text("SURRENDER", 47, -35, .55, 0x000000);
	} break;
	case 2: {
		draw_text("CONTINUE", 47, 10, .55, 0x000000);
		draw_text("MORTGAGE", 47, 5, .55, 0xff0000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0x000000);
		draw_text("SELL", 47, -5, .55, 0x000000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0x000000);
		draw_text("OR HOTEL", 47, -15, .55, 0x000000);
		draw_text("SELL HOUSE", 47, -20, .55, 0x000000);
		draw_text("OR HOTEL", 47, -25, .55, 0x000000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0x000000);
		draw_text("SURRENDER", 47, -35, .55, 0x000000);
	} break;
	case 3: {
		draw_text("CONTINUE", 47, 10, .55, 0x000000);
		draw_text("MORTGAGE", 47, 5, .55, 0x000000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0xff0000);
		draw_text("SELL", 47, -5, .55, 0x000000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0x000000);
		draw_text("OR HOTEL", 47, -15, .55, 0x000000);
		draw_text("SELL HOUSE", 47, -20, .55, 0x000000);
		draw_text("OR HOTEL", 47, -25, .55, 0x000000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0x000000);
		draw_text("SURRENDER", 47, -35, .55, 0x000000);
	} break;
	case 4: {
		draw_text("CONTINUE", 47, 10, .55, 0x000000);
		draw_text("MORTGAGE", 47, 5, .55, 0x000000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0x000000);
		draw_text("SELL", 47, -5, .55, 0xff0000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0x000000);
		draw_text("OR HOTEL", 47, -15, .55, 0x000000);
		draw_text("SELL HOUSE", 47, -20, .55, 0x000000);
		draw_text("OR HOTEL", 47, -25, .55, 0x000000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0x000000);
		draw_text("SURRENDER", 47, -35, .55, 0x000000);
	} break;
	case 5: {
		draw_text("CONTINUE", 47, 10, .55, 0x000000);
		draw_text("MORTGAGE", 47, 5, .55, 0x000000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0x000000);
		draw_text("SELL", 47, -5, .55, 0x000000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0xff0000);
		draw_text("OR HOTEL", 47, -15, .55, 0xff0000);
		draw_text("SELL HOUSE", 47, -20, .55, 0x000000);
		draw_text("OR HOTEL", 47, -25, .55, 0x000000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0x000000);
		draw_text("SURRENDER", 47, -35, .55, 0x000000);
	} break;
	case 6: {
		draw_text("CONTINUE", 47, 10, .55, 0x000000);
		draw_text("MORTGAGE", 47, 5, .55, 0x000000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0x000000);
		draw_text("SELL", 47, -5, .55, 0x000000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0x000000);
		draw_text("OR HOTEL", 47, -15, .55, 0x000000);
		draw_text("SELL HOUSE", 47, -20, .55, 0xff0000);
		draw_text("OR HOTEL", 47, -25, .55, 0xff0000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0x000000);
		draw_text("SURRENDER", 47, -35, .55, 0x000000);
	} break;
	case 7: {
		draw_text("CONTINUE", 47, 10, .55, 0x000000);
		draw_text("MORTGAGE", 47, 5, .55, 0x000000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0x000000);
		draw_text("SELL", 47, -5, .55, 0x000000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0x000000);
		draw_text("OR HOTEL", 47, -15, .55, 0x000000);
		draw_text("SELL HOUSE", 47, -20, .55, 0x000000);
		draw_text("OR HOTEL", 47, -25, .55, 0x000000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0xff0000);
		draw_text("SURRENDER", 47, -35, .55, 0x000000);
	} break;
	case 8: {
		draw_text("CONTINUE", 47, 10, .55, 0x000000);
		draw_text("MORTGAGE", 47, 5, .55, 0x000000);
		draw_text("ANTI MORTGAGE", 47, 0, .55, 0x000000);
		draw_text("SELL", 47, -5, .55, 0x000000);
		draw_text("BUILD HOUSE", 47, -10, .55, 0x000000);
		draw_text("OR HOTEL", 47, -15, .55, 0x000000);
		draw_text("SELL HOUSE", 47, -20, .55, 0x000000);
		draw_text("OR HOTEL", 47, -25, .55, 0x000000);
		draw_text("MY PROPERTIES", 47, -30, .55, 0x000000);
		draw_text("SURRENDER", 47, -35, .55, 0xff0000);
	} break;
	}
	if (pressed(BUTTON_ENTER)) {
		switch (hotButton) {
		case 1: {
			if (lefta[i] >= 0) {
				current_gamemode = GM_ROLL_THE_DICE;
				if ((dice1 != dice2 && !isInJail[i]) ||
					(dice1 == dice2 && isInJail[i]) ||
					(dice1 != dice2 && isInJail[i])) {
					i++;
					if (i > nop) i = 1;
				}
			}
		} break;
		case 2: {
			current_gamemode = GM_WHAT_PROP_SM;
		} break;
		case 3: {
			current_gamemode = GM_WHAT_PROP_AM;
		} break;
		case 4: {
			current_gamemode = GM_WHAT_PROP_SM;
		} break;
		case 5: {
			current_gamemode = GM_WHAT_PROP_H;
		} break;
		case 6: {
			current_gamemode = GM_WHAT_PROP_SELLH;
		} break;
		case 7: {
			current_gamemode = GM_MY_PROPS;
		} break;
		case 8: {
			current_gamemode = GM_END_OF_GAME;
			mciSendString("open we_are_the_champions_trimmed.mp3 type mpegvideo", NULL, 0, 0);
			mciSendString("play we_are_the_champions_trimmed.mp3", NULL, 0, NULL);
		}
		}
	}
}

internal void
yours(Input* input) {
	draw_text("THIS PROPERTY", 50, 0, .5, 0x000000);
	draw_text("IS YOURS", 56, -5, .5, 0x000000);
	draw_text("OK", 63.5, -15, .5, 0xff0000);
	draw_dice(-88, 5, dice1);
	draw_dice(-82, 15, dice2);
	if (dice1 == dice2)	draw_text("DOUBLES!", -93, -2, .5, 0xfffb00);
	if (pressed(BUTTON_ENTER)) {
		current_gamemode = GM_ANYTHING_ELSE;
	}
}

internal void
you_have_to_pay(Input* input, int axies[], int enoikia[], int enoikia1h[], int enoikia2h[], int enoikia3h[], int enoikia4h[], int enoikiahot[]) {
	draw_dice(-88, 5, dice1);
	draw_dice(-82, 15, dice2);
	if (dice1 == dice2)	draw_text("DOUBLES!", -93, -2, .5, 0xfffb00);
	draw_text(names[i], 47, -8, .5, 0x000000);
	draw_text("YOU HAVE TO PAY", 47, -16, .5, 0x000000);
	draw_text("EUROS TO", 70, -24, .5, 0x000000);
	draw_text(names[tablo[theseis[i]]], 47, -32, .5, 0x000000);
	draw_card(theseis[i], prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
	if (theseis[i] == 13 || theseis[i] == 29) {
		if (tablo[13] == tablo[29]) fee = (dice1 + dice2) * 10 * 10000;
		else fee = (dice1 + dice2) * 4 * 10000;
	}
	else if (theseis[i] % 10 == 6) {
		fee = 250000;
		for (int k = 6; k < 40; k += 10) {
			if (tablo[k] == tablo[theseis[i]]) {
				airportCounter++;
				fee *= 2;
			}
		}
		fee /= 2;
	}
	else {
		if (hhtablo[theseis[i]] == 0) {
			if (canBuildHouse(theseis[i])) fee = 2 * enoikia[theseis[i]];
			else fee = enoikia[theseis[i]];
		}
		else if (hhtablo[theseis[i]] == 1) fee = enoikia1h[theseis[i]];
		else if (hhtablo[theseis[i]] == 2) fee = enoikia2h[theseis[i]];
		else if (hhtablo[theseis[i]] == 3) fee = enoikia3h[theseis[i]];
		else if (hhtablo[theseis[i]] == 4) fee = enoikia4h[theseis[i]];
		else if (hhtablo[theseis[i]] == 5) fee = enoikiahot[theseis[i]];
	}
	draw_number(fee, 68, -25, 1, 0x000000);
	draw_text("OK", 65, -42, .55, 0xff0000);
	if (pressed(BUTTON_ENTER)) {
		current_gamemode = GM_ANYTHING_ELSE;
		lefta[i] -= fee;
		lefta[tablo[theseis[i]]] += fee;
		mciSendString("open cash_register2.mp3 type mpegvideo", NULL, 0, 0);
		mciSendString("play cash_register2.mp3", NULL, 0, 0);
		Sleep(2000);
		mciSendString("close cash_register2.mp3", NULL, 0, NULL);
	}
}

internal void
tax(Input* input) {
	draw_rect(0, 0, 40, 20, 0xffffff);
	draw_text("TAX", -7.7, 17, .9, 0x000000);
	draw_text("YOU HAVE TO PAY", -32, 7, .7, 0x888888);
	draw_text("EUROS", 0, -1, .7, 0x888888);
	draw_dice(-88, 5, dice1);
	draw_dice(-82, 15, dice2);
	if (dice1 == dice2)	draw_text("DOUBLES!", -93, -2, .5, 0xfffb00);
	if (theseis[i] == 5) fee = 2000000;
	else fee = 1000000;
	draw_number(fee, -7, -3, 1, 0x888888);
	draw_text("OK", -4, -12, .7, 0xff0000);
	if (pressed(BUTTON_ENTER)) {
		current_gamemode = GM_ANYTHING_ELSE;
		lefta[i] -= fee;
	}
}

internal void
end_of_game(Input* input, float dt, int axies[]) {
		
	draw_rect(0, 0, 60, 50, 0x888888);
	draw_text("SCORES", -14, 40, .8, 0x000000);
	calculate_scores(axies);
	for (i = 1; i <= nop; i++) {
		draw_text(names[i], -40, i * (-7) + 30, .8, 0x000000);
		draw_number(score[i], 40, i * (-7) + 28, 1, 0x000000);
		if (score[i] > maxpoints) {
			maxpoints = score[i];
			winner = i;
		}
		else if (score[i] == maxpoints) {
			if (lefta[i] > lefta[winner]) winner = i;
		}
	}
	draw_text("AND THE WINNER IS", -40, -25, .8, 0x000000);
	if (colors[winner] == 0x888888) draw_text(names[winner], -30, -32, 1, 0x545454);
	else draw_text(names[winner], -30, -32, 1, colors[winner]);
	draw_text("MADE BY CAPTAIN KOUK", -24, -46, .4, 0xffffff);

	if (balloon3y < 130) {
		balloon1y += balloondp * dt;
		if (balloon1y > -33) {
			balloon2y += balloondp * dt;
			if (balloon2y > -37) {
				balloon3y += balloondp * dt;
			}
		}
	}

	draw_balloon(0, balloon1y, 1, colors[winner]);
	draw_balloon(30, balloon2y, .7, colors[winner]);
	draw_balloon(-30, balloon3y, .85, colors[winner]);
}

internal void
simulate_game(Input* input, int axies[], int enoikia[], int enoikia1h[], int enoikia2h[], int enoikia3h[], int enoikia4h[], int enoikiahot[], float dt) {
	srand((int)time(0));
	clear_screen(0x2e42df);
	draw_table(lefta, names, prop_names);
	for (int k = 1; k <= nop; k++) {
		if (theseis[i] != 0) {
			if ((current_gamemode == GM_GRAPHICS_POLICE && (!arrested || k != i)) || current_gamemode != GM_GRAPHICS_POLICE) {
				draw_player(k, &theseis[j], isInJail, hhtablo, colors[k]);
			}
		}
	}
	draw_props(i, tablo, colors);
	if (chancesCounter == -1) chancesCounter = rand() % 16 + 0;
	if (commChestCounter == -1) commChestCounter = rand() % 14 + 0;

	if (i == 0) i = 1;
	if (current_gamemode == GM_MENU) {
		menu(input);
	}

/*	else if (current_gamemode == GM_PLAYER_NAMES) {
		if (typing) {
			draw_rect(0, 0, 78, 50, 0xffffff);
			draw_text2("ENTER THE NAME OF THE PLAYER NO", -65, 10, .6, 0x888888);
			draw_number(1, 50, 10, 1, 0x888888);
			write_text(input, -5, -5, .8, 0x888888);
			if (pressed(BUTTON_ENTER)) {
				typing = false;
				current_gamemode = GM_MENU;
			}
		}
	}
*/
	else if (current_gamemode == GM_COLORS) {
		colors_selection(input);
	}

	else if (current_gamemode == GM_ROLL_THE_DICE) {
		roll_the_dice(input);
	}

	else if (current_gamemode == GM_GAMEPLAY) {
		if (!dontThrowDice) {
			dice1 = rand() % 6 + 1;
			dice2 = rand() % 6 + 1;
		}
		if (isInJail[i]) {
			if (dice1 == dice2) {
				isInJail[i] = false;
				doublesInJail[i] = 0;
			}
			else {
				doublesInJail[i]++;
				if (doublesInJail[i] >= 3) {
					current_gamemode = GM_OUT_OF_JAIL;
				}
				else current_gamemode = GM_ANYTHING_ELSE;
			}
		}
		if (!isInJail[i]) {
			if (dice1 == dice2 && !dontThrowDice) doubles++;
			else if (!dontThrowDice) doubles = 0;
			if (doubles >= 3) {
				current_gamemode = GM_JAIL;
			}
			else {
				if (!dontThrowDice) {
					theseis[i] += dice1 + dice2;
					if (theseis[i] > 40) {
						theseis[i] -= 40;
						lefta[i] += 2000000;
					}
				}
				else dontThrowDice = false;
				if (tablo[theseis[i]] == 0) {
					if (axies[theseis[i]] != 0) {
						current_gamemode = GM_BUY_MENU;
					}
					else {
						if (theseis[i] == 5 || theseis[i] == 39) {
							current_gamemode = GM_TAX;
						}
						else if (theseis[i] == 8 || theseis[i] == 23 || theseis[i] == 37) {
							current_gamemode = GM_CHANCE;
						}
						else if (theseis[i] == 3 || theseis[i] == 18 || theseis[i] == 34) {
							current_gamemode = GM_COMMUNITY_CHEST;
						}
						else if (theseis[i] == 31) {
							current_gamemode = GM_JAIL;
						}
						else current_gamemode = GM_ANYTHING_ELSE;
					}
				}

				else if (tablo[theseis[i]] == i) {
					current_gamemode = GM_YOURS;
				}
				else {
					current_gamemode = GM_YOU_HAVE_TO_PAY;
				}
			}
		}
	}

	else if (current_gamemode == GM_BUY_MENU) {
		buy_menu(input, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
	}

	else if (current_gamemode == GM_AUCTION) {
		auctions_menu(input, dt, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
	}

	else if (current_gamemode == GM_CANT_BUY) {
		cant_buy_menu(input);
	}

	else if (current_gamemode == GM_SUCCESSFUL) {
		successful(input);
	}

	else if (current_gamemode == GM_ANYTHING_ELSE) {
		anything_else(input);
	}

	else if (current_gamemode == GM_YOURS) {
		yours(input);
	}

	else if (current_gamemode == GM_YOU_HAVE_TO_PAY) {
		you_have_to_pay(input, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
	}

	else if (current_gamemode == GM_TAX) {
		tax(input);
	}

	else if (current_gamemode == GM_CHANCE) {
		draw_rect(0, 0, 50, 30, 0xffffff);
		draw_text("CHANCE", -15, 25, 1, 0xff0000);
		draw_dice(-88, 5, dice1);
		draw_dice(-82, 15, dice2);
		if (dice1 == dice2)	draw_text("DOUBLES!", -93, -2, .5, 0xfffb00);

		// go to jail
		if (chancesCounter == 0) {
			draw_text("GO TO JAIL", 0, 15, .7, 0x888888);
			draw_text("DO NOT PASS GO", -10, 8, .7, 0x888888);
			draw_text("DO NOT COLLECT", -10, 1, .7, 0x888888);
			draw_text("EUROS", 17, -6, .7, 0x888888);
			draw_number(2000000, 12, -8, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			draw_rect(-28, 8, 8, .5, 0x000000);
			draw_rect(-28, -8, 8, .5, 0x000000);
			draw_rect(-28, 0, .5, 9, 0x000000);
			draw_rect(-25, 0, .5, 9, 0x000000);
			draw_rect(-31, 0, .5, 9, 0x000000);
			draw_rect(-22, 0, .5, 9, 0x000000);
			draw_rect(-34, 0, .5, 9, 0x000000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_GRAPHICS_POLICE;
				chancesCounter++;
			}
		}

		// 3 spaces back
		else if (chancesCounter == 1) {
			draw_text("GO BACK THREE SPACES", -40, 4, .7, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				theseis[i] -= 3;
				current_gamemode = GM_GAMEPLAY;
				dontThrowDice = true;
				chancesCounter++;
			}
		}

		// crossword competition
		else if (chancesCounter == 2) {
			draw_text("YOU HAVE WON A", -30, 10, .7, 0x888888);
			draw_text("CROSSWORD COMPETITION", -42, 0, .7, 0x888888);
			draw_text("COLLECT     EUROS", -34, -10, .7, 0x888888);
			draw_number(100000, 11, -12, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				lefta[i] += 100000;
				current_gamemode = GM_ANYTHING_ELSE;
				chancesCounter++;
			}
		}

		// drunk
		else if (chancesCounter == 3) {
			draw_text("YOU WERE FOUND", -28, 15, .7, 0x888888);
			draw_text("DRUNK WHILE DRIVING", -38, 7, .7, 0x888888);
			draw_text("FINE      EUROS", -28, -3, .7, 0x888888);
			draw_number(200000, 5, -5, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				lefta[i] -= 200000;
				current_gamemode = GM_ANYTHING_ELSE;
				chancesCounter++;
			}
		}

		// school fees
		else if (chancesCounter == 4) {
			draw_text("PAY SCHOOL FEES", -28, 5, .7, 0x888888);
			draw_text("OF     EUROS", -23, -5, .7, 0x888888);
			draw_number(150000, 2, -7, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				lefta[i] -= 150000;
				current_gamemode = GM_ANYTHING_ELSE;
				chancesCounter++;
			}
		}

		// speeding fine
		else if (chancesCounter == 5) {
			draw_text("SPEEDING FINE", -24, 5, .7, 0x888888);
			draw_text("OF    EUROS", -20, -5, .7, 0x888888);
			draw_number(15000, 1, -7, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				lefta[i] -= 15000;
				current_gamemode = GM_ANYTHING_ELSE;
				chancesCounter++;
			}
		}

		// advance to go
		else if (chancesCounter == 6) {
			draw_text("ADVANCE TO GO", -25, 0, .7, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				theseis[i] = 1;
				lefta[i] += 2000000;
				current_gamemode = GM_ANYTHING_ELSE;
				chancesCounter++;
			}
		}

		// out of jail
		else if (chancesCounter == 7 && outOfJailCard == 0) {
			draw_text("GET OUT OF JAIL", -30, 12, .7, 0x888888);
			draw_text("THIS CARD WILL BE", -34, 2, .7, 0x888888);
			draw_text("KEPT UNTIL NEEDED", -34, -8, .7, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				chancesCounter++;
				outOfJailCard = i;
			}
		}

		// go to Kouk islands
		else if (chancesCounter == 8) {
			draw_text("GO TO", -9.5, 12, .7, 0x888888);
			draw_text("KOUK ISLANDS", -22, 2, .7, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_GAMEPLAY;
				theseis[i] = 40;
				chancesCounter++;
				dontThrowDice = true;
			}
		}

		// won the lottery
		else if (chancesCounter == 9) {
			draw_text("YOU WON THE", -21, 12, .7, 0x888888);
			draw_text("LOTTERY JACKPOT!", -30, 3, .7, 0x888888);
			draw_text("GET     EUROS", -23, -8, .7, 0x888888);
			draw_number(1000000, 7, -10, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 1000000;
				chancesCounter++;
			}

		}

		// pool in Cuba
		else if (chancesCounter == 10) {
			draw_text("YOU BUILT A POOL", -30, 12, .7, 0x888888);
			draw_text("IN CUBA", -12, 3, .7, 0x888888);
			draw_text("PAY     EUROS", -25, -8, .7, 0x888888);
			draw_number(200000, 5, -10, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] -= 200000;
				chancesCounter++;
			}
			
		}

		// catch a plane in Cuba
		else if (chancesCounter == 11) {
			draw_text("YOU HAVE TO CATCH UP THE", -42, 12, .6, 0x888888);
			draw_text("PLANE AT LUIS MARTI AIRPORT", -47, 6, .6, 0x888888);
			draw_text("IF YOU PASS GO", -23, -4, .6, 0x888888);
			draw_text("GET      EUROS", -23, -10, .6, 0x888888);
			draw_number(2000000, 7, -12, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_GAMEPLAY;
				if (theseis[i] > 16) lefta[i] += 2000000;
				theseis[i] = 16;
				chancesCounter++;
				dontThrowDice = true;
			}

		}

		// sell stocks
		else if (chancesCounter == 12) {
			draw_text("YOU SELL SOME STOCKS", -42, 8, .7, 0x888888);
			draw_text("GET      EUROS", -25, -8, .7, 0x888888);
			draw_number(1500000, 8, -10, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 1500000;
				chancesCounter++;
			}
			
		}

		// season ticket
		else if (chancesCounter == 13) {
			draw_text("YOU BOOKED A VIP SEASON", -41, 12, .6, 0x888888);
			draw_text("TICKET FOR CAPTAIN KOUK FC", -46, 6, .6, 0x888888);
			draw_text("PAY      EUROS", -23, -8, .6, 0x888888);
			draw_number(200000, 6, -10, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] -= 200000;
				chancesCounter++;
			}

		}

		// crazy party in Bahamas
		else if (chancesCounter == 14) {
			draw_text("GO FOR A CRAZY", -23, 12, .6, 0x888888);
			draw_text("WEEKEND IN BAHAMAS", -30, 6, .6, 0x888888);
			draw_text("IF YOU PASS GO", -23, -4, .6, 0x888888);
			draw_text("GET      EUROS", -23, -10, .6, 0x888888);
			draw_number(2000000, 7, -12, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_GAMEPLAY;
				if (theseis[i] > 35) lefta[i] += 2000000;
				theseis[i] = 35;
				chancesCounter++;
				dontThrowDice = true;
			}
		}

		// cruise to Corsica
		else if (chancesCounter == 15) {
			draw_text("LETS GO ON A CRUISE", -35, 12, .7, 0x888888);
			draw_text("TO CORSICA!", -20, 6, .7, 0x888888);
			draw_text("IF YOU PASS GO", -23, -4, .6, 0x888888);
			draw_text("GET      EUROS", -23, -10, .6, 0x888888);
			draw_number(2000000, 7, -12, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_GAMEPLAY;
				if (theseis[i] > 14) lefta[i] += 2000000;
				theseis[i] = 14;
				chancesCounter++;
				dontThrowDice = true;
			}
		}

		// house decorator
		else if (chancesCounter == 16) {
			draw_text("YOU HIRE A DECORATOR", -41, 10, .7, 0x888888);
			draw_text("PAY       EUROS FOR EVERY HOUSE", -45, 2, .5, 0x888888);
			draw_text("AND       EUROS FOR EVERY HOTEL", -45, -6, .5, 0x888888);
			draw_number(250000, -18, 1, 1, 0x888888);
			draw_number(1000000, -18, -7, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				for (int k = 1; k <= 40; k++) {
					if (tablo[k] == i) {
						if (hhtablo[k] == 5) lefta[i] -= 1000000;
						else 
							for (int m = 1; m <= hhtablo[k]; m++) 
								lefta[i] -= 250000;
					}
				}
				chancesCounter++;
			}
		}

		if (pressed(BUTTON_LEFT)) {
			current_gamemode = GM_ANYTHING_ELSE;
			chancesCounter++;
		}

		hotButton = 1;
		if (chancesCounter > 16) chancesCounter = 0;
		
	}

	else if (current_gamemode == GM_COMMUNITY_CHEST) {
		draw_rect(0, 0, 50, 30, 0xffffff);
		draw_text("COMMUNITY CHEST", -34.5, 25, .8, 0xff0000);
		draw_dice(-88, 5, dice1);
		draw_dice(-82, 15, dice2);
		if (dice1 == dice2)	draw_text("DOUBLES!", -93, -2, .5, 0xfffb00);

		// internet company
		if (commChestCounter == 0) {
			draw_text("YOUR INTERNET COMPANY", -42, 15, .7, 0x888888);
			draw_text("HAS SHOWN DEVELOPMENT", -42, 8, .7, 0x888888);
			draw_text("GET      EUROS", -28, -6, .7, 0x888888);
			draw_number(2000000, 5, -8, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 2000000;
				commChestCounter++;
			}
		}

		// plot in Ireland
		else if (commChestCounter == 1) {
			draw_text("YOU BUY A PLOT IN", -32, 15, .6, 0x888888);
			draw_text("IRELAND AND SELL IT", -34, 8, .6, 0x888888);
			draw_text("WITH GREAT PROFIT", -32, 1, .6, 0x888888);
			draw_text("GET     EUROS", -27, -6, .7, 0x888888);
			draw_number(200000, 3, -8, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 200000;
				commChestCounter++;
			}
		}

		// go back to Indonesia
		else if (commChestCounter == 2) {
			draw_text("GO BACK TO ", -20, 10, .7, 0x888888);
			draw_text("INDONESIA", -17, 3, .7, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_GAMEPLAY;
				theseis[i] = 2;
				commChestCounter++;
				dontThrowDice = true;
			}
		}

		// 5day tour to Iceland
		else if (commChestCounter == 3) {
			draw_text("YOU GO A FIVE DAY TOUR", -39, 15, .6, 0x888888);
			draw_text("TO ICELAND", -15.5, 8, .6, 0x888888);
			draw_text("PAY     EUROS", -25, -6, .7, 0x888888);
			draw_number(500000, 5, -8, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] -= 500000;
				commChestCounter++;
			}
		}

		// super party in Malta
		else if (commChestCounter == 4) {
			draw_text("PAY      EUROS", -29, 15, .7, 0x888888);
			draw_number(1000000, 3, 13, 1, 0x888888);
			draw_text("TO RENT A DISCO IN", -30, 8, .6, 0x888888);
			draw_text("MALTA FOR A SUPER PARTY", -39, 1, .6, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] -= 1000000;
				commChestCounter++;
			}
		}
		
		// rent from private yacht
		else if (commChestCounter == 5) {
			draw_text("YOU GET     EUROS", -35, 15, .7, 0x888888);
			draw_number(1000000, 11.5, 13, 1, 0x888888);
			draw_text("FROM RENTING YOUR", -30, 4, .6, 0x888888);
			draw_text("PRIVATE YACHT", -22, -5, .6, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 1000000;
				commChestCounter++;
			}

		}

		// tax return
		else if (commChestCounter == 6) {
			draw_text("YOU HAVE TAX RETURN", -39, 10, .7, 0x888888);
			draw_text("RECEIVE     EUROS", -35, -3, .7, 0x888888);
			draw_number(200000, 11, -5, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 200000;
				commChestCounter++;
			}
		}

		//masterchef
		else if (commChestCounter == 7) {
			draw_text("YOU WON THE MASTERCHEF!", -40, 10, .6, 0x888888);
			draw_text("RECEIVE     EUROS", -35, -3, .7, 0x888888);
			draw_number(500000, 11.5, -5, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 500000;
				commChestCounter++;
			}
		}

		// 100K or chance
		else if (commChestCounter == 8) {
			draw_text("OR", -2, 2, .7, 0x888888);
			if (hotButton > 1) hotButton = 0;
			if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT)) hotButton = !hotButton;
			switch (hotButton) {
			case 0: {
				draw_text("PAY", -33, 6, .7, 0xff0000);
				draw_text("EUROS", -25, -5, .7, 0xff0000);
				draw_number(100000, -28.5, -7, 1, 0xff0000);
				draw_text("TAKE A ", 15, 6, .6, 0x888888);
				draw_text("CHANCE CARD", 8, -5, .6, 0x888888);
			} break;
			case 1: {
				draw_text("PAY", -33, 6, .7, 0x888888);
				draw_text("EUROS", -25, -5, .7, 0x888888);
				draw_number(100000, -28.5, -7, 1, 0x888888);
				draw_text("TAKE A ", 15, 6, .6, 0xff0000);
				draw_text("CHANCE CARD", 8, -5, .6, 0xff0000);
			} break;
			}
			if (pressed(BUTTON_ENTER)) {
				switch (hotButton) {
				case 0: {
					lefta[i] -= 100000;
					current_gamemode = GM_ANYTHING_ELSE;
				} break;
				case 1: {
					current_gamemode = GM_CHANCE;
				} break;
				}
				commChestCounter++;
			}

		}

		// car compensation
		else if (commChestCounter == 9) {
			draw_text("YOU GET COMPENSATION FROM THE", -47, 10, .55, 0x888888);
			draw_text("ALLIANCE COMPANY FOR YOUR CAR", -47, 0, .55, 0x888888);
			draw_text("RECEIVE     EUROS", -35, -10, .7, 0x888888);
			draw_number(250000, 11.5, -12, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 250000;
				commChestCounter++;
			}
		}

		// inheritance
		else if (commChestCounter == 10) {
			draw_text("YOU INHERIT", -23, 10, .8, 0x888888);
			draw_text("EUROS", 4, -5, .8, 0x888888);
			draw_number(1000000, -6, -7, 1, 0x888888);
			draw_text("OK", -2, -20, .8, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 1000000;
				commChestCounter++;
			}			
		}

		// 100K from all the players
		else if (commChestCounter == 11) {
			draw_text("YOUR FRIENDS RENT YOUR", -35, 13, .55, 0x888888);
			draw_text("VILLA IN CRETE FOR A WEEK", -42, 5, .55, 0x888888);
			draw_text("RECEIVE     EUROS", -35, -3, .7, 0x888888);
			draw_number(100000, 11.5, -5, 1, 0x888888);
			draw_text("FROM EVERY PLAYER", -27, -13, .55, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				for (int k = 1; k <= nop; k++) {
					if (k != i) {
						lefta[k] -= 100000;
						lefta[i] += 100000;
					}
				}
				commChestCounter++;
			}
		}

		// spa
		else if (commChestCounter == 12) {
			draw_text("YOU PAY     EUROS", -34.5, 10, .7, 0x888888);
			draw_text("FOR A FIVE STAR SPA", -39, -5, .7, 0x888888);
			draw_number(500000, 12, 8, 1, 0x888888);
			draw_text("OK", -2, -20, .8, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] -= 500000;
				commChestCounter++;
			}						
		}

		// beauty contest
		else if (commChestCounter == 13) {
			draw_text("YOU WON FIRST PRIZE", -31, 10, .55, 0x888888);
			draw_text("IN A BEAUTY CONTEST", -31, 0, .55, 0x888888);
			draw_text("RECEIVE     EUROS", -35, -10, .7, 0x888888);
			draw_number(150000, 11.5, -12, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				lefta[i] += 150000;
				commChestCounter++;
			}			
		}

		// taxes for houses and hotels
		else if (commChestCounter == 14) {
			draw_text("NEW TAXES AFFECT YOUR PROPERTIES", -46.5, 10, .5, 0x888888);
			draw_text("PAY       EUROS FOR EVERY HOUSE", -45, 2, .5, 0x888888);
			draw_text("AND       EUROS FOR EVERY HOTEL", -45, -6, .5, 0x888888);
			draw_number(400000, -18, 1, 1, 0x888888);
			draw_number(1150000, -18, -7, 1, 0x888888);
			draw_text("OK", -2, -20, .7, 0xff0000);
			if (pressed(BUTTON_ENTER)) {
				current_gamemode = GM_ANYTHING_ELSE;
				for (int k = 1; k <= 40; k++) {
					if (tablo[k] == i) {
						if (hhtablo[k] == 5) lefta[i] -= 1150000;
						else 
							for (int m = 1; m <= hhtablo[k]; m++) 
								lefta[i] -= 400000;
					}
				}
				chancesCounter++;
			}

		}

		if (pressed(BUTTON_LEFT)) {
			current_gamemode = GM_ANYTHING_ELSE;
			commChestCounter++;
		}

		if (chancesCounter > 14) chancesCounter = 0;
	}

	else if (current_gamemode == GM_JAIL) {
		draw_dice(-88, 5, dice1);
		draw_dice(-82, 15, dice2);
		if (dice1 == dice2)	draw_text("DOUBLES!", -93, -2, .5, 0xfffb00);
		draw_rect(0, 0, 40, 20, 0xffffff);
		draw_text("GO TO JAIL!", -25, 5, 1, 0x888888);
		draw_text("OK", -2, -5, .8, 0xff0000);
		if (pressed(BUTTON_ENTER)) {
			current_gamemode = GM_GRAPHICS_POLICE;
//			mciSendString("open police_siren.mp3 type mpegvideo", NULL, 0, 0);
//			mciSendString("play police_siren.mp3", NULL, 0, 0);
//			Sleep(500);
			doubles = 0;
		}
	}

	else if (current_gamemode == GM_OUT_OF_JAIL) {
		if (hotButton > 1) hotButton = 0;
		draw_rect(0, 0, 53, 30, 0xffffff);
		draw_text("TO GET OUT OF JAIL", -38, 20, .7, 0x888888);
		draw_text("OR", -9, 5, .7, 0x888888);
		if (pressed(BUTTON_LEFT) || pressed(BUTTON_RIGHT)) hotButton = !hotButton;
		if (pressed(BUTTON_ENTER)) {
			if (hotButton == 0) {
				lefta[i] -= 50;
				current_gamemode = GM_GAMEPLAY;
				isInJail[i] = false;
				doublesInJail[i] = 0;
			}
			else if (outOfJailCard == i && hotButton == 1) {
				current_gamemode = GM_GAMEPLAY;
				isInJail[i] = false;
				doublesInJail[i] = 0;
				outOfJailCard = 0;
			}
		}
		switch (hotButton) {
		case 0: {
			draw_text("PAY", -36, 10, .7, 0xff0000);
			draw_number(500000, -36, -2, 1, 0xff0000);
			draw_text("EUROS", -32, 0, .7, 0xff0000);
			draw_text("USE THE OUT", 3, 10, .7, 0x888888);
			draw_text("OF JAIL CARD", 3, 0, .7, 0x888888);
		} break;
		case 1: {
			draw_text("PAY", -36, 10, .7, 0x888888);
			draw_number(500000, -36, -2, 1, 0x888888);
			draw_text("EUROS", -32, 0, .7, 0x888888);
			draw_text("USE THE OUT", 3, 10, .7, 0xff0000);
			draw_text("OF JAIL CARD", 3, 0, .7, 0xff0000);
		} break;
		}
	}

	else if (current_gamemode == GM_WHAT_PROP_SM) {
		draw_rect(0, 0, 40, 50, 0x888888);
		draw_text("WHAT PROPERTY?", -20, 45, .4, 0x000000);
		draw_text("PRESS LEFT ARROW TO GO BACK", -31, -40, .4, 0x000000);
		draw_text("MADE BY CAPTAIN KOUK", -24, -46, .4, 0xffffff);
		if (pressed(BUTTON_LEFT)) {
			current_gamemode = GM_ANYTHING_ELSE;
			prop_chosen = 0;
			hotButton = 0;
			somethingPressed = false;
			somethingToBeViewed = false;
		}
		if (prop_chosen == 0) prop_chosen = 2;
		if (pressed(BUTTON_DOWN)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen++;
				if (prop_chosen > 40) prop_chosen = 2;
				propCounter++;
			} while (tablo[prop_chosen] != i && propCounter < 40);

		}
		if (pressed(BUTTON_UP)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen--;
				if (prop_chosen <= 1) prop_chosen = 40;
				propCounter++;
			} while (tablo[prop_chosen] != i && propCounter <= 40);
		}
		for (int k = 1; k <= 40; k++) {
			if (tablo[k] == i || tablo[k] == 10 * i) {
				if (k < 21) {
					if (prop_chosen != k) draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0x000000);
					else {
						draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
					if (tablo[k] == 10 * i) {
						draw_text("MORTGAGED", -15, k* (-3.5) + 42.5, .35, 0x28ff00);
					}
				}
				else { 
					if (prop_chosen != k) draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0x000000); 
					else {
						draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
					if (tablo[k] == 10 * i) {
						draw_text("MORTGAGED", 20, (k-20)* (-3.5) + 42.5, .35, 0x28ff00);
					}
				}
				somethingToBeViewed = true;
			}
		}
		if (is_down(BUTTON_ENTER) && somethingPressed) {
			if (somethingToBeViewed) {
				if (hotButton == 4) {
					tablo[prop_chosen] = 0;
					lefta[i] += axies[prop_chosen];
					current_gamemode = GM_ANYTHING_ELSE;
				}
				else if (hotButton == 2) {
					tablo[prop_chosen] *= 10;
					lefta[i] += axies[prop_chosen] / 10;
					current_gamemode = GM_ANYTHING_ELSE;
				}
			}
			else {
				current_gamemode = GM_ANYTHING_ELSE;
				propCounter = 0;
			}
			somethingPressed = false;
			somethingToBeViewed = false;
		}
	}

	else if (current_gamemode == GM_WHAT_PROP_AM) {
		draw_rect(0, 0, 40, 50, 0x888888);
		draw_text("WHAT PROPERTY?", -20, 45, .4, 0x000000);
		draw_text("PRESS LEFT ARROW TO GO BACK", -31, -40, .4, 0x000000);
		draw_text("MADE BY CAPTAIN KOUK", -24, -46, .4, 0xffffff);
		if (pressed(BUTTON_LEFT)) {
			current_gamemode = GM_ANYTHING_ELSE;
			prop_chosen = 0;
			somethingPressed = false;
			somethingToBeViewed = false;
		}
		if (prop_chosen == 0) prop_chosen = 2;
		if (pressed(BUTTON_DOWN)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen++;
				if (prop_chosen > 40) prop_chosen = 2;
				propCounter++;
			} while (tablo[prop_chosen] != 10*i && propCounter < 40);

		}
		if (pressed(BUTTON_UP)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen--;
				if (prop_chosen <= 1) prop_chosen = 40;
				propCounter++;
			} while (tablo[prop_chosen] != 10*i && propCounter <= 40);
		}
		for (int k = 1; k <= 40; k++) {
			if (tablo[k] == 10*i) {
				if (k < 21) {
					if (prop_chosen != k) draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0x000000);
					else {
						draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
				}
				else {
					if (prop_chosen != k) draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0x000000);
					else {
						draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
				}
				somethingToBeViewed = true;
			}
		}
		if (is_down(BUTTON_ENTER) && somethingPressed) {
			if (somethingToBeViewed) {
				if (hotButton == 3) {
					tablo[prop_chosen] /= 10;
					lefta[i] -= axies[prop_chosen] / 2;
					current_gamemode = GM_ANYTHING_ELSE;
				}
			}
			else {
				current_gamemode = GM_ANYTHING_ELSE;
				propCounter = 0;
			}
			somethingPressed = false;
			somethingToBeViewed = false;
		}
		
	}

	else if (current_gamemode == GM_WHAT_PROP_H) {
		draw_rect(0, 0, 40, 50, 0x888888);
		draw_text("WHAT PROPERTY?", -20, 45, .4, 0x000000);
		draw_text("PRESS LEFT ARROW TO GO BACK", -31, -40, .4, 0x000000);
		draw_text("MADE BY CAPTAIN KOUK", -24, -46, .4, 0xffffff);
		if (pressed(BUTTON_LEFT)) {
			current_gamemode = GM_ANYTHING_ELSE;
			prop_chosen = 0;
			somethingPressed = false;
			somethingToBeViewed = false;
		}
		if (prop_chosen == 0) prop_chosen = 2;
		if (pressed(BUTTON_DOWN)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen++;
				if (prop_chosen > 40) prop_chosen = 2;
				propCounter++;
			} while (canBuildHouse(prop_chosen) == false && propCounter < 40);

		}
		if (pressed(BUTTON_UP)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen--;
				if (prop_chosen <= 1) prop_chosen = 40;
				propCounter++;
			} while (canBuildHouse(prop_chosen) == false && propCounter <= 40);
		}
		for (int k = 1; k <= 40; k++) {
			if (canBuildHouse(k)) {
				if (k < 21) {
					if (prop_chosen != k) draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0x000000);
					else {
						draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
				}
				else {
					if (prop_chosen != k) draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0x000000);
					else {
						draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
				}
				somethingToBeViewed = true;
			}
		}
		if (is_down(BUTTON_ENTER) && somethingPressed) {
			if (somethingToBeViewed) {
				if (hotButton == 5 || hotButton == 6) {
					hhtablo[prop_chosen]++;
					lefta[i] -= ((((prop_chosen-1)/10)+1) * 500000);
					current_gamemode = GM_ANYTHING_ELSE;
				}
			}
			else {
				current_gamemode = GM_ANYTHING_ELSE;
				propCounter = 0;
			}
			somethingPressed = false;
			somethingToBeViewed = false;
		}

	}

	else if (current_gamemode == GM_MY_PROPS) {
		draw_rect(0, 0, 40, 50, 0x888888);
		draw_text("MY PROPERTIES", -17, 45, .4, 0x000000);
		draw_text("MADE BY CAPTAIN KOUK", -24, -46, .4, 0xffffff);
		for (int k = 1; k <= 40; k++) {
			if (tablo[k] == i || tablo[k] == 10*i) {
				if (k < 21) {
					draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0x000000);
					if (tablo[k] == 10 * i) {
						draw_text("MORTGAGED", -15, k * (-3.5) + 42.5, .35, 0x28ff00);
					}
				}
				else {
					draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0x000000);
					if (tablo[k] == 10 * i) {
						draw_text("MORTGAGED", 25, (k-20) * (-3.5) + 42.5, .35, 0x28ff00);
					}
				}
			}
		}
		draw_text("OK", -2, -34, .7, 0xff0000);
		if (pressed(BUTTON_ENTER)) {
			current_gamemode = GM_ANYTHING_ELSE;
		}
	}

	else if (current_gamemode == GM_WHAT_PROP_SELLH) {
		draw_rect(0, 0, 40, 50, 0x888888);
		draw_text("WHAT PROPERTY?", -20, 45, .4, 0x000000);
		draw_text("PRESS LEFT ARROW TO GO BACK", -31, -40, .4, 0x000000);
		draw_text("MADE BY CAPTAIN KOUK", -24, -46, .4, 0xffffff);
		if (pressed(BUTTON_LEFT)) {
			current_gamemode = GM_ANYTHING_ELSE;
			prop_chosen = 0;
			somethingPressed = false;
			somethingToBeViewed = false;
		}
		if (prop_chosen == 0) prop_chosen = 2;
		if (pressed(BUTTON_DOWN)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen++;
				if (prop_chosen > 40) prop_chosen = 2;
				propCounter++;
			} while (canSellHouse(prop_chosen) == false && propCounter < 40);

		}
		if (pressed(BUTTON_UP)) {
			somethingPressed = true;
			propCounter = 0;
			do {
				prop_chosen--;
				if (prop_chosen <= 1) prop_chosen = 40;
				propCounter++;
			} while (canSellHouse(prop_chosen) == false && propCounter <= 40);
		}
		for (int k = 1; k <= 40; k++) {
			if (canSellHouse(k)) {
				if (k < 21) {
					if (prop_chosen != k) draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0x000000);
					else {
						draw_text(prop_names[k], -37, k * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
				}
				else {
					if (prop_chosen != k) draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0x000000);
					else {
						draw_text(prop_names[k], 3, (k - 20) * (-3.5) + 40, .35, 0xff0000);
						draw_card(prop_chosen, prop_names, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot);
					}
				}
				somethingToBeViewed = true;
			}
		}
		if (is_down(BUTTON_ENTER) && somethingPressed) {
			if (somethingToBeViewed) {
				if (hotButton == 5 || hotButton == 6) {
					hhtablo[prop_chosen]--;
					lefta[i] += ((((prop_chosen-1) / 10)+1) * 500000);
					current_gamemode = GM_ANYTHING_ELSE;
				}
			}
			else {
				current_gamemode = GM_ANYTHING_ELSE;
				propCounter = 0;
			}
			somethingPressed = false;
			somethingToBeViewed = false;
		}
	}

	else if (current_gamemode == GM_END_OF_GAME) {
		end_of_game(input, dt, axies);
	}

	else if (current_gamemode == GM_GRAPHICS_POLICE) {
		police_van_dx = 25;
		if (police_van_direction == 0) {
			if (theseis[i] > 11) {
				police_van_direction = 1;
			}
			else if (theseis[i] < 11) {
				police_van_direction = 2;
			}
			else {
				isInJail[i] = true;
				theseis[i] = 11;
				current_gamemode = GM_ANYTHING_ELSE;
				arrested = false;
				police_van_direction = 0;
				police_van_x = -42;
				police_van_y = -42;
//				mciSendString("close police_siren.mp3", NULL, 0, NULL);
			}
		}
		if (police_van_direction == 1) {
			draw_police_van_up(police_van_x, police_van_y, isSirenOn);
			police_van_y += police_van_dx * dt;
			if (police_van_y > 42) {
				police_van_y = 42;
				if (!arrested) police_van_direction = 2;
				else police_van_direction = 4;
			}
			if (theseis[i] < 22 && theseis[i] > 11) {
				if (police_van_y > drawn_pos_y[theseis[i]]) {
					arrested = true;
					police_van_direction = 3;
				}
			}
			
		}
		else if (police_van_direction == 2) {
			draw_police_van_right(police_van_x, police_van_y, isSirenOn);
			police_van_x += police_van_dx * dt;
			if (police_van_x > 42) {
				police_van_x = 42;
				police_van_direction = 3;
			}
			if ((theseis[i] < 32 && theseis[i] > 21) || (theseis[i] < 11)) {
				if (police_van_x > drawn_pos_x[theseis[i]]) {
					arrested = true;
					police_van_direction = 4;
				}
			}
		}
		else if (police_van_direction == 3) {
			draw_police_van_down(police_van_x, police_van_y, isSirenOn);
			police_van_y -= police_van_dx * dt;
			if (police_van_y < -42) {
				isInJail[i] = true;
				theseis[i] = 11;
				current_gamemode = GM_ANYTHING_ELSE;
				arrested = false;
				police_van_direction = 0;
				police_van_x = -42;
				police_van_y = -42;
			}
			if (theseis[i] > 31 && !arrested) {
				if (police_van_y < drawn_pos_y[theseis[i]]) {
					arrested = true;
					police_van_direction = 1;
				}
			}
		}
		else if (police_van_direction == 4) {
			draw_police_van_left(police_van_x, police_van_y, isSirenOn);
			police_van_x -= police_van_dx * dt;
			if (police_van_x < -42) {
				police_van_x = -42;
				if (police_van_y > 0) police_van_direction = 3;
				else {
					isInJail[i] = true;
					theseis[i] = 11;
					current_gamemode = GM_ANYTHING_ELSE;
					arrested = false;
					police_van_direction = 0;
					police_van_x = -42;
					police_van_y = -42;
					mciSendString("close police_siren.mp3", NULL, 0, NULL);
				}
			}
		}
		total_time += dt;
		if (total_time > .25) {
			total_time = 0;
			isSirenOn = !isSirenOn;
		}
	}

	else if (current_gamemode == GM_GRAPHICS_MONEY) {
		senders[1] = 2;
		receiver = 1;
		money_dx = 30;
		for (int k = 1; senders[k] != 0; k++) {
			
			draw_money(money_x[k], money_y[k]);
			if (money_direction == 0) {
				money_x[k] = -55;
				money_y[k] = drawn_money_pos[k];
				money_direction = 2;
			}
			if (money_direction == 1) {
				money_y[k] += money_dx * dt;
				if (money_y[k] > drawn_money_pos[receiver]) {
					money_y[k] = drawn_money_pos[receiver];
					money_direction = 4;
				}
			}
			if (money_direction == 2) {
				money_x[k] += money_dx * dt;
				if (money_x[k] > -40) {
					money_x[k] = -40;
					money_direction = 1;
				}
			}
		}
	}

	/*outOfJailCard rendering*/	{
	if (outOfJailCard == 1) outOfJailCardPos = 42.5;
	else if (outOfJailCard == 2) outOfJailCardPos = 31;
	else if (outOfJailCard == 3) outOfJailCardPos = 20;
	else if (outOfJailCard == 4) outOfJailCardPos = 9;
	else if (outOfJailCard == 5) outOfJailCardPos = -2;
	else if (outOfJailCard == 6) outOfJailCardPos = -11;
	if (outOfJailCard != 0) {
		draw_rect(-67, outOfJailCardPos, 1.2, .7, 0xffffff);
		draw_rect(-67, outOfJailCardPos + .2, .7, .1, 0x888888);
		draw_rect(-67, outOfJailCardPos - .2, .2, .1, 0xff0000);
	}
	}

}