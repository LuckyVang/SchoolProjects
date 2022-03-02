// #include <fstream>
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <vector>

#include "../src/OPL.h"
#include "../src/IR.h"
#include "../src/helpers.h"

int main(int argc, char *argv[]) {
  std::string fileName, fileContent, electionType, line;
  std::fstream file;
  int candidateNum, seatNum, ballotNum;
  std::vector<std::string> candidateNames, rawBallotInfo;
  VotingSystem *Aegis = nullptr;
  std::cout << "Prototype: Aegis 0.0" << std::endl;

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " <file name>" << std::endl;
  }
  if (argc == 2) {
    fileName = argv[1];
    file.open(fileName, std::ios::in);

    if (!file.is_open()) {
      std::cout << "Couldn't open: " << fileName << std::endl;
    } else {
      getline(file, electionType);
      file >> candidateNum;
      getline(file, line);
      getline(file, line);
      if (electionType == "OPL") {
        candidateNames = extractOPLNames(line);
        file >> seatNum >> ballotNum;
      }
      if (electionType == "IR") {
        candidateNames = extractIRNames(line);
        seatNum = 1;
        file >> ballotNum;
      }
      getline(file, line);
      while (getline(file, line)) {
        rawBallotInfo.push_back(line);
      }

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
        for (auto it = rawBallotInfo.begin(); it != rawBallotInfo.end(); it++) {
          Aegis->getCandidates()
              .at(OPLBallotToIndex(*it))
              .addBallot(Ballot(BallotToVec(candidateNum, *it)));
        }
        //Aegis->assignParty();
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
        for (auto it = rawBallotInfo.begin(); it != rawBallotInfo.end(); it++) {
          Aegis->getCandidates()
              .at(IRBallotToIndex(*it))
              .addBallot(Ballot(IRBallotToVec(candidateNum, *it)));
        }
      }
      // printVec(rawBallotInfo);
      // std::vector<int> test2 = BallotToVec(candidateNum, rawBallotInfo.at(0));

      // print out the index value of first ballet
      // std::cout << OPLBallotToIndex(rawBallotInfo.at(0)) << std::endl;

      // print to see what's in a ballot vector
      // printVecI(test2);

      for (auto it = Aegis->getParties().begin();
           it != Aegis->getParties().end(); it++) {
        std::cout << it->getPartyName() << " ";
      }
      std::cout << std::endl;

      Aegis->assignParty();
      /* std::vector<Party> newParties = Aegis->getParties();
      for (int i = 0; i < 4; i++) {
        Party thisParty = newParties[i];
        std::vector<Candidate *> thisCandidate =
            newParties[i].getPartyMembers();
        std::cout << thisCandidate[0]->getName() << std::endl;
      } */

      //parties are now set up
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

    file.close();
  }

  return 0;
}
