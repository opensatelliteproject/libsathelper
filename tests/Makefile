
INCLUDES := -I../includes -I../includes/exceptions
CFLAGS := -std=c++11 $(INCLUDES) -O0 -g3 -Wall -c -fmessage-length=0 -fPIC -MMD -MP

CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := -L../Release\ \(Static\) -lSatHelper

all: tester

tester: $(OBJ_FILES)
	@echo "Building Test Program"
	g++ $^ $(LD_FLAGS) -o $@

clean:
	@echo "Cleaning build"
	@rm -f *.o *.d tester
	@echo "Cleaning done"

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ $(CFLAGS) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

test: tester
	@echo 'Running Tester Program'
	./tester
	@echo 'Done running Tester Program'