


# here are the directories of the projects
# LIBS_ROOT=E:
LIBS_ROOT=/Users/markoates/Repos
ALLEGRO_DIR=$(LIBS_ROOT)/allegro5/build



GOOGLE_TEST_DIR=$(LIBS_ROOT)/googletest
GOOGLE_TEST_LIB_DIR=$(GOOGLE_TEST_DIR)/build/googlemock/gtest
GOOGLE_TEST_INCLUDE_DIR=$(GOOGLE_TEST_DIR)/googletest/include



# these are the names of the libs you are linking
ALLEGRO_LIBS_WITHOUT_MAIN=-lallegro_color -lallegro_font -lallegro_ttf -lallegro_dialog -lallegro_audio -lallegro_acodec -lallegro_primitives -lallegro_image -lallegro
ALLEGRO_LIBS=$(ALLEGRO_LIBS_WITHOUT_MAIN) -lallegro_main
# OPENGL_LIB=-framework OpenGL
# OPENGL_LIB=-lopengl32
GOOGLE_TEST_LIBS=gtest
VERSION_FLAG=-std=c++17

ifeq ($(OS), Windows_NT)
	OPENGL_LIB=-lopengl32
	# WINDOWS_SUBSYSTEM_FLAGS=-Wl,--subsystem,windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		OPENGL_LIB=-lGL
	endif
	ifeq ($(UNAME_S),Darwin)
		OPENGL_LIB=-framework OpenGL
	endif
endif




.PHONY: all clean main



SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(SOURCES:src/%.cpp=obj/%.o)
TEST_SOURCES := $(shell find tests -name '*Test.cpp')
TEST_OBJECTS := $(TEST_SOURCES:tests/%.cpp=obj/tests/%.o)
INDIVIDUAL_TEST_EXECUTABLES := $(TEST_SOURCES:tests/%.cpp=bin/tests/%)
QUINTESSENCE_BUILDER_EXECUTABLE=../blast/bin/programs/quintessence_from_yaml



main:
	make quintessences
	make tests
	make bin/krampushack



r:
	make main
	./bin/krampushack


quintessences: $(QUINTESSENCE_SOURCES)
	@[ -f $(QUINTESSENCE_BUILDER_EXECUTABLE) ] || echo "The needed executable $(QUINTESSENCE_BUILDER_EXECUTABLE) was not found"
	@find quintessence -name '*.q.yml' | xargs $(QUINTESSENCE_BUILDER_EXECUTABLE) -f
	@echo "(finished)"



bin/krampushack: programs/krampushack.cpp $(OBJECTS)
	g++ -g $(VERSION_FLAG) $(OBJECTS) $< -o $@ $(ALLEGRO_LIBS) -L$(ALLEGRO_DIR)/lib $(OPENGL_LIB) -I$(ALLEGRO_DIR)/include -I./include



obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	g++ -g -c $(VERSION_FLAG) $< -o $@ -I$(ALLEGRO_DIR)/include -I./include



tests: $(INDIVIDUAL_TEST_EXECUTABLES)



bin/tests/%: obj/tests/%.o obj/tests/TestRunner.o
	@mkdir -p $(@D)
	@printf "compiling standalone test \e[1m\e[36m$@\033[0m...\n"
	@g++ -g $(VERSION_FLAG) -Wall -Wuninitialized -Weffc++ $(OBJECTS) $< obj/tests/TestRunner.o -o $@ -l$(GOOGLE_TEST_LIBS) -L$(GOOGLE_TEST_LIB_DIR) $(ALLEGRO_LIBS) -L$(ALLEGRO_DIR)/lib $(OPENGL_LIB)
	@echo "done. Executable at \033[1m\033[32m$@\033[0m"



obj/tests/%.o: tests/%.cpp $(OBJECTS)
	@mkdir -p $(@D)
	@printf "compiling test obj file \e[1m\e[36m$@\033[0m...\n"
	@g++ -g -c $(VERSION_FLAG) -Wall -Wuninitialized -Weffc++ $< -o $@ -I./include -I$(GOOGLE_TEST_INCLUDE_DIR)
	@echo "done. Object at \033[1m\033[32m$@\033[0m"



obj/tests/TestRunner.o: tests/TestRunner.cpp
	@mkdir -p $(@D)
	@printf "Compiling test object for TestRunner \e[1m\e[36m$@\033[0m\n"
	@g++ -g -c -std=c++17 $(UNUSED_ARGUMENTS_FLAG) -Wall -Wuninitialized -Weffc++ $< -o $@ -I$(ALLEGRO_INCLUDE_DIR) -I$(ALLEGRO_PLATFORM_INCLUDE_DIR) -I$(GOOGLE_TEST_INCLUDE_DIR) -I$(GOOGLE_MOCK_INCLUDE_DIR) -I$(ALLEGRO_FLARE_INCLUDE_DIR)
	@printf "Object for TestRunner at \033[1m\033[32m$@\033[0m compiled successfully.\n"




clean:
	-rm $(OBJECTS)
	-rm $(TEST_OBJECTS)
	-rm bin/krampushack



