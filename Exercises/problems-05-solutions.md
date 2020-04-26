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


- -- 05-b-4400
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

                find $SOURCE -type f -mmin -45 -printf "%p" -exec cp {}         $DESTINATION \; >/dev/null

        
        echo "DONE"
  ```

- **-- 05-b-4500**
  ```bash
        #!/bin/bash

        if [ $# -eq 0 ]; then
                echo "Invalid arguments"
                exit 2
        fi

        USER_ID=$1

        ERROR_STATUS=1

        while :
        do

                if [ $ERROR_STATUS -eq 1 ]; then
                        who | grep -w $USER_ID >/dev/null # Output not  specified
                        ERROR_STATUS=$?
                else
                        break
                fi

                sleep 1
        done

        echo "Done"

  ```
  
  - -- 05-b-4600

  ```bash
     #!/bin/bash
        if [ $# -lt 3 ]; then
                echo "Invalid arguments"
        fi
        
        NUMBER=$1
        START=$2
        END=$3
        
        # Check arguments for integer values
        printf "'$*'" | grep -w "[0-9]*\s[0-9]*\s[0-9]*" >/dev/null
        
        # If any argument is different from integer exit status 3
        if [ $? -eq 1 ]; then
                exit 3
        fi
        
        if [ $2 -gt $3 ] ; then
                exit 2
        fi
        
        if [ $1 -gt $2 ] && [ $1 -lt $3 ] ; then
                exit 0
        else
                exit 1
        fi
        
        #Script kiddie material right here

  ```

- -- 05-b-4700
  ```bash
     #!/bin/bash

        if [ $# -eq 0 ] || [ $# -ge 3 ] ; then
                echo "Invalid arguments"
                exit 2
        fi

        NUMBER=$1
        DELIMETAR=$2

        if [ $# -eq 1 ]; then
                DELIMETAR=' '
        fi

        for (( i=0; i<${#NUMBER};i++ )); do
                (( COUNTER=${#NUMBER} - i ))
                if [ $(( COUNTER % 3 )) -eq 1 ] && [ $i -ne $(( ${#NUMBER}-1 )  ) ]; then
                        printf "${NUMBER:$i:1}${DELIMETAR}"
                else
                        printf "${NUMBER:$i:1}"
                fi
        done

        echo #adds a newline

  ```

- -- 05-b-4800
  ```bash
     #!/bin/bash

        if [ $# -ne 2 ]; then
                echo "Invalid arguments"
                exit 2
        fi

        #Check if it is a dir or a file ?
        FILE_NAME=$1
        DIR_NAME=$2

        DIR_CONTENT=$(find ${DIR_NAME} -type f -printf "%f " 2>/dev/null)

        for i in ${DIR_CONTENT}
        do
                cmp ${FILE_NAME} $i
                if [ $? -eq 0 ]; then
                        echo $i
                fi
        done

  ```

- -- 05-b-5500

  ```bash
     #!/bin/bash

        echo "<table>"
        echo "<tr> "
        echo "  <th>Username</th> "
        echo "  <th>group</th> "
        echo "  <th>login</th> "
        echo "  <th>GECKO</th> "
        echo "</tr> "
        
        for ((i=1;i<=$(wc -l passwd.txt | cut -d " " -f 1);i++)); do
                USERNAME=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d     ":" -f 1)
                GROUP=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d ":"    -f 4)
                SHELL=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d ":"    -f 7)
                GECKO=$(cat passwd.txt | head -n $i | tail -n 1 | cut -d ":"    -f 5)
                echo "<tr>"
                echo "<td>${USERNAME}</td>"
                echo "<td>${GROUP}</td>"
                echo "<td>${SHELL}</td>"
                echo "<td>${GECKO}</td>"
                echo "</tr>"
        
        done
        
        echo "</table>"
   
  ```

- -- 05-b-6600
  ```bash
      #!/bin/bash

        if [ $# -ne 1 ]; then
                echo "Invalid arguments "
                exit 2
        fi

        SRC_DIR=$1

        FILES=$(find $SRC_DIR -type f 2>/dev/null | sort )

        # Strings array and find for every string cmp files if found copy and different name delete it
        COUNTER=0
        for i in $FILES :
        do
                for j in $FILES :
                do
                        if [ $i != $j ]; then
                                cmp $i $j  > /dev/null 2>&1
                                        if [ $? -eq 0 ]; then
                                                rm $j
                                        fi
                        fi
                done

        done
                   
  ```

- -- 05-b-6800
  ```bash
     #!/bin/bash

        SRC_DIR=$1
        ARG=$2
        find $SRC_DIR -type f -printf "%f %s \n" |sort|grep -wv ".*.sh"| xargs -I{} -n 1 echo "{} Bytes"
        if [ "$ARG" != "-a" ]; then
        find $SRC_DIR -type d |sort| grep -wv "\./\..*"| xargs  -d $'\n' sh -c  'for arg do printf "$arg $(ls $arg | wc -l ) contents\n";done'
        else
                find $SRC_DIR -type d |sort| xargs  -d $'\n' sh -c  'for arg do printf "$arg $(ls -a $arg | wc -l ) contents\n";done'
        fi



  ```

-- 05-b-7000
  ```bash
        #!/bin/bash

        if [ $# -eq 0 ]; then
                echo "Invalid arguments"
                exit 2
        fi

        for i in $@
        do
                echo "$i number lines : $(wc -l $i | cut -d " " -f 1 )"
        done
   
  ```

-- 05-b-7100
  ```bash
        #!/bin/bash

        if [ $# -ne 2 ]; then
                echo "Invalid arguments"
                exit 2
        fi

        DIR=$1
        NUMBER=$2

        find $DIR -type f -printf "%f %b \n" 2>/dev/null | awk -v NUMBER=$NUMBER '{ if($2>NUMBER) printf "%s \n",$1}'

  ```

-- 05-b-7200
  ```bash
        #!/bin/bash
        for i in $@
        do
                if [ -f $i ];then
                        echo "$i is a file, contents:"
                        cat $i
                elif [ -d $i ];then
                        echo "$i is a directory"
                        NUMBER_CONTENTS=$(ls $i | wc -l )
                        echo "Files greater than directories content : "
                        find $i -type f -printf "%f %b \n" 2>/dev/null | awk    -v NUMBER=$NUMBER_CONTENTS '{if($2>NUMBER) printf "%s      \n",$1 }'
                fi
        done
  ```

- -- 05-b-7500
  ```bash
        #!/bin/bash

        RANDOM_NUMBER=$(( (RANDOM % 100) + 1 ))
        NUMBER_TRIES=0
        while :
        do
                read -p "Enter a number:" INPUT
                (( NUMBER_TRIES=NUMBER_TRIES+1 ))

                if [ $INPUT -gt $RANDOM_NUMBER ]; then
                        echo "Go lower"
                elif [ $INPUT -lt $RANDOM_NUMBER ]; then
                        echo "Go higher"
                else
                        echo "Correct! Number of guesses $NUMBER_TRIES"
                        exit 0
                fi
        done
  ```

-- 05-b-7550

  ```bash
        #!/bin/bash

        if [ $# -eq 0 ]; then
                echo "Nothing to terminate"
                exit 2
        fi

        USER=$1
        PROCESSES=$(ps -o user,pid,cmd | tr -s " " | grep -w "$USER" | cut -d           " " -f 2 )
        COUNTER=0
        for i in $PROCESSES
        do
                echo $i
                kill -9 $i # Rest in peace process
                (( COUNTER=COUNTER+1))
        done
   
  ```

-- 05-b-7700

  ```bash
     #!/bin/bash

        if [ $# -ne 2 ]; then
                echo "Invalid arguments"
                exit 2
        fi

        DIR=$1
        NUMBER=$2

        find $DIR -type f -printf "%f %b \n" 2>/dev/null | awk -v NUMBER=$NUMBER 'BEGIN{SUM=0}{ if($2>NUMBER) SUM+=$2} END{printf "Result :%s \n",SUM}'
   
  ```

-- 05-b-7800
  ```bash
        #!/bin/bash

        NEW_PATH=$(echo $PATH | tr ":" " ")
        COUNT=0
        for i in $NEW_PATH; do
                (( COUNT=COUNT+$(find $i -type f -executable 2>/dev/null | wc   -l) ))
        done
        echo "Final result : $COUNT"   
  ```

-- 05-b-8000
  ```bash
        #!/bin/bash

        if [ $# -ne 1 ] ; then
                echo "Invalid arguments"
                exit 3
        fi

        USER=$1

        ps -o user,pid,rss,vsz | grep -w "$USER" |tr -s " " | sort -nrk 4 |     awk '{printf "PID:%s RATION:%s \n",$2,$3/$4}'
   
  ```

--- 05-b-9100
  ```bash
        #!/bin/bash

        if [ $# -ne 2 ]; then
                echo "Invalid arguments"
                exit 2
        fi

        SRC=$1
        DST=$2

        EXTENTIONS=$(find $SRC -type f -name "*.*" -printf "%f \n" 2>/dev/null  |cut -d "." -f 2 | sort | uniq)
        for i in $EXTENTIONS
        do
                mkdir -p $DST/$i
                find $SRC -name "*.$i" -exec cp {} $DST/$i \; 2>/dev/null
        done

  ```

- -- 05-b-9200
  ```bash
        #!/bin/bash

        RECURSIVE=0
        if [ "$1" == -r ]; then
                ((RECURSIVE=1))
        fi

        for i in $@
        do
                if [ "$i" == "-r" ]; then
                     continue
                fi

                NUM_FILES=$(ls $i | wc -l)

                if [ $NUM_FILES -eq 0 ]; then
                        rmdir $i
                        echo "[$(date +"%y-%m-%d %T")] $i" >> ~/Development/    Operating-Systems/Week-5/logs/remove.log
                fi

                if [ $RECURSIVE -eq 1 ]; then
                        rm -r $i
                        echo "[$(date +"%y-%m-%d %T")] $i" >> ~/Development/    Operating-Systems/Week-5/logs/remove.log
                fi

        done
   
  ```

--- 05-b-9500
  ```bash
        #!/bin/bash

        if [ $# -ne 2 ];then
                echo "Invalid arguments"
                exit 2
        fi

        RED="\033[0;31m"
        GREEN="\033[0;32m"
        BLUE="\033[0;34m"

        if [ "$1" == "-r" ] ; then
                echo -e "$RED$2"
        elif [ "$1" == "-g" ]; then
                echo -e "$GREEN$2"
        elif [ "$1" == "-b" ]; then
                echo -e "$BLUE$2"
        fi
        echo -e '\033[0m'

  ```

- -- 05-b-9600
  ```bash
        #!/bin/bash

        if [ $# -eq 0 ];then
                echo " So you don't want to delete anything ?"
                exit 2
        fi

        RECURSIVE=0 # 0=false 1=true
        SRC_BACK=/home/dario/Development/Operating-Systems/Week-5/      DeleteWithBackup/backup
        if [ "$1" == "-r" ]; then
                ((RECURSIVE=1))
        fi

        for i in $@
        do
                if [ "$i" == "-r" ]; then
                        continue
                fi

                NEW_NAME=""$i"_$(date +"%y-%m-%d-%T" | tr ":" "-"
        ).tar"
                if [  $(ls $i | wc -l ) -eq 0 ]; then
                        tar -cvf $NEW_NAME ./$i
                        mv $NEW_NAME $SRC_BACK
                        rmdir $i
                elif [ $RECURSIVE -eq 1 ]; then
                        echo "$NEW_NAME"
                        tar -cvf $NEW_NAME  --exclude=./$NEW_NAME $i
                        mv $NEW_NAME $SRC_BACK
                        rm -r $i
                fi
        done

  ```

- -- 05-b-9601
  ```bash
        #!/bin/bash

        SRC_BACK=/home/dario/Development/Operating-Systems/Week-5/      DeleteWithBackup/backup
        if [ "$1" == "-l" ];then
                ls $SRC_BACK | awk -F "_" '{printf "%s (%s-%s)\n",$1,$2,$3}' |  sed 's/.tar//'
                exit 1
        fi

        # Add a way to select the name
        FULL_NAME="$(ls $SRC_BACK | grep -e "$1")"

        NUMBER_MATCHES=$(ls $SRC_BACK | grep -e "$1" | wc -l)

        if [ $NUMBER_MATCHES -ne 1 ]; then
                POSITION=1
                for i in $FULL_NAME
                do
                        echo "($POSITION) $i"
                        ((POSITION+=1))
                done

                read -p "enter position " row
                FULL_NAME="$(ls $SRC_BACK | grep -e "$1" | head -n $row | tail  -n 1)"
        fi

        SRC="$SRC_BACK/$FULL_NAME"
        DEST="$(pwd)"

        if [ $# -eq 2 ]; then
                DEST="$2"
        fi

        tar -xf $SRC --directory $DEST


  ```