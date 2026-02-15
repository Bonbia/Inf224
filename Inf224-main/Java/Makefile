# Variables
JC = javac
JRE = java
SOURCES = Client.java MainWindow.java
CLASSES = $(SOURCES:.java=.class)
MAIN = MainWindow

# Cible par défaut : compilation
all: $(CLASSES)

# Règle de compilation des fichiers .java en .class
%.class: %.java
	$(JC) $^

# Règle pour lancer l'application (requise par le sujet)
run: all
	$(JRE) $(MAIN)

# Nettoyage des fichiers compilés
clean:
	rm -f *.class

# Nettoyage complet
distclean: clean
	rm -f *~

.PHONY: all run clean distclean