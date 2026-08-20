#pragma once

// demonized: export console mark enum outside of CConsole class
enum Console_mark // (int)=char
{
	no_mark = ' ',
	mark0 = '~',
	mark1 = '!',
	// error
	mark2 = '@',
	// console cmd
	mark3 = '#',
	mark4 = '$',
	mark5 = '%',
	mark6 = '^',
	mark7 = '&',
	mark8 = '*',
	mark9 = '-',
	// green = ok
	mark10 = '+',
	mark11 = '=',
	mark12 = '/'
};
