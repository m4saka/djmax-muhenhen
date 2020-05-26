# DJMAX向け無変換/変換キー変換ツール
DJMAX用に無変換/変換キーの入力を左Shift/右Shiftキーに変換するツールです。

## 実行ファイルのダウンロード
- こちらからダウンロードできます
    - https://mz-kb.com/tool/djmax-muhenhen/

## 対応OS
- Windowsのみ

## コンパイル方法
1. CMakeとVisual Studio 2019をインストールします
2. cmake.exeおよびdevenv.exe(Visual Studio)のディレクトリにそれぞれパスを通します
3. コマンドプロンプト上で以下を実行します
    ```
    mkdir build
    cd build
    cmake ..
    devenv /build Release djmax_muhenhen.sln
    ```
    実行すると、`build/Release`ディレクトリ内に`djmax_muhenhen.exe`が生成されます
    (slnファイルをVisual Studioで開いてビルドしても構いません)

## ライセンス
- MIT License
