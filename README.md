find dest -ctime -60 # change time 60min
  	   -atime # access time
	   -mtime # modified time
ln src dest # src file you want to link to dest = destination of shortcut

touch - creates regular file
find ./ -type f  # show only regular files in specified directory


**Inode** is a special key that has in itself GID,SID,time of change,size of file and other metadata
it is useful for identifying a file 
Files have to identificatiors the Inode and the Name of the file 

**Hard Link** is a pointer to a directory with the same Inode as the directory it is pointing to
In order to totally remove the file every hard link must be deleted. ( Basically every hard link acts like a original of the file it is linked to )

To see more detail about file ( example . Inode , size , atime ,ctime mtime )
	stat <file_name>

The mtime in the file is changed when me save file, add new stuff in it.
When mtime is changed the ctime is changed too.

If we only change the Inode or the metadata in the Inode then we only change the ctime and not the mtime .
Example. chmod changes only the ctime of the file 

ls -i  shows the inode numbers
df -h shows the size of files

Acces time is when you open the file

**Soft links** work as shortcuts. They have different Inodes than the file they redirect to. 
If you delete the original file the soft link won't be deleted.

Sticky bit = t in the end of the permission means that the file has root access

To be root :
```shell
 sudo su root
```

find ./ -group group_name -perm 002 // only write permission

find ./ -perm -g=w  # will take all the fiels that have write perm on group
find ./ -perm g=w # will only look for files that will have only group write perm

find -anewer file # find files that are newer then give file 
find -anewer file -exec rm {} \; # remove files that are newer than given file
tar -czvf arhiva.tr b* # add all files that start with the letter b to the arhiva.tr 

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
   -  HINT: Handy when used for squeezing spaces and tabs in a text
   - 
   ```
**Sort**
   - 
   - can use file as input
   - sorts output lexicographically be default
   - -k 2 # will sort by 2 column the standard delimetar is space
   - -r # reverse sort
   - -n # numberical sort
   - -t # field separator ( change it if you want for it to be different from psace )
   ```shell
         sort -t ':' -nk 3 # sort by USERID numerically 
   ```  

 **Cut**
   - 



 **Tricky Exercises**
  - Отпечатайте 2 реда над вашия ред в /etc/passwd и 3 реда под него // може да стане и без пайпове

  ```shell
     awk 'BEGIN {printf "\n\n"} {printf$0;printf"\n"} END{printf "\n\n\n" }' passwd.txt
  ```

  - Колко хора не се казват Ivan според /etc/passwd
  ```shell
     grep -Piwvc "Ivan" passwd.txt # w= only word , v = reversed ,c = match count 
  ```
  - Изведете имената на хората с второ име по-дълго от 7 (>7) символа според /etc/passwd
  ```shell
     cut -d ":" -f 5 passwd.txt | grep -P " \w{7}" | cut -d " " -f 1 > usernamesGreaterThenSeven.txt
  ```
