#include <iostream>

int main(){
    FILE *ajuda;
    ajuda = fopen("ajuda.txt","w");

    for (int i = 0; i < 5000; i++)
    {   
        fprintf(ajuda, "-1, \n");    
    }

    for (int i = 0; i < 5000; i++)
    {   
        fprintf(ajuda, "1, \n");    
    }
    
    return 0;
}