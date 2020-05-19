# Void array
  - you can appoint any type to it and then cast it back to that type 
  ```c
	// Casting void array elements to u_int32_t 
	int cmp(const void* a, const void* b){
		u_int32_t x = *((u_int32_t*)a);
	        u_int32_t y = *((u_int32_t*)b);

        	if(x>y)
                	return 1;
        	else if (x<y)
               	 return -1;

	        return 0;
	}	

	int main(){
		int elements =5;
		void* x = malloc(elements * sizeof(u_int32_t));
		qsort(x,elements,sizeof(u_int32_t),cmp);
	}
	
  ```


# Reset the exercise by xxd -r f1.xxd f1 
