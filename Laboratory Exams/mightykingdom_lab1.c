#include <stdio.h>

int main()
{
    char kingdom;
    char op;
    int money;
    int temp;
    int loan = 0;
    int peasant,burgher,noble;
    int monthly_tax=0;
    char army1,army2,army3,selectedarmy;
    int incost1,incost2,incost3;
    int opcost1,opcost2,opcost3;
    int power1,power2,power3;
    int totalcost1,totalcost2,totalcost3;
    float score1,score2,score3;
    int slct_incost,slct_opcost;
    int army_count=0;
    int monthly_opcost = 0;
    int monthly_balance;
    int pay_row = 0;
    
    
    scanf("%c %d",&kingdom,&money);
    
    while(1){
        scanf(" %c",&op);
        
        if (op == 'Q'){
            printf("Our reign may never end...\n");
            break;
        }
        
        else if (op == 'R'){
            printf("We have %d ducats in our treasury.\n",money);
        }
        
        else if (op == 'L'){
            scanf("%d",&temp);
            loan += temp;
            money += temp;
        }
        
        else if (op == 'P'){
            scanf("%d",&temp);
            
            if (temp >= loan){
                loan = 0;
                money -= temp;
                printf("We have no remaining debts.\n");
            }
            
            else if (temp < loan){
                loan -= temp;
                money -= temp;
            }
        }
        
        else if (op == 'F'){
            if (loan == 0 || loan == 1){
                printf("We have %d ducat of remaining loans.\n",loan);
            }
            else{
                printf("We have %d ducats of remaining loans.\n",loan);
            }
        }
        
        else if (op == 'T'){
            scanf("%d %d %d",&peasant,&burgher,&noble);
            monthly_tax = 2*peasant + 5*burgher + 10*noble;
            
            if (monthly_tax == 0 || monthly_tax == 1){
                printf("Our kingdom has %d ducat income.\n",monthly_tax);
            }
            
            else{
                printf("Our kingdom has %d ducats income.\n",monthly_tax);
            }
        }
        
        else if (op == 'A'){
            scanf(" %c %d %d %d",&army1,&incost1,&opcost1,&power1);
            scanf(" %c %d %d %d",&army2,&incost2,&opcost2,&power2);
            scanf(" %c %d %d %d",&army3,&incost3,&opcost3,&power3);

            totalcost1 = incost1 + 12*opcost1;
            totalcost2 = incost2 + 12*opcost2;
            totalcost3 = incost3 + 12*opcost3;
            
            score1 = (float) power1 / totalcost1;
            score2 = (float) power2 / totalcost2;
            score3 = (float) power3 / totalcost3;
            
            if ((score1 > score2) && (score1 > score3)){
                slct_incost = incost1;
                slct_opcost = opcost1;
                selectedarmy = army1;
                printf("Our army will be %c, since its good score of %.4f.\n",selectedarmy,score1);
            }
            
            else if ((score2 > score1) && (score2 > score3)){
                slct_incost = incost2;
                slct_opcost = opcost2;
                selectedarmy = army2;
                printf("Our army will be %c, since its good score of %.4f.\n",selectedarmy,score2);
            }
            
            else if ((score3 > score1) && (score3 > score2)){
                slct_incost = incost3;
                slct_opcost = opcost3;
                selectedarmy = army3;
                printf("Our army will be %c, since its good score of %.4f.\n",selectedarmy,score3);
            }
            
            else if ((score1 == score2) && (score1 > score3)){
                slct_incost = incost1;
                slct_opcost = opcost1;
                selectedarmy = army1;
                printf("Our army will be %c, since its good score of %.4f.\n",selectedarmy,score1);
            }
            
            else if ((score1 == score3) && (score1 > score2)){
                slct_incost = incost1;
                slct_opcost = opcost1;
                selectedarmy = army1;
                printf("Our army will be %c, since its good score of %.4f.\n",selectedarmy,score1);
            }
            
            else if ((score2 == score3) && (score2 > score1)){
                slct_incost = incost2;
                slct_opcost = opcost2;
                selectedarmy = army2;
                printf("Our army will be %c, since its good score of %.4f.\n",selectedarmy,score2);
            }
            
            else if ((score1 == score2) && (score1 == score3)){
                slct_incost = incost1;
                slct_opcost = opcost1;
                selectedarmy = army1;
                printf("Our army will be %c, since its good score of %.4f.\n",selectedarmy,score1);
            }
        }
        
        else if (op == 'C'){
            
            if (slct_incost > money){
                printf("We can not afford this army for now.\n");
            }
            
            else{
                money -= slct_incost;
                army_count += 1;
                monthly_opcost += slct_opcost;
                
                if (army_count > 1){
                    printf("Our army is stronger now. We have %d armies serving our kingdom.\n",army_count);
                }
                
                else {
                    printf("Our army is stronger now. We have %d army serving our kingdom.\n",army_count);
                }
            }
        }
        
        else if (op == 'M'){
            monthly_balance = monthly_tax - monthly_opcost;
            money += monthly_balance;
            printf("This month our kingdom's balance is %d.\n",monthly_balance);
            
            if (money < 0){
                pay_row += 1;
                if (pay_row == 2){
                    loan = 0;
                    army_count = 0;
                    monthly_opcost = 0;
                }
            }
            else{
                pay_row = 0;
            }
        }
    }
    
}
