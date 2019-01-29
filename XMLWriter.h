#pragma once
#ifndef XmlWriter_H
#define XmlWriter_H
#include<iostream>
#include<fstream>
#include<string>
#include <vector>
using namespace std;
class XMLWriter
{
	ofstream outFile;
	int indent;
	int openTags;
	int openElements;
	vector<string> tempOpenTag;
	vector<string> tempElementTag;
public:
	
	bool open(const string);
	void close();
	bool exists(const string);
	void writeOpenTag(const string);
	void writeCloseTag();
	void writeStartElementTag(const string);
	void writeEndElementTag();
	void writeAttribute(const string);
	void writeString(const string);
	void write_endl();
};
#endif

