# Assuming this Makefile lives in project root directory
# Do not use CURDIR in case make is run from elsewhere.

PROJ_DIR := $(shell readlink $(dir $(lastword $(MAKEFILE_LIST))) -f)

SRC = $(PROJ_DIR)/src
THIRD_PARTY = $(PROJ_DIR)/third_party
THIRD_PARTY_INSTALLED = $(THIRD_PARTY)/installed
BIN = $(PROJ_DIR)/bin
TESTS_DIR = $(PROJ_DIR)/tests

CPP = g++
INCFLAGS = -I$(THIRD_PARTY_INSTALLED)/include
CPPFLAGS = -g -O2 -Wall -Wno-strict-aliasing

.PHONY: all

mk_bin:
	mkdir -p $(BIN)

petuum_dnn: mk_bin
	touch $(BIN)/fake_dnn

clean:
	rm -rf $(BIN)

veryclean:
	rm -rf $(BIN)
	rm -rf $(THIRD_PARTY_INSTALLED)

include $(THIRD_PARTY)/third_party.mk # defines target third_party