
class LedPwmEsp32 : public ILedDevice
{
    //const int ledPins[16] = { 2,  4,  5, 18, 19, 21, 22, 23,   // main row
    //                         14, 27, 26, 25, 33, 32, 12, 13};  // extension row

    const int PwmFrequency = 500;
    const int PwmBits = 8;
    const int PwmMax = 256;

    int _pinCount;
    int _pinNumbers[4];
    int _channelNumbers[4];

    static int _nextChannelToUse;

public:
    LedPwmEsp32(int pinCount, int pin1, int pin2, int pin3, int pin4)
    {
        Serial.println(">LedPWM constructor");

        _pinCount = pinCount;
        _pinNumbers[0] = pin1;
        _pinNumbers[1] = pin2;
        _pinNumbers[2] = pin3;
        _pinNumbers[3] = pin4;

        for (int i = 0; i < pinCount; i++)
        {
            _channelNumbers[i] = _nextChannelToUse + i;
            Serial.print("Assigning pin: ");
            Serial.print(_pinNumbers[i]);
            Serial.print(" to channel ");
            Serial.println(_channelNumbers[i]);

            if (_pinNumbers[i] != -1)
            {
                ledcSetup(_channelNumbers[i], PwmFrequency + i, PwmBits);
                ledcAttachPin(_pinNumbers[i], _channelNumbers[i]);
            }
        }
        _nextChannelToUse += pinCount;

        Serial.println("<LedPWM constructor");
    }

    ~LedPwmEsp32()
    {
        Serial.println("LedPwm Free");
    }

    virtual void FreeDevice()
    {
    }

    void UpdateLed(int channel, Variable *pBrightness)
    {
        int brightnessPwmValue = PwmMax * pBrightness->GetValueFloat(0);

        // Translate the global channel number to the group channel number...

        ledcWrite(_channelNumbers[channel], brightnessPwmValue);
        if (channel == 100)
        {
            Serial.print("PWM: ");
            Serial.print(_channelNumbers[channel]);
            Serial.print(" ");
            Serial.print(pBrightness->GetValueFloat(0));
            Serial.print(": ");
            Serial.println(brightnessPwmValue);
        }
    }

#if fred
    void UpdateLed(LedState *pLedState)
    {
        int brightnessPwmValue = PwmMax * pLedState->GetBrightness()->GetValueFloat(0);

        // Translate the global channel number to the group channel number...

        ledcWrite(_channelNumbers[pLedState->GetChannel()], brightnessPwmValue);
        if (pLedState->GetChannel() == 100)
        {
            Serial.print("PWM: ");
            Serial.print(_channelNumbers[pLedState->GetChannel()]);
            Serial.print(" ");
            Serial.print(pLedState->GetBrightness()->GetValueFloat(0));
            Serial.print(": ");
            Serial.println(brightnessPwmValue);
        }
    }
#endif
    void Show()
    {
    }
};

int LedPwmEsp32::_nextChannelToUse = 0;