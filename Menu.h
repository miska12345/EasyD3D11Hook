/*
This is a simple menu class for D3D11.
It utilizes D3D11Renderer to draw text and geometry.
User may navigate the menu by using the four arrow keys.
*/

#pragma once
#include <memory>    // For std::shared_ptr
#include "Renderer/D3D11Renderer.h"
#include <FW1FontWrapper.h>

#pragma comment(lib, "FW1FontWrapper.lib")

#define MAX_ITEMS 25    // The maximum possible items

#define T_FOLDER 1
#define T_OPTION 2

#define LINEH 15    // Space (px) between each listing
#define BUTTOM_SPACE 50

typedef struct sOptions {
	LPCWSTR Name;
	int* Function;
	BYTE Type;
} Options;

typedef struct sMenu {
	LPCWSTR Title;
	int x;
	int y;
	int w;
} MenuHelper;

class D3DMenu {
public:
	D3DMenu();
	void InitMenu(std::shared_ptr<D3D11Renderer> renderer, LPCWSTR Title, int x, int y);
	void DrawString(LPCWSTR Text, int FontSize, int x, int y, DWORD color);

	void DrawMenu();
	void Navigation();
	void AddFolder(LPCWSTR Name, int* Pointer);
	void AddOption(LPCWSTR Name, int* Pointer, int* Folder);

	bool IsReady();

	// Color declarations for FW1FontWrapper
	DWORD Color_Font;
	DWORD Color_On;
	DWORD Color_Off;
	DWORD Color_Folder;
	DWORD Color_Current;
	DWORD Color_Tips;

	// Color declarations for D3D11Renderer
	Color Color_Line;
	Color Color_Background;

private:
	std::shared_ptr<D3D11Renderer> pRenderer;
	bool Is_Ready;
	bool Is_Visible;
	int Items;
	int Cur_Pos;

	Options sOptions[MAX_ITEMS];
	MenuHelper sMenu;
};
