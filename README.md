# 0x16. C - Simple Shell

```

                       _____ _   _ _____    ____    _  _____ _____ ____     ___  _____ 
                      |_   _| | | | ____|  / ___|  / \|_   _| ____/ ___|   / _ \|  ___|
                        | | | |_| |  _|   | |  _  / _ \ | | |  _| \___ \  | | | | |_   
                        | | |  _  | |___  | |_| |/ ___ \| | | |___ ___) | | |_| |  _|  
                        |_| |_| |_|_____|  \____/_/   \_\_| |_____|____/   \___/|_|    

                                       ____  _   _ _____ _     _     
                                      / ___|| | | | ____| |   | |    
                                      \___ \| |_| |  _| | |   | |    
                                       ___) |  _  | |___| |___| |___ 
                                      |____/|_| |_|_____|_____|_____|
                                                                      
```

####  a simple REPL model of the unix shell
<hr>

## Contributor

|Name|Email|
| --- | --- |
| me | olaleyedaniel2000@gmail.com |

<hr>

## Output

* The shell have exact same output as the `sh` (`/bin/sh`)
* The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)

###### Example of an error in `sh`

```shell
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```

###### Example of an error on the program `hsh`

```shell
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

<hr>

## Compilation

###### The program should be compiled with
>
> gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

<hr>

## Testing

###### Your code should work like this in interactive mode

```shell
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```

###### But also in non-interactive mode

```shell
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
