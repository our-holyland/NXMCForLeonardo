//日本語キーボード
//https://qiita.com/nak435/items/bbe04300c67c37febb7e
#define HID_CUSTOM_LAYOUT
#define LAYOUT_JAPANESE
#include "HID-Project.h"

#include "Poke-ControllerForLeonardo_Func.h"
#include "UseKeyboardForNintendoSwitch_Func.h"
#include <SoftwareSerial.h>
#include "switch_controller_plus.h"
#include "auto_command_util_plus.h"

typedef enum
{
  STATE0,//シリアル通信受信→受信成功
  STATE1,//シリアル通信成功時
  STATE2,//判定
} LOOPSTATE;

LOOPSTATE LOOP_STATE;

static String str = "";
static String str_buff = "";
static char chrread[MAX_BUFFER];
static int ProgState = 0;

void setup() {
  Serial1_Init();//RX←0でのシリアル通信
  Controller_Init();//コントローラーの準備
  Keyboard_Init();//キーボードの初期化
}

void loop() {
  //状態に応じて切り替える
  switch (ProgState)
  {
    case STATE1:
      SwitchFunction();
      break;
    default:
      /* バグ回避を兼ねて状態の初期化を行う */
      ProgState = STATE0;
      break;
  }
}

//データが利用可能な時に呼び出される関数(Serial1)
void serialEvent1()
{
  // one character comes at a time
  char c = Serial1.read();

  if (c == '\n')
  {
    pc_report_str[idx++] = c;
    pc_report_str[idx++] = '\0';
    ParseLine(pc_report_str);
    idx = 0;
    memset(pc_report_str, 0, sizeof(pc_report_str));
    ProgState = STATE1;
  }
  else if (idx < MAX_BUFFER)
  {
    pc_report_str[idx++] = c;
  }
}
