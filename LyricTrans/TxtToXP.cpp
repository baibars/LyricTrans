#include "stdafx.h"
#include "TxtToXP.h"

#include "Utils.h"

void TxtToXP::doTrans(void)
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

bool TxtToXP::transImp(const string& fileName)
{
	string inputFile = fileName + ".txt";
	string outputFile = fileName + "XP.txt";
	FILE* pFileIn = fopen(inputFile.c_str(), "rt");
	if (pFileIn)
	{
		FILE* pFileOut = fopen(outputFile.c_str(), "wb");

		char szBuff[10240];
		while (fgets(szBuff, 10240, pFileIn))
		{
			if ('\n' == szBuff[strlen(szBuff) - 1] || '\r' == szBuff[strlen(szBuff) - 1])
			{
				szBuff[strlen(szBuff) - 1] = 0;
			}
			if ('\n' == szBuff[strlen(szBuff) - 1] || '\r' == szBuff[strlen(szBuff) - 1])
			{
				szBuff[strlen(szBuff) - 1] = 0;
			}

			if (strstr(szBuff, "[id:") || strstr(szBuff, "[ar:")
				|| strstr(szBuff, "[ti:") || strstr(szBuff, "[by:")
				|| strstr(szBuff, "[hash:") || strstr(szBuff, "[al:")
				|| strstr(szBuff, "[sign:") || strstr(szBuff, "[qq:")
				|| strstr(szBuff, "[total:") || strstr(szBuff, "[offset:")
				|| strstr(szBuff, "[language:"))
			{
				continue;
			}

			vector<string> vWords;
			Utils::strSplit(szBuff, "<", vWords);

			vector<string> vInWord;
			Utils::strSplit(vWords[0], ",", vInWord);
			int startTime = atoi(vInWord[0].substr(1).c_str());
			int timeLen = atoi(vInWord[1].substr(0, vInWord[1].length() - 1).c_str());			
			for (int i = 1; i < vWords.size(); ++i)
			{
				vInWord.clear();
				Utils::strSplit(vWords[i], ",", vInWord);

				int wordStart = atoi(vInWord[0].c_str());
				int wordLen = atoi(vInWord[1].c_str());
				string word = vInWord[2].substr(2);

				if (string::npos != word.find(Utils::string_To_UTF8("¡¢"))
					|| string::npos != word.find(Utils::string_To_UTF8("£¨"))
					|| string::npos != word.find(Utils::string_To_UTF8("£©"))
					|| string::npos != word.find("(")
					|| string::npos != word.find(")"))
				{
					continue;
				}
				char szOut[260];
				sprintf(szOut, "%d,%d,%s\n", startTime + wordStart, wordLen, word.c_str());
				fputs(szOut, pFileOut);
			}
		}

		cout << inputFile.c_str() << " >>>>>>>> " << outputFile.c_str() << " [SUCCEEDED.]" << endl;
		fclose(pFileOut);
		fclose(pFileIn);
		return true;
	}
	else
	{
		cout << inputFile.c_str() << " [does not exist!]" << endl;
		return false;
	}
}

