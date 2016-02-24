TARGET :=arm-none-eabi
PREFIX ?= $(shell pwd)/../prefix/$(TARGET)
NAME=linkit

install:
	install -Dp lib/*.a  $(PREFIX)/lib/
	mkdir -p $(PREFIX)/include/$(NAME)
	install -Dp include/*.h  $(PREFIX)/include/$(NAME)/;echo -n ""
	
