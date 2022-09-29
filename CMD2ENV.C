// CMD2ENV: Runs a given command, captures the output, and creates a batch
//          file to save that output to the __CMD2ENV environment variable.
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
	FILE *infile, *outfile;
	char tempfile[255], helpchk[2], *lastchar, cmd[255], output[255], outpath[255];
	int count = 0;
	strcpy( helpchk, "/?" );

	if ( argc == 1 || strcmp( argv[1], helpchk ) == 0 ) {
		printf("Runs a given command, captures the output, and creates a batch\n");
		printf("file to save that output to the __CMD2ENV environment variable.\n");
		printf("\n");
		printf("CMD2ENV [command]\n");
		printf("\n");
		printf("  command     The command to run and capture output from\n");
		printf("\n");
		printf("EXAMPLE:\n");
		printf("  cmd2env.exe getdrv.exe\n");
		printf("  call %TEMP%\_cmd2env.bat\n");
		printf("  A:\n");
		printf("  setup.exe\n");
		printf("  %__CMD2ENV%:\n");
		printf("  set __CMD2ENV=\n");
		exit( 0 );
	}

	// Combine arguments together
	strcpy( cmd, argv[1] );
	for( count = 2; count < argc; count = count + 1 )
	{
		strcat( cmd, " " );
		strcat( cmd, argv[count] );
	}

	// Get TEMP folder
	// Order of precedence: TEMP var, TMP var
	strcpy( tempfile, getenv( "TEMP" ) );
	if ( strlen(tempfile) == 0 )
	{
		strcpy( tempfile, getenv( "TMP" ) );
	}
	if ( strlen(tempfile) == 0 )
	{
		printf( "ERROR: Must set either TEMP or TMP variable\n" );
		exit( 2 );
	}

	// Make sure path ends with backslash
	lastchar = &tempfile[strlen(tempfile)-1];
	if ( strcmp(lastchar, "\\") != 0 )
	{
		strcat( tempfile, "\\" );
	}

	// Append temp filename
	strcpy( outpath, tempfile );
	strcat( tempfile, "CMD2ENV.TMP" );
	strcat( outpath, "_CMD2ENV.BAT" );

	// Put together command to run
	strcat( cmd, " > " );
	strcat( cmd, tempfile );

	// Execute command
	system( cmd );

	// Open temp file
	infile = fopen( tempfile, "r" );

	// Read output from temp file, close, and delete
	fgets( output, 255, infile );
	fcloseall();
	remove( tempfile );

	// Write batch file
	strcpy( cmd, "set __CMD2ENV=" );
	strcat( cmd, output );
	outfile = fopen( outpath, "w" );
	fputs( cmd, outfile );

	// Let's go home
	exit( 0 );
}
