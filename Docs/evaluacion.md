--
echo $?hcudshfuewrf ew  wr 4ew""""
nosotros salimos con error 2
2hcudshfuewrf ew wr 4ew
0hcudshfuewrf ew wr 4ew

--
minishell$ e 'la   $LESS'   $USER$cho "ho   $USER" TERM
ho   dponce-g la    dponce-gxterm-256color

dponce-g@c3r8s1:~$ echo "ho   $USER"  'la   $LESS'   $USER$TERM
ho   dponce-g la   $LESS dponce-gxterm-256color

--
minishell$ echo "ho   $USER"'la   $LESS'$USER$TERM
ho      dponce-gxterm-256color

dponce-g@c3r8s1:~$ echo "ho   $USER"'la   $LESS'$USER$TERM
ho   dponce-gla   $LESSdponce-gxterm-256color

--
minishell$ echo '$HOME "$LESS" $USER'
/home/dponce-g "" dponce-g

dponce-g@c3r8s1:~$ echo '$HOME "$LESS" $USER'
$HOME "$LESS" $USER

--
minishell$ echo '$HOME "$LESS 'pa $TERM' na" $USER'
/home/dponce-g " pa xterm-256color na" dponce-g

dponce-g@c3r8s1:~$ echo '$HOME "$LESS 'pa $TERM' na" $USER'
$HOME "$LESS pa xterm-256color na" $USER

--
minishell$ $LESS
execve: Permission denied

-- **Solcuionado**
export a
sustitye la existente por una vacía cuando en bash no hace nada

minishell.
declare -x a="b"
declare -x a=""

bash:
declare -x a="b"
declare -x a="b"

-- **Es ok**
minishell$ export !a=ma
minishell: !a=ma: not a valid identifier

dponce-g@c3r8s1:~$ export !a=ma
bash: !a=ma: event not found

-- **Solcuionado**
minishell$ cd - = $OLDPWD
/home/dponce-g

dponce-g@c3r8s1:~$ cd - = $OLDPWD
bash: cd: too many arguments

-- **Solcuionado**
minishell$ cd ~ = $HOME
minishell$ 

dponce-g@c3r8s1:~$ cd ~ = $HOME
bash: cd: too many arguments

-- **Es ok**
minishell$ cd prueba/
minishell: cd: : Permission denied

dponce-g@c3r8s1:~/sgoinfre$ cd prueba/
bash: cd: prueba/: Permission denied

-- ***Depende del cd***
minishell$ pwd
/sgoinfre/students/dponce-g
minishell$ ls
downloads  minishell_gitHub  prueba  subjects
minishell$ 

dponce-g@c3r8s1:~/sgoinfre$ pwd
/home/dponce-g/sgoinfre
dponce-g@c3r8s1:~/sgoinfre$ ls
downloads  minishell_gitHub  prueba  subjects

-- **Solcuionado**
minishell$ exit 42
exit
zsh: segmentation fault (core dumped)  ./minishell

dponce-g@c3r8s1:~/sgoinfre$ exit 42
exit
~% echo $?
42

-- **Solcuionado**
minishell$ ls || wc
minishell: syntax error near unexpected token `|'

dponce-g@c3r8s1:~/sgoinfre/minishell_gitHub$ ls || wc
Docs	  libft     minishell	   README.md
includes  Makefile  readline.supp  srcs

-- **Solcuionado**
minishell$ ls | wc |
zsh: segmentation fault (core dumped)  ./minishell

dponce-g@c3r8s1:~/sgoinfre/minishell_gitHub$ ls | wc |
> 

--
