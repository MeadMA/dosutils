// GETDRV: Gets the current drive, prints it to the screen, and
//         returns it as an exit code
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

#include <direct.h>
#include <stdio.h>
#include <process.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int cdrv = _getdrive();
	if (argv[1] != NULL)
	{
		printf("Gets the current drive, prints it to the screen, and\n");
		printf("returns it as an exit code\n");
		printf("1 = A, 2 = B, 3 = C, etc.\n");
		printf("\n");
		printf("GETDRV\n");
		printf("\n");
		printf("EXAMPLE:\n");
		printf("  :DRVCHK\n");
		printf("  getdrv.exe > nul\n");
		printf("  if not errorlevel 3 echo Switch to your floppy drive, and try again\n");
		printf("  pause\n");
		printf("  goto :DRVCHK\n");
		exit(0);
	}

	// Get current drive as integer, and return as exit code
	printf("%c", cdrv + 64);
	exit(cdrv);
}
