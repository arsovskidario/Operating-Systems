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
- 
-  make a hexdump or do the reverse.
- example;
```shell
   echo   D > hexCode.txt
   xxd hexCode.txt 
   * Will display : 00000000:2020 44 # 00000000:shows the number of line , 20 is space in hex ascii table , 44 is D in hex ascii table    
```
- **xargs**
- 
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
```shell
   find . -name "*.pdf" | xargs -I pdf rm pdf 
```
- -null  items are terminated by null character instead of whitespace


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
    -%Tk    File's  last modification time in the format specified by
                     k, which is the same as for %A.
    *-%T@  @ = seconds since Jan. 1, 1970, 00:00 GMT, *
    -%s File's size in bytes.
    -%p File's name.
    -%n Number of hard links to file.
    -%t File's last modification time in the format returned by the C `ctime' function.
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
   ```


**Wc(word count)**
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

  - Изведете имената на хората с второ име по-късо от 8 (<=7) символа според /etc/passwd // !(>7) = ?
  ```shell
     cut -d ":" -f 5 passwd.txt | cut -d " " -f 2 | grep -P "\w{1,7"| tr , " " > surnamesLessThanSeven.txt
  ```

  - Изведете целите редове от /etc/passwd за хората от 03-a-5003
  ```shell
    grep -Pi "[a-zA-Z]*\s+[a-zA-Z]{7}[,\s]" passwd.txt > linesWithGreaterUsername
  ```

  - Вижте man 5 services. Напишете команда, която ви дава името на протокол с порт естествено число N. Командата да не отпечатва нищо, ако търсения порт не съществува (например при порт 1337). Примерно, ако номера на порта N е 69, командата трябва да отпечати tftp.
  ```shell
     cat /etc/services | tr -s '\t' | cut -f 2 | grep -P "\d+/(tcp|udp)" | awk -F '[/]' 'if($1 == 69){printf "tftp\n" } if($1 <= 1024){printf $0; printf "\n" } > servicesResult'
  ```

  - Колко файлове в /bin са shell script? (Колко файлове в дадена директория са ASCII text?)
  ```shell
     find /bin -type f -executable | wc -l  # for scripts
     find /bin -type f -name "*.txt" | wc -l #for ascii text 

     find /bin -exec file {} \; | grep -Pc "script" 
     find /bin -exec file {} \; | grep -Pc "ASCII text"
  ```

   - Направете списък с директориите на вашата файлова система, до които нямате достъп. Понеже файловата система може да е много голяма, търсете до 3 нива на дълбочина. А до кои директории имате достъп? Колко на брой са директориите, до които нямате достъп?

   ```shell
      find ~ -maxdepth 3 ! -writable > unavailableDir
      wc -l unavailableDir
      find ~ -maxdepth 3 -writable # have access to 

      # Worst solution ever
      find / -maxdepth 3 -print 2>&1 | grep -P "Permission denied" | cut -d ":" -f 2 | sed 's/ ‘//' | sed 's/’//' > unpermitedFiles.txt 

   ```

   -  Изведете на екрана:
	* статистика за броя редове, думи и символи за всеки един файл
	* статистика за броя редове и символи за всички файлове
	* общия брой редове на трите файла

   ```shell
      * wc -lwc file1 ..... # for every file new cmd 
      * wc -lwc file1 file2 file3 ( wc -lwc *)
      * wc -l file1 file2 file3 | awk '{sum+=$1} END{print sum}'; wc -c file1 file2 file3 | awk '{sum+=$1} END{print sum}' 
   ```
   - Във file2 подменете всички малки букви с главни.
   ```shell
      tr a-z A-Z <file2 > file2.txt; mv file2.txt file2
   ```

   - Във file3 изтрийте всички "1"-ци.
   ``shell
      tr -d 1 < file3 > file3.txt ; mv file3.txt file3
   ```

   - Изведете статистика за най-често срещаните символи в трите файла.?
   ```shell
      insert code here
   ```

   - Изтрийте всички срещания на буквата 'a' (lower case) в /etc/passwd и намерете броят на оставащите символи.
   ```shell
      tr -d 'a' < /etc/passwd | wc -m 
      sed -i 's/a//g' passwd.txt | cat passwd.txt | wc -m # -i means inplace 
   ```
   - Отпечатайте последната цифра на UID на всички редове между 28-ми и 46-ред в /etc/passwd.
   ```shell
       head -n 46 /etc/passwd | tail -n 18 | cut -d ":" -f 3 | grep -Po ".$" 
   ```

   - Didn't make the cut
   - 
      03-b-5400


  
