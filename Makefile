single:
	g++ md5_single.cpp -o md5_single
	./md5_single > message1.txt
	g++ check.cpp -o check
	./check < message1.txt

multi:
	g++ md5_multi.cpp -o md5_multi
	./md5_multi > message2.txt
	g++ check.cpp -o check
	./check < message2.txt

klima:
	g++ md5_klima.cpp -o md5_klima
	./md5_klima > message3.txt
	g++ check.cpp -o check
	./check < message3.txt