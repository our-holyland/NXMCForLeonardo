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
static uint16_t idx = 0;
static uint32_t timeoutCnt = 0;
static uint8_t nxFrameLen = 0;

void setup() {
  Serial1_Init();//RX←0でのシリアル通信
  Controller_Init();//コントローラーの準備
  Keyboard_Init();//キーボードの初期化
}

void loop() {
  while (Serial1.available()) {
    timeoutCnt = 1;
    uint8_t c = 0;
    c = Serial1.read();

    if (c == 0xaa) {
      if (idx == 0) {
        isNx2 = true;
        isText = false;
        nxFrameLen = 10;
      }
    } else if (c == 0xab) {
      if (idx == 0) {
        isNx2 = true;
        isText = false;
        nxFrameLen = 11;
      }
    } else if (c == '\"') {
      if (idx == 0) {
        isText = true;
        isNx2 = false;
      }
    } else {
      if (idx == 0) {
        isNx2 = false;
        isText = false;
      }
    }

    if ((c != '\n' || isNx2 || isText) && idx < MAX_BUFFER)
      pc_report_str[idx++] = c;

    if ((c == '\r' && !isNx2 && !isText) || (isNx2 && idx == nxFrameLen) || (isText && c == '\n' && pc_report_str[idx - 2] == '\r' && pc_report_str[idx - 3] == '"')) {
      pc_report_str[idx++] = '\0';
      idx = 0;
      timeoutCnt = 0;
      ParseLine(pc_report_str);
      if (!isText && proc_state == PC_CALL) sendReportOnly(pc_report);
      memset(pc_report_str, 0, sizeof(pc_report_str));
    }
  }
  if (timeoutCnt > 1000) {
    idx = 0;
    timeoutCnt = 0;
  } else {
    if (timeoutCnt > 0) timeoutCnt++;
  }
  //状態に応じて切り替える
  //switch (ProgState)
  //{
  //  case STATE1:
  //    SwitchFunction();
  //    break;
  //  default:
  //    /* バグ回避を兼ねて状態の初期化を行う */
  //    ProgState = STATE0;
  //    break;
  //}
}

//データが利用可能な時に呼び出される関数(Serial1)
void serialEvent1()
{
  // one character comes at a time
  //char c = Serial1.read();

  //if (c == '\n')
  //{
  //  pc_report_str[idx++] = c;
  //  pc_report_str[idx++] = '\0';
  //  ParseLine(pc_report_str);
  //  idx = 0;
  //  memset(pc_report_str, 0, sizeof(pc_report_str));
  //  ProgState = STATE1;
  //}
  //else if (idx < MAX_BUFFER)
  //{
  //  pc_report_str[idx++] = c;
  //}
}
