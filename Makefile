CC:=clang
CFLAGS:=-Wall -Wextra
INC_DIR:=include
SRC_DIR:=src
OBJ_DIR:=obj
BIN_DIR:=bin
EXP_DIR:=export
EXE_NAME:=unit_test
EXP_BIN_DIR:=$(EXP_DIR)/bin
EXP_LIB_DIR:=$(EXP_DIR)/lib
EXP_INC_DIR:=$(EXP_DIR)/include
LINUX_INC_INST_DIR:=/usr/local/include/struct
LINUX_LIB_INST_DIR:=/usr/local/lib
LINUX_BIN_INST_DIR:=/usr/local/bin
TERMUX_INC_INST_DIR:=$${HOME}/../usr/include/struct
TERMUX_LIB_INST_DIR:=$${HOME}/../usr/lib
TERMUX_BIN_INST_DIR:=$${HOME}/../usr/bin

srcs:=$(wildcard $(SRC_DIR)/*.c)
incs:=$(wildcard $(INC_DIR)/*.h)
objs:=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(srcs))
exe:=$(BIN_DIR)/$(EXE_NAME)

default: run 

.PHONY: \
	default \
	run \
	clean \
	pack \
	install_termux \
	uninstall_termux \
	install_linux \
	uninstall_linux \
	.pack_include \
	.install \
	.uninstall 

run: $(exe)
	./$(exe)

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/* $(EXP_INC_DIR)/* $(EXP_LIB_DIR)/* $(EXP_BIN_DIR)/*

pack: .pack_include

install_termux: inc_inst_dir:=$(TERMUX_INC_INST_DIR)
install_termux: lib_inst_dir:=$(TERMUX_LIB_INST_DIR)
install_termux: bin_inst_dir:=$(TERMUX_BIN_INST_DIR)
install_termux: .install

install_linux: inc_inst_dir:=$(LINUX_INC_INST_DIR)
install_linux: lib_inst_dir:=$(LINUX_LIB_INST_DIR) 
install_linux: bin_inst_dir:=$(LINUX_BIN_INST_DIR)
install_linux: .install

uninstall_termux: inc_inst_dir:=$(TERMUX_INC_INST_DIR)
uninstall_termux: lib_inst_dir:=$(TERMUX_LIB_INST_DIR)
uninstall_termux: bin_inst_dir:=$(TERMUX_BIN_INST_DIR)
uninstall_termux: .uninstall 

uninstall_linux: inc_inst_dir:=$(LINUX_INC_INST_DIR)
uninstall_linux: lib_inst_dir:=$(LINUX_LIB_INST_DIR) 
uninstall_linux: bin_inst_dir:=$(LINUX_BIN_INST_DIR)
uninstall_linux: .uninstall

.pack_include: $(incs)
	cp $^ $(EXP_INC_DIR)

.install: pack
	$(if $(value inc_inst_dir),, $(error "Include install directory is not specified."))
	$(if $(value lib_inst_dir),, $(error "Library install directory is not specified."))
	$(if $(value bin_inst_dir),, $(error "Binary install directory is not specified."))
	if [ ! -d $(inc_inst_dir) ]; then mkdir $(inc_inst_dir); fi
	cp $(EXP_INC_DIR)/* $(inc_inst_dir) 2>/dev/null || :
	cp $(EXP_LIB_DIR)/* $(lib_inst_dir) 2>/dev/null || :
	cp $(EXP_BIN_DIR)/* $(bin_inst_dir) 2>/dev/null || :

.uninstall: 
	$(if $(value inc_inst_dir),, $(error "Include install directory is not specified."))
	$(if $(value lib_inst_dir),, $(error "Library install directory is not specified."))
	$(if $(value bin_inst_dir),, $(error "Binary install directory is not specified."))
	rm -ir $(inc_inst_dir) || :
	rm -ir $($(wildcard $(EXP_LIB_DIR)/*):$(EXP_LIB_DIR)/%=$(lib_inst_dir)/%) || :
	rm -ir $($(wildcard $(EXP_BIN_DIR)/*):$(EXP_LIB_DIR)/%=$(bin_inst_dir)/%) || :

$(exe): $(objs)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: CFLAGS+=-c -I$(INC_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(incs)
	$(CC) $(CFLAGS) $< -o $@
