target_name=comparator

CPP_FLAGS ?= -O2

ifeq ($(VERBOSE),y)
CPP_FLAGS +=  -DVERBOSE
endif

ifeq ($(CHECK_SPACE),y)
CPP_FLAGS += -DCHECK_SPACE
endif

all:
	$(CXX) comparator.cpp $(CPP_FLAGS) -o $(target_name)
	@echo -e "\e[32mBuild Successful\e[0m"

clean:
	rm -rf *.o $(target_name)
