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
