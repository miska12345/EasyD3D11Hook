Welcome\! This repository contains the source code for:

  - Universal D3D11 Hook
  - D3D11Renderer
  - PolyHook

## Universal D3D11 Hook

D3D11 Hook provides the ability for user to detour D3DX functions in an effective manner. This code hooks the Present function and draws functional menu in a target application.

## D3D11Renderer

The D3D11Renderer is a helper class that draws text and basic geometry(line, box, circle...).

## PolyHook

PolyHook is a hooking library developed by Stephen Eckels. The original repo can be found here: https://github.com/stevemk14ebr/PolyHook.

## Demo
![Image description](https://github.com/miska12345/EasyD3D11Hook/blob/master/capture.PNG)

## Usage
Upon successful compilation, you will get 2 DLL files. The D3DHook.dll contain the core of this hook. The FW1FontWrapper.dll is a support library that is used during runtime for text rendering. To use the hook, you should inject FW1FontWrapper.dll to a target process, then inject D3DHook.dll (order does matter).

### Default Hotkeys
Show/Hide Menu: Insert
Navigate up an item: Up arrow
Navigate down an item: Down arrow
Enable a feature: Right arrow
Disable a feature: Left arrow

## Note
The dispayed features are not included with the hook.
