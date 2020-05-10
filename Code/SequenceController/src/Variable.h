class Variable
{
    static const int ValuesPerVariable = 4;
    static const int MaxVariableNameLength = 64;
    static const int MaxStringVariableLength = 128;

    VariableData *_pVariableData;

public:
    Variable()
    {
        _pVariableData = VariableStore::VariableStoreInstance.GetFreePoolEntry();
        _pVariableData->_variableName[0] = '\0';
        _pVariableData->_stringValue[0] = '\0';
        _pVariableData->_valueCount = 0;
    }

    Variable(int value) : Variable()
    {
        _pVariableData->_value[0] = (float)value;
        _pVariableData->_valueCount = 1;
        _pVariableData->_stackLevel = 0;
    }

    Variable(float value) : Variable()
    {
        _pVariableData->_value[0] = value;
        _pVariableData->_valueCount = 1;
        _pVariableData->_stackLevel = 0;
    }

    Variable(const char *pString) : Variable()
    {
        SetValue(pString);
    }

    Variable(const Variable &other)
    {
        // stack levels above zero mean that it's a program variable. Those variables may go away when we
        // delete stack levels, so we need to split it into a non-program variable.
        if (other._pVariableData->_stackLevel != 0)
        {
            _pVariableData = VariableStore::VariableStoreInstance.SplitOffEntry(other._pVariableData);
            other._pVariableData->_referenceCount++; // SplitOffEntry decremented this.
            _pVariableData->_stackLevel = 0;
            return;
        }

        _pVariableData = other._pVariableData;
        _pVariableData->_referenceCount++;
    }

    Variable &operator=(const Variable &other)
    {
        // stack levels above zero mean that it's a program variable. Those variables may go away when we
        // delete stack levels, so we need to split it into a non-program variable.
        if (_pVariableData->_stackLevel != other._pVariableData->_stackLevel)
        {
            _pVariableData->_referenceCount--; // no longer using the current variable...
            _pVariableData = VariableStore::VariableStoreInstance.SplitOffEntry(other._pVariableData);
            other._pVariableData->_referenceCount++; // SplitOffEntry decremented this.
            _pVariableData->_stackLevel = 0;
            return *this;
        }

        if (_pVariableData->_referenceCount != 0)
        {
            _pVariableData->_referenceCount--;
        }
        _pVariableData = other._pVariableData;
        _pVariableData->_referenceCount++;

        return *this;
    }

    ~Variable()
    {
        if (_pVariableData != 0)
        {
            _pVariableData->_referenceCount--;
        }
    }

    static Variable ParseFloat(const char *pCommand)
    {
        Variable variableNew;

        variableNew._pVariableData->_value[0] = (float)atof(pCommand);
        variableNew._pVariableData->_valueCount = 1;
        variableNew._pVariableData->_stackLevel = 0;
        ;

        return variableNew;
    }

    // Getters

    int GetValueInt() { return (int)_pVariableData->_value[0]; }

    int GetValueCount() { return _pVariableData->_valueCount; }

    float GetValueFloat(int index) 
    { 
        if (index >= _pVariableData->_valueCount)
        {
            return NAN;
        }

        return _pVariableData->_value[index]; 
    }

    const char *GetValueString()
    {
        return _pVariableData->_stringValue;
    }

    char *GetVariableName() { return _pVariableData->_variableName; }

    int GetStackLevel() { return _pVariableData->_stackLevel; }

    void Clear()
    {
        _pVariableData->_value[0] = 0.0;
        _pVariableData->_valueCount = 0;
        _pVariableData->_variableName[0] = '\0';
        _pVariableData->_stackLevel = 0;
    }

    static Variable Empty()
    {
        Variable variable;
        variable.SetToNan();
        return variable;
    }

    bool IsNan()
    {
        return isnan(_pVariableData->_value[0]);
    }

    void SplitVariableOnModify()
    {
        if (_pVariableData->_referenceCount > 1)
        {
            _pVariableData = VariableStore::VariableStoreInstance.SplitOffEntry(_pVariableData);
        }
    }

    // Setters: All setters must split if other variables are sharing data with us...

    void Increment(Variable increment)
    {
        SplitVariableOnModify();

        _pVariableData->_value[0] += increment.GetValueFloat(0);
    }

    void SetValue(int index, float value)
    {
        SplitVariableOnModify();

        if (index >= ValuesPerVariable)
        {
            return;
        }

        if (index + 1 > _pVariableData->_valueCount)
        {
            _pVariableData->_valueCount = index + 1;
        }

        _pVariableData->_value[index] = value;
    }

    void SetValue(const char *pString)
    {
        SplitVariableOnModify();

        _pVariableData->_valueCount = 0;

        SafeString::StringCopy(_pVariableData->_stringValue, pString, sizeof(_pVariableData->_stringValue));
    }

    void SetVariableName(const char *pVariableName)
    {
        SplitVariableOnModify();

        if (strlen(pVariableName) >= MaxVariableNameLength)
        {
            Serial.println("Variable too long");
            return;
        }

        strcpy(_pVariableData->_variableName, pVariableName);
    }

    void SetStackLevel(int stackLevel)
    {
        SplitVariableOnModify();

        _pVariableData->_stackLevel = stackLevel;
    }

    void SetToNan()
    {
        SplitVariableOnModify();

        _pVariableData->_value[0] = NAN;
        _pVariableData->_valueCount = 0;
    }

    VariableData *TestOnlyGetVariableData()
    {
        return _pVariableData;
    }
};