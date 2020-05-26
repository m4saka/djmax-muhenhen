#pragma comment(lib, "winmm.lib")
#include "djmax_muhenhen/virtual_keyboard.hpp"

// 中華ボルテコン変換機 http://otogetool.g2.xrea.com/ の
// ソースコードを参考に実装

VirtualKeyboard::VirtualKeyboard()
{
    m_input.type = INPUT_KEYBOARD;
    m_input.ki.time = 0;
}

void VirtualKeyboard::keyDown(WORD key)
{
    m_input.ki.wVk = key;
    m_input.ki.wScan = MapVirtualKey(m_input.ki.wVk, 0);

    if (key == VK_RETURN){
        m_input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY; // Enterキーの場合のみ必要
    }
    else
    {
        m_input.ki.dwFlags = 0;
    }

    m_input.ki.dwExtraInfo = GetMessageExtraInfo();
    SendInput(1, &m_input, sizeof(INPUT));
}

void VirtualKeyboard::keyUp(WORD key)
{
    m_input.ki.wVk = key;
    m_input.ki.wScan = MapVirtualKey(m_input.ki.wVk, 0);

    if (key==VK_RETURN)
    {
        m_input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP; // Enterキーの場合のみ必要
    }
    else
    {
        m_input.ki.dwFlags = KEYEVENTF_KEYUP;
    }

    m_input.ki.dwExtraInfo = GetMessageExtraInfo();
    SendInput(1, &m_input, sizeof(INPUT));
}
