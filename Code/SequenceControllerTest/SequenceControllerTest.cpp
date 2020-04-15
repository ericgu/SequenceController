// SequenceControllerTest.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"

//void delayMicroseconds(int delay) {}
//void vTaskDelay(int delay) {}
//int micros() { return 0; }

#include "Assert.h"
#include "SafeStringTest.h"
#include "Serial.h"
#include "TimeServices.h"
#include "MyRandom.h"
#include "StackWatcher.h"
#include "Instrumentation.h"
#include "Profiler.h"
#include "DelayerTest.h"
#include "SystemCallback.h"
#include "CommandTest.h"
#include "ListParserTest.h"
#include "ParseErrorsTest.h"
#include "CommandSourceTest.h"
#include "CommandFormatterTest.h"
#include "VariableTest.h"
#include "LedState.h"
#include "ILedDevice.h"
#include "ILedDeviceCreator.h"
#include "CommandResult.h"
#include "LedCommand.h"
#include "FunctionStoreTest.h"
#include "StackTest.h"
#include "IExecutionFlow.h"
#include "IExecutionContext.h"
#include "ExpressionTokenSourceTest.h"
#include "FunctionCaller.h"
#include "RDEvaluater.h"
#include "ExecutionContextTest.h"
#include "FunctionCallerTest.h"
#include "RDEvaluaterTest.h"
#include "CommandDecoderTest.h"
#include "LedManagerTest.h"
#include "CommandSourceSimulatorTest.h"
#include "ILedMessageHandler.h"
#include "ExecutionFlowTest.h"
#include "TimebaseTest.h"
#include "IntegrationTest.h"
#include "LoopTest.h"
#include "Settings.h"
#include "SupervisorTest.h"


int main()
{
	ExecutionContextTest::Run();

	SafeStringTest::Run();

	RDEvaluaterTest::Run();
	ExpressionTokenSourceTest::Run();

	DelayerTest::Run();
	LoopTest::Run();

	ExecutionFlowTest::Run();
	IntegrationTest::Run();

	CommandSourceSimulatorTest::Test();
	
	LedManagerTest::Run();
	TimebaseTest::Run();
	CommandSourceTest::Run();
	CommandDecoderTest::Run();

	VariableTest::Run();

	StackTest::Run();
	FunctionStoreTest::Run();

	ListParserTest::Run();
	CommandTest::Run();

	CommandFormatterTest::Run();

	ParseErrorsTest::Run();

	SupervisorTest::Run();

	FunctionCallerTest::Run();

	printf("%d assertions checked\n", Assert::GetAssertCount());

    return 0;
}

