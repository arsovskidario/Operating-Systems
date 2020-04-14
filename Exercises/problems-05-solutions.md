**Solutions**
- 
- 1.05-b-2800
  ```bash
     #!/bin/bash
     
    if [ $# -le 0 ]; then
        echo "Invalid input"
        exit 2
    fi

    if [[ "$1" =~ ^[a-zA-Z0-9]*$ ]]; then
        echo "Valid input" 
        exit 0
    else 
        echo "Invalid input"
    fi

  ```

- 05-b-3100
  ```bash
     #!/bin/bash

     read -p "Enter username:" username

     who | grep -w "${username}" | wc -l 
     
  ```
- - 05-b-3200
  ```bash
     #!/bin/bash
    read -p "Enter full filename :" FILENAME

    echo "${FILENAME}"
    echo "Number of files : $(find "${FILENAME}" -maxdepth 1 2>/dev/null |    wc -l)"

  ```

- -- 05-b-3300
  ```bash
     #!/bin/bash

    read -p "Enter file and string for search " FILENAME STRING

    echo $FILENAME, $STRING

    # Turn off dev/null if you want the found text to appear 
    grep -w "${STRING}" ${FILENAME} > /dev/null


    if [ $? -eq 0 ]; then
    	echo "Found string"
    	exit 0
    else
    	echo "Not found" 
    	exit 1
    fi

  ```

-  05-b-4200
  ```bash
     #!/bin/bash

      BRACKETS="$(grep -wo "[{}]*" sourceFile.c  | xargs -I{} echo -n {})"
      MAX_COUNTER=0
      COUNTER=0
      for (( i=0;i<${#BRACKETS};i++ )); do
              if [[ "${BRACKETS:$i:1}" == "{" ]]; then # ${BRACKETS"$i:1} grap ith letter
                      ((COUNTER=COUNTER+1)) #increment by one
              else
                      ((COUNTER=0))
              fi

              if [ $COUNTER -gt $MAX_COUNTER ]; then
                      ((MAX_COUNTER=COUNTER))
              fi
      done

      echo "Max depth is ${MAX_COUNTER} "

  ```

- -- 05-b-4300
  ```bash
      #!/bin/bash
      if [ $# -le 0 ]; then
              echo " invalid arguments"
              exit 1
      fi

      FILE="$1"
      NAME="$2"

      echo "User's ID : $(grep -w "$NAME" $FILE | cut -d " " -f 2)"
  ```

-  -- 05-b-4301
  ```bash
    #!/bin/bash

    if [ $# -ne 4 ]; then
            echo "Invalid arguments"
            exit 2
    fi

    FILENAME="$1"
    FULL_NAME="$2 $3"
    USER_NAME="$4"

    USER_ID=$(grep -w "${FULL_NAME}" passwd.txt | cut -d ":" -f 1)

    echo "${USER_NAME} ${USER_ID}" >> phoneBook

  ```

  **BONUS**
  ```bash
     #!/bin/bash

      if [ $# -ne 4 ]; then
              echo "Invalid arguments"
              exit 2
      fi

      FILENAME="$1"
      FULL_NAME="$2 $3"
      USER_NAME="$4"

      COUNT_USER=$(grep -w "${FULL_NAME}" passwd.txt | wc -l)
      if [ $COUNT_USER -eq 0 ]; then
              echo "No user found "
      fi

      if [ $COUNT_USER -eq 1 ]; then
              USER_ID=$(grep -w "${FULL_NAME}" passwd.txt | cut -d ":" -f 1)
      else
              USER_NAMES=$(grep -w "${FULL_NAME}" passwd.txt | cut -d ":" -f      1)
              COUNTER=0
              echo " SELECT YOUR USERNAME "
              for item in $USER_NAMES; do
                      ((COUNTER =COUNTER+1))
                      echo "$COUNTER. $item"
              done
              read SELECTED_NUMBER
              USER_ID=$(grep -w "${FULL_NAME}" passwd.txt | cut -d ":" -f 1       | head -$SELECTED_NUMBER | tail -n 1)
      fi

      echo "${USER_NAME} ${USER_ID}" >> phoneBook
    ```

- -- 05-b-4400  **CHECK AGAIN**
Напишете shell script, който да приема параметър име на директория, от която взимаме файлове, и опционално експлицитно име на директория, в която ще копираме файлове. Скриптът да копира файловете със съдържание, променено преди по-малко от 45 мин, от първата директория във втората директория. Ако втората директория не е подадена по име, нека да получи такова от днешната дата във формат, който ви е удобен. При желание новосъздадената директория да се архивира.

  ```bash
     #!/bin/bash

    if [ $# -eq 0 ]; then
            echo "Invalid arguments"
            exit 1
    fi

    SOURCE=$1
    DESTINATION=$2
    if [ -z "$DESTINATION" ]; then
            DESTINATION="./"
    fi

            find $SOURCE -type f -printf -mmin -45 "%p" 2>/dev/null | xargs -I{} -n 1 cp {} DESTINATION

    echo "DONE"
      ```
      /home/dario/Development/Operating-Systems/Week-5/destination
      /home/dario/Development/Operating-Systems/Week-5/source
  ```  


