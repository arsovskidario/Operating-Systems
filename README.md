
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

### Permissions 🔑
- each file is owned by a specific UID(user id) and GID(group id)
- **chown** change UID  of file ( only by root)
- **chgrp** change GID of file 
- UID and GID is given to a file based on the person that has created it 
- r - 4 - Read
- w -2 - Write
- x - 1 - Execute

- ![permissions](https://github.com/arsovskidario/Operating-Systems/blob/master/images/permissions.png?raw=true)
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

  


## Redirection and Pipelines  🚰

- redirections are used to send from command to file
```bash
> send STDOUT to different file overwriting it 
>> append STDOUT to file
# If file doesn't exist it is created
<
<<
cat foo > bar # If bar doesn't exist it is created else it is overwriten with content from foo

# STDIN, STDOUT, STDERR are file descriptors in Linux, because everything is a file 
Filedescriptors : STDIN =0, STDOUT=1, STDERR=2

cat foo 1> bar # same as cat foo > bar

#STDOUT, STDERR are printed to the screen by default
#STDIN takes input from the keyboard by default 

2> send STDERR to file overwriting it 
2>> send STDERR to file appending it to the end

ls -la foo > result.log 2>&1 # Redirect stdout and stderr to result.log
ls -la foo &> result.log # Same as above, just more modern 
ls -la foo >> result.log 2>&1 # Append instead of overwriting 

2>&1 # STDERR converted to STDOUT
2>&0 # STDERR converted to STDIN 

# Sending to bit bucket( /dev/null)
ls -la foo > result.log 2>/dev/null

```

  ### Things to avoid
```bash
tr a-z A-Z <test1 > test1 # test1 will be blank in the end
```

  

*[Stack overflow answer](https://stackoverflow.com/questions/6696842/how-can-i-use-a-file-in-a-command-and-redirect-output-to-the-same-file-without-t)*

  

> *You can't use redirection operator (> or >>) to the same file, because it has a higher precedence and it will create/truncate the file before the command is even invoked. To avoid that, you should use appropriate tools such as tee, sponge, sed -i or any other tool which can write results to the file (e.g. sort file -o file)*.

  

*[Pipeline](https://en.wikipedia.org/wiki/Pipeline_(Unix))*

  

- Pipelines pass STDOUT from one process to STDIN in the chained process.
-  <ins>***EXCLUSIVELY*** </ins>  used for *commands*
```bash
command1 | command2
find . -name ".pdf" 2>/dev/null | grep -w "dario"
```

> **By default *STDERR* is not passed through the pipe**

- **use |& to pass even the stderr through the pipe**


**FIND**
- 

- scan through directory for a file or dir that fits a specific criteria (traversing the tree hierarchy)
- has Tests, Options,  Actions
- **find frequently stats files during the processing  of  the  command
       line itself, before any searching has begun.**
### Find number logic 
- +n = means above/greater than n 
- -n = means lower than n
- n = means exactly n
```bash
find . -name "*.pdf" -amin -10 # PDF that was accessed before 10 mins
```

- -P = by DEFAULT, *never follow symbolic links* ( will only list the links but wont follow them)
-  -L = follow symbolic links (broken sym links are ignored) 

### Tests
- tests are conjucted with the logical AND, thus all tests need to met the criteria before actions are taken
- type <type_file>	
	- f = file
	- l = symbolic link
	- d = directory
```bash 
find . -type f -executable 2>/dev/null # Find files that are executable
```
- name <pattern_name>
- iname  = like name but case-insensitive
- empty = match empty files and directories
```bash
find . -type f -empty
```
- executable = match files which are executable and directories that are searchable
- inum n = match files with inode number n ( Helpful for finding Hard Links )
```bash
find . -inum 123 # Will find all hard links of file with inode 123
```
- samefile <file_name> = same as inum, but you give the file reference ( its name )
- links n = file has n hard links 
- size
	- +n = larger than n amount
	- -n = smaller than n
	- n = exactly n
	- Unit Measurement : 
		- Default is 512 bytes block
		- c = bytes
		- w = 2bytes (words)
		- k = kilobytes
		- M = megabytes
		- G = gigabytes
```bash
find . -type d -size +10M # Directories larger than 10MB
find . -type f -size -5c # less than 5 bytes
find . -type l -size 1024k # exactly 1024KB
```
#### Time modifications
- cmin n   = file/dir changed n minutes ago
- ctime n = file/dir changed n *24 hours ago (DAYS)
- amin n = file/dir accessed n minutes ago
- atime n = file/dir accessed n * 24 hours ago
-  mmin n = modify time
- mtime n 
- newer <file_name> = match file/dir modified more recently than file 
- anewer <file_name> = accessed more recently
- cnewer <file_name> =changed more recently

#### Permissions 
- perm <bin_mode> = match files/dir that have permission set by mode
- user <u_name> = match files belonging to user
- nouser  = not belonging to user
- uid  <u_number> =match files belonging to USER ID
- gid <g_number> = matching group id
- group <g_name> = matching group by name

```bash
We can specify the MODE in three different ways as listed below.

    If we specify the mode without any prefixes, it will find files of exact permissions.
    If we use "-" prefix with mode, at least the files should have the given permission, not the exact permission.
    If we use "/" prefix, either the owner, the group, or other should have permission to the file.

    find . -perm 0777 # Exact 777 permission 
    find . -perm -0400 # user has atleast read permission  (0400 and above is accepted)
    find . -perm -0220 # File has to be read by owner and group
    find . -perm /02220 # Can be read by User OR Group, either will work

    # 0665 file1, 0644

    find . -perm -0220 # Result : file1
    find . -perm /0220 # Result : file1 file2
    # File2 is printed because it has READ user permission, and because you need only one to match it works

```

```bash
find ./ -perm g=w # Find files that have only group write permission ( Like 0020)
find ./ -perm /g=w # Find files that have group write permission
find / -perm /0777 # find all fies that have rwxrwxrwx permission and below 
```
### Actions 
- when result is found we can do various actions on that result 
- **WARNING:** Place at the end of the find statement 
```bash
find ~ -type f - name "*.pdf" -print # if the two conditions are met the files will be printed out
find ~ -print -type f -name "*.pdf" # Will print before the tests and thus will not return desired result 
# Basically it will print out all the files, not only PDF's
```
- delete = delete files that meet criteria
- print = print list of results ( By default this is on )
```bash
find ~ -print # This is on by default
```
- print0  = same as print but will capture names with embedded spaces or null in their name and the same goes for xargs

- printf = print formated text
```bash
-%f  # File original name
-%i  # File inode
-%p  # Full path from starting search point
-%P  # Same as -p without starting point
-%d  # Depth of the file from search destination
-%n  # Number of hard links
-%s  # Size in bytes
-%y  # File type 


-A@ # Aceess time in UNIX Seconds time from 1 Jan 1970
-Ar # Time Formar HH:MM:SS 12 hours
-AT # time, 24-hour (hh:mm:ss.xxxxxxxxxx)
-T@ # Modifiet time -||-
-C@ # change time -||-

find / -printf "@T@ %p \n"

find / -printf "%A@ %p \n" 2>/dev/null | tail -n 1  # Grab full path of Last accessed file


-%G # Group Id
-%g # Group name
-%U # User ID
-%u # user name
-%m # file permissions in bits
-%M # File permissions symobilic like in LS -l

```
- quit = quit once a match has been made
- ls = ls on files and send output to STDOUT
- **exec vs xargs**
```bash
# Why is xargs faster than exec
-exec works likes this : 
# ls -l file1
# ls -l file2
xargs works like this :
# ls -l file1 file2

find . -name "*.pdf" -print0 | xargs -0 ls
```
### Options
- used to control the SCOPE of the find search
- -maxdepth<lvl_number> = levels are non-negtaive maxdepth = do kolko pod direktorie da ide nadole
- mindepth<lvl_number> = kolko minimum pod direktorie da ima toj shto trazimo 
*(prefered to be in front of the options )*
```bash

find / -maxdepth 1 -type f -name "dario"  # Will look only in the curr directory

find / -maxdepth 2 -type f -name "dariO" # Will look in subdirectories too 
```

- mount = not to traverse mounted directories on other systems
- prune = if file is directory don't descend into it 


## Text manipulation 📝

### REGEX 
-  find patterns in text
- Metacharacters reserved for REGEX ( extended regular expressions used by grep, sed)
	- ^ $ . [ ] { } - ? *  +  (  )  |  \  
	- They need to be escaped if you want them to be a literal character.
	```bash
	sed 's/^\(/d*\)/prefix' # Find phone numbers writen with () at the start 
	Example:
	(234) 524 233
	``` 
### REGEX Cheat Sheet
```bash

Anchors :
^ - beginning of line
$ - end of line
^$ - Match all blank lines 

grep "^zip$" /etc/ # Will match only lines that have zip only on the line itself
# Example : 
# Bargakso zip
# ksdsdkzip
# zip
# Output :
# zip 

Groupings :
[] - Matches Characters in brackets ( Set of characters )
egrep "[a-z]$" # Match ending with lower case letter
[^ ] - Matches Characters NOT in brackets ( Negates the Set )
| - Either Or
egrep "AAA|BBB"  # Will match string "AAA" OR "BBB"
( ) - Group
egrep "(AAA|BBB)" # Better practice than above mentioned 
egrep "^(AAA|BBB)\.zip" # Match files startring with AAA OR BBB and ending with .zip

. - Any Character Except New Line
\d - Digit (0-9)
\D - Not a Digit (0-9)
\w - Word Character (a-z, A-Z, 0-9, _)
\W - Not a Word Character
\s - Whitespace (space, tab, newline)
\S - Not Whitespace (space, tab, newline)
\b - Word Boundary
\B - Not a Word Boundary

egrep "(\w+)" # Match words 
egrep "([[:alnum:]]+)" # Same as above 

Quantifiers:

* - 0 or More
+ - 1 or More
? - 0 or One
{3} - Exact Number
{3,4} - Range of Numbers (Minimum, Maximum)
{3,} - 3 or more times
egrep ".{3}\.zip" # Match 3 characters after that .zip extension

#### Sample Regexs ####

[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+
```

### Grep
- works inside of file
- works with regex
- by default if no file is give, recursively searches through whole directory
- **Options:**
	- -i ignore case (doesn't distinguish lowercase/uppercase)
	- -v invert the match
	- -c count matches
	- -l print name of file contains a match insead of the line
	- -L inverse of l ( will print files that dont contain the match)
	- -n on what line the match is located
	- -m NUM , max-count =num stop after num of matches
	- -w select whole word as match
	- A NUM  number of lines after match
	- B NUM number of lines before match
	- C NUM number of lines before AND after match
- **use egrep for the extended REGEX**
```bash
egrep -A 4 "^Jane" data.txt | egrep "[a-zA-Z0-9\-\_\.]+@[a-zA-Z0-9\_]+.[a-zA-Z0-9]+"
 ```
```bash
# Take every word from a line with grep
egrep -o "\s*\w*\s*"
```
### TR

- translate or delete characters
- only works if you pipe or redirect input to it ( can't specify file as input )  
```bash
tr a-z A-Z # will translate every lower case letter to UPPER CASE LETTER
```  
- -d delete specified character
- -s squeeze repeats, basically means removing duplicates of a char in a word 

```bash
tr -s "a"
tr -s " " text.txt
```
-  ***HINT:** Handy when used for squeezing spaces and tabs in a text*

### Sort
- sort file lexicographically by default
- can use file as input
- Sort multiple files into one file
![Sort_fields](https://github.com/arsovskidario/Operating-Systems/blob/master/images/sort.png?raw=true)

```bash
sort file1.txt file2.txt > result_sorted_files.txt
```
- **Options:**
	- n sort based on numerical values
	- r reverse the sorting order ( By default it is Ascending order )
	- k sort based on a key field
	- t define the filed separator ( By default it is space or tabular space)
	- o send sorted output to file and not STDOUT
	```bash
	sort -t ":" -nk 3 /etc/passwd # Sort by USERID numberically 
	sort -t ":" -k 7 /etc/passwd | head 
	```

### Uniq
- accepts data from STDIN or file and send result to STDOUT
- goes in combination with sort
- Lines need to be adjacent to each other (next to each other ) to be removed by uniq
- **Options:**
	- i ignore case while comparing
	- s n, skip n chars from each line
	- u output only unique lines. Lines with duplicates are ignored
	- d output only lines that have duplicate entries and are not unique
	- f n, skips n fields in comparing
	- c counts the number of occurrences
```bash
# Input
dario
dario
dario
brako
uniq -c
# Result:
3 dario
1 brako
```

```bash
# Examples
a
a
b
c
c
c
uniq text_above 
# Result : 
# Duplicates are removed and only one of each group is left
a
b
c

uniq -u text_above 
# Result : 
b

uniq -d text_above 
# Result : 
a
c
```

### Cut 
- extracts/filters text based on columns
-  **Options :**
	- f number of column you want to take ( can be multiple)
	- d symbol, represents a char that will be your delimiter ( By default is TAB )
	- c retrieve bytes/chars from text file in a specific range
	- --complement  = Reverse the cut operation
	```bash
	cut -c 7,10 file.txt # Will take the 7th and 10th character 
	cut -c 7-10 file.txt # Take characters from 7th position to 10th position 
	cut -c 23- file.txt # Take chars starting from 23th position to end of line
	cut -c 3 /etc/passwd # Will return the 3rd character
	cut -d ':' -f 2 /etc/passwd # Will cut by : and take the 2nd column
	cut -d ":" -f 2- /etc/passwd  # Will cut by :  and take from the 2nd column onwards
	```
### Comm 
- comm file1 file2
	- compare two text files and displays the lines that are unique to each one and the lines they have in common
	- First column unique lines for file1,  second column is reserved for unique lines of file2, third column is for the lines that are common for both files
	```bash
	comm -12 file1 file2 # Will show only the common lines between the two files
	# -12 Means don't show the first and the second column 
	comm -1 file1 file2 # Will show the unique lines of file2 and the common lines
	```
### Wc (word count)
- wc - print line, word, and byte counts for each file
- **-l**, --lines - print the newline counts
- **-w**, --words - print the word counts
- **-c**, --bytes - print the byte counts
- **-m**, --chars - print the character counts

### Head 
- print the first 10 lines of input
- **Options:**
	- c print  the  first  NUM bytes of each file, **-** means print all but the last NUM bytes of file
	- n print first NUM liens of file, **-** print all but the last NUM lines
	```bash
	sort -n -5 /etc/passwd
	sort -c 25 
	```
  
### Tail
- print last 10 lines of input
- **Options:**
	- c print the last NUM bytes of file, +NUM print with starting from NUM byte of file
	- n print the last NUM lines, +NUM start print from NUM line 

### AWK

- Reads/Processes only one line at a time .
- **NF** is a variable that counts every word(separeted by whitespace default) in a every line.
- **$NF** prints the last word in every line.
- $0 = references whole line, $1 =references first column , $n = get n column
- BEGIN = block executed at start
- END = block executed at the end 
- FILENAME = get current filename
```bash
awk '{print FILENAME}' f1 
# Result
f1 
f1
f1
```

```bash
### Trcik Alert! 
awk -F "," '{print $NF,$0}' | sort -nrk 1 | cut -d " " -f 2-  # Get last word and sort by that number after wards delete it 

#-- 03-b-9053
# **Използвайки файл population.csv, намерете коя държава има най-много население през 2016. А коя е с най-малко население?
# (Hint: Погледнете имената на държавите)**

```bash
cat population.csv | egrep "2016," | awk -F "," '{print $NF,$0}' | sort -nrk 1 | cut -d " " -f 2-
```

- **NR** - prints number of row(line) you want from the text
```bash
awk 'NR==1 END{print}'  # will print first row and END will print last row
```

- -v add a variable from bash

```bash
$NUMBER=69
awk -v NUMBER=$NUMBER '{printf NUMBER}'
```

#### Function 
- substr(str,index,len) = take string and make substring starting at index and of length len
```bash
cat /etc/passwd | cut -d ":" -f 5 | awk '{for(i=1;i<=length($1);i++) print substr($1,i,1)}' | sort | uniq -cu # get every letter from line
awk '{print substr($1,length($1),1)}' # Get last character of every line(word)
```
- length(strin) = length of string 

```bash
# Input:

A 25 27 50
B 35 75
C 75 7
D 99 88 76

awk '{print NF}' # Will print number of words on every line

# Result :

4
3
3
4
```


```bash
awk '{count = ($2+$3+$4)/3;

if(count <50) print $0,": FAIL";

else if(count <60) print $0,": C";

else if(count <80) print $0,": B";

else print $0,": A";

}' inputs2
```

- Find the,that,those,then insensitive using extended grep( When Pearl version doesn't work :( )

```bash
egrep -iw '(the|that|those|then)'
```

### Sed
- stream editor
- Performs text editing on a stream of text
- Pattern in sed are **REGEX** patterns \
- **Basic commands**
![commands](https://github.com/arsovskidario/Operating-Systems/blob/master/images/sed_editing_cmds.png?raw=true)
- **s** = search and replace strings
```bash
sed "s/str1/str2/" file1 # Will replace only the first instance on every line
sed "s/str1/str2/g" file1 # Will replace every instance of str1 on every line
```
- **addressing** = specifies which lines of the input stream will be edited
- If no address is specified the editing is carried out on every line in the input stream
![set_addressing](https://github.com/arsovskidario/Operating-Systems/blob/master/images/sed_address.png?raw=true)
```bash
# Will translate the string EVERY first occurenec of string darko to magarko
sed 's/darko/magarko'
# Will translate only the string darko on the 2ND LINE of the input
sed '2s/darko/magarko' 
```
- using REGEX you can capture groups and use \n for manipulating the output, n being number of group from 1 to 9  
```bash
# Example REGEX :
# Format given MM/DD/YY
# First group matches the month, second matches the day, the third matches the year
([0-9]{2})/([0-9]{2})/([0-9]{4})$ =REGEX TO MATCH date
\3-\1-\2 # Takes group 3,1,2 and therefore is the format YY/MM/DD
```
- **Meta characters must be escaped in sed because they are treated as character literals by default**
-  **-r** Removes the problem ( use  extended regular expressions in the script (for portability
              use POSIX -E)
```bash
# REGEX
(Lili|Kamen)
sed 's/\(Lili\|Kamen\)/darko' 
# ^ $ . [ ] { } - ? * + ( ) | \
# Must be escaped with \ 

# Bracket group capture doesn't have to be escaped
sed 's/^[[:digit:]]/darko/' passwd.txt  | egrep "darko" # Works

# Must be escaped
sed 's/\([0-9]\{2\}\)\/\([0-9]\{2\}\)\/\([0-9]\{4\}\)$/\3-\1-\2/' distros.txt 

# Nothing needs to be escaped
cat passwd.txt  | sed -r "s/(Lili|Kamen)/Darko/g" | egrep "Darko"
```
- **p** print current line / lines that match REGEX or specified range
- must add -n so sed doesn't print all the lines by default 
```bash
sed -n '2,6p' text  # Print lines 2-6 from text
sed -n '15!p' text # print every line except the 15 line

sed -n '/dario/p' /etc/passwd # Print lines that match the REGEX  (dario)
sed -n '$p' /etc/passwd # Print the last line of the file /etc/passwd

sed "s///g;s/c/C/g" # Have multiple set pattern changes with one invocation of sed cmd 

sed "/pattern/d" # Delete lines where patern was found                                                         
```
- **i** edit files in place (makes backup if SUFFIX supplied)
```bash
sed -i # Change the original file content based on sed expressions 
```

## Processes ⚙️

The kernel on startup initiates a process called init and it launches shell scripts from /etc (init scripts) which start all the system services that are implement as daemon processes ( which run in the background and don't have an interface to interact with)
The init process isn't created with fork() and is the direct or indirect parent of all the processes ( Like Object class in Java )
- Every process has  :
	- Memory 
		- some segment of memory that it can access and if it tries to access a segment of memory that isn't reserved for it, it is therefore killed 
	- Security Context
		- value that informs the OS what privileges does the process have
	- Scheduling 
		- scheduler is responsible for determining how much time should a process be allowed to run on the system
	- Enviroment 

- Child and Parent process
	- Processes are organized in a hierarchy much like a tree structure
	- Every process except for init is created using the fork() function, which creates a new process by duplicating the calling process
	-  The created process is know as the **child process** and the calling process is called the **parent process**.
	- Process created run in separate memory from the parent 
	- Given the above every process is a direct or indirect descendant of the **init** process.

- The kernel keeps track of PID, memory assigned to each process as well as the process readiness.
- Child processes also have PPID ( parent process id) 

### Ps 
- view all processes running on the system
- Syntax : **ps [option]**
```bash
ps 
ps -u # Shows processes for specific user
ps -e # Display every process on the system 
ps -l # long list for ps 
ps -x # Like ps but with STAT 
# VSZ = virtual memory size
# RSS = resident memory size. Ammount of phyisical memory(RAM) used by the process in KB
# DRS = physical memory 
ps -o user,pid,ppid,ni,tty,stat,cmd,drs=physical memory, vsz= virtual memory,rss = resident size,time=execution time # Print in specific format
# User = process owner(USERID)
# %CPU = cpu usage by process in %
# %MEM = memory usage in % 
# START = date when the process was started
# COMMAND = name of the process 
ps -aux
```
- Meaning of the returned result :
	- PID = process id (unique for every process )
	- PPID = parent id
	- TIME = amount of CPU time consumed by the process
	- TTY (teletype) = controlling terminal of the process, ? = no controlling terminal
	-  NI = nice value [-20 high priority, 19 low priority], 0 by default. This is used to determine the priority of the process and is used by the OS to determine which process will have priority in execution ( similar to a priority queue )
	-  STAT = current state of process
		- R = running process or ready to run
		- T = stopped / instructed to stop 
		- S = sleeping / waiting for event (keystroke or network socket)
		- D = uninterruptable sleep , it is linked to some kind of harware and is waiting for IO operation in order to start executing ( can't be touched during this process )
		- Z = zombie process, meaning the process has finished but wasn't cleaned by the parent process 

### Jobs 
- jobs that the current shell is managing 
- jobs are listed and can be accessed using the number in the list 
```bash 
$ jobs 
# Result 
[1] ls
[2] ps 
[3] xlogo

$ jobs %1 # Access the first job running in the shell (ls in our case)
```
- by default processes that you run on the shell are **foreground** processes and don't return control of the terminal until they have finished or are stopped
- you can switch the process to the **background** using <process_name> &, and it will run without blocking the access to the terminal 
-  *bg* PID puts process in the background
- *fg* PID puts process in the foreground
- when a process is working in the background you can still use your terminal for cmds, the oposite is not true for processes working in the forground.
```bash
xlogo & # Run process in background
jobs  # Print current running processes
fg %1 # Bring xlogo to the foreground 
```
### Kill 
- processes communicate by signaling each other 
- processes are always listening for signals
- Kill is used to send a signal to the process that tells it what to do 
- Syntax : **kill [-SIGNAL] PID**
- **You must be the owner of the process in order to send a kill signal**
- by default the TERM ( terminate signal) is sent which terminates a runnig process 
```bash
# Best practice is to -TERM the process first
# If that doesn't work use -KILL

kill -TERM PID # Process is allowed to cleanup its mess
kill -KILL PID # Process is terminated and isn't allowed to perform cleanup
kill -STOP PID # Process is stopped but not terminated
kill -CONT PID # The process will continue if it was stopped 
kill -INT PID # Send interrupt signal to the process (Most of the time this kills it)

killall -KILL name # Will send signal for kill to all instances of the process with the same name 
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
