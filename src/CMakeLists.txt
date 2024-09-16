# Fuentes
set(SOURCES
    main.cpp
    # Añadir aquí otros archivos fuente
)

# Crear el ejecutable
add_executable(proyectoSensiaBridge ${SOURCES})

# Vincular librerías Conan
target_link_libraries(proyectoSensiaBridge ${CONAN_LIBS})