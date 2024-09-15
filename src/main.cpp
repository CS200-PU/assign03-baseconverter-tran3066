//******************************************************************************
// File name:   main.cpp
// Author:      Jason Tran
// Date:        09/14/2024
// Class:       CS200-01
// Assignment:  Base Converter
// Purpose:     Automatically converts a number in a specified base inputted by 
//              the user to equivalent numbers in the other bases
// Hours:       4
//******************************************************************************

#include <iostream>

using namespace std;

const string HEX_PREFIX = "0x";
const string BINARY_PREFIX = "0b";
const char ASCII_ZERO = '0';
const char DECIMAL_NUM = 'D';
const char HEX_NUM = 'H';
const char BINARY_NUM = 'B';
const int ASCII_SHIFT = 55;
const int PREFIX_LENGTH = 2;

string reverseString (const string& str);
char intToHexChar (int intDigit);
int hexCharToInt (char hexDigit);
char getBase (const string& strNumber);
string getNumber (const string& prompt);
void printTitle (const string& myTitle);
string binaryToDecimal (const string& strNumber);
string decimalToBinary (const string& strNumber);
string decimalToHex (const string& strNumber);
string hexToDecimal (const string& strNumber);
string hexToBinary (const string& strNumber);
string binaryToHex (const string& strNumber);

//***************************************************************************
// Function:    main
//
// Description: Converts a number in a specified base to equivalent numbers in
//              the other bases
//
// Parameters:  None
//
// Returned:    Exit Status
//***************************************************************************

int main () {
  const string QUIT = "q";

  string inputNum;
  string title = "**************************************\n"
                 "*****HEX-DECIMAL-BINARY CONVERTER*****\n"
                 "**************************************";

  printTitle (title);

  while (true) {
    inputNum = getNumber("\nEnter your string to convert (q to quit): ");

    if (inputNum == QUIT) {
      break;
    }
    else if (getBase (inputNum) == DECIMAL_NUM) {
      cout << "The binary conversion is: " << decimalToBinary (inputNum) 
           << endl;
      cout << "The hexadecimal conversion is: " << decimalToHex (inputNum) 
           << endl;
    }
    else if (getBase (inputNum) == BINARY_NUM) {
      cout << "The decimal conversion is: " << binaryToDecimal (inputNum)
           << endl;
      cout << "The hexadecimal conversion is: " << binaryToHex (inputNum)
           << endl;
    }
    else if (getBase (inputNum) == HEX_NUM) {
      cout << "The decimal conversion is: " << hexToDecimal (inputNum)
           << endl;
      cout << "The binary conversion is: " << hexToBinary (inputNum)
           << endl;
    }
  }

  return EXIT_SUCCESS;
}

//***************************************************************************
// Function:    reverseString
//
// Description: reverses a string
//
// Parameters:  str - string to reverse
//
// Returned:    reverse of str
//***************************************************************************

string reverseString (const string& str) {
  string reversedString;

  for (int i = str.length() - 1; i >= 0; i--) {
    reversedString += str[i];
  }

  return reversedString;
}

//***************************************************************************
// Function:    intToHexChar
//
// Description: Converts a decimal number to its equivalent hexadecimal
//              character
//
// Parameters:  intDigit - decimal number
//
// Returned:    hex character equivalent of decimal number
//***************************************************************************

char intToHexChar (int intDigit) {
  const int LESS_THAN_TEN = 10;

  char retVal;

  if (intDigit < LESS_THAN_TEN) {
    retVal = intDigit + ASCII_ZERO;
  }
  else {
    retVal = intDigit + ASCII_SHIFT; 
  }

  return retVal;
}

//***************************************************************************
// Function:    hexCharToInt
//
// Description: Converts a hexadecimal character to its equivalent decimal 
//              number
//
// Parameters:  hexDigit - hexadecimal character
//
// Returned:    decimal number equivalent of hex character
//***************************************************************************

int hexCharToInt (char hexDigit) {
  const char ASCII_NINE = '9';

  int retVal;

  if (hexDigit >= ASCII_ZERO && hexDigit <= ASCII_NINE) {
    retVal =  hexDigit - ASCII_ZERO;
  }
  else {
    retVal = hexDigit - ASCII_SHIFT;
  }

  return retVal;
}

//***************************************************************************
// Function:    getBase
//
// Description: Determines the type of base of a number
//
// Parameters:  strNumber - string representing a decimal, hexadecimal, 
//                          or binary number
//
// Returned:    D if the number is a decimal, H if the number is a 
//              hexadecimal, or B if the number is binary
//***************************************************************************

char getBase (const string& strNumber) {
  const int GREATER_THAN_TWO = 2;
  const int INDEX_ONE = 0;
  const int INDEX_THREE = 2;

  char retVal;

  if (strNumber.size () > GREATER_THAN_TWO && 
      strNumber.substr (INDEX_ONE, INDEX_THREE) == HEX_PREFIX) {
    retVal = HEX_NUM;
  }
  else if (strNumber.size () > GREATER_THAN_TWO && 
           strNumber.substr (INDEX_ONE, INDEX_THREE) == BINARY_PREFIX) {
    retVal = BINARY_NUM;
  }
  else {
    retVal = DECIMAL_NUM;
  }

  return retVal;
}

