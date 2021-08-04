#define W 25
#define H 25
#include <stdio.h>

int color_finder(int arr[H][W], int cx, int cy){
	if (cx < W && cx >= 0 && cy < H && cy >= 0){
		return arr[cx][cy];
	}
	else if (cy < 0 && cx <0){
		return 0;
	}
	else if (cy >= 0 && cy < W && cx < 0){
		return 1;
	}
	else if (cy >= W && cx < 0){
		return 2;
	}
	else if (cy >= W && cx >= 0 && cx < H){
		return 3;
	}
	else if (cy >= W && cx >= H){
		return 4;
	}
	else if (cy >= 0 && cy < W && cx >= H){
		return 5;
	}
	else if (cy < 0 && cx >= H){
		return 6;
	}
	else{
		return 7;
	}
}

void color_fill(int arr[H][W], int color, int picked_color, int fill_x, int fill_y){
	
	if (picked_color == color){
		
		return;
	}
	if (fill_x < 0 || fill_y < 0 || fill_x >= H || fill_y >= W || arr[fill_x][fill_y] != color){
		
		return;
		
	}
	
	else{
		
		arr[fill_x][fill_y] = picked_color;
		color_fill(arr, color, picked_color, fill_x-1, fill_y-1);
		color_fill(arr, color, picked_color, fill_x-1, fill_y);
		color_fill(arr, color, picked_color, fill_x-1, fill_y+1);
		color_fill(arr, color, picked_color, fill_x, fill_y+1);
		color_fill(arr, color, picked_color, fill_x+1, fill_y+1);
		color_fill(arr, color, picked_color, fill_x+1, fill_y);
		color_fill(arr, color, picked_color, fill_x+1, fill_y-1);
		color_fill(arr, color, picked_color, fill_x, fill_y-1);
		
	}
		
}

