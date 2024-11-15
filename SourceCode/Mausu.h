#pragma once

#include <Windows.h>

class MouseManager {
public:
    // マウスの座標を更新
    void Update() {
        GetCursorPos(&position);
    }

    // マウスの座標を取得
    POINT GetPosition() const {
        return position;
    }

private:
    POINT position;
};

//まだあまりよくわかってないもの
//マウス管理に必要だが使うかは未定
LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		//マウス左ボタン押下
		return 0;
	case WM_MBUTTONDOWN:
		//マウスホイール押下
		return 0;
	case WM_RBUTTONDOWN:
		//マウス右ボタン押下
		return 0;
	case WM_LBUTTONUP:
		//マウス左ボタン離した
		return 0;
	case WM_MBUTTONUP:
		//マウスホイール離した
		return 0;
	case WM_RBUTTONUP:
		//マウス右ボタン離した
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}