#include "stack.h"
#include <ctime>
#include <locale>
void main() {

	setlocale(LC_CTYPE, "Rus");
	std::vector<int> v1 = { 34, 12, 1, 6, 9 };
	std::vector<std::string> v2 = { "34", "12", "1", "6", "9" };
	Priority_queue<std::string> a(v1, v2);
	Priority_queue<std::string> b;
	b.insert(2, "2");
	b.insert(10, "10");
	Priority_queue<std::string> c = a + b;
	c.remove();
	c.remove();
	c.remove();
	c.remove();
	std::cout << c.get_Min_Priority();
}