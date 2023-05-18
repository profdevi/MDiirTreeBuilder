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

//v1.0 copyright Comine.com 20230517W1838
#include "MStdLib.h"
#include "MDirTreeBuilder.h"
#include "MCommandArg.h"


//******************************************************
//* Module Elements
//******************************************************
static const char *GApplicationName="MDirTreeBuilder.exe";	// Used in Help
static const char *GApplicationVersion="1.0";	// Used in Help

////////////////////////////////////////////////////
static void GDisplayHelp(void);

////////////////////////////////////////////////////
int main(int argn,const char *argv[])
	{
	MCommandArg args(argn,argv);

	///////////////////////////////////////////////
	if(args.GetArgCount()!=3)
		{
		GDisplayHelp();
		return 0;
		}

	if(args.CheckRemoveHelp()==true)
		{
		GDisplayHelp();
		return 0;
		}

	///////////////////////////////////////////////
	const char *targetdir=args.GetArg(1);
	const char *mapfile=args.GetArg(2);
	MStdPrintf("Target Directory: %s\n",targetdir);
	MStdPrintf("Map File        : %s\n",mapfile);

	MDirTreeBuilder builder;
	if(builder.Create(targetdir,mapfile)==false)
		{
		MStdPrintf("**object init failed\n");
		return 1;
		}

	if(builder.BuildTree(true)==false)
		{
		MStdPrintf("**Unable to build subtrees in targer dir\n");
		return 2;
		}

	MStdPrintf("Done...\n");
	return 0;
	}


////////////////////////////////////////////////////
static void GDisplayHelp(void)
	{
	MStdPrintf(	"\n"
				"   usage:  %s [-?] [-d] <TargetDir> <MapFile>\n"
				"           v%s copyright Comine.com\n"
				"\n"
				"  Copies directories from Map File to Target directory"
				"\n"
				"  Example Map File:\n"
				"\n"
				"         # Comment Lines begin \n"
				"         openal=c:/openal/include\n"
				"\n"
				"         opengl=c:/opengl/include\n"
				"\n"
				,GApplicationName,GApplicationVersion);
	}


