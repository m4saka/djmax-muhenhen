#include "djmax_muhenhen/key_detector.hpp"
#include <Windows.h>
#include <winuser.h> // GetAsyncKeyState

KeyDetector::KeyDetector(int key)
    : m_key(key)
{
}

bool KeyDetector::isPressed() const
{
    return GetAsyncKeyState(m_key) != 0;
}
