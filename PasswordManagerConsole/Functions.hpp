# pragma once
# include <iostream>
# include <fstream>
# include <vector>
# include <string>
# include <map>
# include <Windows.h>


void CaseSwither();
void EncryptPassword();
void AddPassword(std::string aPassword);
std::string DecryptPassword(std::string& aPassword);
void GetPassword(std::map<std::string, std::string>* aPasswordBook);

std::string HashPassword(std::string& aPassword);



std::string DecryptPassword(std::string& aPassword);

std::string HashPassword(std::string& aPassword);

std::map<std::string, std::string>* PushPasswordsToMap();

void CopyToClipBoard(std::string& aPassword);