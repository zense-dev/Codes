/*
*	Date 30th August 2014	
*	@author Aditya Paliwal
*	Some arithmetic operations for very large numbers.
*	These functions are useful when a number is stored as a string
*	and cannot be stored as any of the default data types due to memory restrictions.
*/
#include<iostream>
#include<string>
using namespace std;

/*This function adds the two numbers a and b using grade school addition method*/
string add(string a, string b){	
	int a_length = a.length(), b_length = b.length();
	
	string c = "";		//This is the new string where the result will be stored
	
	int digit1, digit2, total = 0, carry = 0, j = 0, i = a_length -1;		//digit1 and digit2 are the digits of a and b respectively
	
	for(j = b_length -1; j >= 0 && i >= 0; j--){	//The loop runs till either of the numbers a or b run out of digits to compute upon
	
		digit1 = a[i] - 48;
		//The character is converted from its ASCII value to an integer value, computed upon and then converted back to ASCII
		digit2 = b[j] - 48;
		
		total = digit1 + digit2 + carry;
		carry = total / 10;
		
		if(carry != 0) total -= 10;	
		//The total should always be a single digit, so if a carry is present, it means that the number is greater than 10
		
		c = char(total + 48) + c;
		
		i--;
	}
	if(i >= 0){				//This handles the case where a has more digits than b
		while(i>=0){
		
			digit1 = a[i] - 48;
			
			total = digit1 + carry;
			carry = total/10;
			
			if(carry!=0) total -= 10;
			
			
			c = (char)(total + 48) + c;
			
			i--;
		}
	}
	if(j >= 0){							//This handles the case where b has more digits than a
		while(j>=0){
		
			digit2 = b[j] - 48;
			
			total = digit2 + carry;
			carry = total/10;
			
			if(carry!=0) total -= 10;
			
			c = (char)(total + 48) + c;
			
			j--;
		}
	}
	
	
	if (carry != 0) c = char(carry + 48) + c;		//This takes care of the final carry over if any
	
	j = 0;
	while(c[j] == '0') c = c.substr(j+1);			//This takes care of any useless 0s in the beginning of the string
	
	if(c.length() == 0) c = '0';					//If the number has no digits at all, it should be a zero
	
	
	return c;
}





/*Ths function subtracts two given strings of numbers. This function runs only for positive integers and assumes that a > b*/
string sub(string a, string b){
	int a_length = a.length(), b_length = b.length();
	
	string c = "";	//The result is appended into this string
	
	int borrow_from, i = a_length -1, j; // borrow_from is the index from which I am borrowing a number is necessary
	
	for(j = b_length -1; j >= 0; j--){ //Since we have assumed that b is always the smaller number, the loop conditon only checks for the number of digits in b
		if(b[j] <= a[i]) c = (char) (a[i] - b[j] + 48) + c;	//This is the case where we dont have to borrow from the next digits
		
		else{
			borrow_from = i - 1;	//In this case we have to borrow
			
			while(a[borrow_from] == '0') borrow_from--;//This loop gives us the first index from where we can borrow aa digit
			
			a[borrow_from++]--;	//Decrease the value of the digit from where we borrow by one and change index towards the next digit to the right
			while(borrow_from < i) a[borrow_from++] = 57;	//All numbers which could not lend a digit were 0s so now they change to 9s
			
			c = char(a[i] - b[j] + 58) + c; // After succesfully borrowing, we can now subtract the numbers
		}
		i--;
	}
	
	if(i >= 0){			//In case the string a has more digits than b, then the remaining digits are appended in this loop
		while(i>=0){
			c = a[i] + c;
			
			i--;
		}
	}
	
	j = 0;
	while(c[j] == '0') c = c.substr(j+1);	//All valueless 0s are removed from the beginning eg. 00001 becomes 1
	
	if(c.length() == 0) c = '0';	//In case the previous loop removes all digits, it means the number was 0. This is fixed here
	
	return c;
}




/*This function divides a string number by 2. Works only for positive numbers and returns the answer rounded down to nearest integer*/
string div_by_two(string a){
	int a_length = a.length();
	int i = 0, digit = 0, carry = 0;
	string c = "";		//The result is stored in this new string c
	for(i = 0; i < a_length; i++){
	
		digit = a[i] - 48;
		
		c = c + (char) ((( digit + carry )/2) + 48); //Each digit is divided by 2
		
		if ( digit%2 == 1) // If the digit was odd it will have a carry over to the next digit
			carry = 10;
		else
			carry = 0;
	}
	
	int j = 0;
	
	while(c[j] == '0') c = c.substr(j+1); //Removing the valuless 0s in the beginning
	
	if(c.length() == 0) c = '0';		//Fixes the case where the previous loop removes all 0s even thought the answer is zero
	
	return c;
}




int main(){
	string a,b;
	cin>>a>>b;
	cout<<add(a,b)<<endl;
	cout<<sub(a,b)<<endl;
	cout<<div_by_two(a)<<endl;
	return 0;
}
