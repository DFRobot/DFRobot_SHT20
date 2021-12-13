/*!
 * @file  getHumidityAndTemperature.ino
 * @brief  DFRobot's SHT20 Humidity And Temperature Sensor Module
 * @details  This example demonstrates how to read the user registers to display resolution and other settings.
 * @n  Uses the SHT20 library to display the current humidity and temperature.
 * @n  Open serial monitor at 9600 baud to see readings.
 * @n  Errors 998 if not sensor is detected. Error 999 if CRC is bad.
 * @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license  The MIT License (MIT)
 * @author  [Zhangjiawei](jiawei.zhang@dfrobot.com)
 * @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
 * @version  V1.0
 * @date  2021-12-03
 * @url  https://github.com/DFRobot/DFRobot_SHT20
 */
#include "DFRobot_SHT20.h"

/**
 * Hardware Connections:
 * -VCC = 3.3V
 * -GND = GND
 * -SDA = A4 (use inline 330 ohm resistor if your board is 5V)
 * -SCL = A5 (use inline 330 ohm resistor if your board is 5V)
 */
DFRobot_SHT20 sht20;

void setup()
{
  Serial.begin(115200);

  // Init SHT20 Sensor
  sht20.initSHT20();
  delay(100);
  Serial.println("Sensor init finish!");

  /**
   * 检测SHT20当前状态信息
   * 状态信息包括: End of battery, Heater enabled, Disable OTP reload
   * 检测结果包括: yes, no
   */
  sht20.checkSHT20();
}

void loop()
{
  /**
   * 读取空气湿度测量数据
   * 返回float类型的空气湿度测量数据, 单位: %
   */
  float humd = sht20.readHumidity();

  /**
   * 读取温度测量数据
   * 返回float类型的温度测量数据, 单位: C
   */
  float temp = sht20.readTemperature();

  Serial.print("Time:");
  Serial.print(millis());   // 从Arduino获取系统时间
  Serial.print(" Temperature:");
  Serial.print(temp, 1);   // 只打印一位小数
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humd, 1);   // 只打印一位小数
  Serial.print("%");
  Serial.println();

  delay(1000);
}
