class FunctionDefinition
{
public:
	static const int FunctionNameMax = 128;

	FunctionDefinition()
	{
		SerialNumberStart = 0;
		SerialNumberEnd = 0;
		Name[0] = '\0';
	}

	FunctionDefinition(const char* pName, int serialNumberStart)
	{
		strcpy(Name, pName);
		SerialNumberStart = serialNumberStart;
		SerialNumberEnd = -1;
	}

	char Name[FunctionNameMax];
	int SerialNumberStart;
	int SerialNumberEnd;
};

class FunctionStore
{
	static const int FunctionMaxCount = 10;

	int _functionDefinitionCount = 0;
	FunctionDefinition _functionDefinitions[FunctionMaxCount];

	bool _isCurrentlyParsingFunction;
	FunctionDefinition* _pCurrentFunctionDefinition;

public:
	FunctionStore()
	{
		_isCurrentlyParsingFunction = false;
		_pCurrentFunctionDefinition = 0;
	}

	bool GetIsCurrentlyParsingFunction()
	{
		return _isCurrentlyParsingFunction;
	}

	int GetCount() { return _functionDefinitionCount; }

	void DefineStart(const char* pFunctionName, ParseErrors* pParseErrors, int serialNumberStart)
	{
		if (_functionDefinitionCount == FunctionMaxCount)
		{
			pParseErrors->AddError("Function: ", "too many defined", serialNumberStart);
			return;
		}

		_isCurrentlyParsingFunction = true;

		FunctionDefinition* pLookup = Lookup(pFunctionName);
		if (pLookup != 0)
		{
			return;
		}

		FunctionDefinition* pCurrent = _functionDefinitions + _functionDefinitionCount;
		if (strlen(pFunctionName) >= FunctionDefinition::FunctionNameMax)
		{
			pParseErrors->AddError("Function: ", "name too long", serialNumberStart);
		}

		strcpy(pCurrent->Name, pFunctionName);
		pCurrent->SerialNumberStart = serialNumberStart;
		pCurrent->SerialNumberEnd = -1;

		_functionDefinitionCount++;

		_pCurrentFunctionDefinition = pCurrent;
	}

	void DefineEnd(int serialNumberEnd)
	{
		_isCurrentlyParsingFunction = false;

		if (_pCurrentFunctionDefinition == 0)
		{
			return;
		}

		_pCurrentFunctionDefinition->SerialNumberEnd = serialNumberEnd;
		_pCurrentFunctionDefinition = 0;
	}

	FunctionDefinition* Lookup(const char* pFunctionName)
	{
		FunctionDefinition* pCurrent = _functionDefinitions;

		for (int i = 0; i < _functionDefinitionCount; i++)
		{
			if (strcmp(pFunctionName, pCurrent->Name) == 0)
			{
				return pCurrent;
			}
			pCurrent++;
		}

		return 0;
	}
};