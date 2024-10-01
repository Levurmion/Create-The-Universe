CXX := g++
CXXFLAGS := -Wall -std=c++17
CMD := $(CXX) $(CXXFLAGS)

# Capture the path to this file (common.mk)
THIS_MAKEFILE := $(lastword $(MAKEFILE_LIST))

# Convert to an absolute path
COMMON_MK_PATH := $(abspath $(THIS_MAKEFILE))

# Extract the directory
ROOT := $(dir $(COMMON_MK_PATH))

SRC := $(ROOT)/src

# module directories
HASHMAP := $(SRC)/hashmap
LINKED_LIST := $(SRC)/linked_list