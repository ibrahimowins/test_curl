# Compiler
CXX = g++

# Environment
ENVIRONMENT = mingw64

# Compiler Flags
CXXFLAGS = -static-libgcc -static-libstdc++ -Wall -O2

# Include Paths
INCLUDE = -I/$(ENVIRONMENT)/include

# Library Paths and Flags
LIB = -L/$(ENVIRONMENT)/lib
LDFLAGS = -lcurl -lssl -lcrypto -lz -lws2_32 -lcrypt32

# Source Files and Target
SRC = testing_curl.cpp
TARGET = test_curl.exe

# Build Target
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LIB) $(SRC) -o $(TARGET) $(LDFLAGS)

# Clean Build Artifacts
clean:
	rm -f $(TARGET)

# Phony Targets
.PHONY: all clean
