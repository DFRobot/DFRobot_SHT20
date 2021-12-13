/*!
 * @file  DFRobot_SHT20.h
 * @brief  Define infrastructure of DFRobot_SHT20 class
 * @details  可以通过这个库驱动SHT20, 可获取温湿度
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [Zhangjiawei](jiawei.zhang@dfrobot.com)
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-12-03
 * @url  https://github.com/DFRobot/DFRobot_SHT20
 */
#ifndef __DFRobot_SHT20_H__
#define __DFRobot_SHT20_H__

#include <Arduino.h>
#include <Wire.h>

// #define ENABLE_DBG   //!< 打开这个宏, 可以看到程序的详细运行过程
#ifdef ENABLE_DBG
  #define DBG(...) {Serial.print("[");Serial.print(__FUNCTION__); Serial.print("(): "); Serial.print(__LINE__); Serial.print(" ] "); Serial.println(__VA_ARGS__);}
#else
  #define DBG(...)
#endif

#define ERROR_I2C_TIMEOUT                     998
#define ERROR_BAD_CRC                         999
#define SHT20_I2C_ADDR                        0x40

#define TRIGGER_TEMP_MEASURE_HOLD             0xE3
#define TRIGGER_HUMD_MEASURE_HOLD             0xE5
#define TRIGGER_TEMP_MEASURE_NOHOLD           0xF3
#define TRIGGER_HUMD_MEASURE_NOHOLD           0xF5
#define WRITE_USER_REG                        0xE6
#define READ_USER_REG                         0xE7
#define SOFT_RESET                            0xFE
#define USER_REGISTER_RESOLUTION_MASK         0x81
#define USER_REGISTER_RESOLUTION_RH12_TEMP14  0x00
#define USER_REGISTER_RESOLUTION_RH8_TEMP12   0x01
#define USER_REGISTER_RESOLUTION_RH10_TEMP13  0x80
#define USER_REGISTER_RESOLUTION_RH11_TEMP11  0x81
#define USER_REGISTER_END_OF_BATTERY          0x40
#define USER_REGISTER_HEATER_ENABLED          0x04
#define USER_REGISTER_DISABLE_OTP_RELOAD      0x02

#define MAX_WAIT                              100
#define DELAY_INTERVAL                        10
#define SHIFTED_DIVISOR                       0x988000
#define MAX_COUNTER                           (MAX_WAIT/DELAY_INTERVAL)

class DFRobot_SHT20
{
public:
  /**
   * @fn DFRobot_SHT20
   * @brief 构造函数
   * @param pWire Wire.h里定义了Wire对象, 因此使用&Wire就能够指向并使用Wire中的方法
   * @param sht20Addr SHT20的i2c通信地址
   * @return None
   */
  DFRobot_SHT20(TwoWire *pWire=&Wire, uint8_t sht20Addr=SHT20_I2C_ADDR);

  /**
   * @fn initSHT20
   * @brief 初始化函数
   * @return None
   */
  void initSHT20(void);

  /**
   * @fn readHumidity
   * @brief 读取空气湿度测量数据
   * @return 返回float类型的空气湿度测量数据, 单位: %
   */
  float readHumidity(void);

  /**
   * @fn readTemperature
   * @brief 读取温度测量数据
   * @return 返回float类型的温度测量数据, 单位: C
   */
  float readTemperature(void);

  /**
   * @fn checkSHT20
   * @brief 检测SHT20当前状态信息
   * @n 状态信息包括: End of battery, Heater enabled, Disable OTP reload
   * @n 检测结果包括: yes, no
   * @return None
   */
  void checkSHT20(void);

protected:
  /**
   * @fn setResolution
   * @brief 设置sht20的测量分辨率
   * @param resBits SHT20的测量分辨率模式
   * @return None
   */
  void setResolution(byte resBits);

  /**
   * @fn readUserRegister
   * @brief 读用户寄存器
   * @return 读到的字节
   */
  byte readUserRegister(void);

  /**
   * @fn writeUserRegister
   * @brief 写用户寄存器
   * @param val 写入的字节
   * @return None
   */
  void writeUserRegister(byte val);

  /**
   * @fn showReslut
   * @brief 打印SHT20当前状态信息的检测结果
   * @param prefix 要打印的状态信息字符串
   * @param val 要打印的状态信息结果
   * @return None
   */
  void showReslut(const char *prefix, int val);

  /**
   * @fn checkCRC
   * @brief 计算并校验crc
   * @param message_from_sensor 从传感器读到的数据
   * @param check_value_from_sensor 从传感器读到的校验值
   * @return 返回校验结果, 为零表示校验通过
   */
  byte checkCRC(uint16_t message_from_sensor, uint8_t check_value_from_sensor);

  /**
   * @fn readValue
   * @brief 通过I2C总线读取寄存器值
   * @param cmd 发送的读取命令
   * @return 返回读取的16位数据
   */
  uint16_t readValue(byte cmd);

private:
  uint8_t _addr;   // SHT20的I2C通信地址
  TwoWire *_pWire;   // I2C通信方式的指针
};

#endif