
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
- **rm  works only on the symlink and not the referenced file**
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

ls -A # Desn't return message "total 0" if directory doesn't have files in it 
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
- **by default find does search for hidden files**
```bash
# Make find skip hidden files
find . -type f -name "[^\.]*"
```
- **by default find prints the result into new line**
- **find frequently stats files during the processing  of  the  command
       line itself, before any searching has begun.**      
- has Tests, Options,  Actions

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
- **xtype l = Find broken links**
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

find / -printf "@T@ %p \n" # Unix time format : 15152525.1231312

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
- -maxdepth 0 means only apply the tests and actions to the starting-points themselves
- mindepth<lvl_number> = kolko minimum pod direktorie da ima toj shto trazimo 
*(prefered to be in front of the options )*
```bash

find / -maxdepth 1 -type f -name "dario"  # Will look only in the curr directory

find / -maxdepth 2 -type f -name "dariO" # Will look in subdirectories too 
```

- mount = not to traverse mounted directories on other systems
- prune = if file is directory don't descend into it 

### Compressing files 
- c = compress, x = extract
```bash
tar -cvf "archivename.tgz" dir
tar -zcvf "filename.gz" filename
tar -xvf "archivename" -C dest_name
```

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
	- -v invert the match (Match not matching lines)
	```bash
	echo "Dario e mnogo jak" | egrep "dario" # Will match the line
	echo "Dario e mnogo jak" | egrep -v "dario" # Will not match the line 
	```
	- -c count matches (Number of lines that match the REGEX)
	```bash
	egrep "dario" /etc/passwd  # Prints only the number of matches
	# Result : 
	1 
	```
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

- Find the,that,those,then insensitive using extended grep
```bash
egrep -iw '(the|that|those|then)'
```

### Date
- prints to STDOUT current date format
```bash
date +"%F-%r"
# %F = full date same as %Y-%m-%d
# %r = locale's 12 hour clock time (eg.. 11:10:04 PM)
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
	- n sort based on numerical values (If n is enabled the numbers will come before the text)
	```bash
	# Example
	ps -o user,pid,rss,cmd
	# Result :
	USER 	PID 	RSS 	CMD
	dario 	23 		23 		442
	dario 	1 		255		bar
	ps -o user,pid,rss cmd | sort -nrk 3
	# Result :
	dario 1 255 bar
	dario 23 23 442
	USER PID RSS CMD
	```
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

### Diff
- **DIFF $FILE1 $FILE2** = if both files have same content no string is returned
- is logically equal to comm -3 $FILE1 $FILE2
```bash
diff task NOTES
# Result :
> ovoj
> ima u task
< razlicno u Notes
```

```bash
# Exercise with diff

if [ -z "$(diff "$file1" "$file2")"]then;
	echo "Files have the same content"
fi
```

### Wc (word count)
- wc - print line, word, and byte counts for each file and **filename next to it**
- **-l**, --lines - print the newline counts
- **-w**, --words - print the word counts
- **-c**, --bytes - print the byte counts
- **-m**, --chars - print the character counts
```bash
wc -l f1
4 f1

# Get number of lines 

COUNT=$(wc -l f1 | cut -d " " -f 1).
```

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
- **$(NF-1)** get next to last word in line ( can be -2, -3 and so on )
- $0 = references whole line, $1 =references first column , $n = get n column
- Default input-field seprator is *SPACE*.
- awk -FS '', to change the field separator
- BEGIN = block executed at start
- END = block executed at the end 
- FILENAME = get current filename
```bash
awk '{print FILENAME}' f1   # f1 has 3 lines in it
# Result
f1 
f1
f1
```

- -v add a variable from bash
```bash
$NUMBER=69
awk -v NUMBER=$NUMBER '{printf NUMBER}'
```
- arithmetics in awk (a+b) where a,b are variabls inside awk
```bash
awk '{ print ($NF+$(NF-1))}'
awk -v a=2 -v b=3 '{print (a+b)}'
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

