#pragma once
enum processState // https://www.youtube.com/watch?v=BjWKfvjV5mA -- enum concept
	//enum or enumeration is a data type consisting of named values 
	// like elements, members, etc., that represent integral constants. 
	// It provides a way to define and group integral constants. 
	//It also makes the code easy to maintain and less complex.
{
	BLK, //0
	NEW, //1
	RDY, //2
	ORPH, //3
	RUN, //4
	TRM //5
};