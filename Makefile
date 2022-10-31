CC:=clang
CFLAGS:=-Wall -Wextra
INC_DIR:=include
SRC_DIR:=src
OBJ_DIR:=obj
GEN_DIR:=gen
EXP_DIR:=export
EXE_NAME:=unit_test
LINUX_INSTALL_DIR:=/usr/include/struct
TERMUX_INSTALL_DIR:=$${HOME}/../usr/include/struct

srcs:=$(wildcard $(SRC_DIR)/*.c)
incs:=$(wildcard $(INC_DIR)/*.h)
objs:=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(srcs))
exe:=$(GEN_DIR)/$(EXE_NAME)

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
	.install \
	.uninstall 

run: $(exe)
	./$(exe)

clean:
	rm -rf $(OBJ_DIR)/* $(GEN_DIR)/* $(EXP_DIR)/*

pack: $(incs)
	for file in $^; do cp $$file ${EXP_DIR}; done 

install_termux: install_dir:=$(TERMUX_INSTALL_DIR)
install_termux: .install

install_linux: install_dir:=$(LINUX_INSTALL_DIR)
install_linux: .install

uninstall_termux: install_dir:=$(TERMUX_INSTALL_DIR)
uninstall_termux: .uninstall 

uninstall_linux: install_dir:=$(LINUX_INSTALL_DIR)
uninstall_linux: .uninstall

.install: pack
	$(if $(value install_dir),, $(error "Install directory is not specified."))
	if [ ! -d $(install_dir) ]; then mkdir $(install_dir); fi
	cp $(EXP_DIR)/* $(install_dir)

.uninstall: 
	$(if $(value install_dir),, $(error "Install directory is not specified."))
	if [ -d $(install_dir) ]; then rm -rf $(install_dir); fi

$(exe): $(objs)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: CFLAGS+=-c -I$(INC_DIR)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(incs)
	$(CC) $(CFLAGS) $< -o $@
