/*
     Nintendo Switchでキーボード(日本語 ローマ字入力)を使うためのプログラム(v01)
     (プログラムで使う各種定義のファイル)
     半角英数、かな、カナ、ASCII準拠の記号(「！」～「～」)、全角記号(下記参照)
     ※1 :半角「'」、「"」、「\」を指定する際は、該当文字の前に「\」をつけてください
     ※2 :数字は半角で入力してください(半角数字と全角数字の区別がないため、半角数字のみ実装)

     ■入力不可の文字列
     　半角: "@" (「@」はSwitchの仕様上使えません)
     　全角: "ゔ", "ゕ", "ゖ", "ヷ", "ヸ", "ヹ", "ヺ"

     ■事前準備
     ①Arduino HID-Projectを日本語キーボードに対応する必要があります
     →　手順については以下を参照してください
     　　https://qiita.com/nak435/items/bbe04300c67c37febb7e

     ■やっておくといいこと
     ①NintendoSwitchControll-masterの以下の箇所を変更することにより処理が改善できます。
     　デフォルトであれば以下の位置にある「BUTTON_PUSHING_MSEC」を「100」→「40」に変更
     　C:\Users\**ユーザー名**\Documents\Arduino\libraries\NintendoSwitchControll-master\src\auto_command_util.cpp

     ■バージョン
     v00:プロトタイプ
     v01:初版
     v02:文字テーブル削除(Python側で実装)
*/
#ifndef UseKeyboardForNintendoSwitch_Func_h
#define UseKeyboardForNintendoSwitch_Func_h

/* プロトタイプ宣言 */
void Keyboard_Init();
void BootKeyboard_Write(uint32_t ch);
void BootKeyboard_Press(uint32_t ch);
void BootKeyboard_Release(uint32_t ch);
void BootKeyboard_WriteSpecialKey(uint32_t mode);
void BootKeyboard_PressSpecialKey(uint32_t mode);
void BootKeyboard_ReleaseSpecialKey(uint32_t mode);
#endif /* #ifndef UseKeyboardForNintendoSwitch_Func_h */
