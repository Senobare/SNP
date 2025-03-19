# Dynamically set the base directory for SNP based on the current directory (CURDIR)
SNP_BASE_DIR := $(realpath $(CURDIR)/../../..)

$(info SNP_BASE_DIR = $(SNP_BASE_DIR))

# Set the target (triangle executable)
TARGET := bin/triangle

# Include paths (correct the path for test_utils.h)
CFLAGS := -std=c99 -Wall -pedantic -g -MD -Isrc -Itests -I/home/senobare/Developer/ZHAW/Sem4/SNP/testlib/include -I/usr/include/CUnit -DTARGET=$(TARGET)

# Sources and object files
SOURCES := src/triangle.c src/read.c src/rectang.c
TSTSOURCES := tests/tests.c

# Libraries
LIBS := -lm -lcunit # this will point to /usr/lib/libcunit.so instead of searching for a static variant

# Define the output binary
OUTPUT := $(TARGET)

# Include shared.mk (ensure this file exists and is correct)
include $(SNP_BASE_DIR)/shared.mk
