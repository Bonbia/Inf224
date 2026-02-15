# Nom de l'exécutable final pour le serveur
SERVER_EXE = server
# Nom de l'exécutable pour les tests locaux (main.cpp)
TEST_EXE = test_main

# Compilateur et options
CXX = g++
CXXFLAGS = -Wall -g -std=c++11 -pthread

# Liste des fichiers sources communs aux deux exécutables
# (On exclut les fichiers contenant un main())
COMMON_SOURCES = MultimediaObject.cpp Photo.cpp Video.cpp MediaManager.cpp \
                 ccsocket.cpp tcpserver.cpp

# Liste des fichiers objets correspondants
COMMON_OBJS = $(COMMON_SOURCES:.cpp=.o)

# Cibles principales
all: $(SERVER_EXE) $(TEST_EXE)

# Compilation du serveur (celui qui communique avec Java)
$(SERVER_EXE): server.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $(SERVER_EXE) server.o $(COMMON_OBJS)

# Compilation du programme de test principal
$(TEST_EXE): main.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXE) main.o $(COMMON_OBJS)

# Règle générique pour les fichiers .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Commande pour lancer le serveur
run: $(SERVER_EXE)
	./$(SERVER_EXE)

# Nettoyage des fichiers objets et des exécutables
clean:
	rm -f *.o $(SERVER_EXE) $(TEST_EXE)

# Nettoyage complet
distclean: clean
	rm -f *~

.PHONY: all clean distclean run