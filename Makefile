MESON_CONFIG_DIR	:= build
MESON_BUILD_DIR		:= release


all: build
	@ninja -C $(MESON_CONFIG_DIR)
	@ninja install -C $(MESON_CONFIG_DIR) >/dev/null

build:
	@meson $(MESON_CONFIG_DIR) --prefix=$$PWD/$(MESON_BUILD_DIR) --bindir="" --libdir=""

clean:
	@rm -rf $(MESON_BUILD_DIR)

fclean: clean
	@rm -rf $(MESON_CONFIG_DIR)

re: fclean all

run: all
	@cd $(MESON_BUILD_DIR) && ./sfml_game_base

runval: all
	@cd $(MESON_BUILD_DIR) && valgrind ./sfml_game_base

install:
	@echo "NEED SUDO FOR INSTALLATION"
	@sudo apt install libopenal-dev libudev-dev

fullinstall: install
	@sudo apt-get install libsfml-dev

update:
	@make fclean
	@for i in $$(find subprojects -maxdepth 1 -type d); do if [ $$i != "subprojects" ]; then rm -rf $$i; fi; done;
	@rm -f subprojects/libpng.wrap
	@make

.PHONY: all clean fclean re run runval install fullinstall update
