OBJECTS = $(patsubst %.cpp,%.o, $(shell find lib/libtcpserver/ -name *.cpp))
CC = g++
CFLAGS = -I./lib/ -fPIC -c
LDFLAGS =
OUT_FILE = libtcpserver.so

.PHONY: install
install: build
	cp $(OUT_FILE) /usr/local/lib/

	rsync -arvz --progress --include='*.h' --include="*/" --exclude="*" ./lib/libtcpserver/ headers/
	cd /usr/local/include && mkdir libtcpserver

	cp -r headers/* /usr/local/include/libtcpserver/
	rm -r headers/

.PHONY: uninstall
uninstall:
	rm /usr/local/lib/libtcpserver.so
	rm -r /usr/local/include/libtcpserver/

.PHONY: build
build: $(OBJECTS)
	$(CC) -shared -o $(OUT_FILE) $(OBJECTS)

.PHONY: all
all: $(OBJECTS)
	echo "$(OBJECTS)"

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

.PHONY: clean
clean:
	rm $(OBJECTS) $(OUT_FILE)