
# Summary based on practical lectures

  
## File management and manipulation   🗄️

- file system is organized as a *hierarchical tree structure*
- at the top of the hierarchy is the **root** directory

```bash
# / = root
# /bin = binaries/programs  for system boot and run
# /boot = boot loader
# /dev = devices/nodes that mount to the system
# /etc = scripts for commands and config files
# /home = directory file for user
# /root = home directory for root
# /tmp = for storage of temporary files used by programs, is wiped when system is rebooted
# /usr = programs and support files for user
# /usr/bin = holds executable programs installed by Linux
# /usr/local = programms not installed by Linux  distro, but are used
# /var = where data is likely to change ( databases, emails, snap )

```


### File 
- has two parts 
- *data part* = file contents (text inside)
- *name part* = files name 
-  Files have two identifiers the **Inode** and the **Name of the file**
- *Hard links* create additional name parts that refer to the same data part

### Inode
- block of information 
- is a special key that has in itself GID, SID, time of change, size of file and other metadata
- is useful for identifying a file

```bash
ls -i  # show inode 

# Example 

ls -li regular
# Result
# 6422698 -rw-rw-r-- 1 dario dario 0 юли 31 18:58 regular
# 6422698 is the INODE 
```  

### Hard Link
-  is a pointer to a directory with the **same Inode** as the directory it is pointing to
- can't reference files outside its own file system/ can't reference a file out of its own disk partition
- it may not reference a directory
- in order to totally remove the file every hard link must be deleted. ( Basically every hard link acts like a original of the file it is linked to )
```bash
ln src dest # src is file you wish to link and dest is the hard link 

# Example 

ln dario darko1 
ln dario darko2 
ln dario darko3

ls -lia 

# Result : 
6424755 -rw-rw-r-- 4 dario dario    0 авг  1 19:52 darko1
6424755 -rw-rw-r-- 4 dario dario    0 авг  1 19:52 darko2
6424755 -rw-rw-r-- 4 dario dario    0 авг  1 19:52 darko3
# Number before @user signifies number of Links that reference the original file 
# All of the links have the same INODE 
```

### Symbolic links
- work as windows  shortcuts. 
- they have **different Inodes** than the file they redirect to.
- if we write something to the symbolic link, the original file is written too
- when we delete a sym link the link is only deleted and not the file itself
- if file is delete the symlink points to **null** ( is considered broken)
- can reference directories
- can span physical devices
- size of sym links is the number of characters in the name of the referenced file  and not the size of the refferenced file
- rm  works only on the symlink and not the referenced file
```bash

ln -s src dest # soft link to src with name dest

# Example 
# Symbolic links :

ln -s libc-2.6.so libc.so.6 
ls -la 

# Result : 
1243 lrwxrwxrwx 1 root root 11 2007-08-11 07:34 libc.so.6 -> libc-2.6.so
# First char *l*, means symbolic link
# Has different Inode than the original file 
```

To see more detail about file ( example . Inode , size , atime ,ctime mtime )

```shel

stat <file_name>

```
- atime (access time) = time when the file was opened /touched
- mtime(modified time) =  in the file is changed when me save file, add new stuff in it (Change the data part of the file ).
- ctime (change time) = when the name part of the file is changed (meta data)
- when mtime is changed the ctime is changed too (because if we add more bytes to the file by writing more to it or deleting something its size increases/decreases affecting the inode).  
- if we only change the Inode or the metadata in the Inode then we only change the ctime and **not the mtime** 
- **chmod changes only the ctime of the file**


### File
- displays short description of file

```bash

file README.md # UTF-8

file regexCheatSheet # ASCII CODE

file Week-1/ # directory

```

  

**Binary files**

- display raw binary data from file (translates all the text in file to hex code)

## Wildcards

