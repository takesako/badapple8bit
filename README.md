[English](#english) | [日本語](#日本語)

<a id="english"></a>

# badapple8bit

Play **Bad Apple!!** in a terminal using an 8-bit-style PAV animation and MML-generated audio.

The video is stored in the lightweight PAV (Palette Animation Video) format, and the audio is generated from MML.

## How to Run

Clone the repository:

```sh
git clone https://github.com/takesako/badapple8bit.git
cd badapple8bit
```

Convert the MML file into a WAV file:

```sh
cc mml2wav.c -o mml2wav
./mml2wav badapple8bit.mml badapple8bit.wav
```

Play the PAV animation with the generated audio:

```sh
cc play_pav.c -o play_pav
./play_pav badapple236.pav badapple8bit.wav
```

## Limitations

- Tested on macOS using the integrated terminal in Visual Studio Code.
- The macOS standard Terminal app may not render the animation correctly due to differences in Unicode block character rendering.
- Audio playback currently uses the macOS `afplay` command. Linux and WSL can also be supported by replacing the `afplay` command in `play_pav.c` with an appropriate audio playback command.

---

<a id="日本語"></a>

# badapple8bit

**Bad Apple!!** を、8-bit風のPAVアニメーションとMMLから生成した音声でターミナル再生します。

映像には軽量なPAV（Palette Animation Video）形式を使用し、音声はMMLから生成します。

## 実行方法

リポジトリをクローンします。

```sh
git clone https://github.com/takesako/badapple8bit.git
cd badapple8bit
```

MMLファイルからWAVファイルを生成します。

```sh
cc mml2wav.c -o mml2wav
./mml2wav badapple8bit.mml badapple8bit.wav
```

生成した音声と一緒にPAVアニメーションを再生します。

```sh
cc play_pav.c -o play_pav
./play_pav badapple236.pav badapple8bit.wav
```

## 制限

- macOS上のVisual Studio Code内蔵ターミナルで動作確認しています。
- macOS標準の「ターミナル」では、Unicode block characters の描画の違いにより、アニメーションの表示が崩れる場合があります。
- 音声再生には現在macOSの `afplay` コマンドを使用しています。`play_pav.c` 内の `afplay` を環境に適した音声再生コマンドへ変更すれば、LinuxやWSLでも再生できます。
