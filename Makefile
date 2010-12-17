TARGET = rev

all:$(TARGET)

rev:rev.c
	gcc -o rev rev.c -lm -lcv -lhighgui -I/usr/include/opencv

clean:
	rm -rf $(TARGET)

