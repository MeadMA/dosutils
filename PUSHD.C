// PUSHD: Saves the current working directory, and changes to the specified
//        directory. Use POPD to return to the saved directory.
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

int main(int argc, char *argv[])
{
	FILE *outfile;
	char *tempfile, *cwd, *helpchk;
	helpchk = "/?";

	if ( argc == 1 || strcmp( argv[1], helpchk ) == 0 ) {
		printf("Saves the current working directory, and changes to the specified\n");
		printf("directory. Use POPD to return to the saved directory.\n");
		printf("\n");
		printf("PUSHD [directory]\n");
		printf("\n");
		printf("  directory     The directory to change to\n");
		exit( 0 );
	}

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

	// Get current directory
	getcwd( cwd );

	// Open temp file
	outfile = _fsopen( tempfile, "wb", SH_DENYWR );

	// Write current directory to temp file and close
	fprintf( outfile, cwd );
	fcloseall();

	// Change to passed directory
	if( argv[1][1] == ':' )
	{
		int drl = toupper( argv[1][0] ) - 'A' + 1;
		_chdrive( drl );
	}
	chdir( argv[1] );

	// Let's go home
	exit( 0 );
}

