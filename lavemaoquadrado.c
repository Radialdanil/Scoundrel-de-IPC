#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main(){
    int random, rp, rpp, cont;
    rp = 5;
    rpp = 5;
    srand(time(NULL));

    while(1){
        do{
            do{
                random = rand()%4+1;
                srand(rand()+rand()*rand()+rand()*rand());
            } while(random == rp);
            rp = random;
        }while(rpp==rp);
        rpp = rp;
        for(cont = 0; cont < rp; cont++){
            printf(" ");
        }
        Sleep(50);
        printf("%d\n", rp);
    }
return 0;
}
