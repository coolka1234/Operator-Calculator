#include <iostream>
#include "CNumber.h"
int main()
{
	CNumber c_num_0, c_num_1;
	c_num_0 = -96706;
	std::cout <<"Liczba pierwsza: " << c_num_0.toStr() << std::endl;
	c_num_1 = 123;
	std::cout <<"Liczba druga:    " << c_num_1.toStr() << std::endl;
	CNumber c_num_3;
	c_num_3 = c_num_0 + c_num_1;
	std::cout << "Oto wynik dodawania:   "<< c_num_3.toStr() << std::endl;
	c_num_3 = c_num_0 - c_num_1;
	std::cout << "Oto wynik odejmowania: " << c_num_3.toStr() << std::endl;
	c_num_3 = c_num_0 / c_num_1;
	std::cout << "Oto wynik dzielenia:   " << c_num_3.toStr() << std::endl;
	c_num_3 = c_num_1 * c_num_0;
	std::cout << "Oto wynik mnozenia:    " << c_num_3.toStr() << std::endl;

}
