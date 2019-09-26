#pragma once

const char* WcsToMbcs(const char* src);
const char* MbcsToWcs(const char* src);
const string& WstringToString(const string& src);
const string& StringToWstring(const string& src);

string& ltrim(string &s);
string& rtrim(string &s);
string& trim(string &s);

#define W2S WstringToString
#define S2W StringToWstring