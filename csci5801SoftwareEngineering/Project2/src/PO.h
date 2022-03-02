/**
 * @file PO.h
 *
 * @copyright 2021 Aegis, All rights reserved.
 */


#ifndef PO_H
#define PO_H
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "../src/Party.h"
#include "../src/VotingSystem.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

/**
 * @brief A class representing the PO Voting System, used to run an PO
 * election results.
 *
 */
class PO : public VotingSystem {
  public:

  /**
   * @brief Constructor for PO. Sets number of candidates, and number of ballots.
   */

  PO(int candidates);
  /**
   * @brief Runs the PO based election.
   *
   * Runs all of the methods needed to run a PO election.
   *
   * @return void.
   */

  void runElection();


  /**
   * @brief Prints the results of the election.
   *
   * Displays all the information an election official would need in an
   * election. Such information includes: Number of Ballots, Winners, Losers
   * and Election Type
   *
   * @return void.
   */
  void displayResults();
  void breakTie();
};

#endif