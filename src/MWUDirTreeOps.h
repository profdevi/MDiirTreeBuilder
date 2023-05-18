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

//v1.1 copyright Comine.com 20230513S1742
#ifndef MWUDirTreeOps_h
#define MWUDirTreeOps_h

/////////////////////////////////////////////////
#include "MStdLib.h"
#include "MStringQueue.h"

//******************************************************
//**  MWUDirTreeOps class
//******************************************************
class MWUDirTreeOps
	{
	////////////////////////////////////////////////
	
	////////////////////////////////////////////////
	void ClearObject(void);
	
	////////////////////////////////////////////////
	public:
	MWUDirTreeOps(bool create=false);
	~MWUDirTreeOps(void);
	bool Create(void);
	bool Destroy(void);
	bool GetPath(const char* dir, const char* subdir,MStdArray<char> &fullpath);
	bool GetPath(const char *dir,const char *subdir,const char *filename,MStdArray<char> &fullpath);
	bool GetFilePath(const char* dir,const char* filename, MStdArray<char>& fullpath);
	bool GetDirs(const char *dir,MStringQueue &dirlist);
	bool GetDirsRelative(const char* dir, const char *relativedir,MStringQueue& dirs,MStringQueue& reldirs);
	bool GetDirsRecursivesly(const char *dir,MStringQueue &dirlist);
	bool GetDirsRecursiveslyRelative(const char* dir,const char* relativedir, MStringQueue& dirs,MStringQueue& dirlist);
	bool GetFiles(const char* dir, MStringQueue& filelist);
	bool GetFilesRelative(const char* dir, const char *relativedir,MStringQueue &files,MStringQueue &filesrel);
	bool GetFilesRecursively(const char *dir,MStringQueue &filelist);
	bool GetFilesRecursivelyRelative(const char* dir, const char *dirrel,MStringQueue& files,MStringQueue &filesrel);
	bool CopyDirTree(const char *srcdir,const char *dstdir);		// Copy source files and directories to destination
	bool DeleteDirTree(const char* dir);							// Delete all files and subdirectories in  directory
	bool MakeDirs(const char *dir,const char *dirlist[]);			// make directories in folder. Order is important
	bool DirsExists(const char *dir,const char *dirlist[]);			// Check if all the subdirectories exists
	bool FileWriteText(const char *dir,const char *subdir,const char *filename,const char *txt);		// Write text to file in directory
	bool FileWriteText(const char* dir,const char* filename, const char*txt);		// Write text to file in directory
	bool FileWriteBinary(const char *dir,const char *subdir,const char *filename,const char *buffer,int elementsize,int elementcount);
	bool FileReadText(const char *dir,const char *subdir,const char *filename,MStdArray<char> &textcontent);	// Read text of file
	bool FileReadBinary(const char* dir,const char* subdir,const char* filename,MStdArray<char>& textcontent);	// Read text of file
	};

#endif // MWUDirTreeOps_h

