#pragma once
#include <iostream>
#include <climits>
#include <utility>
#include <cmath>
#include "Date.h"
using namespace std;

class InputValidate
{
private:
    static bool IsInputMalformed()
    {
        return cin.fail() || (std::cin.peek() != '\n' && std::cin.peek() != EOF);
    }

    static void SwapDates(Date& date1, Date& date2)
    {
        Date placeHolder = date1;
        date1 = date2;
        date2 = placeHolder;
    }

public:

    template <typename T>
    static bool IsNumberBetween(T Number, T From, T To)
    {
        return (Number >= From && Number <= To);
    }

    static long long ReadInteger(string errorMessage = "Invalid Input! Please, enter a valid input\n")
    {
        long long Number = 0;
        cin >> Number;

        while (IsInputMalformed())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << errorMessage;
            cin >> Number;
        }
        return Number;
    }

    static long long ReadIntegerBetween(long long from, long long to, string errorMessage = "Number is not within range, enter a valid number\n")
    {
        long long Number = ReadInteger(errorMessage);

        while (!IsNumberBetween(Number, from, to))
        {
            cout << errorMessage;
            Number = ReadInteger();
        }
        return Number;
    }

    static long double ReadFloat(string errorMessage = "Invalid Input! Please, enter a valid input\n")
    {
        long double Number = 0;
        cin >> Number;

        while (IsInputMalformed())
        {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            cout << errorMessage;
            cin >> Number;
        }
        return Number;
    }

    static long double ReadFloatBetween(long double from, long double to, string errorMessage = "Number is not within range, enter a valid number\n")
    {
        long double Number = ReadFloat(errorMessage);

        while (!IsNumberBetween(Number, from, to))
        {
            cout << errorMessage;
            Number = ReadFloat();
        }
        return Number;
    }


    static bool IsDateBetween(const Date &targetDate, Date date1, Date date2)
    {
        if (!(Date::IsDate1BeforeDate2(date1, date2)))
            SwapDates(date1, date2);

        return (Date::CompareDates(targetDate, date1) != Date::enDateCompare::After) && (Date::CompareDates(targetDate, date2) != Date::enDateCompare::Before);
    }

    static string ReadString()
    {
        string text;
        getline(cin >> ws, text);
        return text;
    }

    static bool IsValidDate(const Date& date1)
    {
        return Date::IsValidDate(date1);
    }
};

