/* Functions to Encrypt/Decrypt a Binary/Text file */
/* Date: 22/03/2022		Modified: 22/06/2022*/

#ifndef _FUNCTION_DEFINATION
#define _FUNCTION_DEFINATION

#include "crypt"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
using namespace std;

// Defining none method.
void method_none(int &a) {
	if(a==-1)
		a=0;	// always 0
}

// For integer input.
int int_input(string s_out=0,int buf=buf_off)
{
	int integer;
	cout<<s_out;
	cin>>integer;
	if(buf==buf_on)
		cin.get();
	return integer;
}

// For string input.
string str_input(string s_out=0,int buf=buf_off)
{
	string str;
	cout<<s_out;
	getline(cin,str);
	if(buf==buf_on)
		cin.get();
	return str;
}

// To get file size.
streampos filesize(const char *file_path) {
	fstream file(file_path,ios::binary|ios::in|ios::ate);
	streampos size=file.tellg();
	file.close();
	return size;
}

/* To encrypt file with a secret code and
series and skip bytes method if provided */
int encrypt(const char *file_path,
			const char *secret_code,
			void (*series)(int&)=method_none,
			void (*skip)(int&)=method_none)
{
	fstream file(file_path,ios::binary|ios::in|ios::out);
	
	if(!file) {
		cout<<"ERROR: The File not Found";
		return 1;
	}
	streampos size=filesize(file_path);
	int i=0,sterm=-1,skipbits=-1;
	series(sterm);
	skip(skipbits);
	file.seekg(skipbits,ios::cur);
	
	while(true)
	{
		char c=file.get();
		if(file.eof())
			break;
		file.seekg(-1,ios::cur);
		
		file.put(c+secret_code[i]+sterm);
		i++;
		if(i>=strlen(secret_code)) {
			skip(skipbits);
			file.seekg(skipbits,ios::cur);
			series(sterm); i=0;
		}
		printf("\rEncrypting... %.1f%%",(file.tellg()*100.0)/size);
	}
	file.close();
	printf("\rEncryption Successful...\n");
	return 0;
}

/* To decrypt file with a secret code and
series and skip bytes method if provided */
int decrypt(const char *file_path,
			const char *secret_code,
			void (*series)(int&)=method_none,
			void (*skip)(int&)=method_none)
{
	fstream file(file_path,ios::binary|ios::in|ios::out);
	
	if(!file) {
		cout<<"ERROR: The File not Found";
		return 1;
	}
	streampos size=filesize(file_path);
	int i=0,sterm=-1,skipbits=-1;
	series(sterm);
	skip(skipbits);
	file.seekg(skipbits,ios::cur);
	
	while(true)
	{
		char c=file.get();
		if(file.eof())
			break;
		file.seekg(-1,ios::cur);
		
		file.put(c-secret_code[i]-sterm);
		i++;
		if(i>=strlen(secret_code)) {
			skip(skipbits);
			file.seekg(skipbits,ios::cur);
			series(sterm); i=0;
		}
		printf("\rDecrypting... %.1f%%",(file.tellg()*100.0)/size);
	}
	file.close();
	printf("\rDecryption Successful...\n");
	return 0;
}

#endif

/* END FUNCTION DEFINITIONS */