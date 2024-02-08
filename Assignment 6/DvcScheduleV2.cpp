#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
#include "DynamicArray.h"
#include "StaticArray.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

#include <cstring> // for strtok and strcpy

struct subject {

    string subjectCode;
    int count;
};
struct SectionForTerm {

    string term;
    int numberOfSectionsSeen;
    DynamicArray<string> seenSectionNumber;
};

int main()
{
    cout << "Programmer: Anna Felipe" << endl;
    cout << "Programmer ID: 1506055" << endl;
    cout << "File: " << __FILE__ << endl;

    
    StaticArray<SectionForTerm, 100> alreadySeen;
    DynamicArray<subject> subjectCount(100);

    int count = 0;
    int duplicates = 0;
    int numberOfTerm = 0;
    int subjectIndex = 0;

    char* token;
    char buf[1000];
    const char* const tab = "\t";

    ifstream fin;
    fin.open("dvc-schedule.txt");
    if (!fin.good())
        cout << "I/O error. File can't find!\n";

    while (fin.good())
    {
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());

        if (buf[0] == 0) continue; // skip blank lines

        //parse the line
        const string term(token = strtok(buf, tab));
        const string section((token = strtok(0, tab)) ? token : "");
        const string course((token = strtok(0, tab)) ? token : "");
        const string instructor((token = strtok(0, tab)) ? token : "");
        const string whenWhere((token = strtok(0, tab)) ? token : "");
        
        if (course.find('-') == string::npos) 
            continue; // invalid line: no dash in course name

        const string subjectCode(course.begin(), course.begin() + course.find('-'));
        
        string classCode = term + "." + section;

        int i = 0, j = 0;
        bool d_check = false;

        for (i = 0; i < numberOfTerm; i++)
        {
            if (alreadySeen[i].term == term)
            {   
                count++;
                break;
            }
        }

        if (i == numberOfTerm)
        {
            alreadySeen[i] = { term, 1 };
            alreadySeen[i].seenSectionNumber[0] = section;
            numberOfTerm++;
        }
        else
        {
            for (j = 0; j < alreadySeen[i].numberOfSectionsSeen; j++)
            {
                if (alreadySeen[i].seenSectionNumber[j] == section)
                {
                    d_check = true;
                    duplicates++;
                    break;
                }
            }
            if (j == alreadySeen[i].numberOfSectionsSeen)
            {
                alreadySeen[i].seenSectionNumber[j] = section;
                alreadySeen[i].numberOfSectionsSeen++;
            }
        }
        if (d_check)
        continue;


        int s = 0;

        for (s = 0; s < subjectIndex; s++)
        {
            if (subjectCount[s].subjectCode == subjectCode)
            {
                subjectCount[s].count++;
                break;
            }
        }
        if (s == subjectIndex)
        {
            subjectCount[subjectIndex++] = { subjectCode, 1 };
        }
               
    }
    fin.close();

    cout << "Finish!" << endl;
    
    int asize = subjectIndex;
  for (int i = 0; i < asize; i++)
    for (int j = i + 1; j < asize; j++)
      if (subjectCount[j].subjectCode < subjectCount[i].subjectCode)
         swap(subjectCount[j], subjectCount[i]);

    for (int i = 0; i < asize; i++)
    {
        cout << subjectCount[i].subjectCode << ", " << subjectCount[i].count << " sections" << endl;
    }
    cout << "\n\nTotal duplications: " << duplicates << endl;
    cout << "Total counts: " << count << endl;
    cout << "Total subjects: " << subjectIndex << endl;
    return 0;
}  
