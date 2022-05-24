/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!

    string alltext = file_to_string(filename); //contains the entire string prior to manipulation.
    //vector<vector<string>> data; //to hold the final information

    //step 1: sort the number of rows of data 
    //char ch = '/n'; //the character each row is split by in the main text
    vector<string> rowvector; //to hold the rows of strings
    int num_rows = SplitString(alltext, '\n', rowvector); 
    
    V2D data(num_rows); //to hold the final information
    //step 2: traverse through each row and use ',' as a separator for each column val
    //ch = ',';
    for (unsigned i = 0; i < rowvector.size(); i++) { //goes through each row of info
      //for each row we must figure out num of column / inputs separated by csv, and then push those into 
      int num_cols = SplitString(rowvector[i], ',', data[i]);
      for (unsigned j = 0; j < data[i].size(); j++) {
        data[i][j] = Trim(data[i][j]);
      }
    }
    
    // for (unsigned i=0; i<data.size(); i++) {
    //   for (unsigned j=0; j<data[i].size(); j++) {
    //     cout << data[i][j] << " ";
    //   }
    //   cout << std::endl;
    // }
    // return data;

    return data;

}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(V2D & cv, V2D & student){
    // YOUR CODE HERE

    V2D finalval; //to return final corrected roster
    //cv - course, students
    //student - students, courses

    //i, j for cv traversal
    //a, b for student traversal
    
    for (unsigned i = 0; i < cv.size(); i++) { //go through rows of cv file]
    vector<string> innervecforstudents;
      int chkfirst = 0; //to check if it is the first student in the course
     
      string currcourse = cv[i][0]; // check if the students have this course in their list
      for (unsigned j = 1; j < cv[i].size(); j++) { //goes through the cols of the cv file

        int studfound = 0;
        for (unsigned a = 0; a < student.size(); a++) {
        
            //find the student we are trying to check
            if (student[a][0] == cv[i][j]) { //if we found the student in the stud roster
                //we must now see if they have the same courses or not
                for (unsigned b = 1; b < student[a].size(); b++) {
                  
                  if (currcourse == student[a][b]) { //if the student has the course we are searching for
                    studfound = 1;
                    if (chkfirst == 0) {
                      innervecforstudents.push_back(currcourse); //the course has not been initialized until we found a match
                      chkfirst = 1;
                    }
                    innervecforstudents.push_back(student[a][0]);
                    break;
                  }
                } //exit of col trav for stud
                if (studfound == 1)
                  break; //check for next student in that course
            }
        } //exit of row trav for stud

      } // end of col trav for cv
      if (innervecforstudents.empty() == 0)
        finalval.push_back(innervecforstudents);
    } // end of row trav for cv

  return finalval;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(V2D courses, std::vector<std::string> timeslots){
    // Your code here!

    if (courses.size() == 0) {
      V2D empt(1);
      empt[0].push_back("-1");
      return empt;
    }

    vector<vector<int>> adjmatrix; //creates a 2d vector that holds int but with the same num of rows as courses
    vector<int> temp(courses.size(), 0);
    for (unsigned a = 0; a < courses.size(); a++)
      adjmatrix.push_back(temp); //created a matrix which is sized as courses x courses
    for (unsigned i = 0; i < courses.size(); i++) { //goes through the rows of the courses file
      ////cout << "i = " << i << " ";
      for (unsigned j = 1; j < courses[i].size(); j++) { //goes through students of current row
        ////cout << "j = " << j << " ";
        for (unsigned k = i+1; k < courses.size(); k++) { //this goes through the next rows of classes to compare to first row
          ////cout << "k = " << k << " ";
          for (unsigned l = 1; l < courses[k].size(); l++) { //this goes through the students (cols) of the next row to check
            ////cout << "l = " << l << endl;
            if (courses[i][j]== courses[k][l]) {
              ////cout << "courses[i][j] " << courses[i][j] << " = " << "courses[k][l] " << courses[k][l] << endl;
              adjmatrix[i][k] = 1;
              adjmatrix[k][i] = 1;
              break; //escapes to k loop
            } //end of checker
          } //end of next student loop (l)
        } //end of next student row (k)
      } //end of curr student loop (j)
    } //end of curr class row (i)
   
     //printing the adjacency matrix
    /** 
    for (unsigned a = 0; a < adjmatrix.size(); a++) {
      for (unsigned b = 0; b < adjmatrix[a].size(); b++) {
        cout << adjmatrix[a][b] << " ";
      }
      cout << endl;
    }*/


    vector<int> startingnodecolorset;
    int avail = 0;

    for (unsigned w = 0; w < adjmatrix.size(); w++) {
      
      vector<int> currentheadcoloring;

      for (unsigned i = 0; i < adjmatrix.size(); i++) { //this goes through all the vertices
      unsigned i_curr = ( (i + w) % (adjmatrix.size()) );
      // cout << "i = " << i << " ";
      vector<int> relevantverticescolors;
        for (unsigned j = 0; j < i ; j++) { //this goes through from first vertice to current one
          unsigned j_curr = ( (j + w) % (adjmatrix.size()) );
          // cout << "j = " << j << " ";
          if (adjmatrix[i_curr][j_curr] == 1) {
            relevantverticescolors.push_back(currentheadcoloring[j]);
          }
        }
        int highestnum = 0;
        //this just goes through to find the total numberof colors used now
        for (unsigned a = 0; a < relevantverticescolors.size(); a++) {
          for (unsigned b = 0; b < relevantverticescolors.size(); b++) {
            if (relevantverticescolors[b] == highestnum)
              highestnum = relevantverticescolors[b]+1;
          }
        }
        currentheadcoloring.push_back(highestnum);
      }
      
      unsigned numofcolorsneeded = 0;

      //cout << "printing the current coloring method / checking for num of colors: " << endl;
      for (unsigned i = 0; i < currentheadcoloring.size(); i++) {
        //cout << currentheadcoloring[i] << " ";
        if ((int)numofcolorsneeded < currentheadcoloring[i])
          numofcolorsneeded = currentheadcoloring[i];
      }
      //cout << "Number of colors used: " << (numofcolorsneeded + 1) << endl;


      V2D answer;
      for (unsigned i = 0; i < timeslots.size(); i++) {
        vector<string> temp;
        temp.push_back(timeslots[i]);
        for (unsigned j = 0; j < currentheadcoloring.size(); j++) {
          int tempint = i;
          if (currentheadcoloring[j] == tempint) {
            temp.push_back(courses[((j + w) % courses.size())][0]);
            //temp.push_back(courses[j][0]);
          }
        }
        answer.push_back(temp);
      }

      //Printing out the answer matrix
      /** 
      cout << "Answer for the matrix starting with " << w << endl;
      for (unsigned a = 0; a < answer.size(); a++) {
        for (unsigned b = 0; b < answer[a].size(); b++) {
          cout << answer[a][b] << " ";
        }
        cout << endl;
      }
      */

      //in case the slots available are enough for coloring, we return the vector answer.
      if (timeslots.size() >= (numofcolorsneeded+1)) {
        avail = 1;
        return answer;
      }

    }

    //in case the slots available are not enough for coloring, we must return a -1 vector.
    
      V2D temporar(1);
      temporar[0].push_back("-1");
      return temporar;
    
}