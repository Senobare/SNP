SNP_BASE_DIR := $(realpath $(CURDIR)/../../..)

SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),$(SNP_BASE_DIR)/shared.mk)

TARGET     := bin/personen-verwaltung
# BEGIN-STUDENTS-TO-ADD-CODE
MODULES    := 
# END-STUDENTS-TO-ADD-CODE
SOURCES    := src/main.c $(MODULES)
TSTSOURCES := tests/tests.c $(MODULES)


include $(SNP_SHARED_MAKEFILE)

# CFLAGS  += -Werror
