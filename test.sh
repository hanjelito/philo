filename='a.out'
if [ -f $filename ]; then
   rm a.out
   echo "$filename is removed"
fi
gcc utils/ft_atoi.c \
philosophers/philosophers.c \
philosophers/create.c \
philosophers/threads.c \
time/time.c \
main.c
./a.out 4 310 200 50