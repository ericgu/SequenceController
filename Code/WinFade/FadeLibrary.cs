﻿using System.Runtime.InteropServices;

namespace WinFade
{
  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void SerialNewTextAvailable(string value);

  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void CreateNewLedDeviceDelegate(string ledType, int ledCount, int pin1, int pin2, int pin3, int pin4);

  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  unsafe public delegate void LedUpdatedDelegate(int ledGroupNumber, int channel, int cycleCount, int brightnessCount, float brightness1, float brightness2, float brightness3, float brightness4);

  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  unsafe public delegate void LedUpdateCycleDoneDelegate();

  [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
  public delegate void ParseErrorDelegate(string message, int lineNumber);

  public class FadeLibrary
    {
      [DllImport("FadeLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
      public static extern int MyCFunc();

      [DllImport("FadeLibrary.dll", CallingConvention = CallingConvention.Cdecl)]
      public static extern int Run(string programText, 
                                    SerialNewTextAvailable serialNewTextAvailableCallback,
                                    CreateNewLedDeviceDelegate createNewLedDeviceCallback,
                                    LedUpdatedDelegate ledUpdatedDelegate,
                                    LedUpdateCycleDoneDelegate ledUpdateCycleDoneDelegate,
                                    ParseErrorDelegate parseErrorDelegate);

    }
}