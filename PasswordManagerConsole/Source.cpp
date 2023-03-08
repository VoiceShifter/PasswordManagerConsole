#include "Functions.hpp"

const std::string DefaultFileName{ "Password.txt" };

void EncryptPassword()
{
	std::string Password;
	std::cout << "Enter the password\n";
	std::cin >> Password;
	AddPassword(HashPassword(Password));


}

std::string HashPassword(std::string& aPassword)
{
	for (char& Character : aPassword)
	{
		Character += 13;
	}
	return aPassword;
}

void AddPassword(std::string aPassword)
{
	std::fstream aFile(DefaultFileName, std::fstream::app);
	std::string Source{};

			
	std::cout << "Enter password source \n";
	std::cin >> Source;
	aFile << Source << " " << aPassword << '\n';
	aFile.close();

}

std::map<std::string, std::string>* PushPasswordsToMap()
{
	std::string aPassword{}, aSource{};
	std::fstream aFile(DefaultFileName, std::fstream::out);
	std::map<std::string, std::string> *aPasswordBook= new std::map<std::string, std::string>;
	while (aFile >> aSource >> aPassword) 
	{
		aPasswordBook->insert(aSource, aPassword);
	}
	return aPasswordBook;
}

std::string DecryptPassword(std::string& aPassword)
{
	for (char& Character : aPassword)
	{
		Character -= 13;
	}
	return aPassword;
}

void GetPassword(std::map<std::string, std::string>* aPasswordBook)
{
	std::string aSource{};
	std::cout << "Enter source of password";
	std::cin >> aSource;
	if (aPasswordBook->find(aSource) == aPasswordBook->end())
	{
		std::cout << "No such password\n\n";
		return;
	}
	std::string DecryptedPassword{ DecryptPassword(aPasswordBook->find(aSource)->second) };
	CopyToClipBoard(DecryptedPassword);
	
}

void CopyToClipBoard(std::string& aPassword)
{
	// Open the clipboard
	if (!OpenClipboard(NULL))
	{
		std::cerr << "Failed to open clipboard" << std::endl;
		return;
	}

	// Allocate global memory for the text to be copied
	std::string text = "Hello, world!";
	HGLOBAL hText = GlobalAlloc(GMEM_MOVEABLE, (text.size() + 1) * sizeof(char));
	if (!hText)
	{
		std::cerr << "Failed to allocate memory" << std::endl;
		CloseClipboard();
		return;
	}

	// Copy the text to the global memory
	char* pText = (char*)GlobalLock(hText);
	strcpy_s(pText, text.size() + 1, text.c_str());
	GlobalUnlock(hText);

	// Empty the clipboard and set the text
	EmptyClipboard();
	SetClipboardData(CF_TEXT, hText);

	// Close the clipboard
	CloseClipboard();

	std::cout << "Text copied to clipboard" << std::endl;

}

void CaseSwither()
{
	unsigned int CaseSwith{};
	std::cout << "Pick action ";
	std::cout << "1 - Add password\n2 - Get Password\n";
	std::cin >> CaseSwith;
	switch (CaseSwith)
	{
	case(1):
	{
		EncryptPassword();
	}
	case(2):
	{
		GetPassword(PushPasswordsToMap());
	}
	case(0):
		exit;
	}
}