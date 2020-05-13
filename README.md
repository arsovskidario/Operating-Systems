**Summary based on practical lectures**
- 


**Inode** is a special key that has in itself GID,SID,time of change,size of file and other metadata
it is useful for identifying a file 
Files have to identificatiors the Inode and the Name of the file 


**Hard Link** is a pointer to a directory with the same Inode as the directory it is pointing to
In order to totally remove the file every hard link must be deleted. ( Basically every hard link acts like a original of the file it is linked to )

```shell
   ln src dest # src file you want to link to dest = destination of shortcut
```

To see more detail about file ( example . Inode , size , atime ,ctime mtime )
```shel
   stat <file_name>
```

The mtime in the file is changed when me save file, add new stuff in it.
When mtime is changed the ctime is changed too.

If we only change the Inode or the metadata in the Inode then we only change the ctime and not the mtime .
Example. chmod changes only the ctime of the file 

```shell
   ls -i  shows the inode numbers
   df -h shows the size of files
```

Acces time is when you open the file


**Soft links** work as shortcuts. They have different Inodes than the file they redirect to. 
If you delete the original file the soft link won't be deleted.

```shell
   ln -s src dest # soft link 
```

Sticky bit = t in the end of the permission means that the file has root access

To be root :
```shell
 sudo su root
```

tar -czvf arhiva.tr b* # add all files that start with the letter b to the arhiva.tr 


**File**
- 
- displays short description  of file
```shell
   file README.md # UTF-8
   file regexCheatSheet # ASCII CODE
   file Week-1/ # directory
```

**Binary files**
- display raw binary data from file (translates all the text in file to hex code)
- **xxd**
-  make a hexdump or do the reverse.
- example;
```shell
   echo   D > hexCode.txt
   xxd hexCode.txt 
   * Will display : 00000000:2020 44 # 00000000:shows the number of line , 20 is space in hex ascii table , 44 is D in hex ascii table    
```
- **xargs**
- use input with a cmd that doesnt normaly use stdin (it uses parametars only)
```shell
   find / -name "*.pdf" | xargs rm  # find all pdf files and remove them 
   # faster than using -exec in find 
```
- by default xargs will get all the input and apply the command only one time on that input
- n 1 will make it apply on every newline (operate one by one )
```shell
   users | xargs echo "Hello," # will print only one Hello, 
   users | xargs echo -n 1 "Hello," #will print Hello, for every user   
```
- I{} create a variable  (the file will be put in the {} as a variable)
- -null  items are terminated by null character instead of whitespace
```shell
   ls -la | grep -Pv "(Wallpapers)"  | egrep -o "Screenshot.*" | xargs -I {} rm {}
```

