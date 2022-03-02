#include "../src/VotingSystem.h"

/* VotingSystem::VotingSystem(std::string type, int candidates, int seats,
                           int ballots)
    : electionType(type),
      numCandidates(candidates),
      numSeats(seats),
      numBallots(ballots) {}
 */
int VotingSystem::getNumBallots() { return numBallots; }

double VotingSystem::getTimeTaken() { return 0; }

void VotingSystem::runElection() {
  std::sort(candidates.begin(), candidates.end());
  std::reverse(candidates.begin(), candidates.end());
  displayResults();
}

void VotingSystem::displayResults() {}



void VotingSystem::makeAuditFile() {
  std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
  std::chrono::system_clock::duration dtn = tp.time_since_epoch();
  auditfilename = "Audit" + std::to_string(dtn.count()) + ".txt";

  auditFile.open(auditfilename);
  auditFile.close();
}

void VotingSystem::writeToAuditFile(std::string string) {
  auditFile.open(auditfilename, std::ios::app);
  auditFile << string << std::endl;
  auditFile.close();  
}

void VotingSystem::makeMediaFile() {
  std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
  std::chrono::system_clock::duration dtn = tp.time_since_epoch();
  mediafilename = "Media" + std::to_string(dtn.count()) + ".txt";
  mediaFile.open(mediafilename);
  mediaFile.close();
}

void VotingSystem::writeToMediaFile(std::string string) {
  mediaFile.open(mediafilename, std::ios::app);
  mediaFile << string << std::endl;
  mediaFile.close();  
}

void VotingSystem::addCandidate(Candidate candidate) {
  candidates.push_back(candidate);
}

void VotingSystem::addWinners(Candidate candidate) {
  winners.push_back(candidate);
}

void VotingSystem::addLosers(Candidate candidate) {
  losers.push_back(candidate);
}

void VotingSystem::addParty(Party party) { parties.push_back(party); }

std::vector<Candidate> &VotingSystem::getCandidates() { return candidates; }

std::vector<Party> &VotingSystem::getParties() { return parties; }

bool VotingSystem::partyExists(char party) {
  for (Party curr : parties) {
    // std::cout << "partyExists Parties: " << parties[0].getPartyName() <<
    // std::endl; for (int i = 0; i < parties.size(); i++) {
    if (curr.getPartyName() == party) {
      return true;
    }
  }
  return false;
}

void VotingSystem::assignParty() {
  for (int i = 0; i < parties.size(); i++) {
    for (int j = 0; j < candidates.size(); j++) {
      if (parties[i].getPartyName() == candidates[j].getParty()) {
        parties[i].addCandidate(
            &candidates[j]);  // If the party names (char) are the same
      }
    }
  }
}
