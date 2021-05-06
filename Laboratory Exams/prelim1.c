#include <stdio.h>
/* A simple crypto exchange system including operations:
R: Read balance
D: Deposit
W: Withdraw
X: Exchange
S: Suggestion buy 
*/

float try_btc = 0.0555;
float btc_try = 18.0180;
float try_eth = 0.0833;
float eth_try = 12.0048;
float btc_eth = 1.5001;
float eth_btc = 0.6666;
float tr;
float btc = 0;
float eth = 0;
char currency;
char op;
char cur;
char sell;
char buy;
float temp;
float fl_amount;
float amount;
float loss1,loss2,exp_gain1,exp_gain2,gain1,gain2;
char code1,code2;

int main()
    {

    scanf("%c %f",&currency,&tr);
    
    if (currency != 'T'){
        tr = 0;
        printf("Error: Operation could not be completed.");
    }
    else{
        
    
        while (1){
            scanf("%c",&op);

            if (op == 'Q'){
                printf("Bye...\n");
                return 0;
            }
            
            if (op == 'R'){
                if (btc == 0 && eth == 0){
                    printf("Our account holds %.2f TRY.\n",tr);
                }
                
                else if (btc == 0 && eth != 0){
                    printf("Our account holds %.2f TRY | %.2f ETH.\n",tr,eth);
                }
                
                else if (btc != 0 && eth == 0){
                    printf("Our account holds %.2f TRY | %.2f BTC.\n",tr,btc);
                }
                
                else if (btc != 0 && eth != 0){
                    printf("Our account holds %.2f TRY | %.2f BTC | %.2f ETH.\n",tr,btc,eth);
                }
            }
            if (op == 'D'){
                scanf(" %c %f",&cur,&temp);
                
                if (cur != 'B' && cur != 'T' && cur != 'E'){
                    printf("Error: Operation could not be completed.\n");
                }
                
                else if (cur == 'T') {
                    tr += temp;
                }
                
                else if (cur == 'B'){
                    btc += temp;
                }
                
                else if (cur == 'E'){
                    eth += temp;
                }
            }
            if (op == 'W'){
                scanf(" %c %f",&cur,&temp);
                
                if (cur != 'B' && cur != 'T' && cur != 'E'){
                    printf("Error: Operation could not be completed.\n");
                }
                
                else if (cur == 'T') {
                    if (temp > tr){
                        printf("Error: Insufficient funds.\n");
                    }
                    else{
                        tr -= temp;
                    }
                }
                
                else if (cur == 'B'){
                    if (temp > btc){
                        printf("Error: Insufficient funds.\n");
                    }
                    else{
                        btc -= temp;
                    }
                }
                
                else if (cur == 'E'){
                    if (temp > eth){
                        printf("Error: Insufficient funds.\n");
                    }
                    else{
                        eth -= temp;
                    }
                }
            }
            
            if (op == 'X'){
                scanf(" %c %f %c",&sell,&temp,&buy);
                
                if (sell == 'T' && buy == 'B'){
                    if (temp <= tr){
                        fl_amount = temp/btc_try;
                        tr -= temp;
                        btc += fl_amount;
                        printf("You have successfully bought %.2f BTC.\n",fl_amount);
                    }
                    else if (temp > tr){
                        amount = (float)(int)(tr/btc_try);
                        tr -= amount*btc_try;
                        btc += amount;
                        printf("This amount is too much, you have successfully bought %.2f BTC.\n",amount);
                    }
                }
                else if (sell == 'T' && buy == 'E'){
                    if (temp <= tr){
                        fl_amount = temp/eth_try;
                        tr -= temp;
                        eth += fl_amount;
                        printf("You have successfully bought %.2f ETH.\n",fl_amount);
                    }
                    else if (temp > tr){
                        amount = (float)(int)(tr/eth_try);
                        tr -= amount*eth_try;
                        eth += amount;
                        printf("This amount is too much, you have successfully bought %.2f ETH.\n",amount);
                    }
                }
                else if (sell == 'B' && buy == 'T'){
                    if (temp <= btc){
                        fl_amount = temp/try_btc;
                        btc -= temp;
                        tr += fl_amount;
                        printf("You have successfully bought %.2f TRY.\n",fl_amount);
                    }
                    else if (temp > tr){
                        amount = (float)(int)(btc/try_btc);
                        btc -= amount*try_btc;
                        tr += amount;
                        printf("This amount is too much, you have successfully bought %.2f TRY.\n",amount);
                    }
                }
                else if (sell == 'B' && buy == 'E'){
                    if (temp <= btc){
                        fl_amount = temp/eth_btc;
                        btc -= temp;
                        eth += fl_amount;
                        printf("You have successfully bought %.2f ETH.\n",fl_amount);
                    }
                    else if (temp > btc){
                        amount = (float)(int)(btc/eth_btc);
                        btc -= amount*eth_btc;
                        eth += amount;
                        printf("This amount is too much, you have successfully bought %.2f ETH.\n",amount);
                    }
                }
                else if (sell == 'E' && buy == 'T'){
                    if (temp <= eth){
                        fl_amount = temp/try_eth;
                        eth -= temp;
                        tr += fl_amount;
                        printf("You have successfully bought %.2f TRY.\n",fl_amount);
                    }
                    else if (temp > eth){
                        amount = (float)(int)(eth/try_eth);
                        eth -= amount*try_eth;
                        tr += amount;
                        printf("This amount is too much, you have successfully bought %.2f TRY.\n",amount);
                    }
                }
                else if (sell == 'E' && buy == 'B'){
                    if (temp <= eth){
                        fl_amount = temp/btc_eth;
                        eth -= temp;
                        btc += fl_amount;
                        printf("You have successfully bought %.2f BTC.\n",fl_amount);
                    }
                    else if (temp > eth){
                        amount = (float)(int)(eth/btc_eth);
                        eth -= amount*btc_eth;
                        btc += amount;
                        printf("This amount is too much, you have successfully bought %.2f BTC.\n",amount);
                    }
                }
                else{
                    printf("Error: Operation could not be completed.\n");
                }

                
            }
            
            if (op == 'S'){
                scanf("%f",&temp);
                scanf(" %c %f %f",&code1,&loss1,&exp_gain1);
                scanf(" %c %f %f",&code2,&loss2,&exp_gain2);
                
                gain1 = (((temp-temp*loss1/100)*(1+exp_gain1/100))*(1-loss1/100))-temp;
                gain2 = (((temp-temp*loss2/100)*(1+exp_gain2/100))*(1-loss2/100))-temp;
                
                if (gain1 < 0 && gain2 < 0){
                    printf("Trading currently is not logical.\n");
                }
                else if (gain1 > gain2){
                    if (code1 == 'B'){
                        if (temp <= tr){
                        fl_amount = temp/btc_try;
                        tr -= temp;
                        btc += fl_amount;
                        
                        printf("BTC is better with %.2f TRY gain. Buying it...\n",gain1);
                        
                        }
                        else if (temp > tr){
                        amount = (float)(int)(tr/btc_try);
                        tr -= amount*btc_try;
                        btc += amount;
                        
                        printf("BTC is better with %.2f TRY gain. Buying it...\n",gain1);
                        }
                        
                    }
                    else if (code1 == 'E'){
                        if (temp <= tr){
                        fl_amount = temp/eth_try;
                        tr -= temp;
                        eth += fl_amount;
                        
                        printf("ETH is better with %.2f TRY gain. Buying it...\n",gain1);
                        
                        }
                        else if (temp > tr){
                        amount = (float)(int)(tr/eth_try);
                        tr -= amount*eth_try;
                        eth += amount;
                        
                        printf("ETH is better with %.2f TRY gain. Buying it...\n",gain1);
                        }
                    }
                    
                }
                
                else if (gain2 > gain1){
                    if (code2 == 'B'){
                        if (temp <= tr){
                        fl_amount = temp/btc_try;
                        tr -= temp;
                        btc += fl_amount;
                        
                        printf("BTC is better with %.2f TRY gain. Buying it...\n",gain2);
                        
                        }
                        else if (temp > tr){
                        amount = (float)(int)(tr/btc_try);
                        tr -= amount*btc_try;
                        btc += amount;
                        
                        printf("BTC is better with %.2f TRY gain. Buying it...\n",gain2);
                        }
                        
                    }
                    else if (code2 == 'E'){
                        if (temp <= tr){
                        fl_amount = temp/eth_try;
                        tr -= temp;
                        eth += fl_amount;
                        
                        printf("ETH is better with %.2f TRY gain. Buying it...\n",gain2);
                        
                        }
                        else if (temp > tr){
                        amount = (float)(int)(tr/eth_try);
                        tr -= amount*eth_try;
                        eth += amount;
                        
                        printf("ETH is better with %.2f TRY gain. Buying it...\n",gain2);
                        }
                    }
                    
                }
                else{
                    printf("Error: Operation could not be completed.\n");
                }

                
                
                
            }
    
        }
        
    }
}
