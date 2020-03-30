**Exercises from the Test**
- 

  **1**
  - 
    ```shell
        grep - v '[a-w]' | grep '[02468]' | wc -l 
    ```

  **2**
  -  
     ```shell
        grep -v '[0-9]{4}\s.г\s-' | awk 'BEGIN[counter =1] {printf "%.0f. %s\n",counter,$1} {counter+=1}' | sort  
     ```

  **5**
  - 
    ```shell
      find / -type f -user $(whoami) 2>/dev/null  | wc -l 

    ```

  **6.1**
  - 
    ```shell
        find . -type d -empty
    ```

 **6.2**
  - 
    ```shell
        find /home  -type f -user $(whoami) -printf "%s %P \n" 2>/dev/null | sort -nrk 1  | head -n 5 | xargs -I{} rm -r {}
    ```

  **7**
  - 
    ```shell
        grep -w 'Inf' passwd.txt  | grep '[a-zA-Z]*\s[a-zA-Z]*a' | cut -c 3,4 | sort -n | uniq -c | sort -nr

    ```

  **8**
  - 
    ```shell
      find . -type f -printf "%n %f \n" 2>/dev/null  | sort -nrk 1  | head -n 5 | cut -d " " -f 2 

    ```

  **9**
  - 
    ```shell
        find /home -type f -user pesho -printf "%i %T@\n" | sort -nrk 2 | head -n 1 | cut -d " " -f 1  
    ```

  **10**
  - 
    ```shell
        grep -w 'SI' passwd.txt  | sort -t ":" -k1 | cut -d ":" -f 5,6
    ```

  **11**
  -  
    ```shell
       #find /home/SI -printf "%C@ %f \n" 2>/dev/null | awk '{if($1 >1551168000 && $1<1551176100) print $2}'  get faculty number
        
        grep -w "$(find /home/SI -printf "%C@ %f \n" 2>/dev/null | awk '{if($1 >1551168000 && $1<1551176100) print $2}')" | cut -c 2-
         | tr "," ":" | cut -d ":" -f 1,5 | tr " " "\t"

    ```