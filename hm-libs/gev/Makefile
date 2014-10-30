#
#        Author:
#        Sep 9th, 2010
#

include Rules.mk

SRCS := $(shell find . -name "*.c")
OBJS := $(patsubst %.c, %.o, $(SRCS))
DEPS := Makefile.deps
TARG := O_TARG
_PWD := $(shell pwd)
BIN  := test

TAR_LIB := libgev.a
TAR_INC := *.h

INS_DIR=$(TAR_DIR)/gev

$(BIN): $(TARG)
#	$(CC) -o $@ $(shell find . -name "O_TARG" -print | xargs cat) $(LIBS) $(shell find . -name "L_TARG" -print | xargs cat)
	$(AR) -r $(TAR_LIB) $(shell find . -name "O_TARG" -print | xargs cat)

$(TARG): $(DEPS) $(OBJS)
	echo $(addprefix "$(_PWD)/", $(OBJS)) > $@

$(DEPS): $(SRCS)
	${CC} -MM ${CFLAGS} $^ > $@ ${INCS}

.PHONY: clean

clean:
	rm -rf $(OBJS) $(DEPS) $(TARG)

install:
	test -z $(INS_DIR)/lib || mkdir -p $(INS_DIR)/lib
	install -m 644 $(TAR_LIB) $(INS_DIR)/lib
	test -z $(INS_DIR)/inc || mkdir -p $(INS_DIR)/inc
	install -m 644 $(TAR_INC) $(INS_DIR)/inc
	
