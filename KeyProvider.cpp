#include "KeyProvider.h"
#include <string>

using namespace std;

KeyProvider::KeyProvider(const std::string& aKeyword)
{

	fIndex = 0;
	fSize = 0;
	fKeyword = new char;

	this->initialize(aKeyword);

}

KeyProvider::~KeyProvider()
{

	delete[] fKeyword;

}

void KeyProvider::initialize(const std::string& aKeyword)
{

	delete[] fKeyword;
	fIndex = 0;
	fSize = aKeyword.size();
	fKeyword = new char[fSize];

	for (int i = 0; i < fSize; i++) {

		fKeyword[i] = toupper(aKeyword[i]);

	}

}

char KeyProvider::operator*() const
{

	return (*this).fKeyword[(*this).fIndex];

}

KeyProvider& KeyProvider::operator<<(char aKeyCharacter)
{

	char Key = toupper(aKeyCharacter);
	fKeyword[fIndex] = Key;
	fIndex++;
	if (fIndex == fSize) {
		fIndex = 0;
	}

	return (*this);

}
