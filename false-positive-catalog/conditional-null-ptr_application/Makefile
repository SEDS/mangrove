ClassCondition: ClassCondition.o client.o
	g++ ClassCondition.o client.o -o ClassCondition
	rm *.o

ClassCondition.o: ClassCondition.h
	g++ -c ClassCondition.cpp

client.o: client.cpp ClassCondition.h
	g++ -c client.cpp

clean:
	rm -f *.o ClassCondition