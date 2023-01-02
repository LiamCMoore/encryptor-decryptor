#include "iVigenereStream.h"

using namespace std;

iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName) :
	fCipherProvider(aKeyword),
	fCipher(aCipher)
{

	if (aFileName)
		(*this).open(aFileName);

}

iVigenereStream::~iVigenereStream()
{

	(*this).close();

}

void iVigenereStream::open(const char* aFileName)
{

	fIStream.open(aFileName, ofstream::binary);

}

void iVigenereStream::close()
{
	
	fIStream.close();

}

void iVigenereStream::reset()
{

	fCipherProvider.reset();
	(*this).seekstart();

}

bool iVigenereStream::good() const
{

	return fIStream.good();

}

bool iVigenereStream::is_open() const
{

	return fIStream.is_open();

}

bool iVigenereStream::eof() const
{

	return fIStream.eof();

}

iVigenereStream& iVigenereStream::operator>>(char& aCharacter)
{
	
	if (fIStream.get(aCharacter)) {

		aCharacter = fCipher(fCipherProvider, aCharacter);

	}

	return (*this);

}
