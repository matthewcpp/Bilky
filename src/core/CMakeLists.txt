set(bilky_files)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Bilky.hpp)

#add interfaces
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/ICardCollection.hpp)

#add classes
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Card.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Card.cpp)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/CardCollection.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/CardCollection.cpp)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Dealer.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Dealer.cpp)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Game.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Player.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Player.cpp)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Roster.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Roster.cpp)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Round.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Round.cpp)

list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Trick.hpp)
list(APPEND bilky_files ${CMAKE_CURRENT_SOURCE_DIR}/Trick.cpp)

add_library( Bilky STATIC ${bilky_files})

if (MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()