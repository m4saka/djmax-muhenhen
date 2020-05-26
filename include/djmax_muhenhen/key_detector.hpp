#pragma once

// キーの状態を調べるクラス
class KeyDetector
{
private:
    // キー番号
    //   リファレンスによればGetAsyncKeyStateの引数はINPUT構造体とは異なり
    //   WORD型ではなくint型らしいのでint型にしています
    const int m_key;

public:
    // コンストラクタ(調べたいキー番号を指定)
    explicit KeyDetector(int key);

    // キーが押下されているかどうかを返す
    bool isPressed() const;
};
