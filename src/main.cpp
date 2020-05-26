#include <iostream>
#include <vector>
#include <memory>
#include <Windows.h> // Sleep
#include <winuser.h> // キー番号の定数

#include "djmax_muhenhen/virtual_keyboard.hpp"
#include "djmax_muhenhen/key_converter.hpp"

int main()
{
    std::cout <<
        "\n"
        "**動作中** 無変換/変換キーを左Shift/右Shiftに変換しています\n"
        "\n"
        "  このウィンドウを閉じると終了します"
        << std::endl;

    // 仮想キーボード
    auto virtualKeyboard = std::make_shared<VirtualKeyboard>();

    // キー変換の一覧
    std::vector<KeyConverter> keyConverters = {
        KeyConverter(VK_NONCONVERT, VK_LSHIFT, virtualKeyboard),
        KeyConverter(VK_CONVERT, VK_RSHIFT, virtualKeyboard),
    };

    // メインループ
    while (true)
    {
        // 入力変換を実行
        for (auto & conv : keyConverters)
        {
            conv.update();
        }

        // 時間待ち
        timeBeginPeriod(1);
        Sleep(1);
        timeEndPeriod(1);
    }

    return 0;
}
