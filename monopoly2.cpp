#include "utils.cpp"
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
#include <string>
#include <ctime>

using namespace std;

global_variable bool running = true;

struct Render_State {
	int height, width;
	void* memory;

	BITMAPINFO bitmap_info;
};

global_variable Render_State render_state;

#include "platform_common.cpp"
#include "renderer.cpp"
#include "game.cpp"

LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY: {
		running = false;
	} break;

	case WM_SIZE: {
		RECT rect;
		GetClientRect(hwnd, &rect);
		render_state.width = rect.right - rect.left;
		render_state.height = rect.bottom - rect.top;

		int size = render_state.width * render_state.height * sizeof(unsigned int);
		if (render_state.memory) VirtualFree(render_state.memory, 0, MEM_RELEASE);
		render_state.memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		render_state.bitmap_info.bmiHeader.biSize = sizeof(render_state.bitmap_info.bmiHeader);
		render_state.bitmap_info.bmiHeader.biWidth = render_state.width;
		render_state.bitmap_info.bmiHeader.biHeight = render_state.height;
		render_state.bitmap_info.bmiHeader.biPlanes = 1;
		render_state.bitmap_info.bmiHeader.biBitCount = 32;
		render_state.bitmap_info.bmiHeader.biCompression = BI_RGB;

	} break;

	default: {
		result = DefWindowProc(hwnd, uMsg, wParam, lParam);

	}
	}
	return result;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {

	// Create Window Class
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = "Game Window Class";
	window_class.lpfnWndProc = window_callback;

	// Register Class
	RegisterClass(&window_class);

	// Create Window
	HWND window = CreateWindow(window_class.lpszClassName, "Monopoly", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 1280, 720, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	Input input = {};

	float delta_time = 0.016666f;
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}

	int axies[41];      // the money you need to buy something
	{
		axies[1] = 0;
		axies[2] = 600000;
		axies[3] = 0;
		axies[4] = 600000;
		axies[5] = 0;
		axies[6] = 2000000;
		axies[7] = 1000000;
		axies[8] = 0;
		axies[9] = 1000000;
		axies[10] = 1200000;
		axies[11] = 0;
		axies[12] = 1400000;
		axies[13] = 1500000;
		axies[14] = 1400000;
		axies[15] = 1600000;
		axies[16] = 2000000;
		axies[17] = 1800000;
		axies[18] = 0;
		axies[19] = 1800000;
		axies[20] = 2000000;
		axies[21] = 0;
		axies[22] = 2200000;
		axies[23] = 0;
		axies[24] = 2200000;
		axies[25] = 2400000;
		axies[26] = 2000000;
		axies[27] = 2600000;
		axies[28] = 2600000;
		axies[29] = 1500000;
		axies[30] = 2800000;
		axies[31] = 0;
		axies[32] = 3000000;
		axies[33] = 3000000;
		axies[34] = 0;
		axies[35] = 3200000;
		axies[36] = 2000000;
		axies[37] = 0;
		axies[38] = 3500000;
		axies[39] = 0;
		axies[40] = 4000000;
	}
	int enoikia[41];    // the money one pays if there's no house
	{
		enoikia[1] = 0;
		enoikia[2] = 20000;
		enoikia[3] = 0;
		enoikia[4] = 40000;
		enoikia[5] = 0;
		enoikia[6] = 0;
		enoikia[7] = 60000;
		enoikia[8] = 0;
		enoikia[9] = 60000;
		enoikia[10] = 80000;
		enoikia[11] = 0;
		enoikia[12] = 100000;
		enoikia[13] = 0;
		enoikia[14] = 100000;
		enoikia[15] = 120000;
		enoikia[16] = 0;
		enoikia[17] = 140000;
		enoikia[18] = 0;
		enoikia[19] = 140000;
		enoikia[20] = 160000;
		enoikia[21] = 0;
		enoikia[22] = 180000;
		enoikia[23] = 0;
		enoikia[24] = 180000;
		enoikia[25] = 200000;
		enoikia[26] = 0;
		enoikia[27] = 220000;
		enoikia[28] = 220000;
		enoikia[29] = 0;
		enoikia[30] = 240000;
		enoikia[31] = 0;
		enoikia[32] = 260000;
		enoikia[33] = 260000;
		enoikia[34] = 0;
		enoikia[35] = 280000;
		enoikia[36] = 0;
		enoikia[37] = 0;
		enoikia[38] = 350000;
		enoikia[39] = 0;
		enoikia[40] = 500000;
	}
	int enoikia1h[41];  // the money one pays if there's a house
	{
		enoikia1h[1] = 0;
		enoikia1h[2] = 100000;
		enoikia1h[3] = 0;
		enoikia1h[4] = 200000;
		enoikia1h[5] = 0;
		enoikia1h[6] = 0;
		enoikia1h[7] = 300000;
		enoikia1h[8] = 0;
		enoikia1h[9] = 300000;
		enoikia1h[10] = 400000;
		enoikia1h[11] = 0;
		enoikia1h[12] = 500000;
		enoikia1h[13] = 0;
		enoikia1h[14] = 500000;
		enoikia1h[15] = 600000;
		enoikia1h[16] = 0;
		enoikia1h[17] = 700000;
		enoikia1h[18] = 0;
		enoikia1h[19] = 700000;
		enoikia1h[20] = 800000;
		enoikia1h[21] = 0;
		enoikia1h[22] = 900000;
		enoikia1h[23] = 0;
		enoikia1h[24] = 900000;
		enoikia1h[25] = 1000000;
		enoikia1h[26] = 0;
		enoikia1h[27] = 1100000;
		enoikia1h[28] = 1100000;
		enoikia1h[29] = 0;
		enoikia1h[30] = 1200000;
		enoikia1h[31] = 0;
		enoikia1h[32] = 1300000;
		enoikia1h[33] = 1300000;
		enoikia1h[34] = 0;
		enoikia1h[35] = 1500000;
		enoikia1h[36] = 0;
		enoikia1h[37] = 0;
		enoikia1h[38] = 1750000;
		enoikia1h[39] = 0;
		enoikia1h[40] = 2000000;
	}
	int enoikia2h[41];  // the money one pays if there are two houses
	{
		enoikia2h[1] = 0;
		enoikia2h[2] = 300000;
		enoikia2h[3] = 0;
		enoikia2h[4] = 600000;
		enoikia2h[5] = 0;
		enoikia2h[6] = 0;
		enoikia2h[7] = 900000;
		enoikia2h[8] = 0;
		enoikia2h[9] = 900000;
		enoikia2h[10] = 1000000;
		enoikia2h[11] = 0;
		enoikia2h[12] = 1500000;
		enoikia2h[13] = 0;
		enoikia2h[14] = 1500000;
		enoikia2h[15] = 1800000;
		enoikia2h[16] = 0;
		enoikia2h[17] = 2000000;
		enoikia2h[18] = 0;
		enoikia2h[19] = 2000000;
		enoikia2h[20] = 2200000;
		enoikia2h[21] = 0;
		enoikia2h[22] = 2500000;
		enoikia2h[23] = 0;
		enoikia2h[24] = 2500000;
		enoikia2h[25] = 3000000;
		enoikia2h[26] = 0;
		enoikia2h[27] = 3300000;
		enoikia2h[28] = 3300000;
		enoikia2h[29] = 0;
		enoikia2h[30] = 3600000;
		enoikia2h[31] = 0;
		enoikia2h[32] = 3900000;
		enoikia2h[33] = 3900000;
		enoikia2h[34] = 0;
		enoikia2h[35] = 4500000;
		enoikia2h[36] = 0;
		enoikia2h[37] = 0;
		enoikia2h[38] = 5000000;
		enoikia2h[39] = 0;
		enoikia2h[40] = 6000000;
	}
	int enoikia3h[41];  // the money one pays if there are three houses
	{
		enoikia3h[1] = 0;
		enoikia3h[2] = 900000;
		enoikia3h[3] = 0;
		enoikia3h[4] = 1800000;
		enoikia3h[5] = 0;
		enoikia3h[6] = 0;
		enoikia3h[7] = 2700000;
		enoikia3h[8] = 0;
		enoikia3h[9] = 2700000;
		enoikia3h[10] = 3000000;
		enoikia3h[11] = 0;
		enoikia3h[12] = 4500000;
		enoikia3h[13] = 0;
		enoikia3h[14] = 4500000;
		enoikia3h[15] = 5000000;
		enoikia3h[16] = 0;
		enoikia3h[17] = 5500000;
		enoikia3h[18] = 0;
		enoikia3h[19] = 5500000;
		enoikia3h[20] = 6000000;
		enoikia3h[21] = 0;
		enoikia3h[22] = 7000000;
		enoikia3h[23] = 0;
		enoikia3h[24] = 7000000;
		enoikia3h[25] = 7500000;
		enoikia3h[26] = 0;
		enoikia3h[27] = 9750000;
		enoikia3h[28] = 9750000;
		enoikia3h[29] = 0;
		enoikia3h[30] = 8500000;
		enoikia3h[31] = 0;
		enoikia3h[32] = 9000000;
		enoikia3h[33] = 9000000;
		enoikia3h[34] = 0;
		enoikia3h[35] = 10000000;
		enoikia3h[36] = 0;
		enoikia3h[37] = 0;
		enoikia3h[38] = 11000000;
		enoikia3h[39] = 0;
		enoikia3h[40] = 14000000;
	}
	int enoikia4h[41];  // the money one pays if there are 4 houses
	{
		enoikia4h[1] = 0;
		enoikia4h[2] = 1600000;
		enoikia4h[3] = 0;
		enoikia4h[4] = 3200000;
		enoikia4h[5] = 0;
		enoikia4h[6] = 0;
		enoikia4h[7] = 4000000;
		enoikia4h[8] = 0;
		enoikia4h[9] = 4000000;
		enoikia4h[10] = 4500000;
		enoikia4h[11] = 0;
		enoikia4h[12] = 6250000;
		enoikia4h[13] = 0;
		enoikia4h[14] = 6250000;
		enoikia4h[15] = 7000000;
		enoikia4h[16] = 0;
		enoikia4h[17] = 7500000;
		enoikia4h[18] = 0;
		enoikia4h[19] = 7500000;
		enoikia4h[20] = 8000000;
		enoikia4h[21] = 0;
		enoikia4h[22] = 8750000;
		enoikia4h[23] = 0;
		enoikia4h[24] = 8750000;
		enoikia4h[25] = 9250000;
		enoikia4h[26] = 0;
		enoikia4h[27] = 9750000;
		enoikia4h[28] = 9750000;
		enoikia4h[29] = 0;
		enoikia4h[30] = 10250000;
		enoikia4h[31] = 0;
		enoikia4h[32] = 11000000;
		enoikia4h[33] = 11000000;
		enoikia4h[34] = 0;
		enoikia4h[35] = 12000000;
		enoikia4h[36] = 0;
		enoikia4h[37] = 0;
		enoikia4h[38] = 13000000;
		enoikia4h[39] = 0;
		enoikia4h[40] = 17000000;
	}
	int enoikiahot[41];  // the money one pays if there's a hotel
	{
		enoikiahot[1] = 0;
		enoikiahot[2] = 2500000;
		enoikiahot[3] = 0;
		enoikiahot[4] = 4500000;
		enoikiahot[5] = 0;
		enoikiahot[6] = 0;
		enoikiahot[7] = 5500000;
		enoikiahot[8] = 0;
		enoikiahot[9] = 5500000;
		enoikiahot[10] = 6000000;
		enoikiahot[11] = 0;
		enoikiahot[12] = 7500000;
		enoikiahot[13] = 0;
		enoikiahot[14] = 7500000;
		enoikiahot[15] = 9000000;
		enoikiahot[16] = 0;
		enoikiahot[17] = 9500000;
		enoikiahot[18] = 0;
		enoikiahot[19] = 9500000;
		enoikiahot[20] = 10000000;
		enoikiahot[21] = 0;
		enoikiahot[22] = 10500000;
		enoikiahot[23] = 0;
		enoikiahot[24] = 10500000;
		enoikiahot[25] = 11000000;
		enoikiahot[26] = 0;
		enoikiahot[27] = 11500000;
		enoikiahot[28] = 1150000;
		enoikiahot[29] = 0;
		enoikiahot[30] = 12000000;
		enoikiahot[31] = 0;
		enoikiahot[32] = 12750000;
		enoikiahot[33] = 12750000;
		enoikiahot[34] = 0;
		enoikiahot[35] = 14000000;
		enoikiahot[36] = 0;
		enoikiahot[37] = 0;
		enoikiahot[38] = 15000000;
		enoikiahot[39] = 0;
		enoikiahot[40] = 20000000;
	}


	while (running) {
		// Input
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);
				switch (vk_code) {

#define process_button(b, vk)\
case vk:{\
input.buttons[b].changed = is_down != input.buttons[b].is_down;\
input.buttons[b].is_down = is_down;\
} break;
					process_button(BUTTON_UP, VK_UP);
					process_button(BUTTON_DOWN, VK_DOWN);
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_ENTER, VK_RETURN);
					process_button(BUTTON_BACKSPACE, VK_BACK);
					process_button(BUTTON_SPACE, VK_SPACE);
					process_button(BUTTON_A, 'A');
					process_button(BUTTON_B, 'B');
					process_button(BUTTON_C, 'C');
					process_button(BUTTON_D, 'D');
					process_button(BUTTON_E, 'E');
					process_button(BUTTON_F, 'F');
					process_button(BUTTON_G, 'G');
					process_button(BUTTON_H, 'H');
					process_button(BUTTON_I, 'I');
					process_button(BUTTON_J, 'J');
					process_button(BUTTON_K, 'K');
					process_button(BUTTON_L, 'L');
					process_button(BUTTON_M, 'M');
					process_button(BUTTON_N, 'N');
					process_button(BUTTON_O, 'O');
					process_button(BUTTON_P, 'P');
					process_button(BUTTON_Q, 'Q');
					process_button(BUTTON_R, 'R');
					process_button(BUTTON_S, 'S');
					process_button(BUTTON_T, 'T');
					process_button(BUTTON_U, 'U');
					process_button(BUTTON_V, 'V');
					process_button(BUTTON_W, 'W');
					process_button(BUTTON_X, 'X');
					process_button(BUTTON_Y, 'Y');
					process_button(BUTTON_Z, 'Z');
				}
			} break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}

		// Simulate
		simulate_game(&input, axies, enoikia, enoikia1h, enoikia2h, enoikia3h, enoikia4h, enoikiahot, delta_time);

		// Render
		StretchDIBits(hdc, 0, 0, render_state.width, render_state.height, 0, 0, render_state.width, render_state.height, render_state.memory, &render_state.bitmap_info, DIB_RGB_COLORS, SRCCOPY);

		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}

}