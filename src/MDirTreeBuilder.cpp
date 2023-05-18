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

//v1.0 copyright Comine.com 20230517W1800
#include "MStdLib.h"
#include "MString.h"
#include "MStringSplitter.h"
#include "MWUDirTreeOps.h"
#include "MFilePathBuilder.h"
#include "MFile.h"
#include "MDirTreeBuilder.h"



//******************************************************
//**  MDirTreeBuilder class
//******************************************************
void MDirTreeBuilder::ClearObject(void)
	{
	}


////////////////////////////////////////////////
bool MDirTreeBuilder::BuildTargetDir(const char *dir)
	{
	MStdArray<char> abspath;
	if(MStdPathGetAbsolute(dir,abspath)==false)
		{
		return false;
		}
	
	MStringSplitter splitter;
	if(splitter.Create(abspath.Get(),"\\/")==false)
		{
		return false;
		}

	MFilePathBuilder pathbuilder;
	if(pathbuilder.Create()==false)
		{
		return false;
		}

	const int pathelementcount=splitter.GetCount();
	if(pathelementcount<2)
		{
		return false;
		}

	if(pathbuilder.Push(splitter.Get(0))==false)
		{
		return false;
		}

	for(int i=1;i<pathelementcount;++i)
		{
		const char *pathelement=splitter.Get(i);
		if(pathbuilder.Push(pathelement)==false)
			{
			return false;
			}

		MBuffer fullpath;
		if(pathbuilder.GetFullPath(fullpath)==false)
			{
			return false;
			}

		if(MStdDirExists(fullpath.GetBuffer() )==true) { continue; }

		//= Directory does not exist

		if(MStdDirCreate(fullpath.GetBuffer())==false)
			{
			return false;
			}

		if(MStdDirExists(fullpath.GetBuffer())==false)
			{
			return false;
			}
		}

	return true;
	}


////////////////////////////////////////////////
bool MDirTreeBuilder::CopyFiles(const char *targetdir,const char *srcdir)
	{
	if(MStdDirExists(srcdir)==false)
		{
		MStdPrintf("Source Dir: %s does not exist. Dir Skipped\n");
		return true;
		}

	if(MStdDirExists(targetdir)==false)
		{
		return false;
		}
	
	MWUDirTreeOps treeops(true);
	if(treeops.CopyDirTree(srcdir,targetdir)==false)
		{
		return false;
		}
	
	return true;
	}


////////////////////////////////////////////////
MDirTreeBuilder::MDirTreeBuilder(void)
	{
	ClearObject();
	}


////////////////////////////////////////////////
MDirTreeBuilder::~MDirTreeBuilder(void)
	{
	Destroy();
	}


////////////////////////////////////////////////
bool MDirTreeBuilder::Create(const char *targetdir,const char *dirmapfile)
	{
	Destroy();

	MStdArray<char> abstargetroot;
	if(MStdPathGetAbsolute(targetdir,abstargetroot)==false)
		{
		Destroy();
		return false;
		}

	if(BuildTargetDir(abstargetroot.Get() )==false)
		{
		return false;
		}

	if (mTargetDir.Create(abstargetroot.Get() ) == false)
		{
		Destroy();
		return false;
		}

	if(mDirMapFile.Create(dirmapfile)==false)
		{
		Destroy();
		return false;
		}

	return true;
	}


////////////////////////////////////////////////
bool MDirTreeBuilder::Destroy(void)
	{
	mTargetDir.Destroy();
	mDirMapFile.Destroy();
	ClearObject();
	return true;
	}



//////////////////////////////////////////////////////
bool MDirTreeBuilder::BuildTree(bool verbose)
	{
	if (MStdDirExists(mTargetDir.Get()) == false)
		{
		return false;
		}

	const int count=mDirMapFile.GetCount();

	for(int i=0;i<count;++i)
		{
		MFilePathBuilder pathbuilder;
		if(pathbuilder.Create(mTargetDir.Get())==false)
			{
			return false;
			}

		const char *targetdir=mDirMapFile.GetTargetDir(i);
		const char *srcdir=mDirMapFile.GetSoureDir(i);
		MStringSplitter splitter;
		if(splitter.Create(targetdir,"\\/")==false)
			{
			return false;
			}

		// Build up target dir
		const int elementcount=splitter.GetCount();
		for(int k=0;k<elementcount;++k)
			{
			const char *element=splitter.Get(k);
			if(pathbuilder.Push(element)==false)
				{
				return false;
				}
			}

		MBuffer fulltargetpath;
		if(pathbuilder.GetFullPath(fulltargetpath)==false)
			{
			return false;
			}

		// Build Target Directory
		if(BuildTargetDir(fulltargetpath.GetBuffer() )==false)
			{
			return false;
			}

		if(CopyFiles(fulltargetpath.GetBuffer(),srcdir)==false)
			{
			return false;
			}

		// Display verbose output
		if(verbose==true)
			{
			MStdPrintf("Copied:%s\n\t-> %s\n",srcdir,fulltargetpath.GetBuffer());
			}
		}
	
	
	return true;	
	}
	

