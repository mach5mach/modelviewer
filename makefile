CC=g++
INC_DIR = ./include
SRC_DIR = ./src
OBJ_DIR = ./object
BUILD_DIR = ./bin
TITLE = modelviewer
CFLAGS=-c -Wall -I${INC_DIR}

OBJECTS = ${OBJ_DIR}/hmi/hmiobject.o ${OBJ_DIR}/hmi/hmigraphicsobject.o ${OBJ_DIR}/hmi/hmiphysicsobject.o ${OBJ_DIR}/hmi/hmianatomyobject.o ${OBJ_DIR}/hmi/hmimuscle.o ${OBJ_DIR}/hmi/hmimuscles.o ${OBJ_DIR}/hmi/hmibone.o ${OBJ_DIR}/hmi/hmibones.o ${OBJ_DIR}/hmi/hmiscene.o ${OBJ_DIR}/hmi/hmiwindow.o
LIBRARIES = -lGLEW -lglfw -lGL -lassimp

#link and build
${BUILD_DIR}/${TITLE}.exe: ${OBJECTS} ${OBJ_DIR}/${TITLE}.o
	mkdir -p ${BUILD_DIR}
	${CC} -o ${BUILD_DIR}/${TITLE}.exe ${OBJECTS} ${OBJ_DIR}/${TITLE}.o ${LIBRARIES}
	
#compile TITLE.cpp
${OBJ_DIR}/${TITLE}.o: ${SRC_DIR}/${TITLE}.cpp
	 mkdir -p ${OBJ_DIR}
	 ${CC} ${CFLAGS} -c $^ -o $@
     
#compile hmi/*.cpp
${OBJ_DIR}/hmi/%.o: ${SRC_DIR}/hmi/%.cpp
	mkdir -p ${OBJ_DIR}/hmi
	${CC} ${CFLAGS} $< -o $@
     
#clean
clean:
	 rm -r ${OBJ_DIR} ${BUILD_DIR}
