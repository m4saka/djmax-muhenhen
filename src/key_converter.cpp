#include "djmax_muhenhen/key_converter.hpp"

KeyConverter::KeyConverter(int srcKey, WORD dstKey, std::shared_ptr<VirtualKeyboard> virtualKeyboard)
    : m_srcKeyDetector(srcKey)
    , m_dstKey(dstKey)
    , m_virtualKeyboard(virtualKeyboard)
{
}

KeyConverter::~KeyConverter()
{
    // 終了時は押下状態を解放
    m_virtualKeyboard->keyUp(m_dstKey);
}

bool KeyConverter::update()
{
    if (m_srcKeyDetector.isPressed())
    {
        // 変換元キーが押下されていれば変換先キーを押下したことにする
        m_virtualKeyboard->keyDown(m_dstKey);
        return true;
    }
    else
    {
        // 変換元キーが押下されていなければ変換先キーを押下していないことにする
        m_virtualKeyboard->keyUp(m_dstKey);
        return false;
    }
}
