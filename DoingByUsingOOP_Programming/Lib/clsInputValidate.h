#pragma once

#include <iostream>
#include <string>
#include "clsString.h"
#include "clsDate.h"

class clsInputValidate
{
public:

	template <typename T>
	static T IsNumberBetween(T Number, T From, T To)
	{
		//this solution
		/*if (Number < From || Number > To)
			return false;
		else
			return true;*/

			//Or this solution is the same results
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	//you don't need this functions because above we used (teplate function) to use all or any (datatype function)  
	/*static bool IsNumberBetween(int Number, int From, int To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(float Number, float From, float To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}

	static bool IsNumberBetween(double Number, double From, double To)
	{
		if (Number >= From && Number <= To)
			return true;
		else
			return false;
	}*/

	bool IsStringLengthBetween(string S1, int FromLength, int ToLength)
	{
		if (S1.length() < FromLength || S1.length() > ToLength)
		{
			return false;
		}
		return true;
	}

	static bool IsDateBetween(clsDate Date, clsDate From, clsDate To)
	{
		//Date >= From && Date <= To
		if (clsDate::IsDate1AfterDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From)
			&&
			clsDate::IsDate1BeforeDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To))
		{
			return true;
		}

		//Date >= To && Date <= From
		if (clsDate::IsDate1AfterDate2(Date, To) || clsDate::IsDate1EqualDate2(Date, To)
			&&
			clsDate::IsDate1BeforeDate2(Date, From) || clsDate::IsDate1EqualDate2(Date, From))
		{
			return true;
		}

		return false;
		
		//Anther Sulotion 
		/*if (clsDate::IsDate1AfterDate2(From, To))
		{
			clsDate::SwapDates(From, To);
		}

		clsPeriod Period1(From, To);

		if (!Period1.IsDateInPeriod(DateToCheck))
		{
			return false;
		}
		return true;*/
	}

	
	template <typename T>
	static T ReadNumber(string ErrorMessage = "Invalid number, enter again\n")
	{
		T Number = 0;

		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}

		//this Another solution
		//while (cin.fail())
		//{
		//	//user didn't input a number
		//	cin.clear();
		//	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		//	//"Invalid number, Enter a valid one"
		//	cout << MessageWrong << endl;
		//	cin >> Number;
		//}

		return Number;
	}

	template <typename T>
	static T ReadNumberBetween(T From, T To, string ErrorMessage = "Numer is not within range, enter again:\n")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadNumber<T>();
		}
		return Number;
	}

	//you don't need this functions because above we used (teplate function) to use all or any (datatype function)
	/*static short ReadShortNumber(string ErrorMessage = "Invalid number, enter again\n")
	{
		short Number = 0;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static short ReadShortNumberBetween(short From, short To, string ErrorMessage = "Numer is not within range, enter again:\n")
	{
		short Number = ReadShortNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadShortNumber();
		}
		return Number;
	}

	static float ReadfloatNumber(string ErrorMessage = "Invalid number, enter again\n")
	{
		float Number = 0;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static float ReadfloatNumberBetween(float From, float To, string ErrorMessage = "Numer is not within range, enter again:\n")
	{
		float Number = ReadfloatNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadfloatNumber();
		}
		return Number;
	}

	static double ReadDblNumber(string ErrorMessage = "Invalid number, enter again\n")
	{
		double Number = 0;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	static double ReadDblNumberBetween(double From, double To, string ErrorMessage = "Numer is not within range, enter again:\n")
	{
		double Number = ReadDblNumber();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << ErrorMessage;
			Number = ReadDblNumber();
		}
		return Number;
	}*/

	static bool IsValidDate(clsDate Date)
	{
		return clsDate::IsValidDate(Date);
	}

	static string ReadString()
	{
		string S1 = "";
		// Usage of std::ws will extract all the whitespace character
		getline(cin >> ws, S1);
		return S1;
	}
};

