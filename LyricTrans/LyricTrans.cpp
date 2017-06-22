#include "stdafx.h"

#include "KrcToTxt.h"
#include "TxtToXP.h"

int main()
{
	int code = 0;

	while (true)
	{
		cout << "1. Krc to Txt" << endl;
		cout << "2. Txt to XP" << endl;
		cout << "0. Exit" << endl;
		cout << "your choice: ";
		cin >> code;

		switch (code)
		{
		case 1:
			KrcToTxt::doTrans();
			break;
		case 2:
			TxtToXP::doTrans();
			break;
		case 0:
			return 0;
			break;
		default:
			break;
		}

		cout << "------------------------------------------------" << endl << endl;
	}

    return 0;
}