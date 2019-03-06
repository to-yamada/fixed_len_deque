PCUNITDIR = PCUnit

CC = gcc
CFLAGS = -Wall -g
CFLAGS += -I$(PCUNITDIR)/..
LFLAGS = -L$(PCUNITDIR) -lpcunit
LIBPCUNIT = $(PCUNITDIR)/libpcunit.a

VPATH = 

TARGET = alltests
OBJS = main.o
OBJS += queue.o
OBJS += test_queue.o


.PHONY: all clean pcunit_register test xml

all: pcunit_register $(TARGET)

pcunit_register:
	-ruby $(PCUNITDIR)/pcunit_register.rb

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $<

queue.o: ../queue.c
	$(CC) $(CFLAGS) -c $<

$(LIBPCUNIT):
	cd $(PCUNITDIR) && $(MAKE)

$(TARGET): $(LIBPCUNIT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LFLAGS)

test: all
	./$(TARGET)

xml: all
	./$(TARGET) -v | ruby $(PCUNITDIR)/pcunit_xml_output.rb $(OUTPUT)

clean:
	cd $(PCUNITDIR) && $(MAKE) clean
	rm -f *.o $(TARGET)

