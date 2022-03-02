/**
 * @file Party.h
 *
 * @copyright 2021 Aegis, All rights reserved.
 */

#ifndef PARTY_H
#define PARTY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>

#include "../src/Candidate.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class representing Parties, who will be filled with Candidates based
 * on their party.
 */
class Party {
 public:
  /**
   * @brief Party constructor that takes in only the party name.
   *
   * @param p, determines the Party's name and who can be in it.
   */
  Party(char p);

  /**
   * @brief Method to return the name of the Party.
   *
   * @return Returns the Party's letter.
   */
  char getPartyName();

  /**
   * @brief Method to return the number of Ballots that belong to the Party.
   *
   * @return Returns the number of ballots.
   */
  int getNumBallots();
  /**
   * @brief Method to return the variable numBallots that belong to the Party.
   * Used for testing purposes.
   *
   * @return Returns the variable numBallots.
   */
  int getVariableNumBallots() { return numBallots; }

  /**
   * @brief Method to return the number of seats the Party has won.
   *
   * @return Returns the number of seats won.
   */
  int getSeatsWon();

  /**
   * @brief Method to return the remainder of votes after the number of votes
   * has been divided by quota.
   *
   * @return Returns the number of votes.
   */
  int getRemainder();

  /**
   * @brief Method to get the vector of members within the party.
   *
   * @return Returns the vector of members within the party.
   */
  std::vector<Candidate *> getPartyMembers();
  /**
   * @brief Sorts partyMembers vector by the number of votes each candidate has
   * from most to least.
   */
  void sortByVotes();
  /**
   * @brief Sets the number of ballots the Candidate has assigned to them
   *
   * @param num, Sets the number of ballots equal to this.
   */
  void setNumBallots(int num);
  /**
   * @brief Method to set the number of seats won by the party.
   *
   * @param seats, represents the number of seats won by the party.
   */
  void setSeatsWon(int seats);
  /**
   * @brief Method to set the remainder of votes.
   *
   * @param num, represents the number of votes remaining after the number of
   * votes has been divided by quota.
   */
  void setRemainder(int num);
  /**
   * @brief Method to add a Candidate to the vector of candidates.
   *
   * @param candidate, represents the Candidate to be added to the partyMembers
   * vector.
   */
  void addCandidate(Candidate *candidate);
  /**
   * @brief Overload operator for equality between two Party's names.
   *
   * @param r, represents the Party to compare "this" to.
   *
   * @return Returns true or false to represent if the two Party instances
   * had the same name.
   */
  bool operator==(Party &r);

 private:
  char name;      ///< A char representing the name of the party.
  int seatsWon;   ///< An integer representing the total number of seats won by
                  ///< the party.
  int remainder;  ///< An integer representing the remainder of votes after the
  ///< number ofvotes has been divided by quota.
  std::vector<Candidate *>
      partyMembers;  ///< A vector of Candidate pointers representing the
  ///< members that make up the party.
  int numBallots;  ///< An integer representing the number of ballots the
                   ///< Candidate has assigned to them.
};

#endif