//***************************************************************************
// Function:    getNumber
//
// Description: Obtains a number from the user prompt
//
// Parameters:  prompt - string that asks user for number
//
// Returned:    string representing a decimal, hexadecimal, or binary number
//***************************************************************************

string getNumber (const string& prompt) {
  string userInput;

  cout << prompt;
  cin >> userInput;

  return userInput;
}

//***************************************************************************
// Function:    printTitle
//
// Description: prints the title
//
// Parameters:  myTitle - title to print
//
// Returned:    None
//***************************************************************************

void printTitle (const string& myTitle) {
  cout << myTitle;
}

//***************************************************************************
// Function:    binaryToDecimal
//
// Description: Converts a binary number to a decimal number
//
// Parameters:  strNumber - string representing a binary number
//
// Returned:    string representing the decimal equivalent
//***************************************************************************

string binaryToDecimal (const string& strNumber) {
  const int NEXT_POWER = 2;

  int decimalNumber = 0;
  int base = 1;
  char currentDigit;
  string binaryNumber;

  binaryNumber = strNumber.substr (PREFIX_LENGTH);

  for (int i = binaryNumber.size () - 1; i >= 0; i--) {
    currentDigit = binaryNumber[i];

    if (currentDigit == '1') {
      decimalNumber += base;
    }

    base *= NEXT_POWER;
  }

  return to_string (decimalNumber);
}

//***************************************************************************
// Function:    decimalToBinary
//
// Description: Converts a decimal number to a binary number
//
// Parameters:  strNumber - string representing a decimal number
//
// Returned:    string representing the binary equivalent
//***************************************************************************

string decimalToBinary (const string& strNumber) {
  const int DIVIDE_BY_TWO = 2;

  string binaryNumber;
  int decimalNumber = stoi (strNumber);
  int remainder;

  if (decimalNumber == 0) {
    binaryNumber = "0";
  }
  else {
    while (decimalNumber != 0) {
    remainder = decimalNumber % DIVIDE_BY_TWO;
    binaryNumber += to_string (remainder);
    decimalNumber = decimalNumber / DIVIDE_BY_TWO;
    }
  }

  binaryNumber = reverseString (binaryNumber);
  binaryNumber = BINARY_PREFIX + binaryNumber;

  return binaryNumber;
}

//***************************************************************************
// Function:    decimalToHex
//
// Description: Converts a decimal number to a hexadecimal number
//
// Parameters:  strNumber - string representing a decimal number
//
// Returned:    string representing the hexadecimal equivalent
//***************************************************************************

string decimalToHex (const string& strNumber) {
  const int DIVIDE_BY_SIXTEEN = 16;

  string hexNumber;
  int decimalNumber = stoi (strNumber);
  int remainder;

  if (decimalNumber == 0) {
    hexNumber = "0";
  }
  else {
    while (decimalNumber != 0) {
    remainder = decimalNumber % DIVIDE_BY_SIXTEEN;
    hexNumber += intToHexChar (remainder);
    decimalNumber = decimalNumber / DIVIDE_BY_SIXTEEN;
    }
  }

  hexNumber = reverseString (hexNumber);
  hexNumber = HEX_PREFIX + hexNumber;

  return hexNumber;
}

//***************************************************************************
// Function:    hexToDecimal
//
// Description: Converts a hexadecimal number to a decimal number
//
// Parameters:  strNumber - string representing a hexadecimal number
//
// Returned:    string representing the decimal equivalent
//***************************************************************************

string hexToDecimal (const string& strNumber) {
  const int NEXT_POWER = 16;

  int decimalNumber = 0;
  int base = 1;
  int currentDigit;
  string hexNumber;

  hexNumber = strNumber.substr (PREFIX_LENGTH);

  for (int i = hexNumber.size () - 1; i >= 0; i--) {
    currentDigit = hexCharToInt (hexNumber[i]);
    decimalNumber += (currentDigit * base);
    base *= NEXT_POWER;
  }

  return to_string (decimalNumber);
}

//***************************************************************************
// Function:    hexToBinary
//
// Description: Converts a hexadecimal number to a binary number
//
// Parameters:  strNumber - string representing a hexadecimal number 
//
// Returned:    string representing the binary equivalent
//***************************************************************************

string hexToBinary (const string& strNumber) {
  return decimalToBinary (hexToDecimal (strNumber));
}

//***************************************************************************
// Function:    binaryToHex
//
// Description: Converts a binary number to a hexadecimal number
//
// Parameters:  strNumber - string representing a binary number
//
// Returned:    string representing the hexadecimal equivalent
//***************************************************************************

string binaryToHex (const string& strNumber) {
  return decimalToHex (binaryToDecimal (strNumber));
}