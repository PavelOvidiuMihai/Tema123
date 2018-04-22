#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#define _CRT_SECURE_NO_WARNINGS

class Minge {
private:
	char* culoare;

public:

	Minge() { };

	void setCuloare(const char * new_culoare) 
	{
		delete culoare; 
		culoare = new char[strlen(new_culoare) + 1];
		strcpy_s(culoare, 20, new_culoare); 
	}

	const char* getCuloare() const {
		return &culoare[0];
	}

	Minge(const char* obj)
		:culoare(new char[std::strlen(obj) + 1])
	{
		std::strcpy(culoare, obj);
	}

	virtual ~Minge() {
		delete[] culoare;
	}

	Minge(const Minge& obj) {
		culoare = new char[std::strlen(obj.culoare) + 1];
		std::strcpy(culoare, obj.culoare);
	}

	Minge(Minge&& obj)
		:culoare(obj.culoare)
	{
		obj.culoare = nullptr;
	}

	Minge& operator=(const Minge& obj) {
		char *tmp_culoare = new char[std::strlen(obj.culoare) + 1];
		std::strcpy(tmp_culoare, obj.culoare);
		delete[] culoare;
		culoare = tmp_culoare;
		return *this;
	}

	Minge& operator=(Minge&& obj) {
		if (this != &obj) {
			delete[] culoare;
			culoare = obj.culoare;
			obj.culoare = nullptr;
		}
		return *this;
	}


	friend bool Apartine(const Minge& n1);
	friend std::ostream& operator<< (std::ostream& os, const Minge& p1);
	friend bool operator==(const Minge& p1, const Minge& p2);

};

bool Apartine(const Minge& n1) {
	char str1[10];
	strcpy(str1, "galben");
	int rez = strcmp(n1.getCuloare(), str1);
	if (rez == 0) return true;
	else return false;
	
}

bool operator==(const Minge& p1, const Minge& p2) {

	return p1.getCuloare() == p2.getCuloare();
}

std::ostream& operator<<(std::ostream& os, const Minge& p1)  
{  
    os << p1.getCuloare()<<" | ";  
    return os;  
}  



int main() {

	std::vector<Minge> vectorMinge;
	vectorMinge.push_back("galben");
	vectorMinge.push_back("negru");
	vectorMinge.push_back("alb");

	
	std::cout << "Vectorul contine: " << " ";
	for (std::vector<Minge>::iterator it = vectorMinge.begin(); it != vectorMinge.end();++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	

	std::vector<Minge>::iterator it = std::find_if(vectorMinge.begin(), vectorMinge.end()-1,Apartine);
	std::cout << "Contine vectorul galben?" << std::endl;
	std::cout << "Vectorul contine : " << *it << '\n';


	std::cout << "Daca vectorul contine galben, sterge-l."<<std::endl;
	vectorMinge.erase(
		std::remove_if(vectorMinge.begin(), vectorMinge.end(), Apartine), vectorMinge.end());




	std::cout << "Vectorul contine: " << " ";
	for (std::vector<Minge>::iterator it = vectorMinge.begin(); it != vectorMinge.end(); ++it) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;

	
	std::cin.get();
}

