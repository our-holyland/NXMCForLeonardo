/*
     Nintendo Switchでキーボード(日本語 ローマ字入力)を使うためのプログラム(v01)
     (関数)
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
*/


/* インクルード */

//日本語キーボード
//https://qiita.com/nak435/items/bbe04300c67c37febb7e
#define HID_CUSTOM_LAYOUT
#define LAYOUT_JAPANESE
#include "HID-Project.h"

//プログラムで使う各種定義
#include "UseKeyboardForNintendoSwitch_Func.h"

#define	CASE_WRITEKEY(n)		\
    case (n):				\
      BootKeyboard.press((n));		\
      delay(30);			\
      BootKeyboard.release((n));	\
      delay(30);			\
      break

#define	CASE_PRESSKEY(n)		\
    case (n):				\
      BootKeyboard.press((n));		\
      delay(30);			\
      break

#define	CASE_RELEASEKEY(n)		\
    case (n):				\
      BootKeyboard.release((n));	\
      delay(30);			\
      break

//キーボード用の初期化を行う関数
void Keyboard_Init()
{
  BootKeyboard.begin();
  BootKeyboard.releaseAll();

  delay(500);
}

//キーボードで対応したcharをタイプする関数
void BootKeyboard_Write(uint32_t ch)
{
  BootKeyboard.press(ch);
  delay(30);
  BootKeyboard.release(ch);
  delay(30);
}
//キーボードで対応したcharを押し続ける関数
void BootKeyboard_Press(uint32_t ch)
{
  BootKeyboard.press(ch);
  delay(30);
}
//キーボードで対応したcharを離す関数
void BootKeyboard_Release(uint32_t ch)
{
  BootKeyboard.release(ch);
  delay(30);
}
void Type_string(char* str)
{
  //先頭の「"」を無視する
  int len = 1;
  char* t_str = str;
  while (true)
  {
    if (t_str[len] == '\0')
    {
      break;
    }
    else if((t_str[len] == '\"')&&(t_str[len+1] == '\r')&&(t_str[len+2] == '\n'))
    {
      break;
    }
    else
    {
      BootKeyboard_Write(t_str[len]);
    }
    len++;
  }
}

void Type_stringBySerialCommunication()
{
  /* シリアル通信で受け取ったデータの先頭末尾にある「"」を削除 */
  
  Type_string(chrread);
  ResetDirections();
  sendReportOnly(pc_report);//解析したデータをSwitchに送信
  delay(40);
}

//キーボードで対応したcharをタイプする関数
void BootKeyboard_WriteSpecialKey(uint32_t mode)
{
  switch(mode){
    CASE_WRITEKEY(KEY_JP_HANZEN);
    CASE_WRITEKEY(KEY_JP_BACKSLASH);
    CASE_WRITEKEY(KEY_JP_HIRAGANA);
    CASE_WRITEKEY(KEY_JP_YEN);
    CASE_WRITEKEY(KEY_JP_HENKAN);
    CASE_WRITEKEY(KEY_JP_MUHENKAN);
    CASE_WRITEKEY(KEY_ENTER);
    CASE_WRITEKEY(KEY_BACKSPACE);
    CASE_WRITEKEY(KEY_DELETE);
    CASE_WRITEKEY(KEY_UP_ARROW);
    CASE_WRITEKEY(KEY_DOWN_ARROW);
    CASE_WRITEKEY(KEY_LEFT_ARROW);
    CASE_WRITEKEY(KEY_RIGHT_ARROW);
    default:
      BootKeyboard_Write(mode);
      break;
  }
}
//キーボードで対応したcharを押し続ける関数
void BootKeyboard_PressSpecialKey(uint32_t mode)
{
  switch(mode){
    CASE_PRESSKEY(KEY_JP_HANZEN);
    CASE_PRESSKEY(KEY_JP_BACKSLASH);
    CASE_PRESSKEY(KEY_JP_HIRAGANA);
    CASE_PRESSKEY(KEY_JP_YEN);
    CASE_PRESSKEY(KEY_JP_HENKAN);
    CASE_PRESSKEY(KEY_JP_MUHENKAN);
    CASE_PRESSKEY(KEY_ENTER);
    CASE_PRESSKEY(KEY_BACKSPACE);
    CASE_PRESSKEY(KEY_DELETE);
    CASE_PRESSKEY(KEY_UP_ARROW);
    CASE_PRESSKEY(KEY_DOWN_ARROW);
    CASE_PRESSKEY(KEY_LEFT_ARROW);
    CASE_PRESSKEY(KEY_RIGHT_ARROW);
    default:
      BootKeyboard_Press(mode);
      break;
  }
}

//キーボードで対応したcharを離す関数
void BootKeyboard_ReleaseSpecialKey(uint32_t mode)
{
  switch(mode){
    CASE_RELEASEKEY(KEY_JP_HANZEN);
    CASE_RELEASEKEY(KEY_JP_BACKSLASH);
    CASE_RELEASEKEY(KEY_JP_HIRAGANA);
    CASE_RELEASEKEY(KEY_JP_YEN);
    CASE_RELEASEKEY(KEY_JP_HENKAN);
    CASE_RELEASEKEY(KEY_JP_MUHENKAN);
    CASE_RELEASEKEY(KEY_ENTER);
    CASE_RELEASEKEY(KEY_BACKSPACE);
    CASE_RELEASEKEY(KEY_DELETE);
    CASE_RELEASEKEY(KEY_UP_ARROW);
    CASE_RELEASEKEY(KEY_DOWN_ARROW);
    CASE_RELEASEKEY(KEY_LEFT_ARROW);
    CASE_RELEASEKEY(KEY_RIGHT_ARROW);
    default:
      BootKeyboard_Release(mode);
      break;
  }
}