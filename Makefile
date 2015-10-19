#---------------------------------
# INITIALISATION DES VARIABLES
#---------------------------------

# Indiquer le compilateur
CXX= g++

# Les chemins ou se trouvent les fichiers a inclure
INCLUDE= -I/usr/include

# Options de compilation.
CXXFLAGS=  $(INCLUDES_DIR) -c -Wno-deprecated

# Les chemins ou se trouvent les librairies
LIBRARY_PATH= -L/usr/lib

# Options pour le linker.
LDFLAGS= $(LIBRARY_PATH) -o

# Les librairies avec lesquelle on va effectueller l'edition de liens
LIBS=

# Les fichiers sources de l'application
FILES= Graph.cpp Edge.cpp Vertex.cpp main.cpp

#-----------
# LES CIBLES
#-----------
Graph :  $(FILES:.cpp=.o)
	$(CXX) $(LDFLAGS) Graph $(FILES:.cpp=.o) $(LIBS)

.PHONY : clean
clean:
	/bin/rm $(FILES:.cpp=.o) Graph

run : clean
	./Graph


#-----------------------------------------------------------------------------
# LES REGLES DE DEPENDANCE. Certaines sont implicites mais je recommande d'en
# mettre une par fichier source.
#-----------------------------------------------------------------------------
Graph.o:Vertex.cpp Edge.cpp
Vertex.o:Vertex.cpp Vertex.h
Edge.o:Edge.cpp Edge.h Vertex.cpp Vertex.h

#---------------------------------
# REGLES DE COMPILATION IMPLICITES
#---------------------------------
%.o : %.cpp ; $(CXX) $(CXXFLAGS) $*.cpp
