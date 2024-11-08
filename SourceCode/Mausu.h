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
