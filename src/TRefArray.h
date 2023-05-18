/*

Copyright (C) 2011-2022, Comine.com ( comine.com@gmail.com )
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
- The the names of the contributors of this project may not be used to 
  endorse or promote products derived from this software without specific 
  prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
`AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

//v1.0 copyright Comine.com 20230516T1032
#ifndef TRefArray_h
#define TRefArray_h

////////////////////////////////////////////
#include "MStdLib.h"

///////////////////////////////////////////
// TRefArray Declaration
///////////////////////////////////////////
template <typename DataType,int initialcap=16>
class TRefArray
	{

	////////////////////////////////////////
	DataType **mArray;
	int mArrayCapacity;
	int mArrayCount;				// Count of items used in array

	/////////////////////////////////////////
	void ClearObject(void);
	bool DoubleCapacity(void);		// Double the  capacity

	/////////////////////////////////////////
	public:
	TRefArray(bool create=false);
	~TRefArray(void);
	bool Create(void);
	bool Destroy(void);
	int GetCount(void) const;
	DataType *Get(int index);
	DataType *Add(void);
	DataType *Add(int index);
	bool Delete(int index);
	};

///////////////////////////////////////////
// TRefArray Implementation
///////////////////////////////////////////
template <typename DataType,int initialcap>
void TRefArray<DataType,initialcap>::ClearObject(void)
	{
	mArray=nullptr;
	mArrayCapacity=0;
	mArrayCount=0;
	}	


///////////////////////////////////////////
template <typename DataType,int initialcap>
bool TRefArray<DataType,initialcap>::DoubleCapacity(void)
	{
	MStdAssert(mArrayCapacity>0 && mArray!=nullptr);
	const int newcapacity=2*mArrayCapacity;
	MStdAssert(newcapacity>0);
	DataType **newarray=new(std::nothrow) DataType *[newcapacity];
	if(newarray==nullptr)
		{
		return false;
		}

	for(int i=0;i<mArrayCount;++i)
		{
		newarray[i]=mArray[i];
		mArray[i]=nullptr;
		}

	for(int i=mArrayCount;i<newcapacity;++i)
		{
		newarray[i]=nullptr;
		}

	delete[] mArray;

	mArray=newarray;
	mArrayCapacity=newcapacity;

	return true;
	}


///////////////////////////////////////////
template <typename DataType,int initialcap>
TRefArray<DataType,initialcap>::TRefArray(bool create)
	{
	ClearObject();
	if(create==true && Create()==false)
		{
		return;
		}
	}


//////////////////////////////////////////
template <typename DataType,int initialcap>
TRefArray<DataType,initialcap>::~TRefArray(void)
	{
	Destroy();
	}


///////////////////////////////////////
template <typename DataType,int initialcap>
bool TRefArray<DataType,initialcap>::Create(void)
	{
	Destroy();

	MStdAssert(initialcap>0);

	mArray=new(std::nothrow) DataType *[initialcap];
	if(mArray==nullptr)
		{
		Destroy();
		return false;
		}

	for(int i=0;i<initialcap;++i)
		{
		mArray[i]=nullptr;
		}

	mArrayCapacity=initialcap;
	mArrayCount=0;
	return true;
	}


/////////////////////////////////////////
template <typename DataType,int initialcap>
bool TRefArray<DataType,initialcap>::Destroy(void)
	{
	if(mArray!=nullptr)
		{
		for(int i=0;i<mArrayCount;++i)
			{
			delete mArray[i];
			mArray[i]=nullptr;
			}


		delete[] mArray;
		mArray=nullptr;
		}

	ClearObject();
	return true;
	}


///////////////////////////////////////
template <typename DataType,int initialcap>
int TRefArray<DataType,initialcap>::GetCount(void) const
	{
	return mArrayCount;
	}


///////////////////////////////////////
template <typename DataType,int initialcap>
DataType *TRefArray<DataType,initialcap>::Get(int index)
	{
	MStdAssert(index>=0 && index<mArrayCount);
	return mArray[index];
	}


///////////////////////////////////////
template <typename DataType,int initialcap>
DataType *TRefArray<DataType,initialcap>::Add(void)
	{
	if(mArrayCount>=mArrayCapacity)
		{
		if(DoubleCapacity()==false)
			{
			return nullptr;
			}
		}

	MStdAssert(mArray[mArrayCount]==nullptr);
	
	DataType *newdata=new(std::nothrow) DataType;
	if(newdata==nullptr)
		{
		return nullptr;
		}

	mArray[mArrayCount]=newdata;
	mArrayCount=mArrayCount+1;

	return newdata;
	}


///////////////////////////////////////
template <typename DataType,int initialcap>
DataType *TRefArray<DataType,initialcap>::Add(int index)
	{
	MStdAssert(index>=0 && index<=mArrayCount);

	if(mArrayCount>=mArrayCapacity)
		{
		if(DoubleCapacity()==false)
			{
			return nullptr;
			}
		}

	MStdAssert(mArray[mArrayCount]==nullptr);
	
	DataType *newdata=new(std::nothrow) DataType;
	if(newdata==nullptr)
		{
		return nullptr;
		}

	for(int i=mArrayCount;i>index;--i)
		{
		mArray[i]=mArray[i-1];
		}

	mArray[index]=newdata;
	mArrayCount=mArrayCount+1;
	return newdata;
	}


///////////////////////////////////////
template <typename DataType,int initialcap>
bool TRefArray<DataType,initialcap>::Delete(int index)
	{
	MStdAssert(index>=0 && index<mArrayCount);
	MStdAssert(mArray[index]!=nullptr);

	delete mArray[index];
	mArray[index]=nullptr;

	for(int i=index;i<mArrayCount;++i)
		{
		mArray[i]=mArray[i+1];
		}

	mArray[mArrayCount-1]=nullptr;
	mArrayCount=mArrayCount-1;
	MStdAssert(mArrayCount>=0);

	return true;
	}

#endif //TRefArray_h

