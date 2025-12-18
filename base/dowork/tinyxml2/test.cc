#include <iostream>
#include "tinyxml2.h"
#include <string>
#include <regex>


using namespace tinyxml2;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::regex;
using std::replace;


void test(){

    XMLDocument doc;
	doc.LoadFile( "coolshell.xml" );

    if(doc.ErrorID()){
        cerr << "LoadFile error" << endl;  
    }

	XMLElement* itemNode = doc.FirstChildElement( "rss" )->FirstChildElement( "channel" )->FirstChildElement( "item" );

	while(itemNode){
        string title = itemNode->FirstChildElement( "title" )->GetText();
        string link = itemNode->FirstChildElement( "link" )->GetText();
        string description = itemNode->FirstChildElement( "description" )->GetText();
        string content = itemNode->FirstChildElement( "content:encoded" )->GetText();

        //cout << "title : " << title << endl;
        //cout << "link : " << link << endl;
        //cout << "description : " << description << endl;
        //cout << "content : " << content << endl;

        regex regex("<[^>]*>");
        description = regex_replace(description, regex, "");
        content = regex_replace(content, regex, "");
        cout << "***********************************************" << endl;
        cout << "description : " << description << endl;
        cout << "content : " << content << endl;

        itemNode = itemNode->NextSiblingElement("item");
    }

}


int main(int argc, char *argv[]){

    test();
}