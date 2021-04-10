CC=g++
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./object
BUILD_DIR = ./bin
TITLE = modelviewer
CFLAGS=-c -Wall -I${INC_DIR}

DEPS = ${INC_DIR}/glm/vec2.hpp ${INC_DIR}/glm/vec3.hpp ${INC_DIR}/glm/mat4x4.hpp ${INC_DIR}/glm/gtc/matrix_transform.hpp ${INC_DIR}/glm/gtc/type_ptr.hpp ${INC_DIR}/nlohmann/json.hpp

all: ${BUILD_DIR}/${TITLE}.exe

${BUILD_DIR}/${TITLE}.exe: ${OBJ_DIR}/${TITLE}.o
	 mkdir -p ${BUILD_DIR}
	 ${CC} -o ${BUILD_DIR}/${TITLE}.exe ${OBJ_DIR}/${TITLE}.o -lGLEW -lglfw -lGL -lassimp

${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	 mkdir -p ${OBJ_DIR}
	 ${CC} ${CFLAGS} -c $< -o $@
 
$(OBJ_DIR)/${TITLE}.o: ${DEPS} 
     
clean:
	 rm -r ${OBJ_DIR} ${BUILD_DIR}
