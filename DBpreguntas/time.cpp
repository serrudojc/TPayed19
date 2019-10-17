// https://www.geeksforgeeks.org/c-program-print-current-day-date-time/
// C++ program to find Current Day, Date 
// and Local Time 
#include<iostream> 
#include<string.h>
#include<string>
#include<stdlib.h>
#include<ctime> 
using namespace std; 
int main() 
{   
    string fechaString;
    char fechaChar[30];
        
    // Declaring argument for time() 
    time_t tt; 
  
    // Declaring variable to store return value of 
    // localtime() 
    tm* ti; 

    // Applying time() 
    time (&tt); 
  
    // Using localtime() 
    ti = localtime(&tt); 

    fechaString = asctime(ti);
    strcpy(fechaChar, fechaString.c_str()); //or pass &fechaString[0]
    cout<<fechaChar<<endl;
     
    return 0; 
} 
