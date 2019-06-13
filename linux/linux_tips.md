### linux tips
* **use ```command < file``` to redirect std input to the file**
* wildcard ```?``` represents one character, ```[...]``` represents the range.
* ```'...'``` cannot include special characters. ```"..."``` can include ```$,\，` ``` etc.
* 1. **```&``` can run command in background, ```jobs -l``` shows all background processes and PID, ```fg``` move background running process to foreground. ```ctrl-z``` suspend a process.**
  2. e.g., ```vim file```, then ```ctrl-z``` to show terminal. Then ```fg``` to resume vim.
* ```ssh-agent, ssh-add``` enter ssh with no password(TODO)
* 1. ```tail -f file``` keeps tracking added contents in file.
  2. ```chown user[:group] file``` changes user and group of file.
  3. ```chmod [ugoa...][[+-=][rwxX]...][,...] file```, where ```u=user, g=group, o=other, a=all, +=add, -=remove, ==set, r=read, w=write, x=execte```, ```,``` can concate many modes.
  4. ```du -h [-a] -d <number> file``` shows occupied disk space of sub-files, where ```-a``` means all, ```-d``` means depth.
  5. ```dig domain name``` shows corresponding ip address of domain name.
  6. **```ctrl-u``` deletes front of cursor, ```ctrl-k``` deletes back of cursor, ```ctrl-l``` clean screen.**
  7. ```set -o vi``` to use vi style command line, ```set -o emacs``` to reset.
  8. **```!!``` execute last command. ```!$``` represents last arg of last command. ```!:n``` represents the nth arg of last command.**
  9. ** ```xargs``` almost equals ```echo```, whose main effect is to transfer multi line output to one line or vise versa and change the output of last command for following commands. **
     1. ```cat file | xargs -dX -nN``` show cotents per N line separated by ```X```.
     2. ```xargs -I {} command {}``` substitute contents
  10. shell command.
     1. ```$*``` is all input params.
     2. ```set -x``` shows commands before running; ```set -u``` returns error if undefined variable is used; ```set -o pipefail``` monitor pipeline failure; ```unset variable``` delete variable; ```set -e``` stop running shell after first error.
     3. ```${#string}``` show length of string; ```echo ${string:Nstart:Nlength}``` get substr from Nstart of length Nlength.
     4. ```array_name=(v0 v1 v2)``` and ```array_name[i]=vi``` initializes an array, ```$array_name[i]``` reads value of the array; ```echo ${array_name[@]}``` reads all values of the array; ```length=${#array_name[@]}``` gets the number of the array; ```${var%suffix}``` cut suffix of var, ```${var#prefix}``` cut prefix of var. ```${i}``` is the ith param variable.
  11. ```echo str1{substr1,substr2,...substrn}str2``` will be unfolded as ```echo str1substr1str2 str1substr2str2 ...```
  12. ```command > file 2>&1``` means write str output and error to file. ```1 == std output, 2 == std error```, redirect std output to file and stderr is same as std output. If ```file == /dev/null ```, all contents are thrown.
  13. ```uniq -[du]```, where ```-u==show uniq lines, -d==show repeated lines```
  14. ```cut, paste, join```
  15. ```awk, sed```
  16. ```rsync``` substitute ```scp```
  17. ```ldconfig, ld.so.conf, ldd, LD_LIBRARY_PATH``` to set searching path of .so files, ```CPLUS_INCLUDE_PATH``` to set include path. ```pkg-config``` to better config include and library path.
  
### useful tools
* ```code-server``` and ```pycharm-professional``` to run ide on server code.
* ```tmux``` for multi screen.
* ```gdb, cgdb``` for debug C++ files.
* 
### other notes
* generate static link library
  1. ```g++ -c src1.cpp src2.cpp ...``` to generate obj files ```src1.o src2.o ...``` which contain definition of functions.
  2. ```ar -cv libname.a src1.o src2.o ...``` to generate static link library.
  3. ```#include <name.h>``` in ```main.cpp``` to include head file where offers declaration of functions in ```libname.a```
  4. ```g++ main.cpp -I${header file environment} -L${static link library environment} -lname``` to generate executable file.
* generate dynamic link library
  1. ```g++ -fPIC -shared -Wl,-soname,libname.so.1 -o libname.so.1.2 hello.cpp``` to generate dynamic link library whose soname is libname.so.1.
  2. add ```path/to/so_file``` in ```/etc/ld.so.cache```, then run ```ldconfig``` or ```export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:path/to/so_file``` to make .so file visible to cpp files.
  3. reset of steps are same as static link library.
  4. ```nm -[DU] libname.so``` where ```-D``` shows initialized data section(including function name), ```-U``` shows undefined symbols.
* error info
  1. undefined symbols : find declaration in header file, but cannot find definition in library file
  2. use of undeclared identifier : cannot find declaration in header file.
