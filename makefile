# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Target executable names
TARGET = TestingMain
DEMO_TARGET = DemoMain

# Source files
MAIN_SOURCES = $(filter-out DemoMain.cpp, $(wildcard *.cpp))
DEMO_SOURCES = $(filter-out TestingMain.cpp, $(wildcard *.cpp))

# Object files
MAIN_OBJECTS = $(MAIN_SOURCES:.cpp=.o)
DEMO_OBJECTS = $(DEMO_SOURCES:.cpp=.o)
ALL_OBJECTS = $(wildcard *.o)

# Default target - builds the main executable
all: $(TARGET)

# Build both executables
both: $(TARGET) $(DEMO_TARGET)

# Build the main executable (TestingMain)
$(TARGET): $(MAIN_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(MAIN_OBJECTS)

# Build the demo executable (DemoMain)
$(DEMO_TARGET): $(DEMO_OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(DEMO_TARGET) $(DEMO_OBJECTS)

# Compile individual source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up generated files
clean:
	rm -f $(ALL_OBJECTS) $(TARGET) $(DEMO_TARGET) valgrind.log

# Run the main program after building
run: $(TARGET)
	./$(TARGET)

# Run the demo program after building
run-demo: $(DEMO_TARGET)
	./$(DEMO_TARGET)

# Run main program with Valgrind for memory leak detection
val: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET)

# Run demo program with Valgrind for memory leak detection
val-demo: $(DEMO_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(DEMO_TARGET)

# Run with Valgrind (quick version - less verbose)
valq: $(TARGET)
	valgrind --leak-check=full ./$(TARGET)

# Run demo with Valgrind (quick version - less verbose)
valq-demo: $(DEMO_TARGET)
	valgrind --leak-check=full ./$(DEMO_TARGET)

# Run with Valgrind and save output to file
vallog: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-main.log ./$(TARGET)
	@echo "Valgrind output saved to valgrind-main.log"

# Run demo with Valgrind and save output to file
vallog-demo: $(DEMO_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file=valgrind-demo.log ./$(DEMO_TARGET)
	@echo "Valgrind output saved to valgrind-demo.log"

# Force rebuild everything
rebuild: clean all

# Force rebuild both executables
rebuild-both: clean both

# Show help with available targets
help:
	@echo "Available targets:"
	@echo "  all          - Build main executable (TestingMain)"
	@echo "  both         - Build both executables"
	@echo "  run          - Build and run main program"
	@echo "  run-demo     - Build and run demo program"
	@echo "  val          - Run main with Valgrind (verbose)"
	@echo "  val-demo     - Run demo with Valgrind (verbose)"
	@echo "  valq         - Run main with Valgrind (quick)"
	@echo "  valq-demo    - Run demo with Valgrind (quick)"
	@echo "  vallog       - Run main with Valgrind, save to log"
	@echo "  vallog-demo  - Run demo with Valgrind, save to log"
	@echo "  clean        - Remove all generated files"
	@echo "  rebuild      - Clean and rebuild main"
	@echo "  rebuild-both - Clean and rebuild both"
	@echo "  help         - Show this help message"

# Mark these targets as phony (not files)
.PHONY: all both clean run run-demo rebuild rebuild-both val val-demo valq valq-demo vallog vallog-demo help