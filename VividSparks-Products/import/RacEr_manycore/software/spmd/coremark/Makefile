RacEr_tiles_X = 1
RacEr_tiles_Y = 1

include ../Makefile.include

COREMARK_DIR = $(RACER_MANYCORE_DIR)/imports/coremark

$(info $(COREMARK_DIR))

vpath %.c $(COREMARK_DIR)

SRCS = core_list_join.c core_main.c core_matrix.c core_state.c \
       core_util.c core_portme.c cvt.c ee_printf.c

OBJECT_FILES = $(patsubst %.c,%.o,$(SRCS))

RISCV_GCC_EXTRA_OPTS += -I$(COREMARK_DIR) -I. -DITERATIONS=1 -DFLAGS_STR=\"$(OPT_LEVEL)\"

all: main.run

main.riscv: $(LINK_SCRIPT) $(OBJECT_FILES) $(SPMD_COMMON_OBJECTS) $(RACER_MANYCORE_LIB) crt.o
	$(RISCV_LINK) $(OBJECT_FILES) $(SPMD_COMMON_OBJECTS) -L. "-l:$(RACER_MANYCORE_LIB)" -o $@ $(RISCV_LINK_OPTS)

include ../../mk/Makefile.tail_rules
