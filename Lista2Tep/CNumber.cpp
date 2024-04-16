#include "CNumber.h"
#include <iostream>
const int CNumber::DEFAULT_LENGHT = 32;
bool isGreater(int* iNum1, int* iNum2, int length1, int length2) 
{

    if (length1 > length2)
    {
        return true;
    }
    else if (length2 > length1)
    {
        return false;
    }
    for (int i = 0; i < length1; i++)
    {
        if (iNum1[i] > iNum2[i])
        {
            return true;
        }
        else if (iNum2[i] > iNum1[i])
        {
            return false;
        }
    }
    return true;
}
bool signedIsGreater(int* iNum1, int* iNum2, int length1, int length2, std::string sSign1, std::string sSign2)
{
    if (sSign1 == "-" && sSign1 == "+")
    {
        return false;
    }
    else if(sSign1 == "+" && sSign1 == "-")
    {
        return true;
    }

    if (length1 > length2)
    {
        return true;
    }
    else if (length2 > length1)
    {
        return false;
    }
    for (int i = 0; i < length1; i++)
    {
        if (iNum1[i] > iNum2[i])
        {
            return true;
        }
        else if (iNum2[i] > iNum1[i])
        {
            return false;
        }
    }
    return false;
}
//dodawanie cyfry na koniec (nie wykorzystywane)
void CNumber::appendDigit(int digit)
{
    int* newTable = new int[i_length + 1];

    for (int i = 0; i < i_length; i++) {
        newTable[i] = pi_table[i];
    }

    newTable[i_length] = digit;
    
    delete[] pi_table;
    pi_table = newTable;

    i_length++;
}
//usuwanie zer wiodacych
void CNumber::removeLeadingZeros()
{
    int firstNonZeroIndex = 0;

    // szukanie 1 indexu nie bedacego zerem
    while (firstNonZeroIndex < i_length && pi_table[firstNonZeroIndex] == 0) {
        firstNonZeroIndex++;
    }

    // jesli sa jakiekolwiek usun
    if (firstNonZeroIndex > 0) {
        int newLength = i_length - firstNonZeroIndex;
        int* newTable = new int[newLength];

        // skopiuj nie-zera do innej tablicy
        for (int i = 0; i < newLength; i++) {
            newTable[i] = pi_table[i + firstNonZeroIndex];
        }

        // zadbaj o odpowiednia alokacje
        delete[] pi_table;
        pi_table = newTable;
        i_length = newLength;
    }
}
//funkcja pomocnicza odejmujaca od 1 liczby 2, nie zwraca uwage na znak
CNumber CNumber::subtract(const CNumber& cValue, const CNumber& cValueThis)
{
    CNumber cResult;
    cResult.sSign = "+";
    int iIndex1 = cValueThis.i_length - 1, iIndex2 = cValue.i_length - 1;
    int largerLength = (cValueThis.i_length > cValue.i_length) ? cValueThis.i_length : cValue.i_length;
    cResult.pi_table = new int[largerLength];
    cResult.i_length = largerLength;
    int borrow = 0;
    if (!isGreater(cValueThis.pi_table, cValue.pi_table, cValueThis.i_length, cValue.i_length)) //sprawdzenie ktora jest wieksza bezwzglednie - jest to wazne przy odejmowaniu
    {
        for (int i = largerLength - 1; i >= 0; i--)
        {
            int thisDigit = (iIndex1 >= 0) ? cValueThis.pi_table[iIndex1] : 0; //dwie linijki sprawdzaja czy ktoras z liczb sie nie skonczyla
            int valueDigit = (iIndex2 >= 0) ? cValue.pi_table[iIndex2] : 0;
            int resultDigit = valueDigit - thisDigit - borrow;
            if (resultDigit < 0) //sprawdzenie koneicznosci pozyczenia
            {
                resultDigit += 10; //pozyczenie
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            cResult.pi_table[i] = resultDigit; //ustawienie wyniku
            iIndex1--;
            iIndex2--;
        }
        cResult.sSign = "+";
    }
    else
    {
        for (int i = largerLength - 1; i >= 0; i--)
        {
            int thisDigit = (iIndex1 >= 0) ? cValueThis.pi_table[iIndex1] : 0; //analogicznie do poprzedniego ifa
            int valueDigit = (iIndex2 >= 0) ? cValue.pi_table[iIndex2] : 0;
            int resultDigit = thisDigit - valueDigit - borrow;
            if (resultDigit < 0)
            {
                resultDigit += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            cResult.pi_table[i] = resultDigit;
            iIndex1--;
            iIndex2--;
        }

    }
    cResult.removeLeadingZeros(); //usuiniecie zer z przodu dla estetyki wyniku
    return cResult;
}
//dodawanie bezwgledne dwoch liczb
CNumber CNumber::add(const CNumber& cValue,const CNumber& cValueThis)
{
    CNumber cResult;
    int iIndex1 = cValueThis.i_length - 1, iIndex2 = cValue.i_length - 1;
    int iPreviousCarry = 0;
    int iBiggerValue = cValue.i_length;
    if (cValueThis.i_length > iBiggerValue) iBiggerValue = cValueThis.i_length;
    cResult.pi_table = new int[iBiggerValue + 1];
    cResult.i_length = iBiggerValue + 1;
    cResult.pi_table[0] = 0;
    for (int i = iBiggerValue; i >= 0; i--) //w przeciwienstwie do odejmowania rozmiar nie ma znaczenia
    {
        int iValue1 = 0;
        int iValue2 = 0;
        if (iIndex1 >= 0) iValue1 = cValueThis.pi_table[iIndex1]; //sprawdzanie czy ktoras z liczb sie nie "skonczyla"
        if (iIndex2 >= 0) iValue2 = cValue.pi_table[iIndex2];
        int iTempResult = iValue1 + iValue2 + iPreviousCarry;
        if (iTempResult > 9) //sprawdzenie czy nie ma przeniesienie
        {
            iPreviousCarry = iTempResult / 10;  //obsluga przeniesienia
            cResult.pi_table[i] = iTempResult % 10; //ustawienie wyniku
        }
        else
        {
            cResult.pi_table[i] = iTempResult; //ustawienie wyniku
            iPreviousCarry = 0;
        }
        iTempResult = 0; //zmiania zmiennych loklanych
        iIndex1--;
        iIndex2--;
    }
    cResult.removeLeadingZeros(); //usuiniecie zer wodzacych
    return cResult;
}
//konstr. bezparametrowy
CNumber::CNumber()
{
    i_length = DEFAULT_LENGHT;
    pi_table = new int[DEFAULT_LENGHT];
    sSign = "+";
}
//destruktor
CNumber::~CNumber()
{
    delete[] pi_table;
}
//konstr. kopiujacy
CNumber::CNumber(const CNumber& pcOther)
{
    i_length = pcOther.i_length;
    pi_table = new int[pcOther.i_length];
    sSign = pcOther.sSign;
    for (int i = 0; i < pcOther.i_length; i++)
    {
        pi_table[i] = pcOther.pi_table[i];
    }
}
//konstr. parametrowy
CNumber::CNumber(int* piTable, int i_lenght, std::string sSign)
{
    this->pi_table = piTable;
    this->i_length = i_lenght;
    this->sSign = sSign;
}
//przeciazenie operatora =
void CNumber::operator=(const CNumber& pcOther)
{
    i_length = pcOther.i_length; //ustawienie zmiennych 
    pi_table = new int[pcOther.i_length];
    sSign = pcOther.sSign;
    for (int i = 0; i < pcOther.i_length; i++) //skopiowanie tabllicy pi_table
    {
        pi_table[i] = pcOther.pi_table[i];
    }
}
//przeciazenie operatora = dla inta
CNumber CNumber::operator=(const int iValue)
{
    if (iValue < 0) //ustalenie znaku
    {
        this->sSign="-";
    }
    else
    {
        this->sSign = "+";
    }
    int iCounter = 0;
    int iValueCopy = iValue;
    while (iValueCopy) //wyznaczenie dlugosci tablicy
    {
        iCounter++;
        iValueCopy /= 10;
    }
    i_length = iCounter;
    pi_table = new int[i_length];
    iValueCopy = iValue;
    while (iCounter) //odpowiednia zamiana inta na tablice jego cyfr
    {
        pi_table[iCounter-1] = abs(iValueCopy) % 10;
        iValueCopy /= 10;
        iCounter--;
    }
    return *this;
}
//przeciazenie operatora + 
CNumber CNumber::operator+(const CNumber& cValue)
{
    CNumber cResult; //ustawienie znaku, zobacz tabela dla wyjasnienia- odpowiednio podejmuje operacje ze wzgledu na wielkosc zmiennych oraz ich znaku 
    if (sSign == "+" && cValue.sSign == "+") {
        cResult= add(cValue,*this);
        return cResult;
    }
    else if (sSign == "-" && cValue.sSign == "-") {
        cResult= add(cValue, *this);
        cResult.sSign = "-";
        return cResult;
    }
    else if (sSign == "+") {
        if (isGreater(this->pi_table, cValue.pi_table,this->i_length,cValue.i_length)) {
            cResult = subtract(cValue, *this);
            cResult.sSign = "+";
            return cResult;
        }
        else {
            cResult = subtract(cValue, *this);
            cResult.sSign = "-";
            return cResult;
        }
    }
    else {
        if (isGreater(this->pi_table, cValue.pi_table,this->i_length,cValue.i_length)) {
            cResult = subtract(cValue, *this);
            cResult.sSign = "-";
            return cResult;
        }
        else {
            cResult = subtract(cValue, *this);
            cResult.sSign = "+";
            return cResult;
        }
    }
}
//przeciazenie operatora -
CNumber CNumber::operator-(const CNumber& cValue)
{
    //amalogicznie jak plus, patrz na tabele wyjasniajaco podejmowana decyzje ze wzgl. na rozmiar i znak
    CNumber cResult;
    if (sSign == "+" && cValue.sSign == "-") {
        cResult = add(cValue, *this);
        cResult.sSign = "+";
        return cResult;
    }
    else if (sSign == "-" && cValue.sSign == "+") {
        cResult = add(cValue, *this);
        cResult.sSign = "-";
        return cResult;
    }
    else if (sSign == "+") {
        if (isGreater(pi_table, cValue.pi_table,this->i_length,cValue.i_length)) {
            cResult = subtract(cValue, *this);
            cResult.sSign = "+";
            return cResult;
        }
        else {
            cResult = add(cValue, *this);
            cResult.sSign = "-";
            return cResult;
        }
    }
    else {
        if (isGreater(pi_table, cValue.pi_table,this->i_length,cValue.i_length)) {
            cResult = subtract(cValue, *this);
            cResult.sSign = "-";
            return cResult;
        }
        else {
            cResult = subtract(cValue, *this);
            cResult.sSign = "+";
            return cResult;
        }
    }

}
//przeciazenie operatora *
CNumber CNumber::operator*(const CNumber& cValue)
{
    //algorytm uzywa tzw long multiplication
    int iLength1 = this->i_length;
    int iLenght2 = cValue.i_length;
    CNumber cResult;
    cResult.sSign = "-"; //na poczatku wynik -
    cResult.pi_table = new int[iLength1 + iLenght2]; //wyznaczenie rozmiary wyniku, nie wiekszy niz sumadlugosci skladowych
    cResult.i_length = iLength1 + iLenght2;

    for (int i = 0; i < cResult.i_length; i++) {
        cResult.pi_table[i] = 0; //inicjacja tabeli
    }

    for (int i = iLength1 - 1; i >= 0; i--) { //mnozenie
        int iCarry = 0;
        for (int j = iLenght2 - 1; j >= 0; j--) {
            int iProduct = this->pi_table[i] * cValue.pi_table[j] + cResult.pi_table[i + j + 1] + iCarry; //produkt to obliczone mnozenie wynik i przeniesienie
            iCarry = iProduct / 10; //przeniesnie to bedzie liczba dziesiatek
            cResult.pi_table[i + j + 1] = iProduct % 10; //wynik to reszta z dzielenia
        }
        cResult.pi_table[i] += iCarry; //dodatkowo trzeba dodac przeniesienie
    }

    cResult.removeLeadingZeros(); //usuniecie zer wiodacych
    if (this->sSign == "+" && cValue.sSign == "+")
    {
        cResult.sSign = "+"; //mnozenie liczb dodatnich daje dodatni wynik
    }
    else if (this->sSign == "-" && cValue.sSign == "-")
    {
        cResult.sSign = "+"; //mnozenie liczb ujemnych daje dodatni wynik
    }
    //reszta nie wymaga zmiany znaku (ustawionego na -)
    return cResult;
}
//przeciazenie operatora 
CNumber CNumber::operator/(const CNumber& cValue)
{
    CNumber cResult;
    cResult = 1;
    int iCounterOfDiv = 0;
    CNumber cCopyOfThis = *this;
    cCopyOfThis.sSign = "+";
    CNumber cCopyOfValue = cValue;
    cCopyOfValue.sSign = "+";
    while (isGreater(cCopyOfThis.pi_table, cCopyOfValue.pi_table, cCopyOfThis.i_length, cCopyOfValue.i_length)) //odpowiedne sprawdzenie petli, sprawdza czy suma naszych dzielnikow nie wykracza poza dzielnik
    {
        cCopyOfThis = cCopyOfThis - (cCopyOfValue); //jesli warunek spelniony to zmniejszamy dzieln¹
        iCounterOfDiv++; //wynik zwieksza sie o 1- po prostu do dzielnej zmiescil sie jeszcze jeden dzielnik
        cCopyOfThis.removeLeadingZeros(); //usuniecia zer
        cCopyOfValue.removeLeadingZeros();
    }
    cResult = iCounterOfDiv;
    cResult.sSign = "-"; //ustalenia znaku, analogicznie jak przy mnozeniu
    if (this->sSign == "+" && cValue.sSign == "+")
    {
        cResult.sSign = "+";
    }
    else if (this->sSign == "-" && cValue.sSign == "-")
    {
        cResult.sSign = "+";
    }
    if (!isGreater(this->pi_table, cValue.pi_table, this->i_length, cValue.i_length)) //sprawdzenie czy liczby nie sa podzielne
    {
        cResult = 0; 
        return cResult;
    }
    return cResult;
}
//funkcja pomocznicza zwracaj¹ca CNumber jako string
std::string CNumber::toStr()
{
    std::string sValue=this->sSign;
    for (int i = 0; i < i_length; i++)
    {
        sValue += std::to_string(abs(pi_table[i]));
    }
    if (i_length == 0)
    {
        sValue+="0";
        sValue[0] = ' ';
    }
    return sValue;
}
