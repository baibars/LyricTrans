#include "stdafx.h"
#include "KrcToTxt.h"

#include "zlib.h"

void KrcToTxt::doTrans(void)
{
	FILE* pf = fopen("TransList.txt", "rt");
	if (pf)
	{
		char szBuff[260];
		while (fgets(szBuff, 260, pf))
		{
			if ('\n' == szBuff[strlen(szBuff) - 1] || '\r' == szBuff[strlen(szBuff) - 1])
			{
				szBuff[strlen(szBuff) - 1] = 0;
			}
			if ('\n' == szBuff[strlen(szBuff) - 1] || '\r' == szBuff[strlen(szBuff) - 1])
			{
				szBuff[strlen(szBuff) - 1] = 0;
			}

			char* pPos = strstr(szBuff, ".");
			if (pPos)
			{
				pPos[0] = 0;
			}
			transImp(szBuff);
		}
		fclose(pf);
	}
	else
	{
		cout << "TransList.txt does not exist." << endl;
	}
}

bool KrcToTxt::transImp(const string& fileName)
{
	string inputFile = fileName + ".krc";
	string outputFile = fileName + ".txt";
	FILE* pFileIn = fopen(inputFile.c_str(), "rb");
	if (pFileIn)
	{
		fseek(pFileIn, 0, SEEK_END);
		unsigned long lenIn = ftell(pFileIn);
		fseek(pFileIn, 0, SEEK_SET);
		unsigned char* pBuffIn = new unsigned char[lenIn + 1];
		fread(pBuffIn, 1, lenIn, pFileIn);

		const unsigned char key[] = { 64, 71, 97, 119, 94, 50, 116, 71, 81, 54, 49, 45, 206, 210, 110, 105 };
		for (unsigned long i = 4; i < lenIn; ++i)
		{
			pBuffIn[i] = pBuffIn[i] ^ key[(i - 4) % 16];
		}

		unsigned long lenOut = lenIn * 3;
		unsigned char* pBuffOut = new unsigned char[lenOut];
		int ret = uncompress(pBuffOut, &lenOut, pBuffIn + 4, lenIn - 4);
		if (0 == ret)
		{
			FILE* pFileOut = fopen(outputFile.c_str(), "wb");
			fwrite(pBuffOut, 1, lenOut, pFileOut);
			fclose(pFileOut);
		}
		else
		{
			cout << inputFile.c_str() << " [translate failed!]" << endl;
			fclose(pFileIn);
			return false;
		}

		cout << inputFile.c_str() << " >>>>>>>> " << outputFile.c_str() << " [SUCCEEDED.]" << endl;
		fclose(pFileIn);
		return true;
	}
	else
	{
		cout << inputFile.c_str() << " [does not exist!]" << endl;
		return false;
	}
}

