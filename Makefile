all: testRelation

testRelation: Relation.cpp Relation.h
	g++ -c Relation.cpp -o testRelation
