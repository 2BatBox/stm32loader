INCLUDES = src/
SOURCES = src/intel_hex.c src/serial.c src/stm32.c src/stm32loader.c
LIBS =
CFLAFS = -g -DDEBUG -Wimplicit-function-declaration -Wall

hello-gl2: clean
	gcc -o stm32loader $(SOURCES) -I$(INCLUDES) $(LIBS) $(CFLAFS) 
	
clean:
	rm -rf stm32loader
