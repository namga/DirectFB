####  Init #########
# Check SMPAPI_DIR
GCC = g++
DIRECTFB_LIBDIR = /usr/local/lib
DIRECTFB_INCDIR = /usr/DirectFB-1.6.1

#### Config #######

SRCS = example_1.cpp
#SRCS = example_2.cpp
	
CFLAGS  += -Wall                      \
         -I/usr/include               \

### link lib ######
CFLAGS  += -I$(DIRECTFB_INCDIR)/include   \
	-I$(DIRECTFB_INCDIR)/lib


LDFLAGS += -L$(DIRECTFB_LIBDIR) -ldirectfb

### Build ######
CXXFLAGS = $(CFLAGS)
TARGET = AppServer
OBJS = $(addsuffix .o, $(basename $(SRCS)))

.PHONY: all
all: install

.PHONY: install
install: $(TARGET)

$(TARGET): $(OBJS)
	$(GCC) -o $@ $(CFLAGS) $^ $(LDFLAGS)

clean::
	$(Q)$(foreach target,$(TARGET),rm -f *.o;)
	$(Q)$(foreach target,$(TARGET),rm -f $(SMPAPI_BINDIR)/$(target) $(target);)








