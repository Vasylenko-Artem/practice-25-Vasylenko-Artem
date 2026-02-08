APP_DIR := apps
BUILD_DIR := $(abspath out)

subdirs :=

# Подключаем только apps/Makefile для subdir-y
ifneq ("$(wildcard $(APP_DIR)/Makefile)","")
  include $(APP_DIR)/Makefile
  subdirs := $(addprefix $(APP_DIR)/, $(subdir-y))
endif

.PHONY: all clean

all: build

build: $(BUILD_DIR)
	@echo "Starting build..."
	@for dir in $(subdirs); do \
		if [ -f $$dir/Makefile ]; then \
			echo "Building $$dir..."; \
			$(MAKE) -C $$dir BUILD_DIR=$(BUILD_DIR)/$$(basename $$dir); \
		else \
			echo "No Makefile in $$dir, skipping"; \
		fi; \
	done
	@echo "All apps built in $(BUILD_DIR)/"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	@echo "Cleaning all apps..."
	@for dir in $(subdirs); do \
		if [ -f $$dir/Makefile ]; then \
			$(MAKE) -C $$dir clean BUILD_DIR=$(BUILD_DIR)/$$(basename $$dir); \
		fi; \
	done
	rm -rf $(BUILD_DIR)
	@echo "Cleaned all builds"


run_app:
ifndef APP
	$(error You must specify APP, e.g., make run_app APP=menu)
endif
	$(MAKE) -C $(APP_DIR)/$(APP) BUILD_DIR=$(BUILD_DIR)/$(APP) run

run:
	$(BUILD_DIR)/menu/main