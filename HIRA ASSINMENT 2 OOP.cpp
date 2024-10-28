#include<iostream>
#include<cstring>
#include<string>
using namespace std;
#define _CRT_SECURE_NO_WARNINGS
class mystring {
private:
    char* str;
    int length;

    //add getting string from buffer
    static char* string_getting_from_buffer(char* str) {
        if (!str) {
            return nullptr;
        }
        else {
            size_t size = strlen(str) + 1;
            char* newstring = new char[size];
            strcpy_s(newstring, size, str); // Using strcpy_s
            return newstring;
        }
    }

    //here i will add concatenation function
    static char* concatenation_of_strings(char* first_string, char* second_string) {
        size_t mylength1 = strlen(first_string);
        size_t mylength2 = strlen(second_string);
        char* concatenation_string = new char[mylength1 + mylength2 + 1];
        strcpy_s(concatenation_string, mylength1 + mylength2 + 1, first_string); // Using strcpy_s
        strcat(concatenation_string, second_string); //qk yha pr hum append kar ky then copy krein gy warna issue hu ga
        return concatenation_string;
    }

    //here i will compare two strings with the help of the strcmp
    static int comparison_of_strings(char* first_string, char* second_string) {
        return strcmp(first_string, second_string);
    }

public:
    //first of all the default constructor
    mystring() {
        str = nullptr;
        length = 0;
    }

    //copy constructor
    mystring(const mystring& other) {
        length = other.length;
        str = string_getting_from_buffer(other.str);
    }

    ~mystring() {
        delete[] str;
    }

    //from now i will add operators overloaded functions to facilitate my required output
    mystring operator+(const mystring& other) {
        char* newstring = concatenation_of_strings(this->str, other.str);
        //yha pr this refer kar raha ha object 1 ko (current object )
        //yha pr other refer kar raha ha object 2 ko jis ko hum as a parameter pass kar rahy hn
        mystring variable; //here temporary object is created to keep maintain the original things unchanged 
        variable.str = newstring;
        variable.length = strlen(newstring);
        return variable;
    }

    //assignment operator
    mystring& operator=(const mystring& other) {
        if (this != &other) {
            delete[] str;
            length = other.length; //yha pr jis object ko hum copy karwana chahty hn uski length pehly hi calculate kar rahy hn hum
            str = string_getting_from_buffer(other.str); //hum ne yha pr yh function is lye use kiya k isky pass string store karwany ki place ha is ky through hum string ko agy ja kar input lein gy qk humy jaga bhi chahye jhan pr string ko input karna ha humne
        }
        return *this;
    }

    //comparison operator
    bool operator<(const mystring& other) {
        return comparison_of_strings(this->str, other.str);
    }

    //output overloading
    friend ostream& operator<<(ostream& os, const mystring& other) {
        os << other.str;
        return os;
    }

    //! not operator overloading
    bool operator!() {
        return (str == nullptr);
    }

    //[] overloading
    char& operator[](int index) {
        if (index < 0 || index >= length) {
            cout << "the index is out of the range" << endl;
        }
        return str[index];
    }

    friend istream& operator>>(istream& is, mystring& other) {
        char character[500];
        is >> character;
        other.str = string_getting_from_buffer(character);  // Allocate new memory and copy input
        other.length = strlen(character);  // Update length
        return is;
    }

    // Overload the () operator to get a substring
    mystring operator()(int start, int end) {
        return this->substring(start, end);
    }

    mystring substring(int start, int end) {
        if (start < 0 || end >= length || start > end) {
            cout << "Invalid range for substring." << endl;
            return mystring();
        }
        char* substrings = new char[end - start + 2]; // Allocate for substring aur end-start+1 tu humari length of substring ha end-start+2 null terminator k lye ha
        strncpy(substrings, str + start, end - start + 1); //yh strncpy characters ko copy karta ha ek jaga se dosri jga pr
        //substrings woh jaga ha jhan pr hum copy karein gy 
        //str+start humary pass is case me character 6 se start hu ga
        substrings[end - start + 1] = '\0'; // Null terminate
        mystring subStr; //this is the temporary object to match the return type 
        subStr.str = substrings;
        subStr.length = end - start + 1;
        return subStr;
    }
};

int main() {
    mystring str1, str2, str3, str4; //Default constructor will make a string of length 0 but having null character(only) i.e. empty string
    if (!str1) {
        cout << "String 1 is Empty.\n";
        cout << "Str 1 = " << str1 << endl << endl << endl;
    }
    cout << "Enter String 1:\t";
    cin >> str1;
    cout << "Enter String 2:\t";
    cin >> str2;
    cout << "\n\n\nUser Entered:\n";
    cout << "String1 = " << str1 << endl;
    cout << "String 2 = " << str2 << endl << endl << endl;

    //What is following code testing? cout<<"Before str1 = str1; str1 = "<<str1<<endl; str1 = str1;
    cout << "After str1 = str1, str1 = " << str1 << endl << endl << endl;
    cout << "Before str4 = str3 = str1 + str2\n";
    cout << "str1 =" << str1 << endl;
    cout << "str2 =" << str2 << endl;
    cout << "str3 =" << str3 << endl;
    cout << "str4 = " << str4 << endl;

    str4 = str3 = str1 + str2;

    cout << "\n\n\nAfter str4 = str3 = str1 + str2\n";
    cout << "str1 = " << str1 << endl;
    cout << "str2 = " << str2 << endl;
    cout << "str3 =" << str3 << endl;
    cout << "str4 = " << str4 << endl;

    cout << "\n\n\nEnter String 3:\t";
    cin >> str3;
    cout << "\n\n\nEnter String 4:\t";
    cin >> str4;
    cout << "\n\n\nstr3 = " << str3 << endl;
    cout << "str4 = " << str4 << endl;

    if (str3 < str4)
        cout << "String 3 is Less than String 4.\n";
    else
        cout << "String 3 is NOT Less than String 4.\n";

    mystring str5 = str1 + str2;
    cout << "\n\n\nStr5:\t" << str5 << endl;

    cout << "Str5." << endl;
        str5[7] = '$';
    cout << "\n\nStr5:\t" << str5 << endl;

    mystring subStr = str5(5, 10);
    cout << subStr;

    system("pause");
    return 0;
}
