#include <stdio.h>
#include <stdlib.h>
#include "the3.h"

Apartment* mk_apartment(char* nme, int maxbandwidth){
	
	Apartment* new_apartment;
	
	new_apartment = (Apartment*) malloc(sizeof(Apartment));
	
	new_apartment -> name = nme;
	new_apartment -> max_bandwidth = maxbandwidth;
	new_apartment -> next = NULL;
	new_apartment -> flat_list = NULL;
	
	return new_apartment;
		
}

Flat* mk_flat(int idd){
	
	Flat* new_flat;
	
	new_flat = (Flat*) malloc(sizeof(Flat));
	
	new_flat -> id = idd;
	new_flat -> initial_bandwidth = 0;
	new_flat -> is_empty = 0;
	new_flat -> next = NULL;
	new_flat -> prev = NULL;
	
	return new_flat;
}

int name_len(char* name){
	
	int len = 1;
	
	while (*name++) len++;
	
	return len;
}

int name_compare(char* name1, char* name2){
	
	int flag = 1;
	
	if (name_len(name1) == name_len(name2)){
		
		while (*name1 && *name2 ){
		
			if (*name1 != *name2){
				flag = 0;
				break;
			}
		
			name1++;
			name2++;
		
		}
		return flag;
	}
	
	else return 0;
	
}

int find_len(Flat* flat_head){
	int length = 0;
	while (flat_head){
		length++;
		flat_head = flat_head -> next;
	}
	
	return length;
}

Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth){
	
	Apartment *new_apartment,*prev,*curr;
	int i = 0;
	
	new_apartment = mk_apartment(apartment_name, max_bandwidth);
	
	prev = NULL;
	curr = head;
	
	if (curr){
		if (index > 0){
			
			while (i++ < index){
				prev = curr;
				curr = curr -> next;
			}
			
			prev -> next = new_apartment;
			new_apartment -> next = curr;
			
			return head;	
		}
		
		else{
		
			while (curr -> next != head) curr = curr -> next;
			new_apartment -> next = head;
			curr -> next = new_apartment;
			
			return new_apartment;
		}
	}
	
	else{
		
		new_apartment -> next = new_apartment;
		
		return new_apartment;
	}	
}

void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth){
	
	Flat *new_flat,*flat_list_head;
	Apartment *current;
	
	new_flat = mk_flat(flat_id);
	current = head;
	
	while (!name_compare(current -> name, apartment_name)) current = current -> next;
	
	flat_list_head = current -> flat_list;
	
	if (flat_list_head){
		
		int total_bandwidth = 0, i = 0;
		Flat *temp,*temp2;
		temp = flat_list_head;
		
		while (temp){
			total_bandwidth += temp -> initial_bandwidth;
			temp = temp -> next;
		}
		
		if (total_bandwidth + initial_bandwidth > current -> max_bandwidth){
			new_flat -> initial_bandwidth = current -> max_bandwidth - total_bandwidth;
		}
		
		else{
			new_flat -> initial_bandwidth = initial_bandwidth;
		}
		
		if (index > 0 && index < find_len(flat_list_head)){
			while (i++ < index){
				flat_list_head = flat_list_head -> next;
			}
			temp2 = flat_list_head -> prev;
			temp2 -> next = new_flat;
			flat_list_head -> prev = new_flat;
			new_flat -> prev = temp2;
			new_flat -> next = flat_list_head;
		}
		
		else if (index == find_len(flat_list_head)){
			while (++i < index){
				flat_list_head = flat_list_head -> next;
			}
			flat_list_head -> next = new_flat;
			new_flat -> prev = flat_list_head;
		}
		
		else{
			flat_list_head -> prev = new_flat;
			new_flat -> next = flat_list_head;
			current -> flat_list = new_flat;
		}
	}
	
	else{
		if (initial_bandwidth > current -> max_bandwidth){
			new_flat -> initial_bandwidth = current -> max_bandwidth;
		}
		else{
			new_flat -> initial_bandwidth = initial_bandwidth;
		} 
		current -> flat_list = new_flat;
	}
}

Apartment* remove_apartment(Apartment* head, char* apartment_name){
	
	Apartment *prev,*curr;
	
	prev = NULL;
	curr = head;
	
	while (!name_compare(curr -> name, apartment_name)){
		prev = curr;
		curr = curr -> next;
	}
	
	if (prev){
		prev -> next = curr -> next;
		
		if (curr -> flat_list){
			
			Flat *target, *flat_head;
			flat_head = curr -> flat_list;
			
			while (flat_head){		/* Freeing the associated flat_list of the removed apartment */
				target = flat_head;
				flat_head = flat_head -> next;
				free(target);
			}
		}
		
		free(curr);		/* Freeing the apartment itself */
		
		return head;
	}
	
	else{
		
		Apartment *temp;
		int len = 1;
		
		temp = curr;
		
		while (temp -> next != head){
			 temp = temp -> next;
			 len++;
		}
		
		temp -> next = curr -> next;
		
		if (curr -> flat_list){
			
			Flat *target, *flat_head;
			flat_head = curr -> flat_list;
			
			while (flat_head){		/* Freeing the associated flat_list of the removed apartment */
				target = flat_head;
				flat_head = flat_head -> next;
				free(target);
			}
		}
		
		free(curr);		/* Freeing the apartment itself */
		
		if (len == 1) return NULL;
		
		else return temp -> next;
	}
}

