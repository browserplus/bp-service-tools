# A minimal makefile to build the sample native service
# environment inputs:
#  BPSDK_PATH: the path to the BrowserPlus SDK

BPSDK_PATH ?= ../external/bpsdk
SRC_PATH ?= .
INCLUDE = -I${BPSDK_PATH}/include -I${SRC_PATH}/../src
NAME = CppToolsSample
CFLAGS ?= -g -Wall
SRCS = ${SRC_PATH}/sample.cpp ${SRC_PATH}/../src/bptypeutil.cpp ${SRC_PATH}/../src/bpserviceversion.cpp ${SRC_PATH}/../src/bpservicedescription.cpp ${SRC_PATH}/../src/bpurlutil.cpp 

${NAME}: ${SRCS}
	g++ ${CFLAGS} -o $@ ${INCLUDE} $^

.PHONY: clean
clean:
	rm -rf ${NAME} *~
