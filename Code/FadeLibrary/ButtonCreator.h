class ButtonCreator : public IButtonCreator
{
public:
    virtual IButton *Create(const char *pButtonType, int pin, int parameter1)
    {
      return 0;
#if fred

        if (strcmp(pButtonType, "TOUCH") == 0)
        {
            return new TouchButton(pin, parameter1);
        }

        return 0;
#endif
    }
};