void make_flat_empty(Apartment* head, char* apartment_name, int flat_id){
	
	Apartment *target_apt;
	Flat *flat_head;
	target_apt = head;
	
	while (!name_compare(target_apt -> name, apartment_name)) target_apt = target_apt -> next;
	
	flat_head = target_apt -> flat_list;
	
	while (flat_head -> id != flat_id) flat_head = flat_head -> next;
	
	flat_head -> is_empty = 1;
	flat_head -> initial_bandwidth = 0;
}

int find_sum_of_max_bandwidths(Apartment* head){
	
	Apartment *current;
	int sum = 0;
	current = head;
	
	if (current){
		while (current -> next != head){
			sum += current -> max_bandwidth;
			current = current -> next;
		}
		sum += current -> max_bandwidth;
	}
	return sum;
}

Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2){
	
	Apartment *apt1,*apt2,*prev2,*curr2;
	Flat *flat_list1,*flat_list2;
	
	prev2 = NULL;
	apt1 = apt2 = curr2 = head;
	
	while (!name_compare(apt1 -> name, apartment_name_1)) apt1 = apt1 -> next;
	while (!name_compare(apt2 -> name, apartment_name_2)){
		prev2 = curr2;
		curr2 = curr2 -> next;
		apt2 = apt2 -> next;
	}
	
	apt1 -> max_bandwidth += apt2 -> max_bandwidth;
	
	flat_list1 = apt1 -> flat_list;
	flat_list2 = apt2 -> flat_list;
	
	if (flat_list2){     /* Connecting the flat lists of apt1 and apt2 */
		
		if (flat_list1){
			
			Flat *curr1,*curr2;
		
			curr1 = flat_list1;
			curr2 = flat_list2;
			
			while (curr1 -> next) curr1 = curr1 -> next;
			
			curr1 -> next = curr2;
			curr2 -> prev = curr1;
			
		}
		
		else{
			
			apt1 -> flat_list = flat_list2;
		}
	}
	
	if (prev2){        /* Removing apartment2 */
		
		prev2 -> next = curr2 -> next;
		free(apt2);
		return head;
		
	}
	
	else{
		
		Apartment* temp;
		temp = curr2;
		
		while (temp -> next != head) temp = temp -> next;
		
		temp -> next = curr2 -> next;
		free(apt2);
		return temp -> next;
	}
}

void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list){
	
	int i = 0, index = 0;
	Flat* shifted_flat;
	Apartment* target_apt = head;
	
	while (!name_compare(target_apt -> name, new_apartment_name)) target_apt = target_apt -> next;
	
	shifted_flat = target_apt -> flat_list;
	
	while (shifted_flat -> id != flat_id_to_shift){
		shifted_flat = shifted_flat -> next;
		index++;
	}
	
	while (flat_id_list[i] != 0){
		
		Flat* rlc_flat;
		Apartment* rlc_apt = head;
		
		while (1){      /* Traversing through the street to find the flat to be relocated */
			
			int found = 0;
			
			if (rlc_apt -> flat_list){
				
				rlc_flat = rlc_apt -> flat_list;
				
				while (rlc_flat){
					
					if (rlc_flat -> id == flat_id_list[i]){
						found = 1;
						break;
					}
					rlc_flat = rlc_flat -> next;
				}
				
				if (found) break;
				else rlc_apt = rlc_apt -> next;
				
			}
			
			else{
				rlc_apt = rlc_apt -> next;
			}
		}
		
		if (index == 0){
			
			Flat *temp = rlc_flat;     /* Don't lose the track of the previous and next pointers of rlc_flat */
			
			if (temp -> prev){
				temp -> prev -> next = temp -> next;
				if (temp -> next) temp -> next -> prev = temp -> prev;     /* Relocated flat is not in the 0th index */
				
			}
			
			else{
				if (temp -> next){      /* Relocated flat is in the 0th index and the length of the flat_list is greater than 1 */
					temp -> next -> prev = NULL;
					rlc_apt -> flat_list = temp -> next;	
				}
				else{					/* Relocated flat is the only flat in the flat_list */
					rlc_apt -> flat_list = NULL;
				}
			}
			
			target_apt -> flat_list = rlc_flat;
			rlc_flat -> next = shifted_flat;
			rlc_flat -> prev = NULL;
			shifted_flat -> prev = rlc_flat;
			
			target_apt -> max_bandwidth += rlc_flat -> initial_bandwidth;
			rlc_apt -> max_bandwidth -= rlc_flat -> initial_bandwidth;
			index++;
			
		}
		
		else{
			Flat *temp = rlc_flat;
			
			if (temp -> prev){
				temp -> prev -> next = temp -> next;
				if (temp -> next) temp -> next -> prev = temp -> prev;     /* Relocated flat is not in the 0th index */
				
			}
			
			else{
				if (temp -> next){      /* Relocated flat is in the 0th index and the length of the flat_list is greater than 1 */
					temp -> next -> prev = NULL;
					rlc_apt -> flat_list = temp -> next;	
				}
				else{					/* Relocated flat is the only flat in the flat_list */
					rlc_apt -> flat_list = NULL;
				}
			}
			
			rlc_flat -> next = shifted_flat;
			rlc_flat -> prev = shifted_flat -> prev;
			shifted_flat -> prev -> next = rlc_flat;
			shifted_flat -> prev = rlc_flat;
			
			target_apt -> max_bandwidth += rlc_flat -> initial_bandwidth;
			rlc_apt -> max_bandwidth -= rlc_flat -> initial_bandwidth;
			index++;
		}
		
		i++;	
	}	
}




