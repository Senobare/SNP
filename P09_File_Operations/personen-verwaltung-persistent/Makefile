SNP_BASE_DIR := $(realpath $(CURDIR)/../../..)

SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),$(SNP_BASE_DIR)/shared.mk)


TARGET     := bin/personen-verwaltung
MODULES    := src/person.c src/list.c src/file_io.c
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)


include $(SNP_SHARED_MAKEFILE)

# CFLAGS  += -Werror
