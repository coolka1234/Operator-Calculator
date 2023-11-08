#pragma once
#include <string>

class CNumber
{
private:
	static int const DEFAULT_LENGHT;
	int* pi_table;
	int i_length;
	std::string sSign;
public:
	CNumber();
	~CNumber();
	CNumber(const CNumber& pcOther);
	CNumber(int* piTable, int i_lenght, std::string sSign);
	void operator=(const CNumber& pcOther);
	CNumber operator=(const int iValue);
	CNumber operator+(const CNumber& cValue);
	CNumber operator-(const CNumber& cValue);
	CNumber operator*(const CNumber& cValue);
	CNumber operator/(const CNumber& cValue);
	void appendDigit(int digit);
	void removeLeadingZeros();
	CNumber subtract(const CNumber& cValue, const CNumber& cValueThis);
	CNumber add(const CNumber& cValue, const CNumber& cValueThis);
	std::string toStr();
};

