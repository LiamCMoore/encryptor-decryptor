
#pragma once

#include <fstream>
#include <functional>

#include "Vigenere.h"

using Cipher = std::function<char ( Vigenere& aCipherProvider, char aCharacter )>;

class iVigenereStream
//Operations run throughout program for file handleing
{
private:
	std::ifstream fIStream;
	Vigenere fCipherProvider;
	Cipher fCipher;

public:
	iVigenereStream( Cipher aCipher, const std::string& aKeyword, const char* aFileName = nullptr ); //Check for valid file, then open on self
	~iVigenereStream(); //Close file, free memory

	void open( const char* aFileName ); //Provides open operation to self. Does not check for valid file.
	void close(); //Provides close file to self.
	void reset(); //Restarts both file locations and cipher position

	// conversion operator to bool
	operator bool() { return !eof(); }

	// stream positioning
	uint64_t position() { return fIStream.tellg(); }
	void seekstart() { fIStream.clear(); fIStream.seekg( 0, std::ios_base::beg ); } //Provides self ability to return to character 0

	bool good() const; //Provides file validation to self
	bool is_open() const; //Provides stream validation to self
	bool eof() const; //Provides end of file checking to self

	iVigenereStream& operator>>( char& aCharacter ); //allows retrieval of current character from self's stream
};
