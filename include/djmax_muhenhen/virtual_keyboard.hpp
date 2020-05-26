#pragma once
#include <Windows.h> // WORD型
#include <winuser.h>

// 仮想キーボードを扱うクラス
class VirtualKeyboard
{
private:
    INPUT m_input;

public:
    VirtualKeyboard();

    // 指定されたキーを押下したことにする
    void keyDown(WORD key);

    // 指定されたキーを押下していないことにする
    void keyUp(WORD key);
};
