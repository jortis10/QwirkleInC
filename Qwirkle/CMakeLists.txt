cmake_minimum_required(VERSION 3.5)
#list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2")

project(quirkle)

set(SRC
main.c
Modele/gestionSac.c
Modele/joueur.c
Modele/partie.c 
Modele/plateau.c
Modele/regle.c
Modele/score.c 
Modele/tuile.c
Vue/affichage_plateau.c 
Vue/affichage_sdl.c 
Controleur/controleur.c 
Controleur/respectRegles.c)

set(HEADER
Modele/joueur.h
Modele/partie.h
Modele/plateau.h
Modele/regle.h
Modele/score.h 
Modele/tuile.h
Vue/affichage_plateau.h 
Vue/affichage_sdl.h 
Controleur/controleur.h 
Controleur/respectRegles.h)


add_executable(qwirkle ${SRC} ${HEADER})


find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    target_include_directories(qwirkle PUBLIC ${SDL2_INCLUDE_DIR})
    target_link_libraries(qwirkle ${SDL2_LIBRARY})
else()
    message(FATAL_ERROR "libSDL2 not found")
endif()

#find_package(SDL2_ttf REQUIRED)
#if(SDL2_ttf_FOUND)
#    target_include_directories(qwirkle PUBLIC ${SDL2_ttf_INCLUDE_DIR})
#    target_link_libraries(qwirkle ${SDL2_ttf_LIBRARY})
#else()
#    message(FATAL_ERROR "libSDL2-ttf not found")
#endif()