make gen 2> /dev/null
make avr 2> /dev/null

touch total
rm total
for((i=1;i<=10;++i)); do
	echo $i
	./gen $i | ./pro > /dev/null 2>> total &
done
wait
./avr < total
