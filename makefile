.PHONY: cp_test
cp_test: cp_test.cpp
	g++ -o $@ $^ -std=c++11 -lpthread -lrt

.PHONY: rw
rw: rw.cpp
	g++ -o $@ $^ -std=c++11 -lpthread -lrt

.PHONY: phil
phil: phil.cpp
	g++ -o $@ $^ -std=c++11 -lpthread -lrt

.PHONY: timeSliceScheduling
timeSliceScheduling: timeSliceScheduling.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY: bank
bank: bank.cpp
	g++ -o $@ $^ -std=c++11 -lpthread

.PHONY: clean
clean:
	rm -f cp_test timeSliceScheduling phil rw bank
