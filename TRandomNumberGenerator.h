#pragma once

class TRandomNumberGenerator {
public:
	virtual ~TRandomNumberGenerator() {};
	virtual double Generate() const = 0;
};