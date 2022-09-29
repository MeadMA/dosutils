// SLEEP: Waits number of seconds specified
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
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *stopstr;
	unsigned long ul, upper, lower;
	ul = strtoul(argv[1], &stopstr, 10);

	if (ul == 0)
	{
		printf("Waits number of seconds specified\n");
		printf("\n");
		printf("SLEEP count\n");
		printf("\n");
		printf("  count         Number of seconds to wait\n");
		exit(0);
	}

	// Convert seconds to microseconds
	ul = ul * 1000000;

	// Split number into upper and lower two byte blocks
	// Will be put into CX and DX registers later
	upper = ul / 65536;
	lower = ul - (upper * 65536);

	// int 15h, func 86h
	// 32-bit number
	// Upper 16 bits in CX, lower 16 bits in DX
	_asm
	{
		mov al,0
		mov ah,86h
		mov cx,upper
		mov dx,lower
		int 15h
	}

	exit(0);
}