void copy_paste(int arr[H][W],int c1x,int c1y,int c2x,int c2y,int p1x,int p1y,int p2x,int p2y){
	
	int i,j,k,m,counter = 0;
	int botrightcx,botrightcy,topleftcx,topleftcy;
	int botrightpx,botrightpy,topleftpx,topleftpy;
	
	if ((c1x < c2x && c1y < c2y) || (c1x < c2x && c1y == c2y) || (c1x == c2x && c1y < c2y)){
		topleftcx = c1x;
		topleftcy = c1y;
		botrightcx = c2x;
		botrightcy = c2y;
	}
	else if ((c1x > c2x && c1y > c2y) || (c1x > c2x && c1y == c2y) || (c1x == c2x && c1y > c2y)){
		topleftcx = c2x;
		topleftcy = c2y;
		botrightcx = c1x;
		botrightcy = c1y;
	}
	else if (c1x < c2x && c1y > c2y){
		topleftcx = c1x;
		topleftcy = c2y;
		botrightcx = c2x;
		botrightcy = c1y;
	}
	else{
		topleftcx = c2x;
		topleftcy = c1y;
		botrightcx = c1x;
		botrightcy = c2y;
	}
	if ((p1x < p2x && p1y < p2y) || (p1x < p2x && p1y == p2y) || (p1x == p2x && p1y < p2y)){
		topleftpx = p1x;
		topleftpy = p1y;
		botrightpx = p2x;
		botrightpy = p2y;
	}
	else if ((p1x > p2x && p1y > p2y) || (p1x > p2x && p1y == p2y) || (p1x == p2x && p1y > p2y)){
		topleftpx = p2x;
		topleftpy = p2y;
		botrightpx = p1x;
		botrightpy = p1y;
	}
	else if (p1x < p2x && p1y > p2y){
		topleftpx = p1x;
		topleftpy = p2y;
		botrightpx = p2x;
		botrightpy = p1y;
	}
	else{
		topleftpx = p2x;
		topleftpy = p1y;
		botrightpx = p1x;
		botrightpy = p2y;
	}
	for (i = topleftcx,j = topleftpx; i <= botrightcx && j <= botrightpx; i++,j++ ){
		for (k = topleftcy,m = topleftpy; k <= botrightcy && m <= botrightpy; k++,m++){
			if (arr[i][k] == arr[j][m]){
				continue;
			}
			else{
				arr[j][m] = arr[i][k];
				counter++;
			}
		}
	}
	for (i=0; i<H; i++){
		
		for (j=0; j<W; j++){
			
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	printf("%d\n",counter);
	
}

void rotate(int arr[H][W],char direction,int deg,int c1x,int c1y,int c2x,int c2y,int p1x,int p1y,int p2x,int p2y){
	
	int i,j,k,m,counter = 0;
	int botrightcx,botrightcy,topleftcx,topleftcy;
	int topleftpx = p1x,topleftpy = p1y,botrightpx = p2x,botrightpy = p2y;
	
	if ((direction == 'R' && deg == 0) || (direction == 'L' && deg == 0)){
		topleftcx = c1x;
		topleftcy = c1y;
		botrightcx = c2x;
		botrightcy = c2y;
		
		for (i = topleftcx,j = topleftpx; i <= botrightcx && j <= botrightpx; i++,j++ ){
		for (k = topleftcy,m = topleftpy; k <= botrightcy && m <= botrightpy; k++,m++){
			if (arr[i][k] == arr[j][m]){
				continue;
			}
			else{
				arr[j][m] = arr[i][k];
				counter++;
			}
		}
	}
	}
	
	else if ((direction == 'R' && deg == 90) || (direction == 'L' && deg == 270)){
		topleftcx = c2x;
		topleftcy = c1y;
		botrightcx = c1x;
		botrightcy = c2y;
		for (i = topleftcx,j = topleftpy;i >= botrightcx && j <= botrightpy;i--,j++){
			for(k = topleftcy,m = topleftpx;k <= botrightcy && m <= botrightpx;k++,m++){
				if (arr[i][k] == arr[m][j]){
					continue;
				}
				else{
					arr[m][j] = arr[i][k];
					counter++;
				}
			}
		}
	}
	
	else if ((direction == 'R' && deg == 180) || (direction == 'L' && deg == 180)){
		topleftcx = c2x;
		topleftcy = c2y;
		botrightcx = c1x;
		botrightcy = c1y;
		for (i = topleftcx,j = topleftpx;i >= botrightcx && j <= botrightpx;i--,j++){
			for (k = topleftcy,m = topleftpy;k >= botrightcy && m <= botrightpy;k--,m++){
				if (arr[i][k] == arr[j][m]){
					continue;
				}
				else{
					arr[j][m] = arr[i][k];
					counter++;
				}
			}
		}
	}
	
	else if ((direction == 'R' && deg == 270) || (direction == 'L' && deg == 90)){
		topleftcx = c1x;
		topleftcy = c2y;
		botrightcx = c2x;
		botrightcy = c1y;
		for (i = topleftcy,j = topleftpx;i >= botrightcy && j <= botrightpx;i--,j++){
			for (k = topleftcx,m = topleftpy;k <= botrightcx && m <= botrightpy;k++,m++){
				if (arr[k][i] == arr[j][m]){
					continue;
				}
				else{
					arr[j][m] = arr[k][i];
					counter++;
				}
			}
		}
	}

	for (i=0; i<H; i++){
		
		for (j=0; j<W; j++){
			
			printf("%d ",arr[i][j]);
		}
		printf("\n");
	}
	printf("%d\n",counter);
	
}

int main(){
	
	int photo[H][W];
	char op,rotation;
	int cl_pickx,cl_picky;
	int fill_x,fill_y;
	int i,j;
	int color,picked_color;
	int copy1x,copy1y,copy2x,copy2y,paste1x,paste1y,paste2x,paste2y,degree;
	
	for (i=0; i<H; i++){
		
		for (j=0; j<W; j++){
			
			scanf("%d",&photo[i][j]);
		}
	}
	
	scanf(" %c",&op);
	
	if (op == 'F'){
		
		scanf("%d %d",&cl_pickx,&cl_picky);
		
		scanf("%d %d",&fill_x,&fill_y);
		
		picked_color = color_finder(photo, cl_pickx, cl_picky);
		
		color = color_finder(photo, fill_x, fill_y);
		
		color_fill(photo, color, picked_color, fill_x, fill_y);
		
		for (i=0; i<H; i++){
		
			for (j=0; j<W; j++){
			
			printf("%d ",photo[i][j]);
			}
		printf("\n");
		}
		
	}
	
	else if (op == 'P'){
		
		scanf("%d %d %d %d",&copy1x,&copy1y,&copy2x,&copy2y);
		
		scanf("%d %d %d %d",&paste1x,&paste1y,&paste2x,&paste2y);
		
		copy_paste(photo, copy1x, copy1y, copy2x, copy2y, paste1x, paste1y, paste2x, paste2y);
	}
	
	else if (op == 'R'){
		
		scanf(" %c %d",&rotation,&degree);

		scanf("%d %d %d %d",&copy1x,&copy1y,&copy2x,&copy2y);
		
		scanf("%d %d %d %d",&paste1x,&paste1y,&paste2x,&paste2y);

		rotate(photo, rotation, degree, copy1x, copy1y, copy2x, copy2y, paste1x, paste1y, paste2x, paste2y);
		
	}
	
	return 0;
}
