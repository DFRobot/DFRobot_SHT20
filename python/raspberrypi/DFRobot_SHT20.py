# -*- coding: utf-8 -*
'''!
  @file  DFRobot_SHT20.h
  @brief  Define infrastructure of DFRobot_SHT20 class
  @details  可以通过这个库驱动SHT20, 可获取温湿度
  @copyright  Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license  The MIT License (MIT)
  @author  [Zhangjiawei](jiawei.zhang@dfrobot.com)
  @maintainer  [qsjhyy](yihuan.huang@dfrobot.com)
  @version  V1.0
  @date  2021-12-03
  @url  https://github.com/DFRobot/DFRobot_SHT20
'''
import sys
import time

import smbus

import logging
from ctypes import *


logger = logging.getLogger()
# logger.setLevel(logging.INFO)   # Display all print information
logger.setLevel(logging.FATAL)   # If you don’t want to display too many prints, only print errors, please use this option
ph = logging.StreamHandler()
formatter = logging.Formatter("%(asctime)s - [%(filename)s %(funcName)s]:%(lineno)d - %(levelname)s: %(message)s")
ph.setFormatter(formatter) 
logger.addHandler(ph)


## SHT20 I2C通信错误码
ERROR_I2C_TIMEOUT = 998
## SHT20 crc校验错误码
ERROR_BAD_CRC     = 999
## SHT20 I2C通信地址
SHT20_I2C_ADDR    = 0x40

# SHT20 通信命令
TRIGGER_TEMP_MEASURE_HOLD            = 0xE3
TRIGGER_HUMD_MEASURE_HOLD            = 0xE5
TRIGGER_TEMP_MEASURE_NOHOLD          = 0xF3
TRIGGER_HUMD_MEASURE_NOHOLD          = 0xF5
WRITE_USER_REG                       = 0xE6
READ_USER_REG                        = 0xE7
SOFT_RESET                           = 0xFE
USER_REGISTER_RESOLUTION_MASK        = 0x81
USER_REGISTER_RESOLUTION_RH12_TEMP14 = 0x00
USER_REGISTER_RESOLUTION_RH8_TEMP12  = 0x01
USER_REGISTER_RESOLUTION_RH10_TEMP13 = 0x80
USER_REGISTER_RESOLUTION_RH11_TEMP11 = 0x81
USER_REGISTER_END_OF_BATTERY         = 0x40
USER_REGISTER_HEATER_ENABLED         = 0x04
USER_REGISTER_DISABLE_OTP_RELOAD     = 0x02

MAX_WAIT        = 100
DELAY_INTERVAL  = 10
SHIFTED_DIVISOR = 0x988000
MAX_COUNTER     = 10


class DFRobot_SHT20(object):
  '''!
    @brief 定义DFRobot_SHT20基类
    @details 用于驱动温湿度传感器
  '''

  def __init__(self, i2c_addr=SHT20_I2C_ADDR, bus=1):
    '''!
      @brief Module I2C communication init
      @param i2c_addr I2C通信地址
      @param bus I2C总线
    '''
    self._addr = i2c_addr
    self._i2c = smbus.SMBus(bus)

  @property
  def read_humidity(self):
    '''!
      @brief 读取空气湿度测量数据
      @return 返回float类型的空气湿度测量数据, 单位: %
    '''
    buf = self._read_reg(TRIGGER_HUMD_MEASURE_HOLD, 2)
    humidity = ((buf[0] << 8) | buf[1]) * (125.0 / 65536.0) - 6.0
    return humidity

  @property
  def read_temperature(self):
    '''!
      @brief 读取温度测量数据
      @return 返回float类型的温度测量数据, 单位: C
    '''
    buf = self._read_reg(TRIGGER_TEMP_MEASURE_HOLD, 2)
    temperature = ((buf[0] << 8) | buf[1]) * (175.72 / 65536.0) - 46.85
    return temperature

  @property
  def check_SHT20(self):
    '''!
      @brief 检测SHT20当前状态信息
      @n 状态信息包括: End of battery, Heater enabled, Disable OTP reload
      @n 检测结果包括: yes, no
    '''
    status = self._read_reg(READ_USER_REG, 1)[0]
    self._show_reslut("End of battery: ", status & USER_REGISTER_END_OF_BATTERY)
    self._show_reslut("Heater enabled: ", status & USER_REGISTER_HEATER_ENABLED)
    self._show_reslut("Disable OTP reload: ", status & USER_REGISTER_DISABLE_OTP_RELOAD)

  def _show_reslut(self, str, val):
    '''!
      @brief 打印SHT20当前状态信息的检测结果
      @param str 要打印的状态信息字符串
      @param val 要打印的状态信息结果
    '''
    print(str, end='')
    if val:
      print("yes")
    else:
      print("no")

  def _read_reg(self, reg, length):
    '''!
      @brief read the data from the register
      @param reg register address
      @param length read data length
      @return read data list
    '''
    return self._i2c.read_i2c_block_data(self._addr, reg, length)
