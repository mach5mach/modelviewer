CC=g++
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./object
BUILD_DIR = ./bin
CFLAGS=-c -Wall -I${INC_DIR}

DEPS = ${INC_DIR}/glm/vec2.hpp ${INC_DIR}/glm/vec3.hpp ${INC_DIR}/glm/mat4x4.hpp ${INC_DIR}/glm/gtc/matrix_transform.hpp ${INC_DIR}/glm/gtc/type_ptr.hpp ${INC_DIR}/nlohmann/json.hpp

all: ${BUILD_DIR}/gameengine.exe

${BUILD_DIR}/gameengine.exe: ${OBJ_DIR}/gameengine.o
	 ${CC} -o ${BUILD_DIR}/gameengine.exe ${OBJ_DIR}/gameengine.o -lGLEW -lglfw -lGL -lassimp

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	 ${CC} ${CFLAGS} -c $< -o $@
 
$(OBJ_DIR)/gameengine.o: ${DEPS} 
     
clean:
	 rm ${OBJ_DIR}/gameengine.o ${BUILD_DIR}/gameengine.exe
