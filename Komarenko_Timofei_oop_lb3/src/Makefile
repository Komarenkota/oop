# Компилятор
CXX = g++

# Флаги компиляции
CXXFLAGS = -c -Wall

# Заголовочные файлы
INCLUDES = GameMap.hpp Manager.hpp ship.hpp Cell.hpp Segment.hpp Ability.hpp DoubleDamage.hpp Scanner.hpp Shelling.hpp AbilityManager.hpp Exceptions.hpp Game.hpp GameState.hpp

# Исходные файлы
SOURCES = main.cpp GameMap.cpp Manager.cpp ship.cpp Cell.cpp Segment.cpp Ability.cpp DoubleDamage.cpp Scanner.cpp Shelling.cpp AbilityManager.cpp Exceptions.cpp Game.cpp GameState.cpp

# Объектные файлы
OBJECTS = main.o GameMap.o Manager.o ship.o Cell.o Segment.o Ability.o DoubleDamage.o Scanner.o Shelling.o AbilityManager.o Exceptions.o Game.o GameState.o

# Итоговый исполняемый файл
TARGET = a.out

# Правило сборки проекта
all: $(TARGET)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Правила сборки объектных файлов
main.o: main.cpp $(INCLUDES)
	$(CXX) $(CXXFLAGS) main.cpp

GameMap.o: GameMap.cpp GameMap.hpp Exceptions.hpp
	$(CXX) $(CXXFLAGS) GameMap.cpp

Manager.o: Manager.cpp Manager.hpp ship.hpp
	$(CXX) $(CXXFLAGS) Manager.cpp

ship.o: ship.cpp ship.hpp
	$(CXX) $(CXXFLAGS) ship.cpp

Cell.o: Cell.cpp Cell.hpp
	$(CXX) $(CXXFLAGS) Cell.cpp

Segment.o: Segment.cpp Segment.hpp
	$(CXX) $(CXXFLAGS) Segment.cpp

Ability.o: Ability.cpp Ability.hpp
	$(CXX) $(CXXFLAGS) Ability.cpp

DoubleDamage.o: DoubleDamage.cpp DoubleDamage.hpp
	$(CXX) $(CXXFLAGS) DoubleDamage.cpp

Scanner.o: Scanner.cpp Scanner.hpp
	$(CXX) $(CXXFLAGS) Scanner.cpp

Shelling.o: Shelling.cpp Shelling.hpp
	$(CXX) $(CXXFLAGS) Shelling.cpp

AbilityManager.o: AbilityManager.cpp AbilityManager.hpp
	$(CXX) $(CXXFLAGS) AbilityManager.cpp

GameException.o: Exceptions.cpp Exceptions.hpp
	$(CXX) $(CXXFLAGS) Exceptions.cpp

Game.o: Game.cpp Game.hpp
	$(CXX) $(CXXFLAGS) Game.cpp

GameState.o: GameState.cpp GameState.hpp
	$(CXX) $(CXXFLAGS) GameState.cpp


# Очистка сгенерированных файлов
clean:
	rm -f *.o