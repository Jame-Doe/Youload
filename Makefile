CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LIBS     = -pthread
TARGET   = debug/server.exe

SRCS     = main.cpp components/serverRoutes.cpp components/serverDownloadFile.cpp components/serverRun.cpp
OBJS     = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p debug
	$(CXX) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS)
	clear

.PHONY: all run clean
