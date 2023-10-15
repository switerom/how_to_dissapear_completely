#pragma once

// Сделать синглтоном потом, если получится
class KeyGen
{
public:
	static int getKey() { return ++_counter; };	// возможно приписать условие, что он не может возвращать 0(хоть это вредли произойдет)
private:
	static int _counter;
};

