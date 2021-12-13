# -*- coding: utf-8 -*
'''!
  @file  get_humidity_temperature.py
  @brief  DFRobot's SHT20 Humidity And Temperature Sensor Module
  @details  This example demonstrates how to read the user registers to display resolution and other settings.
  @n  Uses the SHT20 library to display the current humidity and temperature.
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [Zhangjiawei](jiawei.zhang@dfrobot.com)
  @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
  @version  V1.0
  @date  2021-12-03
  @url  https://github.com/DFRobot/DFRobot_SHT20
'''
from __future__ import print_function
import sys
import os
sys.path.append(os.path.dirname(os.path.dirname(os.path.dirname(os.path.realpath(__file__)))))

from DFRobot_SHT20 import *

'''
  # Module I2C communication init
  # i2c_addr I2C通信地址
  # bus I2C总线
'''
sensor = DFRobot_SHT20(i2c_addr = 0x40, bus = 1)


def setup():
  '''
    # 检测SHT20当前状态信息
    # 状态信息包括: End of battery, Heater enabled, Disable OTP reload
    # 检测结果包括: yes, no
  '''
  sensor.check_SHT20


def loop():
  '''
    # 读取空气湿度测量数据
    # 返回float类型的空气湿度测量数据, 单位: %
  '''
  print("Humidity : %.1f %%" %(sensor.read_humidity))

  '''
    # 读取温度测量数据
    # 返回float类型的温度测量数据, 单位: C
  '''
  print("Temperature : %.1f C" %(sensor.read_temperature))

  print()
  time.sleep(1)


if __name__ == "__main__":
  setup()
  while True:
    loop()
