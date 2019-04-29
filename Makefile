#
# Makefile for CSE 30 -- PA3
# You should not need to change anything in this file.
#
# XXX DO NOT EDIT
#

HEADERS		= pa3.h pa3Strings.h
TEST_HEADERS	= $(HEADERS) test.h

C_SRCS		= countChars.c 
GENERATE_C_SRCS	= generateAnagramMain.c generateAnagramFile.c pa3Globals.c
QUERY_C_SRCS	= queryAnagramMain.c executeQuery.c insertIntoBucket.c \
		  pa3Globals.c queryLoop.c loadQueryTable.c 
ASM_SRCS	= assembleAnagram.s getBucketIndex.s getHashcode.s \
		  anagramCmp.s countsCmp.s hashcodeCmp.s \
		  isInBounds.s getURemainder.s

GENERATE_C_OBJS	= $(GENERATE_C_SRCS:.c=.o) $(C_SRCS:.c=.o)
QUERY_C_OBJS	= $(QUERY_C_SRCS:.c=.o) $(C_SRCS:.c=.o)
C_OBJS		= $(GENERATE_C_SRCS:.c=.o) $(QUERY_C_SRCS:.c=.o) $(C_SRCS:.c=.o)
ASM_OBJS	= $(ASM_SRCS:.s=.o)
GENERATE_OBJS	= $(GENERATE_C_OBJS) $(ASM_OBJS)
QUERY_OBJS	= $(QUERY_C_OBJS) $(ASM_OBJS)

GENERATE_EXE	= generate
QUERY_EXE	= query

TEST_EXES	= testassembleAnagram testcountChars testgetBucketIndex \
		  testgetHashcode \
		  testanagramCmp testcountsCmp testhashcodeCmp \
		  testgetURemainder testexecuteQuery
TEST_OBJS	= $(TEST_EXES:=.o)

GCC		= gcc
ASM		= $(GCC)
RM		= rm

DEBUG_FLAGS	= -g
GCC_FLAGS	= -c $(DEBUG_FLAGS) -std=c99 -pedantic -Wall -D__EXTENSIONS__
ASM_FLAGS	= -c $(DEBUG_FLAGS)
LD_FLAGS	= $(DEBUG_FLAGS) -Wall

OPT_FLAGS	= -O3 -fstack-protector-all
OPT_GCC_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(GCC_FLAGS))
OPT_ASM_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(ASM_FLAGS))
OPT_LD_FLAGS	= $(subst $(DEBUG_FLAGS),$(OPT_FLAGS),$(LD_FLAGS))

#
# Standard rules
#

.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Target to create both programs (generate and query). This is the default
# target that gets run when you type 'make' with no target specified
#

all:
	@echo "-----------------------------------------------------------"
	@echo "| Compile GENERATE:                                       |"
	@echo "-----------------------------------------------------------"
	@make --no-print-directory $(GENERATE_EXE)
	@echo ""
	@echo ""
	@echo "-----------------------------------------------------------"
	@echo "| Compile QUERY:                                          |"
	@echo "-----------------------------------------------------------"
	@make --no-print-directory $(QUERY_EXE)

#
# Target to make the generate executable.
#

$(GENERATE_EXE): $(GENERATE_OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(GENERATE_EXE) $(GENERATE_OBJS)
	@echo ""
	@echo "Compilation Successful!"

#
# Target to make the query executable.
#

$(QUERY_EXE): $(QUERY_OBJS)
	@echo "Linking all object modules ..."
	$(GCC) $(LD_FLAGS) -o $(QUERY_EXE) $(QUERY_OBJS)
	@echo ""
	@echo "Compilation Successful!"

$(C_OBJS): $(HEADERS)

clean:
	@echo "Cleaning up project directory ..."
	$(RM) -f *.o $(GENERATE_EXE) $(QUERY_EXE) core a.out \
		$(TEST_EXES) *$(OPT_EXT)
	@echo ""
	@echo "Clean."

#
# Unit test targets
#

# List dependencies for tester executable in variable suffixed with "Deps"
testassembleAnagramDeps = testassembleAnagram.o assembleAnagram.o countChars.o \
			  getHashcode.o pa3Globals.o
testcountCharsDeps = testcountChars.o countChars.o
testgetBucketIndexDeps = testgetBucketIndex.o getBucketIndex.o getURemainder.o
testgetHashcodeDeps = testgetHashcode.o getHashcode.o pa3Globals.o
testanagramCmpDeps = testanagramCmp.o anagramCmp.o countsCmp.o hashcodeCmp.o \
                     pa3Globals.o
testcountsCmpDeps = testcountsCmp.o countsCmp.o pa3Globals.o
testhashcodeCmpDeps = testhashcodeCmp.o hashcodeCmp.o pa3Globals.o
testgetURemainderDeps = testgetURemainder.o getURemainder.o 
testexecuteQueryDeps = testexecuteQuery.o executeQuery.o assembleAnagram.o \
		       getBucketIndex.o getHashcode.o hashcodeCmp.o \
		       countChars.o pa3Globals.o getURemainder.o anagramCmp.o \
		       countsCmp.o

OPT_EXT = -opt

# Optimized object file rules.
%$(OPT_EXT).o: %.s
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(OPT_ASM_FLAGS) -o $(<:.s=$(OPT_EXT).o) $<
	@echo ""

%$(OPT_EXT).o: %.c
	@echo "Compiling each C source file separately ..."
	$(GCC) $(OPT_GCC_FLAGS) -o $(<:.c=$(OPT_EXT).o) $<
	@echo ""

$(TEST_OBJS): $(TEST_HEADERS)

# Rules for compiling tester toplevels.
$(TEST_EXES):
	@echo "Compiling $@ ..."
	$(GCC) $(LD_FLAGS) -o $@ $(filter %.o, $^)
	@echo "Compilation Successful!"

TEST_OPT_EXES = $(TEST_EXES:=$(OPT_EXT))
$(TEST_OPT_EXES): $(TEST_HEADERS)
	@echo "Compiling $@ ..."
	$(GCC) $(OPT_LD_FLAGS) -o $@ $(filter %.o, $^)
	@echo "Compilation Successful!"

# Lay out dependencies for each test file (regular and optimized).
define testRule
$(1): $$($(1)Deps)				# Regular dependencies.
$(1)$$(OPT_EXT): $$($(1)Deps:.o=$$(OPT_EXT).o)	# Optimized .o dependencies.
endef

# This calls the above function on each test file target, generating rules
# for each tester file's regular and optimized executables.
$(foreach test,$(TEST_EXES),$(eval $(call testRule,$(test))))

new:
	make clean
	make
