// BEEP: Beeps the number of times specified
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

int main(int argc, char *argv[])
{
	char *stopstr;
	long l;
	int i;

	l = strtol(argv[1], &stopstr, 10);

	if (l == 0)
	{
		printf("Beeps the number of times specified\n");
		printf("\n");
		printf("BEEP count\n");
		printf("\n");
		printf("  count         Number of times to beep\n");
		exit(0);
	}

	for (i = 0; i < l; i++)
	{
		_asm
		{
			mov ah,2
			mov dl,7
			int 21h
		}
	}

	exit(0);
}
