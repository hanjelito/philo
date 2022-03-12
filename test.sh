filename='a.out'
if [ -f $filename ]; then
   rm a.out
   echo "$filename is removed"
fi
gcc utils/ft_atoi.c \
philosophers/philosophers.c \
philosophers/create_philos.c \
philosophers/threads.c \
philosophers/create_threads.c \
time/time.c \
main.c
./a.out 1 310 200 100