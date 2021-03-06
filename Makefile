TARGET :=arm-none-eabi
PREFIX ?= $(shell pwd)/../prefix/$(TARGET)
NAME=linkit

all:install

install:
	mkdir -p $(PREFIX)/lib
	mkdir -p $(PREFIX)/include
	install -Dp lib/*.a  $(PREFIX)/lib/
	rm -rf $(PREFIX)/include/$(NAME)
	mkdir -p $(PREFIX)/include/$(NAME)
	install -Dp include/*.h  $(PREFIX)/include/$(NAME)/
	cp -r include/lwip  $(PREFIX)/include/
	cp -r include/posix  $(PREFIX)/include/$(NAME)/

