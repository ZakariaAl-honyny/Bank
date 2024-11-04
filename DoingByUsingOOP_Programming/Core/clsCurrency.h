#pragma once
#include <iostream>
#include "fstream"
#include <string>
#include <vector>
#include "clsString.h"
using namespace std;

class clsCurrency
{
private:
	enum enMode {EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string DataLine, string Sperator = "#//#")
	{
		vector <string> vCurrencyData;

		vCurrencyData = clsString::Split(DataLine, Sperator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1],
			vCurrencyData[2], stof(vCurrencyData[3]));
	}

	static string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Sperator = "#//#")
	{
		string stCurrencyRecordLine = "";

		stCurrencyRecordLine += Currency.Country() + Sperator;
		stCurrencyRecordLine += Currency.CurrencyCode() + Sperator;
		stCurrencyRecordLine += Currency.CurrencyName() + Sperator;
		stCurrencyRecordLine += to_string(Currency.Rate());

		return stCurrencyRecordLine;
	}

	static vector <clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector <clsCurrency> vCurrencys;

		fstream MyFile; 
		MyFile.open("Currencies.txt", ios::in);//Read Mode

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				if (Line != "")
				{
					clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

					vCurrencys.push_back(Currency);
				}
				else
				{
					break;
				}
				
			}

			MyFile.close();
		}
		return vCurrencys;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);//OverWrite

		if (MyFile.is_open())
		{
			string DataLine;

			for (clsCurrency& Currency : vCurrencys)
			{
				DataLine = _ConvertCurrencyObjectToLine(Currency);
				MyFile << DataLine << endl;
			}

			MyFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> vCurrencys = _LoadCurrencysDataFromFile();

		for (clsCurrency& Currency : vCurrencys)
		{
			if (Currency.CurrencyCode() == CurrencyCode())
			{
				Currency = *this;
				break;
			}
		}

		_SaveCurrencyDataToFile(vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}
	
	static vector <clsCurrency> GetAllUSDRates()
	{
		return _LoadCurrencysDataFromFile();
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string Country()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	float Rate()
	{
		return _Rate;
	}

	static clsCurrency FindByCurrencyCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);

		vector <clsCurrency> vCurrencys = GetCurrenciesList();

		for (clsCurrency& Currency : vCurrencys)
		{
			if (Currency.CurrencyCode() == CurrencyCode)
			{
				return Currency;
			}
		}

		return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);

		vector <clsCurrency> vCurrencys = GetCurrenciesList();

		for (clsCurrency& Cureency : vCurrencys)
		{
			if (clsString::UpperAllString(Cureency.Country()) == Country)
			{
				return Cureency;
			}
		}
		
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCurrencyCode(CurrencyCode);
		
		return (!Currency.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		vector <clsCurrency> vCurrencys = _LoadCurrencysDataFromFile();
		return vCurrencys;
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToAnotherCurrency(float Amount, clsCurrency CurrencyTo)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (CurrencyTo.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}

		return (float)(AmountInUSD * CurrencyTo.Rate());
	}

};