![Wildcards](https://github.com/arsovskidario/Operating-Systems/blob/master/images/Wildcards.png?raw=true)
![wildcards-example](https://github.com/arsovskidario/Operating-Systems/blob/master/images/Wildcards-example.png?raw=true)

**XXD**
- 
- make a hexdump or do the reverse.
```bash
# Example  
echo D > hexCode.txt

xxd hexCode.txt

* Will display : 00000000:2020 44 # 00000000:shows the number of line , 20 is space in hex ascii table , 44 is D in hex ascii table

```
**PWD**
- 
- print working directory / current directory we are in

**CD**
- 
- change current directory
- cd -  = changes the working directory to the previous working directory

**LS**
- 
- list directory contents
-  can take multiple arguments 
```bash
ls ~ ~/Development
# Result : 
/home/dario:
Books    Development  Downloads  Pictures  snap       Videos
Desktop  Documents    Music      Public    Templates
/home/dario/Development
Operating-Systems
```
- options :
	--  t =  sort by modification time (mtime)
	--  r  --reverse = display in reverse order 
	--  h = human readable, displays file size in human readable format rather than bytes
	--  S = sort results by file size 
	--  i = show inode of file 
	--  A = show almost all 
```bash
ls -t # by modification time, newest first
ls -r || ls --reverse
ls -h 
ls -S # sorted by size
ls - i # Show inode 
ls -A # show all files without . and .. 
```
**TOUCH**
- 
-  change file timestamps
- Update  the  access  and modification times of each FILE to the current time.
```bash
touch file1 # Create file1
touch -a file1 # change atime
touch -m file1 # change mtime 
touch file2.txt file3.txt # Create fle2.txt and file3.txt
```


**CP**
- 
- copy file and directories to destination file/directory 
- can copy multiple files to dest file 
```bash
cp item1 item2 ... itemN dest # copies multiple files to dest directory
```
- Options:
	-- -i = prompt before overwriting file 
	-- -u = update old files and don't copy already existing ones
	-- -v = display informative message as the cmd is executed 
```bash
cp -i item1 dest # Prompts if you want to overwrite file with same name 
cp -u *.html destination # Copy all HTML files that are newer or missing to DEST file 
```
**MV**
- 
- move or rename
- move files/directories or rename if the  file doesn't exist
```bash
mv dir1 dir2 # If dir2 doesn't exist rename dir1 to dir2, if it exists move dir1 inside dir2
```
**MKDIR**
- 
- make directory 
-  can have multiple arguments
- -p make directory with parents
```bash
mkdir f1 f2 f3  # Create 3 dir f1 f2 and f3
mkdir f4 
mkdir -p a/b/c/d # Will created 4 directories a,b,c,d starting with a on top of the hierarchy
mkdir -p foo/bar 
# -- foo
#     -- bar
```
**RM**
-
- remove file or directory
- can have multiple arguments 
- Options:
	-- -r = recursively delete directories, if directory being deleted has subdirectories delete them too 
	-- -i =prompt message before deleting file
	-- **-f** = force remove. Ignore prompt message and non-existent files. This will overwrite the -i option
	-- -v = verbose message ( Information about what the command will be doing )
- **Pro Tip: rm with wildcards is dangerous because there is no undelete cmd, so use *ls* with the *wildcards* you are planning to use in the rm in order to see if the wildcards are working as you want**


**XARGS**
-

- use input with a cmd that doesnt normaly use stdin (it uses parametars only)

```bash

find / -name "*.pdf"  | xargs rm # find all pdf files and remove them

# faster than using -exec in find

```

- by default xargs will get all the input and apply the command only one time on that input

- **-n 1 will make it apply on every newline (operate one by one )**

```bash

users | xargs echo  "Hello,"  # will print only one Hello,

users | xargs echo -n 1 "Hello,"  #will print Hello, for every user

```

- I{} create a variable (the file will be put in the {} as a variable)

- -null items are terminated by null character instead of whitespace

```bash
ls -la | grep -Pv "(Wallpapers)"  | egrep -o "Screenshot.*"  | xargs -I {} rm {}
```

### Permissions 
- each file is owned by a specific UID(user id) and GID(group id)
- **chown** change UID  of file ( only by root)
- **chgrp** change GID of file 
- UID and GID is given to a file based on the person that has created it 
- r - 4 - Read
- w -2 - Write
- x - 1 - Execute
![permissions](https://github.com/arsovskidario/Operating-Systems/blob/master/images/permissions.png?raw=true)
- **l symlink has dummy permissions and not the actual of the file it is referencing**
- **chmod** permission file_path 
![chmodperm](https://github.com/arsovskidario/Operating-Systems/blob/master/images/chmod_permissions.png?raw=true)
-  permission = 0755(rwxr-xr-x), 0644 (rw-r--r--)
- Sticky bit = t in the end of the permission means that the file has root access
- *default permission* = 0666(files), 0777(directories)
-  **umask** mask set to change the default permission 0002 OR 0022 by default ( remove write permission of group and others )
- **userdadd**
- **groupadd**

```bash
# File Permission :
-rw-r--r-- 1

- first dash means file / can have d for dir or l for symlink
- 3 dashes = file owner
- 3 dashes = group
- 3 final dashes = for everyone
- 1 Means number of hard links

drwxr-xr-x 7 dario dario 4096 юли 31 19:32 snap

d - directory
rwx - read write execute for owner
r-x - read execute for group
r-x - read and execute for everyone
7 - 7 hard links
dario - user
dario - group
4096 - size in bytes
юли 31 19:32 - date
snap - name of file/directory
```


## Text manipulation
  

**Grep**
- 

- work inside of the file

- works with regex

- by default if no file is given, recursively searches threw whole dir

- -i makes grep search for case insensitive words

- -v reverse search

- -w select whole word as match ( ex. grep -w "Dario" file => will only search for Dario)

- -c shows on which line the match appears

ex. grep -wirc "Dario" . -> prints how many matches are there in every file for the word Dario

- -B <number> number of lines before match

- -A <number> number of lines after match

- -C <number> number of lines before and after the match

./* =>search for every dir and file

  

- -l shows files that contain the match

- -m <number> limits the number of matches that will be found in a given file

ex. if you have x10 Dario users it will return match for only 5 if grep -m 5 "Dario"

grep "..." => . means any character

- -P means using the Pearl language regex

ex. grep -P "/d {3} " -> search for 3 decimals in a row

  

- -o shows only the matching words and not the entire line

  

- -r recursively search threw current directory and subdirectories but dont follow symbolic links

ex. if grep -r "darko" foo =>and foo is a sym link it will follow it

  

- -R same as -r but will follow sym links by default

  

Some examples of the grep command in use :

```shell

grep -P -A 4 "^Jane" data.txt | grep -P "[a-zA-Z0-9\-\_\.]+@[a-zA-Z0-9\_]+.[a-zA-Z0-9]+"

cat allJaneEmails.txt | sort | awk 'BEGIN { "print \$1" > "allJaneEmails.txt"}'

```

  

- $? specia symbol that returns the exit code of the last command ( 0 = okay, 1 = minor problem ex. cant acces subdir, 2 = serious trouble ex. command line arguments )

- /dev/null special file (null device ) discards everything inputed to it and return EOF

  
  

**FIND**
- 

- scan through directory for a file or dir that fits a specific criteria

- -type (d,f) search for dir or file

- -name <input> search for file/dir with a given name

exampls:

```shell

find . -name "darko.txt"

find . -name "darko.*"

find . -name "darko*"  # name contains darko

find . -name "*.pdf"  # every pdf file

```

- -iname <input> same as -name but case insensitive

- -group <group_name> find file by group name

- -user <group_name> find file by user name

- -user <group_name> find file by user name

- -perm <binary_or_symobols> find file based on a specifi permission

- -executable for executable files

```shell

find ./ -perm -g=w # will take all the fiels that have write perm on group

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

find / -maxdepth 1 -type f -name "dario"  # will look only in the curr directory

find / -maxdepth 2 -type f -name "dariO"# will look in subdirectories too

```

- -anewer <file_name> # find files that are newer then give file

```shell

find -anewer file -exec rm {} \;  # remove files that are newer than given file

```

- -size +/ <number>M/K/G search for file/dir +(above) <number> MB(M),KB(K),GB(G), -(below) that <number>

- -empty find empty files

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

-%Tk File's last modification time in the format specified by

k, which is the same as for %A.

*-%T@ @ = seconds since Jan. 1, 1970, 00:00 GMT, *

-%Ak acces time

-%Ck same as %Tk but for change time

*k = @,H(hour),M(min),S(sec),Z(timezone),D(mm/dd/yy)*

```shell

find / -printf '%T@ %p \n'  #list all files and seconds from 1970 ,Starting from oldest to newest

find / -printf '%T@ %p \n'  2>/dev/null | tail -n 1 # grab name of last created file

```

  
  

**TR**
- 

- translate or delete characters

- only works if you pipe or redirect input to it ( can't specify file as input )

  

```shell

tr a-z A-Z # will translate every lower case letter to UPPER CASE LETTER

```

  

- -d delete specified character

- -s squeeze repeats, basically means removing duplicates of a char in a word

  

```shell

tr -s "a"

```

-  *HINT: Handy when used for squeezing spaces and tabs in a text*

  

**Sort**
- 

- can use file as input

- sorts output lexicographically be default

- -k 2 will sort by 2 column the standard delimetar is space

- -r reverse sort

- -n numberical sort

- -t field separator ( change it if you want for it to be different from psace )

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

- -c <range> retrive bytes/chars from text file in a specific range

```shell

cut -c 1-5 /etc/passwd # will retrive the first 5 chars of passwd file

cut -c 3 /etc/passwd # will return the 3rd character

cut -d ':' -f 2 /etc/passwd # will cut by : and take the 2 column

cut -d ":" -f 2, # take from 2 column onwards

```

  
  

**Wc (word count)**
- 

- wc - print line, word, and byte counts for each file

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

grep -iw -e 'the\|that\|those\|then'

  

```

- NR - prints number of row(line) you want from the text

```shell

awk 'NR==1 END{print}'  # will print first row and END will print last row

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

exec  > myFile # everything in this script will be redirected to myFile and won't be displayed on screen

cat passwd

date

echo  "hell"

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

-  *fg <id>* puts a process in forground (id se dobiva od jobs [])

-  *bg<id>* puts a process in background

-  *cmd &* puts a process in background

- when a process is working in the background you can still use your terminal for cmds, the oposite is not true for processes working in the forground.

  

-  **<ins>Kill</ins>**

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

-  **Variables**
- 

-  **Environment variables**

- variables that are created in the current shell and are accessible by all derived shells from the original shell.

- you can override the inherited variables from parent

-  **printenv** shows all the environmental variables

-  **export** makes shell variable to an environmental variable.

-  **export -n** demotes a environmental variable back to a shell variable.

-  **Shell variable**

- variable only available in shell that it was created in.

-  **set** shows all shell variables.

-  **unset** unset a shell variable.

- by convention variables should be name with UPPERCASE.

- which <cmd> = shows directory of command

-  **Creating scripts**

-

-  **#!/bin/bash** -> use bash as the scripts command-line interpreter.

- .sh - convient name for script

- chmod +x <name>.sh set the script to be executable

-  **when you open a script from one shell it will have 2 shells running at the same time, one being the one that executes the code in the script**

-  **variables in the script wont be accesible to you unless you open the script using the special cmd *source***

-  **source <name>.sh** is a bash shell built-in command that executes the content of the file passed as argument, in the current shell.

- this cmd allows you to use the variables in the script as local shell variables.

- when using variables inside cmds make sure to use ${VAR} notation

-  **Test**
-

- special command that is used for testing(comparing) data inside conditionals and loops;

- -eq,-gt,-ge,-lt,-le

- comparing strings with "string"

- "string1" = "strin2" or test ["dario" = "dario"]

  

-  **Parametars**
-

- $@ get a list of all arguments passed

  

-  **Get user input**

-

- read VAR enables you to intake a variable from user input

- read -n "Enter " var lets you prompt a text message infront

-  **Loop String**
- 

```bash

#C style

foo=string

for  (( i=0; i<${#foo}; i++ ));  do

echo  "${foo:$i:1}"

done

```

  

-  **${#foo} expands to the length of foo. ${foo:$i:1} expands to the substring starting at position $i of length 1.**

-  [Link to answer](https://stackoverflow.com/a/10552175/11054284)

-  **Using the‘#’ symbol to count the length of a string**

```bash

$ string="Learn Bash Programming with LinuxHint"

$ echo ${#string} # Output: 37

```

-  **Convert arguments into string**

- to avoid special characters not being used as a string in script

- str="'$*'" or str="'$@'"

-  [Link to answer](https://unix.stackexchange.com/a/197794/402386)

  

-  **RANDOM**

- $(( (RANDOM % b) + a ))

  

# C Linux

  

**Open**
- 

- Opens a file based on the given path and returns a file descriptor or -1 if it failed.

- int open(const char *pathname, int flags);

- int open(const char *pathname, int flags, mode_t mode);

-  *flags* must be specified (O_RDONLY, O_WRONLY, O_RDWR)

- O_CREAT (create a file if it doesn't exist)

- O_TRUNC (overwrites the file that will be opened)

- O_APPEND (when write() lseek() is position to EOF and you write to EOF)

-  *mode* is specified when using O_CREAT flag for creating a new file

- S_IRWXU 00700 user (file owner) has read, write, and execute permission

- S_IRUSR 00400 user has read permission

- S_IWUSR 00200 user has write permission

  

**Read**
- 

- ssize_t read(int fd, void *buf, size_t count);

- read() attempts to read up to *count* bytes from *file descriptor* fd *into the buffer* starting at buf.

  

- read starts from the file offset made by lseek

- if file seek is at or past EOF no bytes are read and 0 is returned

- on success read the number of bytes read is returned and file is seeked by that ammount

- can read even smaller than the *count* given (if the file has less bytes to read)

  

**Write**
- 

- ssize_t write(int fd, const void *buf, size_t count);

- write() writes up to *count* bytes *from the buffer** starting at buf to the file referred to by the *file descriptor* fd.

- The number of bytes written may be less than count if, for example, there is insufficient space on the underlying physical medium

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

- int stat(const char *pathname, struct stat *statbuf); -> full path name

- int fstat(int fd, struct stat *statbuf); -> file descriptor

- int lstat(const char *pathname, struct stat *statbuf); -> symbolic link is pathname and return info about the link itself

  

- stat return information about file in the buffer *statbuf* (object of struct stat)

```c

struct stat {

dev_t st_dev; /* ID of device containing file */

ino_t st_ino; /* Inode number */

mode_t st_mode; /* File type and mode */

nlink_t st_nlink; /* Number of hard links */

uid_t st_uid; /* User ID of owner */

gid_t st_gid; /* Group ID of owner */

dev_t st_rdev; /* Device ID (if special file) */

off_t st_size; /* Total size, in bytes */

blksize_t st_blksize; /* Block size for filesystem I/O */

blkcnt_t st_blocks; /* Number of 512B blocks allocated */

  

/* Since Linux 2.6, the kernel supports nanosecond

precision for the following timestamp fields.

For the details before Linux 2.6, see NOTES. */

  

struct timespec st_atim; /* Time of last access */

struct timespec st_mtim; /* Time of last modification */

struct timespec st_ctim; /* Time of last status change */

  

#define st_atime st_atim.tv_sec /* Backward compatibility */

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

  

**Void array**
- 

- you can appoint any type to it and then cast it back to that type

```c

// Casting void array elements to u_int32_t

int  cmp(const void* a, const void* b){

u_int32_t x = *((u_int32_t*)a);

u_int32_t y = *((u_int32_t*)b);

  

if(x>y)

return 1;

else if (x<y)

return -1;

  

return 0;

}

  

int  main(){

int elements =5;

void* x = malloc(elements * sizeof(u_int32_t));

qsort(x,elements,sizeof(u_int32_t),cmp);

}

```

## Processes

  

**Execl**
- 

- int execl(const char *path, const char *arg0, ... /*, (char *)0 */);

- path = path to command/executable , arg0 = executable name, arg[1]..= parameters of executable, NULL = terminate list of arguments (arg[1],arg[2]..etc)
- *(char *)NULL* list of arguments must be terminated by it.
- **execl replaces the current process image with a new process image.**
- replaces the curent runnig program with a new one.  (basically the pice of code that is left is overriden)

- process iamge = executable program stored on the disk.

- return -1 on failure

- execl takes full path to executable

- int execlp(const char *file, const char *arg, ... /* (char *) NULL */);

- execlp takes name of command and searches $PATH for it.


- **[Execl vs Fork](https://stackoverflow.com/a/4205020/11054284)**

```c
    // Basically execl opens a different process and executes it to the full degree
    // if it can't execute a cmd / doesnt enter a new process  -1 is returned

    if ( excel("ls","ls","-l") == -1) {
            err(1,"Couldn't execute cmd !");
    }

    printf("Print me!"); // Wont be printed because the current process is swaped with the ls process image 
    // ne se navagja vishe u ovj proces nego u swaped process e

    int childPid;
    int forkId= fork();
    if (forkId == 0){
        wait(NULL); // wait for child to finish
    }
    else {
        
         childPid = getpid();
         if ( excel("ls","ls","-l") == -1) {
            err(1,"Couldn't execute cmd !");
    }

    printf("Command was executed by %d",childPid); // Wont work
    // Because the child doesn't use the parents childPid variable, but it's own copy...
    // Output from printf is line buffered. Basically /n flushes the buffer or fflush() if you do it manually. 
    }

    Pro tip: 
        // Use \n with fork processes because of buffer issues when flushing stdout 
        printf("Print \n"); // will flush buffer and print to screen



```

  

```c

execl("/bin/ls","ls","-la",(char*)NULL);

  

execlp("ls","ls","-la",(char*)NULL);

```

  

**Fork**
- 

-  *pid_t fork(void);*

- create a new process by duplicating the *calling process*.

- new proces = child, old process= parent

- inherits nearly everything from the parent process, including parents open file descriptors.

- the *child* and *parent* process work concurrently starting from the next line after the fork() function.

- the *child* and *parent* process have the same priority.

- when the *parent* process finishes before the *child* process, the prompt is returned for use but the *child* process keeps on runnig until it finishes.

- when the *parent* process finishes before the *child* process, the child process PPID is set to 1 (init PID) because the parent has finished and its PID no longer exists.

-  *RETURN*: pid_t = 0 *for child*, pid_t >0 *for parent*, pid_t = -1 *for failure*

  

```c

// Will print out father and son 1000 times in different order.

int n =  1000000;

  

if (fork() > 0) {

// In Parent

for (int i = 0; i < n; i++) {

printf("father\n");

}

} else {

// In Child

for (int i = 0; i < n; i++) {

printf("son\n");

}

}

```

  

**Wait**
- 

-  *pid_t wait(int *wstatus);*

- makes the calling process(parent) wait for state changes in a child process in order to obtain information about the state change.

- return PID of terminated child process on success and -1 on error.

- status information also includes : normal/abnormal termination, termination cause, exit status.

- WIFEXITED(status): child exited normally

- WEXITSTATUS(status): return code when child exits

- WIFSIGNALED(status): child exited because a signal was not caught

- WTERMSIG(status): gives the number of the terminating signal

- WIFSTOPPED(status): child is stopped

- WSTOPSIG(status): gives the number of the stop signal

  

```c

int status;

  

if (fork ==0) {

exit(0);

}

else{

wait(&status);

  

if (WIFEXITED(stat)) {

printf("Exit status: %d\n", WEXITSTATUS(stat));

}

}

```

  

**getpid & getppid**
- 

- pid_t getpid(void);

- pid_t getppid(void);

- return PID and PPID of calling process.

- function is always succesful.

  

**Pipes**
- 

-  *int pipe(int pipefd[2]);*

- creates a pipe by giving pipefd[0] and pipefd[1] random fd and connecting them

- pipefd[0] = read end, pipefd[1] = write end

- if you close a fd in the parent process, the fd is not closed in the child process (works like hard links).

- Data writen to the **write end** of the pipe can be read by the **read end** of the pipe.

- write >>>> read

- the **write end data* is *buffered* until it is fully read by the read end.
```c
	
Parent A Child B

a[0] <<<<<<<<<<<< a[1] // output ide kym input 1 stdout 0 stdin

a[1] >>>>>>>>>>>>> a[0]

  

// Close used pipe sides

  

// Child

close(a[1]);

read(a[0],...); // will wait for read from parent

  

// Parent

close(a[0]);

write(a[1],...);

```  

-  **After writing to pipe always close it in order to avoid a deadlock**

  

- Example

```c

//Child

close(a[1]); //unused pipe side

read(a[0],ch,1); // will read until parent has sent signal that it has finished writing

close(a[0]);

  

//Parent

close(a[0]); //unused pipe-side

write(a[1],str,sizeof(str));

//close(a[1]); if you dont close the stdout it will create a deadlock

  

```

  

**DUP**
- 

-  *int dup(int oldfd);*

-  *int dup2(int oldfd, int newfd);*

- creates a copy of the oldfd using the lowest-numbered unused file descriptor as the new file descriptor.

  

```c

// 0 1 2

int f = open ....

  

// 0 1 2 3

close(1); // close stdout

  

// 0 x 2 3

dup(f);

  

// 0 1 2 3

// 1==3

printf(); // will write in f (fd=3) not on stdout

  

dup2(f,1); // if the fd is already in use it will silently close it

// and will use it as the new file descriptor.

// here f is equl to stdout

```
  

**EXERCISES**
- 

-  **[3.Обработка на текст](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/3.%D0%9E%D0%B1%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%BA%D0%B0%20%D0%BD%D0%B0%20%D1%82%D0%B5%D0%BA%D1%81%D1%82.md)**

-  **[4.Процеси](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/problems-04-solutions.md)**

-  **[5.Shell Scripts](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/problems-05-solutions.md)**

-  **[6.C Kernel Functions](https://github.com/arsovskidario/Operating-Systems/tree/master/Week-7/ExamPrep_C)**
