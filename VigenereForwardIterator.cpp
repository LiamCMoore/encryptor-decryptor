#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream) :
	fIStream(aIStream),
	fCurrentChar(),
	fEOF(false)
{

	++(*this);

}

char VigenereForwardIterator::operator*() const
{

	return fCurrentChar;

}

VigenereForwardIterator& VigenereForwardIterator::operator++()
{
	fIStream >> fCurrentChar;
	fEOF = fIStream.eof();

	return (*this);

}

VigenereForwardIterator VigenereForwardIterator::operator++(int)
{
	VigenereForwardIterator old = (*this);

	++(*this);

	return old;

}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const
{

	if (fIStream.position() == aOther.fIStream.position() && !(fEOF || aOther.fEOF)) {
		return true;
	}
	else if (fEOF && aOther.fEOF) {
		return true;
	}

	return false;

}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const
{

	return !(aOther == (*this));

}

VigenereForwardIterator VigenereForwardIterator::begin() const
{
	VigenereForwardIterator itr = VigenereForwardIterator(*this);

	//itr.fEOF = false;

	//itr.fIStream.reset();

	if (!(itr.fIStream.eof())) {

		fCurrentChar << itr.fIStream;

	}
	else {
		itr.fEOF = true;
	}
	
	return itr;

}

VigenereForwardIterator VigenereForwardIterator::end() const
{
	VigenereForwardIterator itr = VigenereForwardIterator(*this);

	itr.fEOF = true;

	return itr;

}
