/** \addtogroup helpers
 *  @{
 */
/** @file helpers.h
 *
 *   @copyright 2021 Aegis, All rights reserved.
 */

#ifndef HELPERS_H
#define HELPERS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Returns an int that is the index representation of a candidate from an
 * OPL ballot.
 *
 * @param ballot a string that represents ballot information.
 *
 * @return int index of ballot choice.
 */
int OPLBallotToIndex(std::string ballot);

/**
 * @brief Returns an in that is the index representation of a candidate from an
 * IR ballot.
 *
 * @param ballot a string that represents ballot information.
 *
 * @return int index of first choice.
 */
int IRBallotToIndex(std::string ballot);

/**
 * @brief Returns a vector that represents an OPL ballot.
 *
 * @param num the size of the vector, or the number of candidates.
 * @param ballot a string that represents ballot information.
 *
 * @return vector representing any ballot.
 */
std::vector<int> BallotToVec(int num, std::string ballot);

/**
 * @brief Returns a vector that represents an IR ballot.
 *
 * @param num the size of the vector, or the number of candidates.
 * @param ballot a string that represents ballot information.
 *
 * @return vector representing specifically an IR ballot.
 */
std::vector<int> IRBallotToVec(int num, std::string ballot);

/**
 * @brief Parse and pop a string between the first occurence of two symbols l
 * and r.
 *
 * @param line the string to be parsed
 * @param l the left symbol
 * @param r the right symbol
 *
 * @return string the substring  that is popped from line.
 */
std::string popItem(std::string &line, char l, char r);

/**
 * @brief Parse a line and create a vector of names and party from an OPL file.
 *
 * @param line the string containing candidate names.
 *
 * @return vector that contains the candidate name and party info.
 */
std::vector<std::string> extractOPLNames(std::string line);

/**
 * @brief Parse a line and create a vector of names and party from an IR file.
 *
 * @param line the string containing candidate names.
 *
 * @return vector that contains the candidate name and party info.
 */
std::vector<std::string> extractIRNames(std::string line);

/**
 * @brief print the elements in a string vector
 *
 * @return void
 */
void printVec(std::vector<std::string> vec);

/**
 * @brief print the elements in an int vector
 *
 * @return void
 */
void printVecI(std::vector<int> vec);

/** @}*/
#endif