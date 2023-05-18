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

//v1.0 copyright Comine.com 20230517W1409
#include "MStdLib.h"
#include "TPair.h"
#include "TRefArray.h"
#include "MString.h"
#include "MFile.h"
#include "MDirMapConfig.h"


//******************************************************
//**  Module elements
//******************************************************
static bool GRemoveComments(char *buf)
	{
	for(char *p=buf;*p!=0;++p)
		{
		if(*p=='#') { *p=0; break; }
		}

	return true;
	}


/////////////////////////////////////////////////
static bool GGetTargetSourceDirs(char *line,char *&target,char *&source)
	{
	MStdAssert(line!=nullptr);

	for(char *p=line;*p!=0;++p)
		{
		if(*p!='=') { continue; }

		// Found the '='
		*p=0;

		source=p+1;
		target=line;
		return true;
		}

	target=nullptr;
	source=nullptr;
	return false;
	}


//******************************************************
//**  MDirMapConfig class
//******************************************************
void MDirMapConfig::ClearObject(void)
	{
	}


////////////////////////////////////////////////
MDirMapConfig::MDirMapConfig(void)
	{  ClearObject();  }


////////////////////////////////////////////////
MDirMapConfig::~MDirMapConfig(void)
	{  Destroy();  }


////////////////////////////////////////////////
bool MDirMapConfig::Create(const char *filename)
	{
	Destroy();

	MFileInput fileinput;
	if(fileinput.Create(filename)==false)
		{
		Destroy();
		return false;
		}

	if(mArray.Create()==false)
		{
		Destroy();
		return false;
		}

	MStdArray<char> line(3*MStdPathMaxSize);

	while(fileinput.ReadLine(line.Get(),line.GetLength()-2)==true)
		{
		GRemoveComments(line.Get() );
		MStdStrTrim(line.Get());

		char *ptargetdir=nullptr;
		char *psourcedir=nullptr;
		if(GGetTargetSourceDirs(line.Get(),ptargetdir,psourcedir)==false)
			{  continue;  }
	
		MStdAssert(ptargetdir!=nullptr && psourcedir!=nullptr);

		auto parrayitem=mArray.Add();
		MStdAssert(parrayitem!=nullptr);

		if( parrayitem->First.Create(ptargetdir)==false
				|| parrayitem->Second.Create(psourcedir)==false )
			{
			Destroy();
			return false;
			}
		}

	fileinput.Destroy();
	return true;
	}


////////////////////////////////////////////////
bool MDirMapConfig::Destroy(void)
	{
	ClearObject();
	return true;
	}


////////////////////////////////////////////////
int MDirMapConfig::GetCount(void) const
	{
	const int count=mArray.GetCount();
	return count;
	}

////////////////////////////////////////////////
const char *MDirMapConfig::GetTargetDir(int index)
	{
	auto datapair=mArray.Get(index);
	MStdAssert(datapair!=nullptr);

	return datapair->First.Get();
	}


////////////////////////////////////////////////
const char *MDirMapConfig::GetSoureDir(int index)
	{
	auto datapair=mArray.Get(index);
	MStdAssert(datapair!=nullptr);

	return datapair->Second.Get();	
	}


//////////////////////////////////////////////////////////
bool MDirMapConfig::Print(void)
	{
	int count=mArray.GetCount();
	for(int i=0;i<count;++i)
		{
		auto pitem=mArray.Get(i);
		MStdAssert(pitem!=nullptr);
		MStdPrintf("%s = %s\n", pitem->First.Get() ,pitem->Second.Get() );
		}
	return true;
	}


