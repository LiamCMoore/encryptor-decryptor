
#pragma once

#include "iVigenereStream.h"

class VigenereForwardIterator
{
private:
    iVigenereStream& fIStream;
    char fCurrentChar;
    bool fEOF;
    
public:

    VigenereForwardIterator( iVigenereStream& aIStream );

    // forward iterator interface
    char operator*() const; //return current Encryption target
    VigenereForwardIterator& operator++();           // prefix increment
    VigenereForwardIterator operator++( int );       // postfix increment
    
    bool operator==( const VigenereForwardIterator& aOther ) const; //establishing equivilence operator
    bool operator!=( const VigenereForwardIterator& aOther) const;  //establishing unequivilence operator
    
    VigenereForwardIterator begin() const; //Check for valid file data. Runs once, easy to run tests here
    VigenereForwardIterator end() const; //Encrpytion finished, begin cleanup
};
