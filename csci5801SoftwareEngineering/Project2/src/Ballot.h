/**
 * @file Ballot.h
 *
 * @copyright 2021 Aegis, All rights reserved.
 */

#ifndef BALLOT_H
#define BALLOT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <iostream>
#include <vector>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class representing Ballots, who will be assigned to Candidates based
 * on their top vote.
 */
class Ballot {
 public:
  /**
   * @brief Default constructor. Takes in only a vector of ints representing
   * ranked choices and assigns it to candidates.
   *
   * @param v1, vector of ints representing ranked chocies. Assigned to
   * candidates.
   */
  Ballot(std::vector<int> v1);

  Ballot(const Ballot& b);

  /**
   * @brief Increments currBallot pointer to next value in the candidates
   * vector.
   */
  void incrCurrent();
  /**
   * @brief Overload operator for comparisons between Ballot's candidate
   * vectors.
   *
   * @param r, represents the Ballot to compare "this" to.
   *
   * @return Returns true or false to represent if Ballots are equal to one
   * another
   */
  bool operator==(Ballot& r);

  /**
   * @brief Method to return candidates vector.
   *
   * @return Returns the vector of candidates.
   */
  std::vector<int> getCandidates();
  /**
   * @brief Method to get the current ballot index required to identify the
   * candidate the ballot currently belongs to.
   *
   * @return Returns the current ballot index.
   */
  int getCurrBallotIndex();
  /**
   * @brief Method to get the current the index that currBallot is pointing to
   * in candidates. Used for debugging.
   *
   * @return Returns currBallot
   */
  int getCurrBallot();
  /**
   * @brief Prints out candidates vector for debugging purposes.
   */
  void printBallot(std::ostream &os);

 private:
  std::vector<int> candidates;  ///< A vector of ints representing the order in
                                ///< which the ballot favors candidates.
  int currBallot =
      0;  ///< An integer representing which candidate the ballot is currently
          ///< voting for. Starts at 0 and only increments by 1.
};

#endif
