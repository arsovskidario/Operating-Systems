**Solutions**
- 

1. ```shell
	ps -e -o cmd --sort=start_time | head -n 10
   ```

2. ```shell
        ps -e -o vsz,pid,cmd | sort -nrk1 | head -n1 | cut -d " " -f 2-
   ``` 

3. ```shell
        ps -e -o group,drs | awk 'BEGIN{count=0} {if($1=="dario") count+=$2} END{print count}'
   ```

4. ```shell
     ps -e -o -user,cmd  | sort -k 1 | awk '{ if($2=="vim) print$0}' | uniq -c | tr -s ' ' |awk '{ if($1>='vim') print $2}'
   ```

5. ```shell
     users | awk '{for(i=1;i<NF;i++) print $i}' | grep "$(ps -e -o user |sort | uniq)"
   ```

6. ```shell
     print -e -o drs,group | sort -k 2 | awk 'BEGIN{count=0} {if($2 == "student") count+=$1} END{print count} '
   ```

7. ```shell
        ps -e -o tty,pid,cmd |  tail -n +2 | awk '{if($1 != "?") print $2,$3}' | sort -u -k 2
   ```

8. ```shell
   ```