**Grep** 
   - 
   - work inside of the file 
   - works with regex
   - by default if no file is given, recursively searches threw whole dir
   - -i  makes grep search for case insensitive words
   - -v reverse search 
   - -w select whole word as match ( ex. grep -w "Dario" file => will only search for Dario)
   - -c shows on which line the match appears 
      ex. grep -wirc "Dario" .  -> prints how many matches are there in every file for the word Dario
   - -B <number>  number of lines before match
   - -A <number> number of lines after match
   - -C <number> number of lines before and after the match
   
     ./* =>search for every dir and file 
   

   - -l shows files that contain the match 
    
   - -m <number> limits the number of matches that will be found in a given file 
	ex. if you have x10 Dario users it will return match for only 5 if grep -m 5  "Dario"
   
   
   grep "..."  => . means any character 
   
   - -P means using the Pearl language regex  
	ex.   grep -P "/d {3} " -> search for 3 decimals in a row 

   - -o shows only the matching words and not the entire line

   - -r recursively search threw current directory and subdirectories but dont follow symbolic links
    ex. if grep -r "darko" foo  =>and foo is a sym link it will follow it 

   - -R same as -r but will follow sym links by default 
   

   Some examples of the grep command in use  :
   ```shell
      grep -P -A 4 "^Jane" data.txt | grep -P "[a-zA-Z0-9\-\_\.]+@[a-zA-Z0-9\_]+.[a-zA-Z0-9]+"
      cat allJaneEmails.txt  | sort | awk 'BEGIN { "print \$1" > "allJaneEmails.txt"}' 	
   ```

   - $? specia symbol that returns the exit code of the last command ( 0 = okay,      1 = minor problem ex. cant acces subdir, 2 = serious trouble ex. command line arguments )
   - /dev/null special file (null device ) discards everything inputed to it and    return EOF


**FIND**
-  
- scan through directory for a file or dir that fits a specific criteria
- -type (d,f) search for dir or file
- -name <input> search for file/dir with a given name
  exampls:
  ```shell
     find . -name "darko.txt"
     find . -name "darko.*" 
     find . -name "darko*" # name contains darko
     find . -name "*.pdf" # every pdf file 
  ```
- -iname <input> same as -name but case insensitive
- -group <group_name> find file by group name
- -user <group_name> find file by user name
- -user <group_name> find file by user name
- -perm <binary_or_symobols> find file based on a specifi permission
- -executable for executable files 
```shell
   find ./ -perm -g=w  # will take all the fiels that have write perm on group
   find ./ -perm g=w # will only look for files that will have only group write perm
   find / -perm -0777 # find all fies that have rwxrwxrwx permission
   *Notice: without the - it will search for 000 permission*
```
- -mmin,amin,cmin +/ <number> modified number min ago (+more than 10min ago, - less than 10min ago)
- -mtime,atime,ctime +/- <number> same as min but for days <number>*24 hours
```shell
   find dest -ctime -60 # change time 
    	   -atime # access time
   	   -mtime # modified time
```
 - -maxdepth<number> give number of levels the find can recursively search in 
   *(prefered to be in front of the options )*
```shell
   find / -maxdepth 1 -type f -name "dario" # will look only in the curr directory
   find / -maxdepth 2 -type f -name "dariO"# will look in subdirectories too
```
- -anewer <file_name> # find files that are newer then give file 
```shell
 find -anewer file -exec rm {} \; # remove files that are newer than given file 
 ```
- -size +/ <number>M/K/G search for file/dir +(above) <number> MB(M),KB(K),GB(G), -(below) that <number>
- -empty  find empty files
- -exec \; execute multiple commands when you find the specific file/dir

- -printf print formated text 
    -%d depth of file
    -%f file original name
    -%p full path of file from search destination
    -%P same as %p but without the first /
    -%G get group id , %g group name or group id
    -%U get user id, %u user name or user id
    -%i file inode
    -%m file permission in bits
    -%M permission in symbolic form as in LS -L
    -%s size of file in bytes
    -%y file type 
    -%n number of hard links 
    -%Tk    File's  last modification time in the format specified by
                     k, which is the same as for %A.
    *-%T@  @ = seconds since Jan. 1, 1970, 00:00 GMT, *
    -%Ak acces time 
    -%Ck same as %Tk but for change time 
      *k = @,H(hour),M(min),S(sec),Z(timezone),D(mm/dd/yy)*
    ```shell
       find / -printf '%T@ %p \n' #list all files and seconds from 1970 ,Starting from oldest to newest
       find / -printf '%T@ %p \n' 2>/dev/null | tail -n 1 # grab name of last created file   
    ```


**TR**
   - 
   - translate or delete characters 
   - only works if you pipe or redirect input to it  ( can't specify file as input )

   ```shell 
	tr a-z A-Z  # will translate every lower case letter to UPPER CASE LETTER
   ```

   - -d delete specified character
   - -s squeeze repeats, basically means removing duplicates of a char in a word

   ```shell
      tr -s "a"	
   
   ```
   - *HINT: Handy when used for squeezing spaces and tabs in a text*
  

**Sort**
   - 
   - can use file as input
   - sorts output lexicographically be default
   - -k 2  will sort by 2 column the standard delimetar is space
   - -r  reverse sort
   - -n  numberical sort
   - -t  field separator ( change it if you want for it to be different from psace )
   - -u unique (same as cmd unique )
   ```shell
         sort -t ':' -nk 3 # sort by USERID numerically 
   ```  


**Uniq**
- 
- goes in combination in sort 
- removes continues same strings from lines 
  example :
  ```
      dario
      dario 
      dario 
      brako
      Result :
      dario
      brako
  ```
- -c counts the number of occurences 
  example :
  ```shell
     dario
     dario
     dario
     brako
     uniq -c 
     Result: 
     3 dario
     1 brako
  ```
- -d display only repeated strings in file with the highest repeated(most popular) being on top 
   example :
   ```shell
      apple
      apple
      apple
      pear
      orange
      pear
      plum
      orange
      uniq -d
      Result: 
      apple
      pear
      orange
   ```
- -dc show even the count of the most popular
- -u reverse the uniq command (not repeated lines by default)


**Cut**
   - 
   - extracts/filters text based on columns 
   - -f <number> number of column you want to take
   - -d <symbol> symbol represents a char that will be your delimiter (*By default it is TAB*)
   - -c <range>  retrive bytes/chars from text file in a specific range
   ```shell
         cut -c 1-5 /etc/passwd # will retrive the first 5 chars of passwd file
         cut -c 3 /etc/passwd # will return the 3rd character
         cut -d ':' -f 2 /etc/passwd # will cut by : and take the 2 column 
         cut -d ":" -f 2, # take from 2 column onwards
   ```


**Wc (word count)**
-  
-  wc - print line, word, and byte counts for each file
- -c, --bytes - print the byte counts
- -m, --chars - print the character counts
- -l, --lines - print the newline counts
- -w, --words - print the word counts


**Sed**
  - 
  - functions the same as TR
  - -i can modify the file and write back the output in the same file
  ```shell
     sed -i 's/0/3/' foo.txt # s means substitute 0 with 3 in file
  ```


**Redirection and Pipelines**
   - 
   - /> to file
   - />> append to file
   - <
   - <<
   - 2> stderr to file
   - 1> stdout to file
   - 2>&1 stderr converted to stdout
   - 2>&0 stderr converted to stdin

   ```shell
       tr a-z A-Z <test1 > test1 # test1 will be blank in the end 
   ```

   *[Stack overflow answer](https://stackoverflow.com/questions/6696842/how-can-i-use-a-file-in-a-command-and-redirect-output-to-the-same-file-without-t)*

   > *You can't use redirection operator (> or >>) to the same file, because it has a higher precedence and it will create/truncate the file before the command is even invoked. To avoid that, you should use appropriate tools such as tee, sponge, sed -i or any other tool which can write results to the file (e.g. sort file -o file)*.

   *[Pipeline](https://en.wikipedia.org/wiki/Pipeline_(Unix))*

   Pipelines passs stdout from one process to stdin in the chained process.
   
   > *By default stderr is not passed through the pipe*
   ```
      use |& to pass even the stderr through the pipe
   ```


 **AWK**
 - 
 - Reads/Processes only one line at a time .
 - NF is a variable that counts every word(separeted by whitespace default) in a every line.
 - $NF prints the last word in every line.
 ```shell
   Input: 
         A 25 27 50
         B 35 75
         C 75 7
         D 99 88 76
         awk '{print NF}'
   Result : 
         4
         3
         3
         4
 ```

 ```shell
    awk '{count = ($2+$3+$4)/3;
         if(count <50) print $0,": FAIL";
         else if(count <60) print $0,": C";
         else if(count <80) print $0,": B";
         else print $0,": A";
         }' inputs2

 ```
 - Find the,that,those,then insensitive using extended grep( When Pearl version doesn't work :( )
 ```shell
     grep -iw -e  'the\|that\|those\|then' 

 ```
 
- NR - prints number of row(line) you want from the text
```shell
   awk 'NR==1 END{print}' # will print first row and END will print last row 
``` 

- -v add a variable from bash 
```shell
   $NUMBER=69
   awk -v NUMBER=$NUMBER '{printf NUMBER}'
```


**Processes**
- 
- PID (process ID)
- Nice value 
   * [-20 highest priority,19 lowest] , default=0
   * стойност който определя, кои процес ще се изпълни преди другите. (пример. като приоритетна опашка)
- Memory
   * всеки процес има право да достъпи някакви сегменти в паметта и при достъп на не позволена памет той бива убит.
- Security context
   * стойност която информира ОС за кои права на достъп (privileges) има процесът.
- Scheduling 
   * преценява се на кой процес, колко време ще трябва да му се даде от страна на ОС.
- Context Switch
   * създава илюзия, че процесите работят едновременно а те реално се switchvat един друг и се прекъсват за много мали интервали.
- Enviroment (enviroment i shell promenlivi)
- File descriptor (pipes,sockets,etc)
   * stdin
   * stdout
   * stderr 

- init(PID=1)
   * пръв процес в Линукс който не се създава с fork()
   * starts first during booting
   * is the direct or indirect parent of all the processes (Like the object class in Java)

- pstree
   * displays a tree of processes
   * since every process has a parent a tree structure is formed.

- child process
   * process created using the fork() function
   * copy of parent process

- fork()
   * creates a new process by duplicating the calling process.
   * the created process is called a **child process** and the calling process is called the **parent process**.
   * processes created run in separate memory from the parent.
   * the child process is an exact copy except for : 
      * the child has its own ID, different from the parent,
      * child parent PID = PID of parent
      * doesnt get some signals,semaphores from parent.

- exec 
   * used to run cmds in shell
   * without parameters = "unholy power"
   
   * example 
         ```shell
            exec > myFile # everything in this script will be redirected to myFile and won't be displayed on screen
            cat passwd
            date 
            echo "hell"
         ```

- Process states
   * R - running
   * D - uninterruptable sleep(usually IO)
      * linked directly to hardware
      * can't be touched because its executing IO operations.
   * S - interruptable sleep(waiting for event to complete /sleeping)
      * waiting for signals in order to start executing.
      * mainly all processes are in this state.
   * T - stopped processes by a job.
   * Z - zombie/defunct 
      * process has completed execution but still appears in the process tab.

**PS**
- 
- displays current running processes.
- -u <username> shows processes for specific user
- -e display every process on system
- -l long list for ps cmd
- -o print in specific format (pid,ppid,user,group,cmd,drs=physical memory,vsz = virtual memory,time)
- ps -e -o user=Ime # change name of column header
- --sort=<condition> sort by give condition ex. --sort=start_time 

**JOBS**
- 
- lists your own processes
- processes can work in background and in the foreground
- *fg <id>* puts a process in forground (id se dobiva od jobs [])
- *bg<id>* puts a process in background
- *cmd &* puts a process in background 
- when a process is working in the background you can still use your terminal for cmds, the oposite is not true for processes working in the forground.

- **<ins>Kill</ins>** 
- you can signal your processes whilest root can signal all processes.
- kills(terminates) it by default. (15)
- kill -9 <pid> kills a process that doesn't want to terminate.
- First you try to terminate the process, then if that doesn't work you kill it.

```shell
   kill -SIGTERM <pid>
   kill -SIGKILL <pid>
```


**Scripting** 
- 
   - **Variables**
   - 
      - **Environment variables**
         - variables that are created in the current shell and are accessible by all derived shells from the original shell.
         - you can override the inherited variables from parent
         - **printenv** shows all the environmental variables
         - **export** makes shell variable to an environmental variable.
         - **export -n** demotes a environmental variable back to a shell variable.
   
      - **Shell variable**
         - variable only available in shell that it was created in. 
         - **set** shows all shell variables.
         - **unset** unset a shell variable.
         - by convention variables should be name with UPPERCASE.
   
   - **Creating scripts**
   - 
      - **#!/bin/bash** -> use bash as the scripts command-line interpreter.
      - .sh - convient name for script 
      - chmod +x <name>.sh set the script to be executable
      - **when you open a script from one shell it will have 2 shells running at the same time, one being the one that executes the code in the script**
      - **variables in the script wont be accesible to you unless you open the script using the special cmd *source***
      - **source <name>.sh** is a bash shell built-in command that executes the content of the file passed as argument, in the current shell.
      - this cmd allows you to use the variables in the script as local shell variables.
      - when using variables inside cmds make sure to use ${VAR} notation
   
   - **Test**
   - 
      - special command that is used for testing(comparing) data inside conditionals and loops;
      - -eq,-gt,-ge,-lt,-le 
      - comparing strings with "string"
      - "string1" = "strin2" or test ["dario" = "dario"]

   - **Parametars**
   - 
   - $@ get a list of all arguments passed

   - **Get user input**
   - 
   - read VAR enables you to intake a variable from user input
   - read -n "Enter " var  lets you prompt a text message infront
   - **Loop String**
   - 
     ```bash
         #C style 
         foo=string
         for (( i=0; i<${#foo}; i++ )); do
           echo "${foo:$i:1}"
         done
     ```

   - **${#foo} expands to the length of foo. ${foo:$i:1} expands to the substring starting at position $i of length 1.**
   - [Link to answer](https://stackoverflow.com/a/10552175/11054284)
   - **Using the‘#’ symbol to count the length of a string**
   ```bash
      $ string="Learn Bash Programming with LinuxHint"
      $ echo ${#string} #  Output: 37
   ```
   - **Convert arguments into string**
   - to avoid special characters not being used as a string in script
   - str="'$*'" or str="'$@'"
   - [Link to answer](https://unix.stackexchange.com/a/197794/402386)

   - **RANDOM**
   -  $(( (RANDOM % b) + a  ))

# C Linux

**Open**
- 
- Opens a file based on the given path and returns a file descriptor or -1 if it failed.
- int open(const char *pathname, int flags);
- int open(const char *pathname, int flags, mode_t mode);
- *flags* must be specified (O_RDONLY, O_WRONLY, O_RDWR)
- O_CREAT (create a file if it doesn't exist)
- O_TRUNC (overwrites the file that will be opened)
- O_APPEND (when write() lseek() is position to EOF and you write to EOF)
- *mode* is specified when using O_CREAT flag for creating a new file 
- S_IRWXU  00700 user (file owner) has read,  write,  and  execute permission
- S_IRUSR  00400 user has read permission
- S_IWUSR  00200 user has write permission

**Read**
- 
- ssize_t read(int fd, void *buf, size_t count);
- read()  attempts to read up to *count* bytes from *file descriptor* fd *into the buffer* starting at buf.

- read starts from the file offset made by lseek
- if file seek is at or past EOF no bytes are read and 0 is returned
- on success read the number of bytes read is returned and file is seeked by that ammount 
- can read even smaller than the *count* given (if the file has less bytes to read)

**Write**
- 
- ssize_t write(int fd, const void *buf, size_t count);
- write() writes up to *count* bytes *from the buffer** starting at buf to the file referred to by the *file descriptor* fd.
- The number of bytes written may be less than  count  if,  for  example, there  is  insufficient space on the underlying physical medium
- writing takes place where the last lseek was placed if O_APPEND it will always be the EOF.
- can read even smaller than the *count* given (if the file has less bytes space to write)
- return number of bytes that were written 

**Close**
- 
- int close(int fd);
- closes a file descriptor so it doesn't refer to a file and can be reused
- the lseek is reset on the file 
- return 0 on success and -1 on failure to close 

**errno**
- 
- variable keeps the last function return value 

**lseek**
-  
- lseek(int fd, off_t offset, int whence);
- repositions *file descriptor* to the *offset* according to *whence*
- whence :
- SEEK_SET - sets fd to offset bytes
- SEEK_CUR - current fd offset location plus offset in bytes
- SEEK_END - end of file offset plus offset bytes 

**stat**
- 
-  int stat(const char *pathname, struct stat *statbuf); -> full path name
-  int fstat(int fd, struct stat *statbuf); -> file descriptor
-  int lstat(const char *pathname, struct stat *statbuf); -> symbolic link is pathname and return info about the link itself 

- stat return information about file in the buffer *statbuf* (object of struct stat)
```c
    struct stat {
               dev_t     st_dev;         /* ID of device containing file */
               ino_t     st_ino;         /* Inode number */
               mode_t    st_mode;        /* File type and mode */
               nlink_t   st_nlink;       /* Number of hard links */
               uid_t     st_uid;         /* User ID of owner */
               gid_t     st_gid;         /* Group ID of owner */
               dev_t     st_rdev;        /* Device ID (if special file) */
               off_t     st_size;        /* Total size, in bytes */
               blksize_t st_blksize;     /* Block size for filesystem I/O */
               blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

               /* Since Linux 2.6, the kernel supports nanosecond
                  precision for the following timestamp fields.
                  For the details before Linux 2.6, see NOTES. */

               struct timespec st_atim;  /* Time of last access */
               struct timespec st_mtim;  /* Time of last modification */
               struct timespec st_ctim;  /* Time of last status change */

           #define st_atime st_atim.tv_sec      /* Backward compatibility */
           #define st_mtime st_mtim.tv_sec
           #define st_ctime st_ctim.tv_sec
           };

   ```
   - returns 0 if stat is succesful, and -1 if it failed
   ```c
      // Check if stat was succesfull
      char* fd; // assume it is opened
      struct stat file;
      if ( stat(fd,&file) == -1 ){
         close(fd);
         errx(1,"Couldn't stat file ");
      }
       
   ```


**EXERCISES**
-  
- **[3.Обработка на текст](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/3.%D0%9E%D0%B1%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%BA%D0%B0%20%D0%BD%D0%B0%20%D1%82%D0%B5%D0%BA%D1%81%D1%82.md)**
- **[4.Процеси](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/problems-04-solutions.md)**