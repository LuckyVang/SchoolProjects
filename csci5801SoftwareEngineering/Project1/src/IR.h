/**
 * @file IR.h
 *
 * @copyright 2021 Aegis, All rights reserved.
 */

#ifndef IR_H
#define IR_H
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "../src/VotingSystem.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class representing the IR Voting System, used to run an IR
 * election results.
 *
 */
class IR : public VotingSystem {
 public:
  /**
   * @brief Empty constructor for the IR election.
   *

  */
  IR(std::string type, int candidates, int seats, int ballots);
  /**
   * @brief Attempts to find a winner in the IR election.
   *
   */
  void findWinner();
  /**
   * @brief Eliminates a candidate.
   *
   * Recieves the candidate with the lowest ballots and redistributes their
   * ballots
   *
   * @return void.
   */
  void elimination();

  /**
   * @brief Returns a candidate after tie.
   *
   * Takes in two candidates that are "tied" and randomly decides one to remove.
   *
   * @return Candidate that won the tie breaker.
   */

  Candidate* breakTie(Candidate *a, Candidate *b);

  /**
   * @brief virtual function to handle election program.
   */

  virtual void runElection();

  /**
   * @brief virtual function to display results of election.
   */

  virtual void displayResults();

  /**
   * @brief prints out information about candidates for debugging purposes.
   */

  void printCandidateInfo();
  /**
   * @brief checks if only one candidate is left in the running. If so, that
   * candidate is declared the winner.
   *
   */

  void checkIfOneCand();
  /**
   * @brief Sets elim to the passed in Candidate candidate
   *
   * @param candidate, sets elim equal to this.
   *
   */
  void setElim(Candidate* candidate) { elim = candidate; }
  /**
   * @brief Method to get the elim Candidate.
   *
   * @return Returns the elim candidate.
   */
  Candidate* getElim() { return elim; }

 private:
  Candidate* elim;  ///< Holds the current candidate to be eliminated.
};

#endif