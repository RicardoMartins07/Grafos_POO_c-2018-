#include "XMLWriter.h"


bool XMLWriter::exists(const string fileName) {
	std::fstream checkFile(fileName);
	return checkFile.is_open();
}

bool XMLWriter::open(const string strFile) {

	if (exists(strFile)) {
		cout << "Erro: Ficheiro ja existe\n";
		return false;
	}

	outFile.open(strFile);
	if (outFile.is_open()) {
		outFile << "<!--XML Document-->\n";
		outFile << "<?xml version='1.0' encoding='us-ascii'>\n";
		indent = 0;
		openTags = 0;
		openElements = 0;
		return true;
	}

	return false;
}

void XMLWriter::close() {
	if (outFile.is_open()) {
		outFile.close();
	}
	else {
		std::cout << "Ficheiro encontra-se fechado\n";
	}

}

void XMLWriter::writeOpenTag(const string openTag) {
	if (outFile.is_open()) {
		/*for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}*/
		tempOpenTag.resize(openTags + 1);
		outFile << "<" << openTag << ">\n";
		tempOpenTag[openTags] = openTag;
		indent += 1;
		openTags += 1;
	}
	else {
		std::cout << "Erro\n";
	}
}

void XMLWriter::writeCloseTag() {
	if (outFile.is_open()) {
		/*indent -= 1;
		for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}*/
		outFile << "</" << tempOpenTag[openTags - 1] << ">\n";
		tempOpenTag.resize(openTags - 1);
		openTags -= 1;
	}
	else {
		std::cout << "Erro\n";
	}
}

void XMLWriter::writeStartElementTag(const string elementTag) {
	if (outFile.is_open()) {
		/*for (int i = 0; i < indent; i++) {
			outFile << "\t";
		}*/
		tempElementTag.resize(openElements + 1);
		tempElementTag[openElements] = elementTag;
		openElements += 1;
		outFile << "<" << elementTag;
	}
	else {
		cout << "Erro\n";
	}
}

void XMLWriter::writeEndElementTag() {
	if (outFile.is_open()) {
		outFile << "\n</" << tempElementTag[openElements - 1] << ">\n";
		tempElementTag.resize(openElements - 1);
		openElements -= 1;
	}
	else {
		cout << "Erro\n";
	}
}

void XMLWriter::writeAttribute(const string outAttribute) {
	if (outFile.is_open()) {
		outFile << " " << outAttribute;
	}
	else {
		cout << "Erro\n";
	}
}


void XMLWriter::writeString(const string outString) {
	if (outFile.is_open()) {
		outFile << ">\n" << outString;
	}
	else {
		cout << "Erro\n";
	}
}

void XMLWriter::write_endl()
{
	if (outFile.is_open()) {
		outFile << endl;
	}
	else {
		cout << "Erro\n";
	}
}
