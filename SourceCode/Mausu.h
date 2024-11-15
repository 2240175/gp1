#pragma once

#include <Windows.h>

class MouseManager {
public:
    // �}�E�X�̍��W���X�V
    void Update() {
        GetCursorPos(&position);
    }

    // �}�E�X�̍��W���擾
    POINT GetPosition() const {
        return position;
    }

private:
    POINT position;
};

//�܂����܂�悭�킩���ĂȂ�����
//�}�E�X�Ǘ��ɕK�v�����g�����͖���
LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_LBUTTONDOWN:
		//�}�E�X���{�^������
		return 0;
	case WM_MBUTTONDOWN:
		//�}�E�X�z�C�[������
		return 0;
	case WM_RBUTTONDOWN:
		//�}�E�X�E�{�^������
		return 0;
	case WM_LBUTTONUP:
		//�}�E�X���{�^��������
		return 0;
	case WM_MBUTTONUP:
		//�}�E�X�z�C�[��������
		return 0;
	case WM_RBUTTONUP:
		//�}�E�X�E�{�^��������
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}