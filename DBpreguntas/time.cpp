// https://www.geeksforgeeks.org/c-program-print-current-day-date-time/
// C++ program to find Current Day, Date 
// and Local Time 
#include<iostream> 
#include<ctime> 
using namespace std; 
int main() 
{   char fecha[30];
    // Declaring argument for time() 
    time_t tt; 
  
    // Declaring variable to store return value of 
    // localtime() 
    struct tm * ti; 
  
    // Applying time() 
    time (&tt); 
  
    // Using localtime() 
    ti = localtime(&tt); 
  
    cout << "Current Day, Date and Time is = " 
         << asctime(ti); 
    fecha = asctime(ti);
    cout<<fecha<<endl;
  return 0; 
} 
