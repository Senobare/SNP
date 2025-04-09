# Setze das Basisverzeichnis relativ zur aktuellen Position des Makefiles
SNP_BASE_DIR := $(realpath $(CURDIR)/../../..)

# Falls ein gemeinsames Makefile spezifiziert ist, verwende es, sonst benutze das Standard-Shared-File
SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),$(SNP_BASE_DIR)/shared.mk)

# Ziel des Projekts (der Haupt-Executable-Dateipfad)
TARGET     := bin/personen-verwaltung

# Modulverzeichnis (falls nötig, hier sind keine weiteren C-Module, daher leer)
MODULES    := src/person.c src/list.c

# Quellcode-Dateien für die Anwendung (nur main.c, da keine weiteren Module vorhanden sind)
SOURCES    := src/main.c $(MODULES)

# Quellcode-Dateien für die Tests (nur tests.c, da keine weiteren Test-Module vorhanden sind)
TSTSOURCES := tests/tests.c $(MODULES)

# Include das gemeinsame Makefile, um grundlegende Kompiliereinstellungen zu laden
include $(SNP_SHARED_MAKEFILE)

# Füge den Include-Pfad für das src-Verzeichnis hinzu, wo sich linkedlist.h befinden sollte
CFLAGS += -I$(CURDIR)/src

# Füge gegebenenfalls Fehlerbehandlung hinzu
# CFLAGS  += -Werror  # Uncomment if you want to treat warnings as errors
