
#include <iostream>
#include <fstream>
#include <cctype>

using namespace std;

//#define TestKeyGeneration
//#define TestBasicString
#define DecodeFile
//#define EncodeFile

#ifdef TestKeyGeneration

#include "KeyProvider.h"

int TestKeyGen( string argv[2] )
{
    string& lMessage = argv[1];
    KeyProvider lKeyWord( argv[0] );

    cout << "Testing KeyProvider with \"" << argv[0] << "\" and \"" << lMessage << "\"" << endl;
        
    for ( char c : lMessage )
    {
        if ( isalpha( c ) )
        {
            cout << *lKeyWord;
            lKeyWord << c;
        }
        else
        {
            cout << ' ';
        }
    }

    cout << "\n";
    
    for ( char c : lMessage )
    {
        cout << (isalpha( c ) ? static_cast<char>(toupper( c )) : c);
    }

    cout << "\nCompleted" << endl;

    return 0;
}

#endif

#ifdef TestBasicString

#include "Vigenere.h"

int TestString( string argv[2] )
{
    string lMessage = argv[1];
    Vigenere lSrambler( argv[0] );

    // Test encoding
    
    cout << "Encoding \"" << lMessage
         << "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;

    for ( char c : lMessage )
    {
        cout << (isalpha( c ) ? static_cast<char>(toupper( c )) : c);
    }
    
    cout << "\n";
    
    string lEncodedMessage;

    for ( char c : lMessage )
    {
        lEncodedMessage += lSrambler.encode( c );
    }

    cout << lEncodedMessage << "\nCompleted" << endl;

    // Test decoding
    
    lSrambler.reset();
    
    cout << "Decoding \"" << lEncodedMessage
         << "\" using \"" << lSrambler.getCurrentKeyword() << "\"" << endl;

    for ( char c : lEncodedMessage )
    {
        cout << (isalpha( c ) ? static_cast<char>(toupper( c )) : c);
    }
    
    cout << "\n";

    string lDecodedMessage;

    for ( char c : lEncodedMessage )
    {
        lDecodedMessage += lSrambler.decode( c );
    }
    
    cout << lDecodedMessage << "\nCompleted" << endl;

    return 0;
}

#endif

#ifdef DecodeFile

#include "iVigenereStream.h"

int DecodeCall( string argv[2] )
{
    iVigenereStream lInput( []( Vigenere& aCipherProvider, char aCharacter )
                                {
                                    return aCipherProvider.decode( aCharacter );
                                } , argv[0], argv[1].c_str() ); //Runs all the characters in argument against the decoder

    if ( !lInput.good() ) //checking if the filestream has a valid input file
    {
        cerr << "Cannot open input file: " << argv[1] << endl;

        return 2;
    }

    cout << "Decoding \"" << argv[1] << "\" using \"" << argv[0] << "\"." << endl; 

    char lCharacter;

    while ( lInput >> lCharacter )
    {
        cout << lCharacter;
    }

    lInput.close();

    cout << '\n' << '\n' << "Completed." << endl;
    
    return 0;
}

#endif

#ifdef EncodeFile

#include "VigenereForwardIterator.h"

int EncodeCall( string argv[2] )
{
    iVigenereStream lInput( []( Vigenere& aCipherProvider, char aCharacter )
                                {
                                    return aCipherProvider.encode( aCharacter );
                                } , argv[0], argv[1].c_str() ); //Runs all the characters in argument against the decoder

    if ( !lInput.good() ) //checking if the filestream has a valid input file
    {
        cerr << "Cannot open input file: " << argv[1] << endl;

        return 2;
    }

    cout << "Forward Iterator Encoding \"" << argv[1] << "' using \"" << argv[0] << "\"." << endl;

    for ( char c : VigenereForwardIterator( lInput ) )
    {
        cout << c;
    }

    lInput.close();

    cout << '\n' << '\n' << "Completed." << endl;

    return 0;
}

#endif

int main( int argc, char* argv[] )
{
#ifdef TestKeyGeneration
    string lArgv1[] = { "Relations", "To be, or not to be: that is the question:" };
    
    return TestKeyGen( lArgv1 );
#endif

#ifdef TestBasicString
    string lArgv2[] = { "Relations", "To be, or not to be: that is the question:" };
    
    return TestString( lArgv2 );
#endif

#ifdef DecodeFile
    string lArgv3[] = { "Relations", "GGG Cipher Decode.txt" };
    
    return DecodeCall( lArgv3 );
#endif

#ifdef EncodeFile
    string lArgv4[] = { "Relations", "GGG Cipher Encode.txt" };
        
    return EncodeCall( lArgv4 );
#endif
}
