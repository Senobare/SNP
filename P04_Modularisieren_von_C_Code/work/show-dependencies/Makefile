SNP_BASE_DIR := $(realpath $(CURDIR)/../../..)

SNP_SHARED_MAKEFILE := $(if $(SNP_SHARED_MAKEFILE),$(SNP_SHARED_MAKEFILE),$(SNP_BASE_DIR)/shared.mk)

TARGET     := bin/dep2dot
# Add all additional c-files to the SOURCES variable
# BEGIN-STUDENTS-TO-ADD-CODE
SOURCES    := src/main.c src/data.c src/output.c
# END-STUDENTS-TO-ADD-CODE
TSTSOURCES := tests/tests.c

include $(SNP_SHARED_MAKEFILE)

# Im gitrpo beschriebenes gcc nicht auffindbar?!
# Ordner wird hier erstellt
$(TARGET): $(SOURCES) | bin
	$(CC) $(CFLAGS) -o $@ $^

bin:
	mkdir -p bin


# DEPFILES :=  ... define a list of png file names: %.c -> %.c.png
# BEGIN-STUDENTS-TO-ADD-CODE
DEPFILES = $(SOURCES:.c=.c.png)

# END-STUDENTS-TO-ADD-CODE



# define dep target as .PHONEY
# BEGIN-STUDENTS-TO-ADD-CODE
.PHONY: all clean dep-clean dep

# BEGIN-STUDENTS-TO-ADD-CODE



# define dep target depending on FULLTARGET and DEPFILES above
# action: echo some text telling that the target is done using $@ - the echo command shall not be echoed before execution
# BEGIN-STUDENTS-TO-ADD-CODE
dep: $(TARGET) $(DEPFILES)
	@echo "Target $@ is done."

# BEGIN-STUDENTS-TO-ADD-CODE



# define new suffix rule for %.png depending on %.dot
# action: dot -Tpng $< >$@ || $(RM) $@

# This rule translates a .dot file into a .png file using the `dot` command.
# $< refers to the input file (the .dot file), and $@ refers to the output file (the .png file).
# If the command fails, the output file is removed using $(RM).

# BEGIN-STUDENTS-TO-ADD-CODE
%.png: %.dot
		dot -Tpng $< > $@ || $(RM) $@

# BEGIN-STUDENTS-TO-ADD-CODE



# define new suffix rule for %.dot depending on %.dep
# action: call $(TARGET) $(@:.dot=) <$< >$@ || $(RM) $@

# define new suffix rule for %.dot depending on %.dep
# action: call $(TARGET) $(@:.dot=) <$< >$@ || $(RM) $@
# This rule converts a .dep file into a .dot file using the $(TARGET) (dep2dot).
# $< refers to the input file (the .dep file), and $@ refers to the output file (the .dot file).
# The $(@:.dot=) expression removes the .dot suffix from the output file name and passes the filename to $(TARGET).
# If the command fails, the output file is removed using $(RM).

# BEGIN-STUDENTS-TO-ADD-CODE
%.dot: %.dep
		$(TARGET) $(@:.dot=) < $< > $@ || $(RM) $@

# BEGIN-STUDENTS-TO-ADD-CODE



# converts any .c file into a .c.dep file by means of GCC -H switch
# note: it removes intermediate files which were created as side effect
%.c.dep: %.c
	$(COMPILE.c) -H -o $@.x $< 2>$@ && $(RM) $@.x $@.d


# cleanup all results, including the ones od creating the dependencies
dep-clean: clean
	$(RM) $(DEPFILES) $(wildcard src/*.dep src/*.dot)

