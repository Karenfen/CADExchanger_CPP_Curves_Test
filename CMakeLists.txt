cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER gcc)

project(CADExchanger_CPP_Curves_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание папки для исполняемых файлов
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Устанавливаем путь к библиотеке intel TBB
set(LIB_DIR_TBB C:/libs/oneapi-tbb)

# Добавление пути к заголовочным файлам (если они есть)
include_directories(${PROJECT_SOURCE_DIR}/include  ${LIB_DIR_TBB}/include)

# Указать путь к папке с библиотекой
link_directories(${LIB_DIR_TBB}/lib/intel64/vc14)


# Получение списка всех файлов из папки src
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Создание исполняемого файла из найденных файлов
add_executable(CADExchanger_CPP_Curves_Test ${SOURCES})

target_link_libraries(CADExchanger_CPP_Curves_Test PRIVATE tbb)

# Установка пути для установки исполняемого файла
install(TARGETS CADExchanger_CPP_Curves_Test
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)