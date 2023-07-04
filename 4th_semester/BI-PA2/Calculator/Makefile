CXX = g++
CXXFLAGS = -Wall -pedantic -std=c++17

HEADERS = $(wildcard src/*.h)
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)
TESTS = $(wildcard tests/*.test.cpp)

.DEFAULT_GOAL := all

.PHONY: all
all: compile doc

.PHONY: run
run: compile
	olsheden

.PHONY: compile
compile: olsheden

olsheden: build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	$(CXX) $^ -o $@

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $< -c -o $@

debug/%.test: tests/%.test.cpp $(filter-out build/main.o,$(OBJECTS))
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< $(filter-out build/main.o,$(OBJECTS)) -I src/ -o $@

.PHONY: doc
doc: Doxyfile $(HEADERS)
	doxygen Doxyfile
	mv doc/html/* doc/
	rm -rf html

Doxyfile:
	doxygen -g Doxyfile

.PHONY: clean
clean:
	rm -rf olsheden build/ doc/ 2>/dev/null

.PHONY: test_all
test_all: $(TESTS:tests/%.test.cpp=debug/%.test)
	for TEST in debug/*.test; do ./$$TEST; done

CAddOperator.o: src/CAddOperator.cpp src/CAddOperator.h src/COperator.h \
  src/CNumber.h src/CIntegerNumber.h src/./CNumber.h \
  src/CDecimalNumber.h
CAddVisitor.o: src/CAddVisitor.cpp src/CAddVisitor.h src/CVisitor.h \
  src/CIntegerNumber.h src/./CNumber.h src/CDecimalNumber.h \
  src/CNumber.h
CCalculator.o: src/CCalculator.cpp src/./CCalculator.h src/./CNumber.h \
  src/./CParsing.h src/./COperator.h src/CNumber.h src/./CVariables.h \
  src/./CQueue.h src/./CIntegerNumber.h src/./CDecimalNumber.h \
  src/CIntegerNumber.h
CDecimalNumber.o: src/CDecimalNumber.cpp src/./CDecimalNumber.h \
  src/CNumber.h src/CIntegerNumber.h src/./CNumber.h src/CAddVisitor.h \
  src/CVisitor.h src/CDecimalNumber.h src/CDivideVisitor.h \
  src/CMultiplyVisitor.h src/CSubtractVisitor.h src/CAddOperator.h \
  src/COperator.h src/CDivideOperator.h src/CMultiplyOperator.h \
  src/CSubtractOperator.h src/CPowerVisitor.h src/CPowerOperator.h
CDivideOperator.o: src/CDivideOperator.cpp src/CDivideOperator.h \
  src/COperator.h src/CNumber.h src/CIntegerNumber.h src/./CNumber.h \
  src/CDecimalNumber.h
CDivideVisitor.o: src/CDivideVisitor.cpp src/CDivideVisitor.h \
  src/CVisitor.h src/CIntegerNumber.h src/./CNumber.h \
  src/CDecimalNumber.h src/CNumber.h
CFactOperator.o: src/CFactOperator.cpp src/CFactOperator.h \
  src/COperator.h src/CNumber.h src/CIntegerNumber.h src/./CNumber.h
CIntegerNumber.o: src/CIntegerNumber.cpp src/./CIntegerNumber.h \
  src/./CNumber.h src/CAddVisitor.h src/CVisitor.h src/CIntegerNumber.h \
  src/CDecimalNumber.h src/CNumber.h src/CDivideVisitor.h \
  src/CSubtractVisitor.h src/CMultiplyVisitor.h src/CAddOperator.h \
  src/COperator.h src/CDivideOperator.h src/CMultiplyOperator.h \
  src/CSubtractOperator.h src/CPowerVisitor.h src/CPowerOperator.h
CModOperator.o: src/CModOperator.cpp src/CIntegerNumber.h src/./CNumber.h \
  src/CModOperator.h src/COperator.h src/CNumber.h
CMultiplyOperator.o: src/CMultiplyOperator.cpp src/CMultiplyOperator.h \
  src/COperator.h src/CNumber.h src/CIntegerNumber.h src/./CNumber.h \
  src/CDecimalNumber.h
CMultiplyVisitor.o: src/CMultiplyVisitor.cpp src/CMultiplyVisitor.h \
  src/CVisitor.h src/CIntegerNumber.h src/./CNumber.h \
  src/CDecimalNumber.h src/CNumber.h
CNumber.o: src/CNumber.cpp src/CNumber.h
COperator.o: src/COperator.cpp src/COperator.h src/CNumber.h
CParrenOperator.o: src/CParrenOperator.cpp src/CParrenOperator.h \
  src/COperator.h src/CNumber.h
CParsing.o: src/CParsing.cpp src/./CParsing.h src/./CNumber.h \
  src/./COperator.h src/CNumber.h src/./CVariables.h src/./CQueue.h \
  src/./CDecimalNumber.h src/CIntegerNumber.h src/./CIntegerNumber.h \
  src/CParrenOperator.h src/COperator.h src/CPowerOperator.h \
  src/CSubtractOperator.h src/CMultiplyOperator.h src/CDivideOperator.h \
  src/CAddOperator.h src/CFactOperator.h src/CRoundOperator.h \
  src/CModOperator.h
CPowerOperator.o: src/CPowerOperator.cpp src/CPowerOperator.h \
  src/COperator.h src/CNumber.h src/CMultiplyOperator.h \
  src/CIntegerNumber.h src/./CNumber.h src/CModOperator.h \
  src/CDecimalNumber.h
CPowerVisitor.o: src/CPowerVisitor.cpp src/CPowerVisitor.h src/CVisitor.h \
  src/CIntegerNumber.h src/./CNumber.h src/CDecimalNumber.h \
  src/CNumber.h
CQueue.o: src/CQueue.cpp src/./CQueue.h src/./CNumber.h src/./COperator.h \
  src/CNumber.h src/CParrenOperator.h src/COperator.h \
  src/CPowerOperator.h src/CSubtractOperator.h src/CMultiplyOperator.h \
  src/CDivideOperator.h src/CAddOperator.h src/CFactOperator.h \
  src/CModOperator.h src/CRoundOperator.h
CRoundOperator.o: src/CRoundOperator.cpp src/CRoundOperator.h \
  src/COperator.h src/CNumber.h
CSubtractOperator.o: src/CSubtractOperator.cpp src/CSubtractOperator.h \
  src/COperator.h src/CNumber.h src/CIntegerNumber.h src/./CNumber.h \
  src/CDecimalNumber.h
CSubtractVisitor.o: src/CSubtractVisitor.cpp src/CSubtractVisitor.h \
  src/CVisitor.h src/CIntegerNumber.h src/./CNumber.h \
  src/CDecimalNumber.h src/CNumber.h
CVariables.o: src/CVariables.cpp src/./CVariables.h src/./CNumber.h
CVisitor.o: src/CVisitor.cpp src/CVisitor.h src/CIntegerNumber.h \
  src/./CNumber.h src/CDecimalNumber.h src/CNumber.h
main.o: src/main.cpp src/./CCalculator.h src/./CNumber.h src/./CParsing.h \
  src/./COperator.h src/CNumber.h src/./CVariables.h src/./CQueue.h \
  src/./CIntegerNumber.h src/./CDecimalNumber.h src/CIntegerNumber.h
