TARGET = bin/sanic
SRC = $(wildcard src/*.c)

default: $(TARGET)

clean:
	rm -f bin/*

$(TARGET): $(SRC)
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -Llib -Iinclude -lraylib $? -o $@ 

