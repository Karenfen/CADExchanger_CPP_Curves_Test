cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER gcc)

project(CADExchanger_CPP_Curves_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание папки для исполняемых файлов
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Добавление пути к заголовочным файлам (если они есть)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Получение списка всех файлов из папки src
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Путь к папке с библиотекой
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/libs)

# Указываем путь к папке с заголовочными файлами
include_directories(${PROJECT_SOURCE_DIR}/libs/include)

# Добавление пути к папке с библиотекой для поиска
link_directories(${LIBRARY_DIR})

# Создание исполняемого файла из найденных файлов
add_executable(CADExchanger_CPP_Curves_Test ${SOURCES})

# Добавляем .dll библиотеку к исполняемому файлу
target_link_libraries(CADExchanger_CPP_Curves_Test PRIVATE ${LIBRARY_DIR}/curvs)

# Установка пути для установки исполняемого файла
install(TARGETS CADExchanger_CPP_Curves_Test
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)