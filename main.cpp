/*Main File: Use of crypt library.*/

#include "crypt"

// Define your own methods like:

void ap_series(int &a)
{
	if(a==-1) {
		a=0; return;
	}
	a+=1;	// ap series 1,2,3,4,5,...
}

void ap_skip(int &a)
{
	if(a==-1) {
		a=0; return;
	}
	a=5;	// const 5 bytes skip
}

int main()
{
	std::string path=str_input("Enter File Path: ",buf_off);
	int crypt_type=int_input("Enter 1 to Encrypt, 0 to Decrypt,\n",buf_on);
	std::string secret_code=str_input("Enter secret code: ",buf_off);
	
	if(crypt_type)
		encrypt(path.c_str(),secret_code.c_str(),ap_series,ap_skip);
	else
		decrypt(path.c_str(),secret_code.c_str(),ap_series,ap_skip);
	return 0;
}