JAVAC = javac
JAVA = java
SRC_DIR = src
BUILD_DIR ?= build
MAIN = app.Main

# путь к postgresql jdbc драйверу
PG_JAR = libs/postgresql-42.7.8.jar

SOURCES := $(shell find $(SRC_DIR) -name "*.java")

all: $(BUILD_DIR)
	$(JAVAC) -d $(BUILD_DIR) $(SOURCES)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

run: all
	$(JAVA) -Duser.timezone=UTC -cp "$(BUILD_DIR):$(PG_JAR)" $(MAIN)

clean:
	rm -rf $(BUILD_DIR)
