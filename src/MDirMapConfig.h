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
#ifndef MDirMapConfig_h
#define MDirMapConfig_h

/////////////////////////////////////////////////
#include "MStdLib.h"
#include "TPair.h"
#include "TRefArray.h"
#include "MString.h"

// Class will read an text config file that has 
//    (target dir=source dir) values
// 
// Example:
// 
// # Comment maps openal folder to include dir for openal
// #  All spaces are stripped automatically
// openal=c:/openal/include
// opengl=c:/github/opengl/include
// 
// 
// 
//******************************************************
//**  MDirMapConfig class
//******************************************************
class MDirMapConfig
	{
	////////////////////////////////////////////////
	TRefArray< TPair<MString,MString> > mArray;

	////////////////////////////////////////////////
	void ClearObject(void);

	////////////////////////////////////////////////
	public:
	MDirMapConfig(void);
	~MDirMapConfig(void);
	bool Create(const char *filenames);
	bool Destroy(void);
	int GetCount(void) const;
	const char *GetTargetDir(int index);
	const char *GetSoureDir(int index);
	bool Print(void);							// Print out the target and source dirs
	};

#endif // MDirMapConfig_h

