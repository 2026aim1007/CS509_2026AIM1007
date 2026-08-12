.PHONY: all clean assignment_01 assignment_02 wrapper

all: assignment_01 assignment_02 wrapper

assignment_01:
	@echo "======================================="
	@echo " Building Assignment 01..."
	@echo "======================================="
	$(MAKE) -C assignment_01

assignment_02:
	@echo "======================================="
	@echo " Building Assignment 02..."
	@echo "======================================="
	$(MAKE) -C assignment_02

wrapper:
	@echo "======================================="
	@echo " Building Common Wrapper..."
	@echo "======================================="
	g++ common_wrapper/wrapper.cpp -o common_wrapper/wrapper.exe -std=c++11 -O3

clean:
	@echo "Cleaning Assignment 01..."
	$(MAKE) -C assignment_01 clean
	@echo "Cleaning Assignment 02..."
	$(MAKE) -C assignment_02 clean
	@echo "Cleaning Common Wrapper..."
	rm -f common_wrapper/wrapper.exe
	@echo "All clean!"