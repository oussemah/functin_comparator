
target_name=comparator

all:
	$(CXX) comparator.cpp -o $(target_name)
	@echo -e "\e[32mBuild Successful\e[0m"

clean:
	rm -rf *.o $(target_name)
