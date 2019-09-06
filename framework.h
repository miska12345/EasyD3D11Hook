// header.h : include file for standard system include files,
// or project specific include files
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <string>

// D3d Related Files
#include <DXGI.h>
#include <d3d11.h>
#include <D3D10.h>
#include <d3d9types.h>

#include <WinUser.h>
#include <mutex>

#include "Menu.h"
#include "Renderer/D3D11Renderer.h"

/*********************Normal Colors**********************/
#define WHITE			D3DCOLOR_ARGB(255, 255, 255, 255)
#define RED			D3DCOLOR_ARGB(255, 255, 000, 000)
#define GREEN			D3DCOLOR_ARGB(255, 000, 255, 000)
#define BLUE			D3DCOLOR_ARGB(255, 000, 000, 255) 
#define BLACK			D3DCOLOR_ARGB(150, 000, 000, 000)
#define mBLACK			D3DCOLOR_ARGB(100, 000, 000, 205)
#define PURPLE			D3DCOLOR_ARGB(255, 125, 000, 255) 
#define GREY			D3DCOLOR_ARGB(255, 128, 128, 128) 
#define YELLOW			D3DCOLOR_ARGB(255, 255, 255, 000) 
#define ORANGE			D3DCOLOR_ARGB(255, 255, 125, 000)
#define PINK			D3DCOLOR_ARGB(255, 255, 050, 250)
#define CYAN			D3DCOLOR_ARGB(255, 000, 255, 255)
#define WHITE2			D3DCOLOR_ARGB(100, 255, 255, 255)
#define RED2			D3DCOLOR_ARGB(100, 255, 000, 000)
#define GREEN2			D3DCOLOR_ARGB(100, 000, 255, 000)
#define BLUE2			D3DCOLOR_ARGB(100, 000, 000, 255) 
#define BLACK2			D3DCOLOR_ARGB(100, 000, 000, 000)
#define PURPLE2			D3DCOLOR_ARGB(100, 125, 000, 255) 
#define GREY2			D3DCOLOR_ARGB(100, 128, 128, 128) 
#define YELLOW2			D3DCOLOR_ARGB(100, 255, 255, 000) 
#define ORANGE2			D3DCOLOR_ARGB(100, 255, 125, 000)
#define PINK2			D3DCOLOR_ARGB(100, 255, 050, 250)
#define CYAN2			D3DCOLOR_ARGB(100, 000, 255, 255)
#define BROWN                   D3DCOLOR_ARGB(255, 77, 46, 38)