### Sed
- stream editor
- Performs text editing on a stream of text
- Pattern in sed are **REGEX** patterns \
- **Basic commands**
![commands](https://github.com/arsovskidario/Operating-Systems/blob/master/images/sed_editing_cmds.png?raw=true)
- **s** = search and replace strings
- **used for removing words in a LINE**
```bash
sed "s/str1/str2/" file1 # Will replace only the first instance on every line
sed "s/str1/str2/g" file1 # Will replace every instance of str1 on every line
sed -r "s/^[0-9]*god.\s//" file1 # Will remove year from text

# Remove word from text example
# 1979 g. - ,,Trifun'' (sbornik)
# 1979 g. - ,,Double star'' - Lyub
# 1979 g. - ,,Alibi'' - Dimityr Peev
# 1979 g. - ,,Zavrshvane ot zvezdite'' - Stanislav Lem
# 1979 g. - ,,SReshta s rama'' - Artyr Klark

cat file1 | sed -r "s/^[0-9]*\sg\.\s-\s//"

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
	- exec() is used to swap the current running process with a new process
- The kernel keeps track of PID, memory assigned to each process as well as the process readiness.
- Child processes also have PPID ( parent process id) 

### Ps 
- view all processes running on the system
- Syntax : **ps [option]**
- **--sort=start_time**
- **--sort=vsz** 
- sorts in ascending order
- can have pi,ppid and any column name 

```bash
ps 
ps -u user_name # Shows processes for specific user
-s -g group_name # Show processes for specific group
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

ps -o user=User_name,pid,ppid,stat=Status # used to set custom Column names 
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

# Shell Scripting 🐚

- **The shell expands all qualifying chars(wildcards) on the command line before the command is carried out**

- $((expression)) for math

- Brace expansion = For ranges
```bash
echo Number {1..5}
### Result Number 1 Number 2 Number 3
echo letter{A..Z}
mkdir {2007..2009}-{01..12}
```
## Command Substitution 
- allows you to use output of a command as an expansion

- echo $(ls)

- echo $(sort darko.txt)


- file $(ls -d /usr/bin | grep zip)


- **"$()" # suppresses whitespaces and everything except for $ \ `** 
- **'$()' # supresses everything including $ \ '** 

```bash
foo=
[ $foo = 1 ];
[ =1 ]; # = is a binary operation and it expects input on both sides 
        # If no input on on side = ERROR : unary operator expected

[ "$foo" = 1 ]; # Solves the problem 
# Is : ""=1 
```

### Best practice always  escape variables with " " ex. "$FOO" 
- **" "**  don't permit word splitting and treats everything as as string
 - Doesn't escape $, \ and `
 - **escape special characters in " " with \\**
```bash
echo "I have    $50"
RESULT :
I have    50
Solution : echo "I have \$50"
```
Other implementation:
- if file has multiple spaces in it's name
```bash
ls -l two words.txt # Will treat this input as two files not one
ls -l "two words.txt "  # Will treat the input as one file with the name two words.txt
```
###  Command substitution is allowed inside "" also arithmetic operations
```bash
echo " $(ls) $((2+3))"
```
### '  ' escapes all chars that means $,\  and shell substitution doesn't work
```bash
echo '$(ls)'
# Result : $(ls)
```

## Portion a string
- **${#parameters}** - Expands into the length of the string contained in braces
- ${#@} - get number of positional parameters 
 
- Get portion of string, offset is index where it will start, length the length of the new portioned string
-  If offset is negative the portioning starts from the back of the string 
- **${parameter:offset}**
- **${parameter:offset:length}** 

```bash
foo="Dario e mnogo jak"
${VAR:$i:1} # Substring function (str,start_position,number_of_chars), here it gets all letters from a word 
echo "${foo:5}"  # Result: e mnogo jak
echo "${foo:6:1}" # Result : e 

# Portion from back

echo "${foo:-3:1}" # Result k 
```

## Arithmetic Evaluation 
- **$((expression))**
```bash
echo $(( 5 * 2))
echo $((5**2)) # Result : 25 

#############################
FOO=5
((FOO+=25))
echo $FOO # Result : 30
```

## Enviromental variabels
- variables placed by the shell
- **printenv** = prints enviromental variables
- **set** = prints all enviromental variables + shell variable and functions
- **Non login shells inherit the enviroment variables from their parents ( login shells) **
-   **source <script_name>**  = bring env variables to current shell calling the source cmd

## Permissions 
- scripts need to be readable so they can be executable
700 Only owner can run 
755 everyone can execute

## If statements
```bash
if [ ]; then
elif [ ]; then
else
fi
```
-  If a list of cmds follows if, the last command in the list is evaluated
```bash
if true;false; then echo "Its true"; fi  
# Wont enter the if block because false is executed last
```

## Test
- return 0 exit status when expression is true 
- returns 1 exit status when expression is false
-  exit <status_number> = Used to exit with status number 
Options : 
	-e = Test if file exists
	-d = Test if it is a directory
	-f = Test if it is a regular file
	-L = Test if file is a symbolic link 
	-r = File exists and is readable
	-w = File exists and is writable
	-x = File exists and is executable
	file1 -ef file2 = If file 1 has same inode as file2
	file1 -nt file2 = File1 is newer than file2
	file1 -ot file2 = File1 is older than file2
```bash
if [ -e foo.txt] && [ -e bar.txt]; then
	echo "Both exist" 
	if [ foo.txt -nt bar.txt ]; then
		echo "Foo is newer" 
	else
		echo " Is older"
	fi
	exit 0 # Will terminate program with exit status 0 
fi

if [[ "$INT" -ge "$MIN_VAL" && "$INT" -le "$MAX_VAL" ]]; then
echo "$INT is within $MIN_VAL to $MAX_VAL."

exit 1 
```

```bash
[ -d temp ] || exit 1 # If the temp is a directory it will continue without exiting
# If it is not a directory it will exit immediatly with status 1 
[ -d temp ] || mkdir temp # If the directory temp doesn't exist create it 
```
- **Negate test evaluation using !**
```bash
if [[ ! ("$INT" -ge "$MIN_VAL" && "$INT" -le "$MAX_VAL") ]];
if [[ ! -d $DIRECTORY ]];
```
### Test and Strings
- Options : 
	- string = tests if the string is not null
	- if [ "dario" ]; then echo "Congrats not null" fi 
	- -n string = len of string is greater than zero
	- -z string = len of string is zero
	- if [ -z "dario" ]; then echo "String is zero" fi
	- string1 == string2  - string1 and string2 are equal 
	- string1 = string2 - same as above but for POSIX compliance
	- string1 != string2 - strings are not equal
	- string1 > string2 - must be escaped with " or \ 
	- string2 < string2 
	- [[ string =~ REGEX ]]; # Special case of test used for REGEX matching strings( Must have double brackets)  
	- INTEGER -le integer2 # Less or equal
	- INTEGER -lt INTEGER2 # lesser than integer2
	- INTEGER -eq INTEGER2 # integers are equal
	- INTEGER -ne INTEGER2 # Integer1 is not equal to integer2 
	- INTEGER -ge INTEGER2
	- INTEGER -gt INTEGER2 # greater than integer2
	- (()) # used for arithmetics on integers
	- if(( INT < O )); then echo ..
	- if (( (( INT%2 )) == 0 )); then echo "Even"

```bash
# Test if second arguments is a number
if [[ $2 =~ ^[0-9]*$ ]]; then
                echo "$2 is a number"
        else
                echo "Not a number"
                exit 3
fi

# Find even number
if [ $((INT%2)) -eq 0 ]; then echo "Even number" fi 
# $(()) is the termianl for math operations $(($INT%2)) functions the same   
```
## Reading user input
- **read VAR_NAME**
```bash
read VAR
echo $VAR # WORKS
READ VAR1 VAR2 VAR3 VAR4 # Can intake multiple variables 
# If read receives fewer than expected number of variables it will return empty variables/ strings.
read -p "Enter ur age" AGE
REPLY #  Variable that holds all the values entered with the read command 
read $darko
```

## Positional Parameters


-  Get parametars provided from the shell, variables are named 0 through 9 
- **$0** = Pathname to the file which is being executed 
```bash
#!/bin/bash
echo $0

## Execution in terminal
$ ./posit-param
# Result :
/home/me/bin/posit-param
```


- user parametars start from $1
- **$#** = shows thhe number of parametars 
- **$@** =(all positional parameteres except $0 )  creates array of params and takes all of them with delimiter space  
- **"$@"** =takes all the params that are enclosed by " "
```bash 
# "dario" "najjak chovek univerzum"
# $@ 
# $1 = dario
# $2 = najjak
# $3 = chovek
# $4 = univerzum
# "$@"
# $1=dario
# $2=najjak chovek univerzum
# $3=
# $4=
```
- **((MAX_COUNTER=MAX_COUNTER+1))**
```bash
```read -p "Enter file name : " FILE


MAX_LEVEL=0

if [ -e $FILE ]; then
        RESULT=$(cat $FILE | egrep -o "[\{\}]" | xargs echo  | tr -s " ")

        COUNT=0
        for(( i=0;i<${#RESULT};i++ )); do

             if [ "${RESULT:$i:1}" == "{" ]; then
                     ((COUNT=COUNT+1))
             fi

             if [ "${RESULT:$i:1}" == "}" ]; then
                     ((COUNT=COUNT-1))
             fi

             if [ ${COUNT} -gt ${MAX_LEVEL} ]; then
                     MAX_LEVEL=$COUNT
             fi

        done

        echo "Max level of nesting is : $MAX_LEVEL" 
        exit 0
fi

exit 1
```

## While loop
```bash
While read line; do
...
done < <( echo -e "$Name" )
# echo -e = Acknowledges \n \t \\ as meaningful characters
# echo = Doenst acknowledge chars above as meaningful

# Read words
while read line;
do
	for i in $line
	do
		echo $i
	done
done < <(echo -e "$VAR")
```
 

## C-Notes

### xxd
- make a hex dump 
- by default prints output to STDOUT
- xxd -r  = rтетeverse the dump into binary file 
- xxd -r dump result
```bash
xxd dump
# Result :
00000000: 46be 6444 31c0 290b 64e5 8635 edbf 9c2d  F.dD1.).d..5...-
00000010: d7a6 1fb5 c214 0701 25a5 488c 20d4 a2af  ........%.H. ...
00000020: c43c a8bb 5a83 eb7c 0b51 2045 41a5 4941  .<..Z..|.Q EA.IA

# Every row can have up to 16bytes 
0000020 = Will start after character at position 0x20 of file ( after the 32 character)
46be 
46 = 1 byte = hex representation of F
be = 1 byte = hex representation of .
```

####  Little endian
- Ox1234
- 34 12
```c
u_int16_t foo= 0x1234;
u_int8_t bar=foo; ( ke ga zeme 34) 

u_int16_t = 2^16 = 65355
u_int32_t = 2^32 = 4bil
printf("%d %d",foo,bar); 
# Result is :
1234 12 = Big Endian 
```


### getuid() = get user id 

uid_t me = getuid();

### malloc()
- **return void ptr by default**
- has to be casted so it can be used

```c
# Syntax:
 ptr = (cast-type*) malloc(byte-size)  # cast-type is so it can be casted to the type you want to use instead of void
int* ptr = (int*) malloc(100*sizeof(int)) # int(4bytes) size of array = 4*100 = 400
free(ptr) # Free the memory block
```
- **Returns null if the allocation was *unsuccesful***
- **Always test if pointers is different then NULL before using array**


## exit(int status)
- terminates calling process immediately and closes any open file descriptors belonging to the process
- children of the terminated process immediately inherit PPID 1 (init)
- exit(0) on success
- exit(1) on failure

## open
- return the lowest file descriptor available  int >=0
- if return == -1, open has failed
- **By default the file is opened with the cursor positioned at the start. Writing overwrites the bytes at the beginning of the file.**

```c
int open(const char* pathname, int flag)
```
- Flags :
	- must include one of the following access mode flags
	- O_RDONLY read only
	- O_WRONLY write only
	- O_RDWR read write
	- Optional :
	- O_CREAT if file does not exist, it will be created  by open() owner is the user id of the process, perm are default by the processes umask
	- O_APPEND when this option is selected lseek() is placed at the end of the file before using write() on the file 
	- O_TRUNC if the file can be read and is a regular file it will be deleted and used with nothing in it (length=0)

- Options (after using O_CREAT):
	- S_IRWXU, 0700, rwx permission
	- S_IRUSR, 0400 read permissino
	- S_IWUSR, 0200 write permission
```c
fd3=open(argv[1], O_CREAT | O_RDWR, SIRUSR | S_IWUSR);
```

## close
- closes a file descriptor, and that fd can be reused again.
- return 0 on success
- return -1 on failure and errno is set appropriately
```bash
int close(int fd);
```

## read

```c
ssize_t read(int fd, void* buf, size_t count)
```
- read starts from the **lseek() offset**
- reads up to **count** bytes from file descriptor **fd** into the buffer **buff**
- *return value can be =0 count if there are no more bytes to be read from the file*
- returns the number of bytes read, if return is 0 means EOF
- **after successful read the lseek() offset is appropriately to count ammount**
- returns -1 on failure and **errno** is set appropriately

## write
```c
size_t write(int fd, const void* buf,size_t count);
```
- write starts where the last lseek() was placed, if O_APPEND flag is set that it always will be EOF
- writes up to **count** bytes from the **buffer** into the file specified by the **fd**
- lseek() offset is incremented by **count**
- returns number of bytes writen to file, if it is less than count means there is no more space to be writen into ( partial writes)
- **returns -1 if the operation has failed and is applied to errno**


## lseek 
```c
off_t lseek(int fd, off_t offset, int whence);
```
- **offset** how many blocks should it be move
- whence can be :
	- SEEK_SET = set to exactly **offset** position
	- SEEK_CUR = current position + **offset** count
	- SEEK_END = EOF + **offset** count
```c
	lseek(fd,0,SEEK_SET) // Beginning of file 
	lseek(fd,100,SEEK_SET) // Start from 100 
	lseek(fd,0,SEEK_END) // Start from EOF (after last byte in file)
	lseek(fd,-10,SEEK_CUR) // Seek 10 positions back from your current position
```
- **returns **offset** count on successs**
- **return -1 if the operation has failed**

## errno
- variable that stores the last error return status of a function  that has failed

## err 
- terminates the program with custom error code and message 
- display message on STDERR 
- err verr warn - exit with the value of the arg eval
- **errx,warnx** dont affect the errno vaiable

- **err = the string associated with the current value of errno**
- **errx = doesn't care about the errno**

```c
// Err and errx exit with status  eval
void err(int eval, const char *fmt, ...);
err(1, "%s", file_name);
// Err when some functions didn't work / System not user fault
void errx(int eval, const char *fmt, ...);
// Errx when user broke the program


// Used for warning user with messages
void warn(const char *fmt, ...);
void warnx(const char *fmt, ...);
```

- errx used when user has failed in some logic 
```c
  if ( name != "root") {
	close(fd);
	errx(-1,"You didn't enter the correct name");
 }
```

- err is used when the system failed on some operation
```c
if ( open(fd,O_RDONLY) == -1 )
{
	err(-1,"Failed to open file %s!",fd);
	# char* ERROR_MESSAGE="Failed to open file!"
	# err(-1,"%s\",ERROR_MESSAGE);
}
```


```c
// Test this to see difference

// f3 doesn't exist on the system
int fd1 = open("f3",O_APPEND | O_RDWR);

        if ( fd1 == -1 )
        {
                //char c;
                //read(fd1,&c,1);
                err(-2,"Failed to open file ");
		//errx(-2,"Failed to open file ");
        }

// Result : 
// Faiiled to oepn file : No such file or directory
// the part after : is promped thanks to the errno

// the errx part won't =print the No such file string..

```


## printf 
- %d = decimal
- %x = hex value

## stat
- successs =0
- fail =-1
- st_size;  

```c
struct stat st;
// fstat(fd,&st);

int fd1 = open(argv[1], O_RDONLY);

fstat(fd1,&st);
```
```c

#include<stdlib.h>
#include<stdio.h>
#include<err.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>


// File check for size
        struct stat st;

        if(fstat(fd,&st) == -1)
        {
                close(fd);
                err(-4,"FAILED TO STAT");
        }

        if( st.st_size == 0 )
        {
                close(fd);
                errx(-7,"File is empty");
        }

        if( (st.st_size % sizeof(u_int16_t) ) !=0 )
        {
                close(fd);
                errx(-6,"Does not contain only u_int16_t numbers");
        }
```

## Parametar logic in C
```c
int main(int argc, char* argv[])`
argc by default is 1 because of file name ./main.c
argv[0] = ./main.c  // File name 
argv[1] = param  // Parametar next to ./main 


// Example

./main 
argc=1
argv[0] = ./main

./main darko magarko 

argc=3
argv[0] =./main
argv[1] = darko
argv[2] = magarko


\n = newline
after newline count word
\t = tab
' ' = space
```

## strcmp
```c
int strcmp(const char* s1, const char *s2);
```
if return value = 0, s1 and s2 full match
if return vaue  > 0, s1 longer than s2
if return value < 0, s2 longer than s2

#qsort function

```c
// Ascending
int cmp(const void* a, const void* b)
{
	return ( *(uint32_t)*a) - *(uint32_t*)b ); // cast to appropriate type and dereference value
}

// Descending

int cmp (const void* a, const void* b )
{
        uint8_t x = *((uint8_t*)a);
        uint8_t y = *((uint8_t*)b);
        if ( x  > y) {
                return -1;
        }
        else if ( x <y )
        {
                return 1;
        }

        return 0;
}
```


## Processes

### Execl
- replaces the current process with a new process 
- **returs -1 if error occured**
```c
// Executes the command that is given by the full path
int execl(const char *pathname, const char* arg, ..., (char  *) NULL */);
execl("/bin/ls","ls","-la",(char*)NULL);

// Doesn't take in full path, only the command name
// Searches through PATH variable for the command matching the name
// The first command that will be found will be used 
int execlp(const char *file, const char* arg, ..., (char  *) NULL */);
execlp("ls","ls","-la",(char*)NULL);
```
- **pathname** is the full path to the command you're trying to use
- **arg** is the options that the command will intake. ( the first arg can be used to name the process)
- **(char*) NULL** tells the command that we have stopped with the options
-  **on failure returns -1 exit code**

```c
// Takes the process image and executes it to the full degree
// This means everything else in the current program will be ignored

execlp("ls","ListingContents","la",".",(char*)NULL);

printf("If the execlp is successfull you wont see this message");

// Test
if ( excelp("ls","ls","-l") == -1) {
            err(1,"Couldn't execute cmd !");
}

printf("Print me"); // won't be printed
```
-   
- Always check WIFEXITED () in parent and WEXITSTATUS()
- WIFEXITED() - nqma znachenie dali e terminiral s greshka ili bez

- **For the above mention to work always use execlvp() exclusivley in fork() childs, so you can be able to check the exit status of the execution of execlvp() in the parent process.**

```c
int fd =open("f1",O_RDWR);

pid_t fid = fork();

if ( fid == 0) {
    // Child 
    execvp("ls","ls",(char*)NULL);
}

// Parent

int status;
wait(&status);

if(WIFEXITED(status) && WEXITSTATUS(status) == 0){
    printf("Command has executed successfully")
}
```


### fork()
```c
pid_t fork(void); // doesn't intake parametars
```
- creates a new process by duplicating the calling process
- calling process = parent, new process = child
- pid,ppid
- parent and child run in separate memory spaces.
- parent and child work **concurently** starting from the line after the fork()
- parent and child have the same priority in execution
- child inherits copies of the parent's set of open file descriptors.
- **lseek() pointer of file descriptors are inherited by the child and can be moved by the child affecting the lseek() in the parent**

### канала е отворен докато не се затвори навсякъде ( all fd must be closed )

### when a child is forked it inherits a *copy* of the file descriptors. So closing the descriptor in the child will close it for the child, but not the parent,and vice versa
### The channel tho stays the same even in the child
```c
#include<err.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( )
{

        int fd = open("f1",O_RDWR);

        int pid=fork();

        if ( pid == -1 )
        {
                err(1,"error");
        }

        if( pid == 0 ) {
                //Child
                write(fd,"dariosrce",9);
                close(fd);
                exit(0);
        }

        wait(NULL);

        lseek(fd,0,SEEK_SET); // Reset lseek() that was changed in the child
        char c;
        while( read(fd,&c,sizeof(c)) >0 )
        {
                write(1,&c,sizeof(c));
        }
        close(fd); // Channel is closed because all instances of the fd are gone
        exit(0);
}

```

- **Return value for child is 0, value >0 is for parent, and -1 is failure and is reported in parent because child process wasn't created.**

- basically the parent receives PID of child in the return
- when the parent process finishes before the child process, the prompt is returned for use but the child process keeps on runnig until it finishes.
- when the parent process finishes before the child process, the child process PPID is set to 1 (init PID) because the parent has finished and its PID no longer exists.

### wait()
- **check task 13 in processes**
- will wait for the first child process that terminates
- parent process waits for child process to change state ( to terminate, to be stopped by a signal or resumed by a signal)
- wait() only waits for the child process to **terminate**
- wait(NULL) if you are not interested in the status and you just want to wait for the child to be terminated
```c
pid_t wait(int* wstatus);
pid_t waitpid(pid_t pid, int* wstatus,int options);
```
- **returns pid of child if on successful termination and -1 on error**

- make thread wait for atleast one child process to finish execution
- -1     meaning wait for any child process
- **waitpid(-1, &wstatus, 0);**

- status information :
	- WIFEXITED(status) : child exited normally
	- WEXITSTATUS(status): return code when child exits
	- WIFSIGNALED(status) : child exited because of a signal
	- WTERMSIG(status) : gives the number of the terminating signal
	- WIFSTOPPED(status) : child is stopped
	- WSTOPSIG(status): gives the number of the stop signal
```c
int status;

if (fork() == 0){
	execlp("sleep","sleep","60",(char*)NULL);
}
else{
	wait(&status);

	if( WIFEXITED(status)) {
		prnitf("exit status of child %d\n",WEXITSTATUS(status));
	}
}

```

### getpid()
- return the PID of the calling process
```c
pid_t gepid(void); // doesn't intake any parametars
```

### getppid()
- returns the PPID of the calling process 
- either returns the PID of the parent that has created the current process via fork() or if the parent has terminated it will return 1 ( PID of init)
```c
pid_t getppid(void); // doesn't intake any parametars
```

- getpid() and getppid() are always successful


## Pipes
- create communication channels between processes, that transfer data without writing/using the disk.
```c
int pipe(int pipefd[2]);
```
- pipefd[0] = read end, pipefd[1] = write end
- If a process attempts to read from an empty  pipe,  then  read(2) will block until data is available. If a process attempts to write to a full pipe (see below), then write(2) blocks until sufficient data has been read from the pipe to allow the write to complete. 
- ako se zatvori close(fd[1]) ; tg i fd[0] ke prestane da chita i da ochekue input
- ako ne se zatvori STIDN(fd[1]) na pipe tg tj shto chita ot fd[0] nema da prestane da chita i ke mozhe da se sluchi deadlock

- If all file descriptors referring to the write end of a pipe have been  closed,  then  an attempt to read(2) from the pipe will see end-of-file (read(2) will return 0). ( Example: close(fd[1]) )

- **returns -1 on error**
```c
int fd[2];

pipe(fd);
if (fork () == 0 ) {
	close(fd[1]);
	char c;
   	while(read(fd[0],&c,sizeof(c)) > 0 ){
	  	write(1,&c,sizeof(c)); // write to STDOUT 
	}
	close(fd[0]);
	exit(0);
}

// Parent

close(fd[0]);
write(fd[1],"dario",5);

// Reader will see EOF with close(fd[1]) and stop reading from pipe
close(fd[1]); // will tell the child than there is nothing more to be read from the pipe 

wait(NULL); // will wait for child process to finish reading and then exit with prompt returned
```

### DUP

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

## FIFO
- opening an end of a FIFO for r/w is blocked until another the other end is opened by another process
```c
int mkfifo(const char* pathname, mode_t mode);
```
- **returns -1 on failure**

## Compress
tar cJf <archive>

## Extract

tar xf <archive>

## strchr(set,char)

### p - pos = index of array element

```c
uint32_t size= (st.st_size /sizeof(uint32_t))/2;
uint32_t* fhalf=(uint32_t*) malloc(half);

if( read(fd,fhalf,half) != half)
```
  

**EXERCISES**
- 

-  **[3.Обработка на текст](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/3.%D0%9E%D0%B1%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%BA%D0%B0%20%D0%BD%D0%B0%20%D1%82%D0%B5%D0%BA%D1%81%D1%82.md)**

-  **[4.Процеси](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/problems-04-solutions.md)**

-  **[5.Shell Scripts](https://github.com/arsovskidario/Operating-Systems/blob/master/Exercises/problems-05-solutions.md)**

-  **[6.C Kernel Functions](https://github.com/arsovskidario/Operating-Systems/tree/master/Week-7/ExamPrep_C)**
