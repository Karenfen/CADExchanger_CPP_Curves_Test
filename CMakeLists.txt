cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER gcc)

project(CADExchanger_CPP_Curves_Test LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание папки для исполняемых файлов
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

# Задаём путь к папке с библиотекой
set(LIBRARY_DIR ${PROJECT_SOURCE_DIR}/libs)

# Устанавливаем путь к библиотеке intel TBB
set(LIB_DIR_TBB ${PROJECT_SOURCE_DIR}/libs/oneapi-tbb)

# Добавление пути к заголовочным файлам библиотек
include_directories(${PROJECT_SOURCE_DIR}/libs/include  ${LIB_DIR_TBB}/include)

# Указываем путь к папкам с библиотеками
link_directories(${LIBRARY_DIR} ${LIB_DIR_TBB}/lib/intel64/vc14)

# Получение списка всех файлов из папки src
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Создание исполняемого файла из найденных файлов
add_executable(CADExchanger_CPP_Curves_Test ${SOURCES})

# Добавляем иблиотеки к исполняемому файлу
target_link_libraries(CADExchanger_CPP_Curves_Test PRIVATE ${LIBRARY_DIR}/curvs tbb)

# Установка пути для установки исполняемого файла
install(TARGETS CADExchanger_CPP_Curves_Test
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Копирование .dll в папку с исполняемым файлом
add_custom_command(TARGET CADExchanger_CPP_Curves_Test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${LIB_DIR_TBB}/redist/intel64/vc14/tbb12.dll  # Путь к .dll
        $<TARGET_FILE_DIR:CADExchanger_CPP_Curves_Test>)