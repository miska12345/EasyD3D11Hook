#include "Menu.h"

D3DMenu::D3DMenu() {
	this->Is_Visible = true;
}

void D3DMenu::InitMenu(std::shared_ptr<D3D11Renderer> renderer, LPCWSTR Title, int x, int y) {
	this->pRenderer = renderer;
	this->Is_Ready = true;
	this->sMenu.Title = Title;
	this->sMenu.x = x;
	this->sMenu.y = y;
	this->sMenu.w = 190;
}

void D3DMenu::AddFolder(LPCWSTR Name, int* Pointer) {
	sOptions[this->Items].Name = (LPCWSTR)Name;
	sOptions[this->Items].Function = Pointer;
	sOptions[this->Items].Type = T_FOLDER;
	this->Items++;
}

void D3DMenu::AddOption(LPCWSTR Name, int* Pointer, int* Folder) {
	if (*Folder == 0) {
		return;
	}
	sOptions[this->Items].Name = Name;
	sOptions[this->Items].Function = Pointer;
	sOptions[this->Items].Type = T_OPTION;
	this->Items++;
}

void D3DMenu::Navigation() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		this->Is_Visible = !this->Is_Visible;

	if (!this->Is_Visible)
		return;

	int value = 0;

	if (GetAsyncKeyState(VK_DOWN) & 1)
	{
		this->Cur_Pos++;
		if (sOptions[this->Cur_Pos].Name == 0)
			this->Cur_Pos--;
	}

	if (GetAsyncKeyState(VK_UP) & 1)
	{
		this->Cur_Pos--;
		if (this->Cur_Pos == -1)
			this->Cur_Pos++;
	}

	else if (GetAsyncKeyState(VK_RIGHT) & 1)
	{
		if (*sOptions[this->Cur_Pos].Function == 0)
			value++;
	}

	else if ((GetAsyncKeyState(VK_LEFT) & 1) && *sOptions[this->Cur_Pos].Function == 1)
	{
		value--;
	}


	if (value) {
		*sOptions[this->Cur_Pos].Function += value;
	}

}

void D3DMenu::DrawMenu() {
	if (!this->Is_Visible)
		return;
	float height = LINEH * (this->Items + 2) + BUTTOM_SPACE;
	this->pRenderer->FillRect(this->sMenu.x, this->sMenu.y, sMenu.x + sMenu.w, height, Color_Background);    // Background
	this->pRenderer->DrawBox(sMenu.x, sMenu.y, sMenu.x + sMenu.w, sMenu.y + height, Color_Line);    // Box outline
	this->DrawString(this->sMenu.Title, 12, sMenu.x + 5, sMenu.y, this->Color_Font);    // Title
	this->pRenderer->DrawLine(sMenu.x, sMenu.y + 18, sMenu.x + sMenu.w, sMenu.y + 18, Color_Line);    // Title underline
	for (int i = 0; i < this->Items; i++)
	{
		float offset = 5;    // For item indention
		if (this->sOptions[i].Type == T_OPTION)
		{
			offset *= 2;
			if (*this->sOptions[i].Function)
			{
				this->DrawString(L"On", 12, sMenu.x + 155, sMenu.y + LINEH * (i + 2), this->Color_On);
			}
			else {
				this->DrawString(L"Off", 12, sMenu.x + 155, sMenu.y + LINEH * (i + 2), this->Color_Off);
			}
		}
		if (this->sOptions[i].Type == T_FOLDER)
		{
			if (*this->sOptions[i].Function)
			{
				this->DrawString(L"Opend", 12, sMenu.x + 150, sMenu.y + LINEH * (i + 2), this->Color_Folder);
			}
			else {
				this->DrawString(L"Closed", 12, sMenu.x + 150, sMenu.y + LINEH * (i + 2), this->Color_Folder);
			}
		}
		DWORD Color = this->Color_Font;
		if (this->Cur_Pos == i)
			Color = this->Color_Current;
		this->DrawString(this->sOptions[i].Name, 12, sMenu.x + offset, sMenu.y + LINEH * (i + 2), Color);
	}
}

bool D3DMenu::IsReady() {
	return Is_Ready;
}

void D3DMenu::DrawString(LPCWSTR text, int FontSize, int x, int y, DWORD Col) {
	if (this->IsReady()) {
		pRenderer->DrawString(text, (float)FontSize, (float)x, (float)y, Col);
	}
}
