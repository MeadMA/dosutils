// POPD: Returns to the directory saved when you used PUSHD.
//
// Copyright (C) 2022  Michael A. Mead
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <conio.h>
#include <share.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	FILE *infile;
	char *tempfile, *olddir, *drive;

	// Get TEMP folder
	// Order of precedence: TEMP var, TMP var, C:\
	tempfile = getenv( "TEMP" );
	if ( tempfile == NULL )
	{
		tempfile = getenv( "TMP" );
	}
	if ( tempfile == NULL )
	{
		tempfile = "C:\\";
	}

	// Append temp filename
	strcat( tempfile, "PUSHD.TMP" );

	// Open temp file
	infile = fopen( tempfile, "r" );

	// Read directory from temp file, close, and delete
	fgets( olddir, 255, infile );
	fcloseall();
	remove( tempfile );

	// Change back to old drive and directory
	if( olddir[1] == ':' )
	{
		int drl = toupper( olddir[0] ) - 'A' + 1;
		_chdrive( drl );
	}
	chdir( olddir );

	// Let's go home
	exit( 0 );
}

