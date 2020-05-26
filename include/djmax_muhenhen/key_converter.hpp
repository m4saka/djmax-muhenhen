#pragma once
#include "djmax_muhenhen/key_detector.hpp"
#include "djmax_muhenhen/virtual_keyboard.hpp"
#include <memory>
#include <Windows.h> // WORD型

// キー入力の変換を行うクラス
class KeyConverter
{
private:
    const KeyDetector m_srcKeyDetector;
    const WORD m_dstKey;
    const std::shared_ptr<VirtualKeyboard> m_virtualKeyboard;

public:
    // コンストラクタ
    // (変換元キー, 変換先キー, 仮想キーボードクラスを指定)
    KeyConverter(int srcKey, WORD dstKey, std::shared_ptr<VirtualKeyboard> virtualKeyboard);

    ~KeyConverter();

    // 状態を更新(フレーム毎に呼ぶこと)
    // キーが押下されているかどうかを返す
    bool update();
};
