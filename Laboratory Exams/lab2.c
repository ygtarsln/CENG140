#include "stdio.h"
#include "lab2.h"

/* TASK SOLUTIONS */
void print_sentence(char * sentence) {
    int i = 0;
    while (sentence[i] != '!'){
        if (sentence[i] == '_'){
            i++;
            continue;
        }
        printf("%c",sentence[i]);
        i++;
    }
    printf("\n");
}

void capital(char * sentence) {
    int i = 0;
    int pos = 0;
    int counter = 0;
    int k;
    for (i = 0; sentence[i] != '!'; i++,counter++){
        if (sentence[i] == ' '){
            pos += counter+1;
        }
        else if (sentence[i] == '_'){
            if (sentence[pos] >= 'a'){
                sentence[pos] -= 32;
            }
            for (k = i; sentence[k] != '!'; k++){
                sentence[k] = sentence[k+1];
                
            }
            i--;
            counter--;
        }
    }
}

void sortPos(int * arr, int * sortedArr) {
    int changed = 1, i, k, temp;
    while (changed){
        changed = 0;
        i = 0;
        while (arr[i+1] != 0){
            if (arr[i] > arr[i+1]){
                changed = 1;
                temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
            }
            i++;
        }
    }
    
    for (k = 0; k < posLen; k++){
        sortedArr[k] = arr[k];
    }
    
}

void to_ascii (char * sentence, int * positions, int count, char * ascii_result) {
    int i = 0, a = 0;
    int k;
    while (positions[i] != 0){
        for (k = positions[i]; k < positions[i]+count; k++){
            if ((sentence[k] >= 65 && sentence[k] <= 90)||(sentence[k] >= 97 && sentence[k] <= 122)){
                if (sentence[k] >= 100){
                    ascii_result[a] = (int)sentence[k]/100+'0';
                    ascii_result[a+1] = ((int)sentence[k]-100)/10+'0';
                    ascii_result[a+2] = ((int)sentence[k]%10)+'0';
                    a += 3;
                }
                
                else{
                    ascii_result[a] = '0';
                    ascii_result[a+1] = ((int)sentence[k]/10)+'0';
                    ascii_result[a+2] = ((int)sentence[k]%10)+'0';
                    a += 3;
                }
            }
            
            else{
                ascii_result[a] = sentence[k];
                a++;
            }
            
        }
     i++;   
    }
    
}

void sos(char map[3][3], int locations[9][2], char labels[9]) {
    int winning[9] = {1,2,1,2,1,2,1,2,1};
    int i,k = 0;
    for (i = 0; i < 9; i++){
        map[locations[i][0]][locations[i][1]] = labels[i];
        
        if ((map[0][0] == 'S' && map[0][1] == 'O' && map[0][2] == 'S')||
        (map[1][0] == 'S' && map[1][1] == 'O' && map[1][2] == 'S')||
        (map[2][0] == 'S' && map[2][1] == 'O' && map[2][2] == 'S')||
        (map[0][0] == 'S' && map[1][0] == 'O' && map[2][0] == 'S')||
        (map[0][1] == 'S' && map[1][1] == 'O' && map[2][1] == 'S')||
        (map[0][2] == 'S' && map[1][2] == 'O' && map[2][2] == 'S')||
        (map[0][0] == 'S' && map[1][1] == 'O' && map[2][2] == 'S')||
        (map[0][2] == 'S' && map[1][1] == 'O' && map[2][0] == 'S')){
            printf("Player %d wins the game.\n",winning[k]);
            return;
        }
        
        else{
            k++;
        }
    }
    printf("Draw Game.\n");
}
