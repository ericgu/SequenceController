#pragma once
#include "CommandSourceSimulator.h"

class CommandSourceSimulatorTest
{
	static void TestSingle()
	{
		CommandSourceSimulator commandSource;

		commandSource.AddCommand(Command("D 15 11,1.0", 0));

		Command command = commandSource.GetNextCommand();

		Assert::AreEqual("D 15 11,1.0", command.GetString());
	}

	static void TestMultiple()
	{
		CommandSourceSimulator commandSource;

		commandSource.AddCommand(Command("D 15 11,1.0", 0));
		commandSource.AddCommand(Command("D 5 15,0.5", 1));

		Command command = commandSource.GetNextCommand();
		Assert::AreEqual("D 15 11,1.0", command.GetString());
		Assert::AreEqual(0, command.GetSerialNumber());

		command = commandSource.GetNextCommand();
		Assert::AreEqual("D 5 15,0.5", command.GetString());
		Assert::AreEqual(1, command.GetSerialNumber());

		command = commandSource.GetNextCommand();
		Assert::AreEqual(-1, command.GetSerialNumber());
	}

	static void TestReset()
	{
		CommandSourceSimulator commandSource;

		commandSource.AddCommand(Command("D 15 11,1.0", 0));
		commandSource.AddCommand(Command("D 5 15,0.5", 1));
		commandSource.AddCommand(Command("D 9 9,0.5", 2));
		commandSource.AddCommand(Command("D 6 6,0.5", 3));

		Command command = commandSource.GetNextCommand();
		Assert::AreEqual("D 15 11,1.0", command.GetString());
		Assert::AreEqual(0, command.GetSerialNumber());

		command = commandSource.GetNextCommand();
		Assert::AreEqual("D 5 15,0.5", command.GetString());
		Assert::AreEqual(1, command.GetSerialNumber());

		command = commandSource.GetNextCommand();
		Assert::AreEqual("D 9 9,0.5", command.GetString());
		Assert::AreEqual(2, command.GetSerialNumber());

		commandSource.SetCommandToSerialNumber(1);

		command = commandSource.GetNextCommand();
		Assert::AreEqual("D 5 15,0.5", command.GetString());
		Assert::AreEqual(1, command.GetSerialNumber());
	}

public:
	static void Test()
	{
		TestSingle();
		TestMultiple();
		TestReset();
	}
};
