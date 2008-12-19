# A minimal makefile to build the sample native service
# environment inputs:
#  BPSDK_PATH: the path to the BrowserPlus SDK

BPSDK_PATH ?= ../external/bpsdk
SRC_PATH ?= .
INCLUDE = -I${BPSDK_PATH}/include -I${SRC_PATH}/../src
NAME = DataMappingSample

${NAME}: ${SRC_PATH}/sample.cpp ${SRC_PATH}/../src/bptypeutil.cpp
	g++ -o $@ ${INCLUDE} $^

.PHONY: clean
clean:
	rm -rf ${NAME} *~
