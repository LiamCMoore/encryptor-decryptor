
#include "Vigenere.h"

using namespace std;

void Vigenere::initializeTable()
{
    for (char row = 0; row < CHARACTERS; row++)
    {
        char lChar = 'B' + row;

        for (char column = 0; column < CHARACTERS; column++)
        {
            if (lChar > 'Z') // first
                lChar = 'A';

            fMappingTable[row][column] = lChar++;
        }
    }
}

Vigenere::Vigenere(const std::string& aKeyword) :
    fKeyword( aKeyword ),
    fKeywordProvider(fKeyword)
{
	
    initializeTable();

}

std::string Vigenere::getCurrentKeyword()
{

    string result = "";
    char newChar;

    for (size_t i = 0; i < fKeyword.size(); i++) {
        newChar = *fKeywordProvider;
        result = result + newChar;
        fKeywordProvider << newChar;
    }

	return result;
}

void Vigenere::reset()
{

    fKeywordProvider.initialize(fKeyword);

}

char Vigenere::encode(char aCharacter)
{
    if (isalpha(aCharacter)) {
        
        char result;
        bool isLower = false;
        char check = toupper(aCharacter);
        
        if (aCharacter != check) {
            isLower = true;
        }
        
        int row = *fKeywordProvider - 'A';
        fKeywordProvider << check;
        int col = check - 'A';

        result = fMappingTable[row][col];

        if (isLower == true) {
            result = tolower(result);
        }

        return result;
    }
    else {
        return aCharacter;
    }
}

char Vigenere::decode(char aCharacter)
{
    if (isalpha(aCharacter)) {
        
        char result;
        bool isLower = false;
        char check = toupper(aCharacter);
        
        if (aCharacter != check) {
            isLower = true;
        }
        int row = *fKeywordProvider - 'A';
        int col;

        for (size_t i = 0; i < 26; i++) {

            col = i;
            result = fMappingTable[row][col];
            if (result == check) {
                break;
            }

        }
        result = col + 'A';
        fKeywordProvider << result;

        if (isLower == true) {
            result = tolower(result);
        }

        return result;
    }
    else {
        return aCharacter;
    }
}
