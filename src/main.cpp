#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <iostream>
#include <vector>
#include <winuser.h> // GetAsyncKeyState,INPUT

class VirtualKeyboard
{
private:
    INPUT m_input;

public:
    VirtualKeyboard()
    {
        m_input.type = INPUT_KEYBOARD;
        m_input.ki.time = 0;
    }

    void keyDown(WORD key)
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

    void keyUp(WORD key)
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
};

class KeyDetector
{
private:
    const int m_key;

public:
    explicit KeyDetector(int key)
        : m_key(key)
    {
    }

    bool isPressed() const
    {
        return GetAsyncKeyState(m_key) != 0;
    }
};

class KeyConverter
{
private:
    const KeyDetector m_srcKeyDetector;
    const WORD m_dstKey;
    const std::shared_ptr<VirtualKeyboard> m_virtualKeyboard;

public:
    KeyConverter(int srcKey, int dstKey, std::shared_ptr<VirtualKeyboard> virtualKeyboard)
        : m_srcKeyDetector(srcKey)
        , m_dstKey(dstKey)
        , m_virtualKeyboard(virtualKeyboard)
    {
    }

    ~KeyConverter()
    {
        m_virtualKeyboard->keyUp(m_dstKey);
    }

    bool update()
    {
        if (m_srcKeyDetector.isPressed())
        {
            m_virtualKeyboard->keyDown(m_dstKey);
            return true;
        }
        else
        {
            m_virtualKeyboard->keyUp(m_dstKey);
            return false;
        }
    }
};

int main()
{
    auto virtualKeyboard = std::make_shared<VirtualKeyboard>();

    std::vector<KeyConverter> keyConverters = {
        KeyConverter(VK_NONCONVERT, VK_LSHIFT, virtualKeyboard),
        KeyConverter(VK_CONVERT, VK_RSHIFT, virtualKeyboard),
    };
    std::cout <<
        "\n"
        "**動作中** 無変換/変換キーを左Shift/右Shiftに変換しています\n"
        "\n"
        "  このウィンドウを閉じると終了します"
        << std::endl;

    while (true)
    {
        for (auto & conv : keyConverters)
        {
            conv.update();
        }

        timeBeginPeriod(1);
        Sleep(1);
        timeEndPeriod(1);
    }

    return 0;
}
