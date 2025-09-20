# Test for minishell

# Echo
    - echo
    - echo hola
    - echo ""
    - echo "" hola
    - echo -n hola
    - echo -n -n hola
    - echo -n -nh -n hola
    - echo $?hcudshfuewrf ew  wr 4ew""""
    - echo ""uhjkhnkj"hjbmb"'''' defdjhfkjb "iujiouhj"f'f'f'f'f''f'f'f'f'f'f'
    - echo ""uhjkhnkj"hjbmb"'''' defdjhfkjb "iujiouhj"f'f'a'j'o''i'w'q''q
    - echo ""aaaaaaaa"bbbbb"'''' ccccccccc "dddddddd"e'e'e
    - echo "ho   $USER"  'la   $LESS'   $USER$TERM
    - echo "ho   $USER"'la   $LESS'$USER$TERM
    - echo"ho   $USER"
    - echo"ho   $USE$LESS"
    - "echo ho   $USER"
    - "echo" "ho   $USER"
    - e"cho" "ho   $USER"
    -        echo "ho   $USER"
    - echo "$HOME '$LESS' $USER"
    - echo '$HOME "$LESS" $USER'
    - echo "$HOME '$LESS "pa $TERM" na' $USER"
    - echo '$HOME "$LESS 'pa $TERM' na" $USER'
    - echo '$'"HOME"

# Export
    - export a=b
    - export b=wawa
    - export b=lala
    - export c=lala=kaka
    - export a
    - export a=
    - export a= b=o
    - export a===
    - export a3=l
    - export 2a=lala
    - export !a=ma
    - export $USER=la
    - export $USER=$TERM
    - export $USER=$TERM$HOME
    - export $USER=$TERM$HOM
    - export $HOME=$USER
    - export $USER$SHLVL
    - export
    -            export
    - export ""
    - export a b=$LESS $USER $HOME=la $COLORTERM=pa c=d

# cd
    - directorio existe
    - directorio no existe
    - file existe
    - cd
    -            cd
    - cd - = $OLDPWD
    - cd ~ = $HOME
    - cd $HOME si $HOME no existe
    - cd directorio con distintos permisos

# Env
    - env
    - env lalal
    - env directorio

# pwd
    - con y sin argumentos

# unset
    - con y sin argumentos
    - varios argumentos

# exit 
    - exit
    - exit 0
    - exit 1
    - exit 42
    - exit lalal

# pipe
    - ls | wc
    - ls|wc
    - sort colors.txt | uniq | sort -r | wc
    - ls || wc
    - ls |   | wc
    - ls |   >/>>/</<< wc *REVISAR
    - ls | wc |
    - |
    - | ls | wc

# redirecciones
    - </<</>/>>
    - echo hola >>>>>>> file
    - echo hola <<<<<<< file
    - echo hola>file
    - echo hola </<</>/>>   </<</>/>> file
    - echo hola </<</>/>>   | file
    - echo hola > file </<</>/>>
    - echo hola > file
    - echo hola > file > file2 > file3
    - echo hola > file > file2 > file3 | ls
    - wc < colors.txt
    - wc < colors.txt > file
    - cat colors.txt | wc
    - echo hola > file << EOF
    - cat << EOF > file
    - << EOF
    - cat << hola << que << tal
    - cat << hola << que << tal -> aplicarle señales a heredoc
    - cat << EOF | ls
    - echo hola | cat | cat | cat | cat | cat | cat | cat

# general
    - enter en input -> vacio
    - solo espaciostoken->value = result;
    - comillas sin cerrar
    - echo $?
    - unset $PATH -> ls -> /bin/ls
    - unset $HOME -> cd