// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>

#include "../src/IR.h"
#include "../src/OPL.h"
#include "../src/PO.h"
#include "../src/helpers.h"

int main(int argc, char *argv[]) {
  //Setting up Variables
  std::string fileName, fileContent, electionType, line;
  std::fstream file;
  int candidateNum, seatNum, ballotNum = 0;
  std::vector<std::string> candidateNames, rawBallotInfo;
  VotingSystem *Aegis = nullptr;
  std::cout << "Prototype: Aegis 0.0" << std::endl;
  //If the arguments is less than 2, show current way to use.
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <file name>" << std::endl;
  }
  //If there are more than two arguments, then take in all the file arguments given.
  if (argc >= 2) {
    fileName = argv[1];
    file.open(fileName, std::ios::in);
    //Checking for the type of the election.
    if (!file.is_open()) {
      std::cout << "Couldn't open: " << fileName << std::endl;
    } else {
      getline(file, electionType);
      file >> candidateNum;
      getline(file, line);
      getline(file, line);
      if (electionType == "OPL") {
        candidateNames = extractOPLNames(line);
        file >> seatNum;
      }
      if (electionType == "IR") {
        candidateNames = extractIRNames(line);
        seatNum = 1;
      }
      if (electionType == "PO") {
        candidateNames = extractOPLNames(line);
        file >> ballotNum;
      }
      getline(file, line);
      //Same for IR and OPL, it just adds the information needed for that type of election.
      if (electionType == "OPL") {
        Aegis = new OPL(electionType, candidateNum, seatNum, ballotNum);
        for (auto it = candidateNames.begin(); it != candidateNames.end();
             it++) {
          char partyLetter = it->at(it->find(',') + 1);
          if (!Aegis->partyExists(partyLetter)) {
            Aegis->addParty(Party(partyLetter));
          }
          Aegis->addCandidate(
              Candidate(partyLetter, it->substr(0, it->find(','))));
        }
        file.close();
        for (int i = 1; i < argc; i++) {
          rawBallotInfo.clear();
          fileName = argv[i];
          file.open(fileName, std::ios::in);
          getline(file, line);
          getline(file, line);
          getline(file, line);
          getline(file, line);
          getline(file, line);
          Aegis->addNumBallots(std::stoi(line));

          while (getline(file, line)) {
            rawBallotInfo.push_back(line);
          }
          for (auto it = rawBallotInfo.begin(); it != rawBallotInfo.end();
               it++) {
            Aegis->getCandidates()
                .at(OPLBallotToIndex(*it))
                .addBallot(Ballot(BallotToVec(candidateNum, *it)));
          }
          file.close();
        }
        // Aegis->assignParty();
      }

      if (electionType == "IR") {
        Aegis = new IR(electionType, candidateNum, seatNum, ballotNum);
        for (auto it = candidateNames.begin(); it != candidateNames.end();
             it++) {
          std::string line = *it;
          char partyLetter = it->at(it->find('(') + 1);
          if (!Aegis->partyExists(partyLetter)) {
            Aegis->addParty(Party(partyLetter));
          }
          Aegis->addCandidate(
              Candidate(partyLetter, it->substr(0, it->find(' '))));
        }
        file.close();
        for (int i = 1; i < argc; i++) {
          rawBallotInfo.clear();
          fileName = argv[i];
          file.open(fileName, std::ios::in);
          getline(file, line);
          getline(file, line);
          getline(file, line);
          getline(file, line);
          Aegis->addNumBallots(std::stoi(line));

          while (getline(file, line)) {
            rawBallotInfo.push_back(line);
          }
          int numInvalidatedBallots = 0;
          for (auto it = rawBallotInfo.begin(); it != rawBallotInfo.end();
               it++) {
            std::vector<int> ballot_int_vector(
                IRBallotToVec(candidateNum, *it));
            if (ballot_int_vector.at((ballot_int_vector.size() + 1) / 2 - 1)) {
              Aegis->getCandidates()
                  .at(IRBallotToIndex(*it))
                  .addBallot(Ballot(ballot_int_vector));
            } else {
              numInvalidatedBallots++;
            }
          }
          Aegis->setNumBallots(Aegis->getNumBallots() - numInvalidatedBallots);
          file.close();
        }
      }

      if (electionType == "PO") {
        Aegis = new PO(candidateNum);
        for (auto it = candidateNames.begin(); it != candidateNames.end();
             it++) {
          std::string line = *it;
          char partyLetter = it->at(it->find(',') + 1);
          Aegis->addCandidate(
              Candidate(partyLetter, it->substr(0, it->find(','))));
        }
        file.close();
        for (int i = 1; i < argc; i++) {
          rawBallotInfo.clear();
          fileName = argv[i];
          file.open(fileName, std::ios::in);
          getline(file, line);
          getline(file, line);
          getline(file, line);
          getline(file, line);
          Aegis->addNumBallots(std::stoi(line));

          while (getline(file, line)) {
            rawBallotInfo.push_back(line);
          }
          for (auto it = rawBallotInfo.begin(); it != rawBallotInfo.end();
               it++) {
            Aegis->getCandidates()
                .at(OPLBallotToIndex(*it))
                .addBallot(Ballot(BallotToVec(candidateNum, *it)));
          }
          file.close();
        }
      }
      // printVec(rawBallotInfo);
      // std::vector<int> test2 = BallotToVec(candidateNum,
      // rawBallotInfo.at(0));

      // print out the index value of first ballet
      // std::cout << OPLBallotToIndex(rawBallotInfo.at(0)) << std::endl;

      // print to see what's in a ballot vector
      // printVecI(test2);

      //Prints out the party names.
      else {
        for (auto it = Aegis->getParties().begin();
             it != Aegis->getParties().end(); it++) {
          std::cout << it->getPartyName() << " ";
        }
        std::cout << std::endl;
        //Assigns the parties to the system.
        Aegis->assignParty();

      }
      /* std::vector<Party> newParties = Aegis->getParties();
      for (int i = 0; i < 4; i++) {
        Party thisParty = newParties[i];
        std::vector<Candidate *> thisCandidate =
            newParties[i].getPartyMembers();
        std::cout << thisCandidate[0]->getName() << std::endl;
      } */

      // parties are now set up
      Aegis->runElection();
      Aegis->displayResults();

      // std::cout << "Election Type: \t" << electionType << std::endl;
      // std::cout << "Number of Candidates: \t" << candidateNum << std::endl;
      // std::cout << "Names of Candidates:" << std::endl;
      // printVec(candidateNames);
      // std::cout << "Number of seats: \t" << seatNum << std::endl;
      // std::cout << "Number of ballots: \t" << ballotNum << std::endl;
      // std::cout << "Raw ballow info:" << std::endl;
      // printVec(rawBallotInfo);
    }

    if (Aegis != nullptr) {
      delete Aegis;
    }
    // TODO: close all files if needed
  }

  return 0;
}
