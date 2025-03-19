SNP_BASE_DIR := $(realpath $(CURDIR)/../../..)

SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),$(SNP_BASE_DIR)/shared.mk)

TARGET     := bin/tic-tac-toe
MODULES    := src/model.c src/view.c src/control.c
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)

include $(SNP_SHARED_MAKEFILE)

