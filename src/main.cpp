#include "MyApp.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio> 
#include <unistd.h>
#include <vector>
char *getcwd(char *buf, size_t size);

vector<string> recipe;


using namespace std;

int main()
{

  FILE* ptr; //file location after parsing
    char ch; //
  
    ptr = fopen("src/DummyData.txt", "r");
 
    if (NULL == ptr) {
        perror("Error");
    }
  
    // Printing what is written in file
    // character by character using loop.
    do {
      while(ch != '\n'){
        ch = fgetc(ptr);
        printf("%c", ch); 
      }
    } while (ch != EOF);
 
    // Closing the file
    fclose(ptr);
  
  return 0;
}
