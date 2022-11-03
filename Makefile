CC:=clang
CFLAGS:=-Wall -Wextra
INC_DIR:=include
SRC_DIR:=src
OBJ_DIR:=obj
BIN_DIR:=bin
TST_DIR:=test
EXP_DIR:=export
EXE_NAME:=hello
TST_EXE_NAME:=unit_test
EXP_BIN_DIR:=$(EXP_DIR)/bin
EXP_LIB_DIR:=$(EXP_DIR)/lib
EXP_INC_DIR:=$(EXP_DIR)/include
INC_INST_DIRNAME:=basec

LINUX_INC_INST_DIR:=/usr/local/include/$(INC_INST_DIRNAME)
LINUX_LIB_INST_DIR:=/usr/local/lib
LINUX_BIN_INST_DIR:=/usr/local/bin
TERMUX_INC_INST_DIR:=$${HOME}/../usr/include/$(INC_INST_DIRNAME)
TERMUX_LIB_INST_DIR:=$${HOME}/../usr/lib
TERMUX_BIN_INST_DIR:=$${HOME}/../usr/bin

tst_srcs:=$(wildcard $(TST_DIR)/*.c)
tst_objs:=$(patsubst $(TST_DIR)/%.c, $(OBJ_DIR)/_test_%.o, $(tst_srcs))
tst_exe:=$(BIN_DIR)/$(TST_EXE_NAME)
srcs:=$(wildcard $(SRC_DIR)/*.c)
objs:=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(srcs))
exe:=$(BIN_DIR)/$(EXE_NAME)
incs:=$(wildcard $(INC_DIR)/*.h)

default: test

.PHONY: \
	default \
	test \
	debug \
	release \
	clean \
	pack \
	install_termux \
	uninstall_termux \
	install_linux \
	uninstall_linux \
	.pack_include \
	.install \
	.uninstall 

test: CFLAGS+=-O0 -g
test: $(tst_exe)
	./$(tst_exe)

debug: CFLAGS+=-O0 -g
debug: $(exe)

release: CFLAGS+=-O2
release: $(exe)

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
	cp -i --backup=t $(EXP_INC_DIR)/* $(inc_inst_dir) || :
	cp -i --backup=t $(EXP_LIB_DIR)/* $(lib_inst_dir) || :
	cp -i --backup=t $(EXP_BIN_DIR)/* $(bin_inst_dir) || :

.uninstall: 
	$(if $(value inc_inst_dir),, $(error "Include install directory is not specified."))
	$(if $(value lib_inst_dir),, $(error "Library install directory is not specified."))
	$(if $(value bin_inst_dir),, $(error "Binary install directory is not specified."))
	rm -ir $(inc_inst_dir) || :
	rm -ir $($(wildcard $(EXP_LIB_DIR)/*):$(EXP_LIB_DIR)/%=$(lib_inst_dir)/%) || :
	rm -ir $($(wildcard $(EXP_BIN_DIR)/*):$(EXP_LIB_DIR)/%=$(bin_inst_dir)/%) || :

$(tst_exe): $(tst_objs)
	$(CC) $(CFLAGS) $^ -o $@

$(exe): $(objs)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: CFLAGS+=-c -I$(INC_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(incs)
	$(CC) $(CFLAGS) $< -o $@
$(OBJ_DIR)/_test_%.o: $(TST_DIR)/%.c $(incs)
	$(CC) $(CFLAGS) $< -o $@
