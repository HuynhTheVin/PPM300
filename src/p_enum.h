/*
 * p_enum.h
 *
 *  Created on: 2023/06/16
 *      Author: VINH-NT
 */

#ifndef P_ENUM_H_
#define P_ENUM_H_

enum RUNMD
{ /* 現在モード                            */

  UNTENMD,   /* 運転モード                        */
  STANDBYMD, /* 無表示モード                          */
  TIMEMD,    /* 時刻管理                        */
  JOSOMD,    /* 除霜設定管理                        */
  SPECALMD,  /* 詳細パラメータモード            */
  CHECKMD,   /* 点検履歴モード                        */
  CHECKRYMD, /* リレー累積リセットモード              */
  FACTRYMD,  /* ファクトリーモード               	*/
  CLERAMD,   /* データクリアモード               	*/
  SELFMD,    /* 自己診断モード                        */
  AJUSTMD    /* 調整モード                            */
};
enum UNTENMD
{
  REITOMD, /* 冷凍 */
  REITOZOUMD  /* 冷凍・冷蔵 */
};
 enum KOUTEIMD
{           /* 工程モード                            */
  // KIYUMD,   /* 急速冷却運転モード                    */
  // REITOMD,  /* 冷凍・冷蔵運転モード                  */
  // KAITOMD,  /* 解凍運転モード                        */
  // YONETUMD, /* 予熱運転モード                        */
  // HOIROMD   /* ホイロ運転モード                      */
};
enum SETMD
{             /* 設定モード                            */
  NOTMD,      /* 設定モードでない                      */
  SETDATAMD,  /* 時間、温度、湿度設定モード            */
  SETDATAMD2, /* 時間、温度、湿度設定モード            */
  OVENMD      /* オーブン開始時間 時間設定モード       */
};

#endif /* P_ENUM_H_ */
