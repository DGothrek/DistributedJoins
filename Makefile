all: testRelation

Relation.o: Relation.cpp Relation.h
	g++ -c Relation.cpp -o Relation.o

testRelation: Relation.o testRelation.cpp
	g++ testRelation.cpp -o testRelation

testDistributedRelation: DistributedRelation.o testDistributedRelation.cpp
	mpic++ testDistributedRelation.cpp -o testDistributedRelation
