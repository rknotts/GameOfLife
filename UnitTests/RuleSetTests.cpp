#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\GameOfLife\RuleSet.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{		
	TEST_CLASS(RuleSetTests)
	{
	public:
		//

		TEST_METHOD(RuleSetLiveWithNeighbors)
		{
			RuleSet *rules = new RuleSet();
			for (unsigned short i = 0; i < 10; i++)
			{
				if (i == 2 || i == 3)
				{
					Assert::IsTrue(rules->newState(true, i));
				}
				else
				{
					Assert::IsFalse(rules->newState(true, i));
				}
			}
		}

		TEST_METHOD(RuleSetDeadWithNeighbors)
		{
			RuleSet *rules = new RuleSet();
			for (unsigned short i = 0; i < 10; i++)
			{
				if (i == 3)
				{
					Assert::IsTrue(rules->newState(false, i));
				}
				else
				{
					Assert::IsFalse(rules->newState(false, i));
				}
			}
		}
	};
}