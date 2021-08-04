#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* Fill in the functions and define helper functions if you need to */


float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){
    
    int i,j,k;
    float temp;
	float*** sector_times;
    scanf("%u %u",n_drivers,n_laps);
    
	sector_times = (float ***) malloc(sizeof(float **)*(*n_drivers));
    
	for (i = 0; i < *n_drivers; i++){
    	
		sector_times[i] = (float **) malloc(sizeof(float *)*(*n_laps));
		
		for (j = 0; j < *n_laps; j++){
			
			sector_times[i][j] = (float *) malloc(sizeof(float)*n_sector);
		}
	}
	
	for (i = 0; i < *n_drivers; i++){
		for (j = 0; j < *n_laps; j++){
			for (k = 0; k < n_sector; k++){
				scanf("%f",&temp);
				sector_times[i][j][k] = temp;
			}
		}
	}

	return sector_times;
}

unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){
    
	int i,j;
	unsigned int temp;
    unsigned int** positions;
	scanf("%u %u",p_drivers,n_races);
    
	positions = (unsigned int **) malloc(sizeof(unsigned int *)*(*p_drivers));
    
    for (i = 0; i < *p_drivers; i++){
    	positions[i] = (unsigned int *) malloc(sizeof(unsigned int)*(*n_races));
	}
	
	for (i = 0; i < *p_drivers; i++){
		for (j = 0; j < *n_races; j++){
			scanf("%u",&temp);
			positions[i][j] = temp;
		}
	}
	
	
	return positions;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){
    
    int i,j,k;
    float sum;
	float** lap_times;
	
	lap_times = (float **) malloc(sizeof(float *)*n_drivers);
	
	for (i = 0; i < n_drivers; i++){
		lap_times[i] = (float *) malloc(sizeof(float)*n_laps);
	}
	
	for (i = 0; i < n_drivers; i++){
		for (j = 0; j < n_laps; j++){
			sum = 0.0;
			for (k = 0; k < n_sector; k++){
				sum += sector_times[i][j][k];
			}
			lap_times[i][j] = sum;
		}
		
	}
	
	return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    
	int i,j;
	float min = lap_times[0][0];
	unsigned int id = 0;
	
	for (i = 0; i < n_drivers; i++){
		for (j = 0; j < n_laps; j++){
			if (lap_times[i][j] < min){
				min = lap_times[i][j];
				id = i;
			}
		}
	}
	
	return id;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){
    
	int i,j;
	float min = 0.0,sum = 0.0;
	unsigned int lap = 0;
	
	for (i = 0; i < n_sector; i++){
		min += sector_times_of_driver[0][i];
	}
	
	for (i = 0; i < n_laps; i++){
		sum = 0.0;
		for (j = 0; j < n_sector; j++){
			sum += sector_times_of_driver[i][j];
		}
		if (sum < min){
			min = sum;
			lap = i;
		}
	}
	
	return lap;
}


float* selection_sort(float* arr, unsigned int len, char ord){
    
	int i,j,min_index,max_index,unsorted_ind = 0;
	float min,max,temp;
	float* sorted_arr;
	
	sorted_arr = (float *) malloc(sizeof(float)*len);
	
	for (i = 0; i < len; i++){
		sorted_arr[i] = arr[i];
	}
	
	if (ord == 'A'){
		
		while (unsorted_ind < len){
			
			min = sorted_arr[unsorted_ind];
			min_index = unsorted_ind;
			
			for (j = unsorted_ind; j < len; j++){
				if (sorted_arr[j] < min){
					min = sorted_arr[j];
					min_index = j;
				}
			}
			temp = sorted_arr[unsorted_ind];
			sorted_arr[unsorted_ind] = min;
			sorted_arr[min_index] = temp;
			unsorted_ind++;
		} 
	}
	
	if (ord == 'D'){
		
		while (unsorted_ind < len){
			
			max = sorted_arr[unsorted_ind];
			max_index = unsorted_ind;
			
			for (j = unsorted_ind; j < len; j++){
				if (sorted_arr[j] > max){
					max = sorted_arr[j];
					max_index = j;
				}
			}
			temp = sorted_arr[unsorted_ind];
			sorted_arr[unsorted_ind] = max;
			sorted_arr[max_index] = temp;
			unsorted_ind++;
		} 
	}

	return sorted_arr;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    
	unsigned int* finishing_positions;
	float* sum_lap_times;
	unsigned int i,j,tempv2,min_index,unsorted_ind = 0;
	float sum,temp,min;
	
	finishing_positions = (unsigned int *) malloc(sizeof(unsigned int)*n_drivers);
	sum_lap_times = (float *) malloc(sizeof(float)*n_drivers);
	
	for (i = 0; i < n_drivers; i++) finishing_positions[i] = i;
	
	for (i = 0; i < n_drivers; i++){
		sum = 0.0;
		for (j = 0; j < n_laps; j++){
			sum += lap_times[i][j];
		}
		sum_lap_times[i] = sum; 
	}
	
	while (unsorted_ind < n_drivers){
		min = sum_lap_times[unsorted_ind];
		min_index = unsorted_ind;
		
		
		for (i = unsorted_ind; i < n_drivers; i++){
			if (sum_lap_times[i] < min){
				min = sum_lap_times[i];
				min_index = i;
			}
		}
		tempv2 = finishing_positions[unsorted_ind];
		finishing_positions[unsorted_ind] = finishing_positions[min_index];
		finishing_positions[min_index] = tempv2;
		
		temp = sum_lap_times[unsorted_ind];
		sum_lap_times[unsorted_ind] = min;
		sum_lap_times[min_index] = temp;
		unsorted_ind++;
	}

	return finishing_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){
    
    float* time_diff;
    int i;
    float prev = 0.0;
    
    time_diff = (float *) malloc(sizeof(float)*n_laps);
	
	
	for (i = 0; i < n_laps; i++){
		time_diff[i] = lap_times[driver1][i] - lap_times[driver2][i] + prev;
		prev = time_diff[i];
	}
	
	return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){
    
    unsigned int *mapping,*total_points;
    int i,j;
    unsigned int pts;
    
    mapping = (unsigned int *) malloc(sizeof(unsigned int)*p_drivers);
    total_points = (unsigned int *) malloc(sizeof(unsigned int)*p_drivers);
	
	for (i = 0; i < p_drivers; i++) scanf("%u",mapping+i);
	
	for (i = 0; i < p_drivers; i++){
		pts = 0;
		for (j = 0; j < n_races; j++){
			pts += mapping[positions[i][j]-1];
		}
		total_points[i] = pts; 
	}
	
	return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){
    
	unsigned int season_ranking = 1;
	int i;
	
	for (i = 0; i < id; i++){
		if (total_points[i] >= total_points[id]) season_ranking++;
	}
	for (i = id+1; i < p_drivers; i++){
		if (total_points[i] > total_points[id]) season_ranking++;
	}
	
	return season_ranking;
}
