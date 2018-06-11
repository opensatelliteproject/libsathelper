INTSIZE := $(shell getconf LONG_BIT)

all: libSatHelper

clean:
	@echo -e '\033[0;32mCleaning target Debug\033[0m'
	@echo -e '\033[0;34m'
	$(MAKE) -C build clean
	@echo -e '\033[0m'
	@echo -e '\033[0;32mFinished cleaning Debug\033[0m'

libSatHelper:
	@echo -e '\033[0;32mBuilding target: $@\033[0m'
	@echo -e '\033[0;34m'
	@mkdir build -p
	@cd build && cmake ..
	$(MAKE) -C build
	@echo -e '\033[0;32mFinished building target: $@\033[0m'
	@echo ' '

bootstrapgo:
	@echo -e '\033[0;32mBuilding target: $@\033[0m'
	@echo -e '\033[0;34m'
ifeq ($(INTSIZE), 32)
	@echo -e '\033[0;32mFixing Compiler bug for 32 bit\033[0m'
	@sed -i 's/CXXFLAGS:.*-std=c++11.*/CXXFLAGS: -std=c++11 -O0/g' SatHelper.i
endif
	swig -go -cgo -c++ -intgosize $(INTSIZE) SatHelper.i
	@echo -e '\033[0;32mFinished building target: $@\033[0m'
	@echo ' '

updatego: bootstrapgo

libSatHelperGo: bootstrapgo libSatHelper
	@echo -e '\033[0;32mBuilding target: $@\033[0m'
	@echo -e '\033[0;34m'
	go build
	@echo -e '\033[0;32mFinished building target: $@\033[0m'
	@echo ' '

test: libSatHelper
	@echo -e '\033[0;32mBuilding target: $@\033[0m'
	@echo -e '\033[0;34m'
	$(MAKE) -C build test
	@echo -e '\033[0m'
	@echo -e '\033[0;32mFinished building target: $@\033[0m'
	@echo ' '

testGo: libSatHelperGo
	@echo -e '\033[0;32mBuilding target: $@\033[0m'
	@echo -e '\033[0;34m'
	go test ./...
	@echo -e '\033[0m'
	@echo -e '\033[0;32mFinished building target: $@\033[0m'
	@echo ' '

libcorrect: FORCE
	@echo -e '\033[0;32mBuilding target: $@\033[0m'
	@echo -e '\033[0;34m'
	@git clone https://github.com/quiet/libcorrect/
	@mkdir libcorrect/build -p
	@cd libcorrect/build && cmake ..
	$(MAKE) -C libcorrect/build
	@echo -e '\033[0m'
	@echo -e '\033[0;32mFinished building target: $@\033[0m'
	@echo ' '

libcorrect-install: FORCE
	@echo -e '\033[0;32mInstalling target: $@\033[0m'
	@echo -e '\033[0;34m'
	$(MAKE) -C libcorrect/build install
	@ldconfig
	@echo -e '\033[0m'
	@echo -e '\033[0;32mFinished installing target: $@\033[0m'
	@echo ' '

install: libSatHelper
	@echo -e '\033[0;32mInstalling target: $@\033[0m'
	@echo -e '\033[0;34m'
	$(MAKE) -C build install
	@ldconfig
	@echo -e '\033[0m'
	@echo -e '\033[0;32mFinished installing target: $@\033[0m'
	@echo ' '

package: libSatHelper
	@echo -e '\033[0;32mInstalling target: $@\033[0m'
	@echo -e '\033[0;34m'
	$(MAKE) -C build package
	@echo -e '\033[0m'
	@echo -e '\033[0;32mFinished installing target: $@\033[0m'
	@echo ' '

FORCE:
