#include <vector>

#include "../src/OPL.cpp"
#include "gtest/gtest.h"
class OPLTest : public ::testing::Test {
 public:
  OPLTest() {}

  void SetUp() {
    // numCandidates = 6; // 3D, 2R, 1I
    // numSeats = 4;
    // numBallots = 20;

    opl = new OPL("OPL", 6, 4, 20);

    Candidate *Derrick, *Derrick2, *Derrick3;
    Candidate *Ryan, *Ryan2;
    Candidate *Ian;

    Derrick = new Candidate('D', "Derrick");
    Derrick2 = new Candidate('D', "Derrick2");
    Derrick3 = new Candidate('D', "Derrick3");
    Ryan = new Candidate('R', "Ryan");
    Ryan2 = new Candidate('R', "Ryan2");
    Ian = new Candidate('I', "Ian");

    Ballot b1(std::vector<int>{1, 0, 0});
    for (int i = 0; i < 5; i++) {  // give 5 ballots to Derrick
      Derrick->addBallot(b1);
    }
    for (int i = 0; i < 2; i++) {  // give 2 ballots to Derrick2
      Derrick2->addBallot(b1);
    }
    for (int i = 0; i < 3; i++) {  // give 3 ballots to Derrick3
      Derrick3->addBallot(b1);
    }
    for (int i = 0; i < 4; i++) {  // give 4 ballots to Ryan
      Ryan->addBallot(b1);
    }
    for (int i = 0; i < 4; i++) {  // give 4 ballots to Ryan2
      Ryan2->addBallot(b1);
    }
    for (int i = 0; i < 2; i++) {  // give 2 ballots to Ian
      Ian->addBallot(b1);
    }

    Party D('D');  // owns 10 ballots, r0
    Party R('R');  // owns 8 ballots, r3
    Party I('I');  // owns 2 ballots, r2

    D.addCandidate(Derrick);
    D.addCandidate(Derrick2);
    D.addCandidate(Derrick3);
    R.addCandidate(Ryan);
    R.addCandidate(Ryan2);
    I.addCandidate(Ian);

    D.setRemainder(0);
    R.setRemainder(3);
    I.setRemainder(2);

    std::vector<Party> parties{D, R, I};

    opl->setQuota(5);
    opl->setParties(parties);
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to throw exceptions from here if need be
  }

  ~OPLTest() {
    // cleanup any pending stuff, but no exceptions allowed
  }
  OPL *opl;
};

TEST_F(OPLTest, sortByVotes) {  // already in sorted order
  std::vector<Party> partiesOriginal = opl->getParties();  // 10, 8, 2
  std::vector<Party> partiesOrdered = partiesOriginal;
  opl->setParties(partiesOrdered);
  opl->sortByVotes();

  for (int i = 0; i < partiesOriginal.size(); i++) {
    EXPECT_EQ(opl->getParties().at(i).getPartyName(),
              partiesOrdered.at(i).getPartyName())
        << "sortByVotes: party vector isn't sorted correctly";
  }
}

TEST_F(OPLTest, sortByVotesReverse) {  // already in reverse sorted order
  std::vector<Party> partiesOriginal = opl->getParties();  // 10, 8, 2
  std::vector<Party> reverseParties;
  reverseParties.push_back(partiesOriginal.at(2));
  reverseParties.push_back(partiesOriginal.at(1));
  reverseParties.push_back(partiesOriginal.at(0));
  opl->setParties(reverseParties);
  opl->sortByVotes();

  for (int i = 0; i < partiesOriginal.size(); i++) {
    EXPECT_EQ(opl->getParties().at(i).getPartyName(),
              partiesOriginal.at(i).getPartyName())
        << "sortByVotesReverse: party vector isn't sorted correctly";
  }
}

TEST_F(OPLTest, sortByRemainder) {                         // general case
  std::vector<Party> partiesOriginal = opl->getParties();  // 0,3,2
  std::vector<Party> partiesOrdered;
  partiesOrdered.push_back(partiesOriginal.at(1));
  partiesOrdered.push_back(partiesOriginal.at(2));
  partiesOrdered.push_back(partiesOriginal.at(0));
  opl->sortByRemainder();

  for (int i = 0; i < partiesOriginal.size(); i++) {
    EXPECT_EQ(opl->getParties().at(i).getRemainder(),
              partiesOrdered.at(i).getRemainder())
        << "sortByRemainder: party vector isn't sorted correctly";
  }
}

TEST_F(OPLTest, sortByRemainderOrdered) {  // already in sorted order
  std::vector<Party> partiesOriginal = opl->getParties();  // 0,3,2
  std::vector<Party> partiesOrdered;
  partiesOrdered.push_back(partiesOriginal.at(1));
  partiesOrdered.push_back(partiesOriginal.at(2));
  partiesOrdered.push_back(partiesOriginal.at(0));
  opl->setParties(partiesOrdered);
  opl->sortByRemainder();

  for (int i = 0; i < partiesOriginal.size(); i++) {
    EXPECT_EQ(opl->getParties().at(i).getRemainder(),
              partiesOrdered.at(i).getRemainder())
        << "sortByRemainder: party vector isn't sorted correctly";
  }
}

TEST_F(OPLTest, sortByRemainderReverse) {  // already in reverse sorted order
  std::vector<Party> partiesOriginal = opl->getParties();  // 0,3,2
  std::vector<Party> partiesReverse;
  std::vector<Party> partiesOrdered;
  partiesReverse.push_back(partiesOriginal.at(0));
  partiesReverse.push_back(partiesOriginal.at(2));
  partiesReverse.push_back(partiesOriginal.at(1));

  partiesOrdered.push_back(partiesOriginal.at(1));
  partiesOrdered.push_back(partiesOriginal.at(2));
  partiesOrdered.push_back(partiesOriginal.at(0));

  opl->setParties(partiesReverse);
  opl->sortByRemainder();

  for (int i = 0; i < partiesOriginal.size(); i++) {
    EXPECT_EQ(opl->getParties().at(i).getRemainder(),
              partiesOrdered.at(i).getRemainder())
        << "sortByRemainder: party vector isn't sorted correctly";
  }
}

TEST_F(OPLTest, allocateSeatsAllSeatsToOneParty) {
  // 89, 8, 2;; ballots = 100; quota = 25; seats = 3;
  // D = 4, R = 0; I = 0;
  // tests for all seats going to one party
  Ballot b1(std::vector<int>{1, 0, 0});
  for (int i = 0; i < 79; i++) {  // add 80 ballots to Derrick
    opl->getParties().at(0).getPartyMembers().at(0)->addBallot(b1);
  }
  opl->setNumSeats(3);
  opl->setQuota(25);
  opl->allocateSeats();
  std::vector<Party> partiesOriginal = opl->getParties();

  EXPECT_EQ(partiesOriginal.at(0).getSeatsWon(), 0)
      << "allocateSeatsAllSeatsToOneParty: Party R should've won 0 seats";  // Party R after sorting
  EXPECT_EQ(partiesOriginal.at(1).getSeatsWon(), 0)
      << "allocateSeatsAllSeatsToOneParty: Party I should've won 0 seats";  // Party I after sorting
  EXPECT_EQ(partiesOriginal.at(2).getSeatsWon(), 3)
      << "allocateSeatsAllSeatsToOneParty: Party D should've won 3 seats";  // Party D after sorting
}

TEST_F(OPLTest, allocateSeatsPartyMembersGreaterThanSeats) {
  // 10, 8, 2;; quota = 5; seats = 4
  // D = 2, R = 2; I = 0;
  // tests the condition if the party has more candidates than seats their party
  // has earned
  opl->allocateSeats();
  std::vector<Party> partiesOriginal = opl->getParties();

  EXPECT_EQ(partiesOriginal.at(0).getSeatsWon(), 2)
      << "allocateSeatsPartyMembersGreaterThanSeats: Party R should've won 2 "
         "seats";  // Party R after sorting
  EXPECT_EQ(partiesOriginal.at(1).getSeatsWon(), 0)
      << "allocateSeatsPartyMembersGreaterThanSeats: Party I should've won 0 "
         "seats";  // Party I after sorting
  EXPECT_EQ(partiesOriginal.at(2).getSeatsWon(), 2)
      << "allocateSeatsPartyMembersGreaterThanSeats: Party D should've won 2 "
         "seats";  // Party D after sorting
}

TEST_F(OPLTest, allocateSeatsPartyMembersEqualSeats) {
  // 90, 8, 2;; ballots = 100; quota = 25; seats = 4
  // D = 3, R = 1; I = 0;
  // tests the condition if the party has less candidates than earned seats
  opl->setQuota(25);

  Ballot b1(std::vector<int>{1, 0, 0});
  for (int i = 0; i < 80; i++) {  // add 80 ballots to Derrick
    opl->getParties().at(0).getPartyMembers().at(0)->addBallot(b1);
  }
  opl->allocateSeats();
  std::vector<Party> partiesOriginal = opl->getParties();

  EXPECT_EQ(partiesOriginal.at(0).getSeatsWon(), 1)
      << "allocateSeatsPartyMembersEqualSeats: Party R should've won 1 seats";  // Party R after sorting
  EXPECT_EQ(partiesOriginal.at(1).getSeatsWon(), 0)
      << "allocateSeatsPartyMembersEqualSeats: Party I should've won 0 seats";  // Party I after sorting
  EXPECT_EQ(partiesOriginal.at(2).getSeatsWon(), 3)
      << "allocateSeatsPartyMembersEqualSeats: Party D should've won 3 seats";  // Party D after sorting
}

TEST_F(OPLTest, allocateSeatsNoRemainder) {
  // 10, 10, 10;; ballots = 30; quota = 10; seats = 3
  // D = 1, R = 1; I = 1;
  opl->setQuota(10);
  opl->setNumSeats(3);

  Ballot b1(std::vector<int>{1, 0, 0});
  for (int i = 0; i < 2; i++) {  // add 2 ballots to Ryan
    opl->getParties().at(1).getPartyMembers().at(0)->addBallot(b1);
  }
  for (int i = 0; i < 8; i++) {  // add 8 ballots to Ian
    opl->getParties().at(2).getPartyMembers().at(0)->addBallot(b1);
  }
  opl->allocateSeats();
  std::vector<Party> partiesOriginal = opl->getParties();

  EXPECT_EQ(partiesOriginal.at(0).getSeatsWon(), 1)
      << "allocateSeatsNoRemainder: Party R should've won 1 seats";  // Party R
                                                                     // after
                                                                     // sorting
  EXPECT_EQ(partiesOriginal.at(1).getSeatsWon(), 1)
      << "allocateSeatsNoRemainder: Party I should've won 1 seats";  // Party I
                                                                     // after
                                                                     // sorting
  EXPECT_EQ(partiesOriginal.at(2).getSeatsWon(), 1)
      << "allocateSeatsNoRemainder: Party D should've won 1 seats";  // Party D
                                                                     // after
                                                                     // sorting
  EXPECT_EQ(partiesOriginal.at(0).getRemainder(), 0)
      << "allocateSeatsNoRemainder: Party R should've had a remainder of 0";
  EXPECT_EQ(partiesOriginal.at(1).getRemainder(), 0)
      << "allocateSeatsNoRemainder: Party R should've had a remainder of 0";
  EXPECT_EQ(partiesOriginal.at(2).getRemainder(), 0)
      << "allocateSeatsNoRemainder: Party R should've had a remainder of 0";
}

TEST_F(OPLTest, findPartyWinnersWinners) {
  std::vector<Candidate *> winningCandidates;
  opl->getParties()[0].setSeatsWon(2);  // D.setSeats(2);
  opl->getParties()[1].setSeatsWon(2);  // R.setSeats(2);
  opl->getParties()[2].setSeatsWon(0);  // I.setSeats(0);
  opl->findPartyWinners();
  winningCandidates.push_back(opl->getParties().at(0).getPartyMembers().at(0));
  winningCandidates.push_back(opl->getParties().at(0).getPartyMembers().at(1));
  winningCandidates.push_back(opl->getParties().at(1).getPartyMembers().at(0));
  winningCandidates.push_back(opl->getParties().at(1).getPartyMembers().at(1));
  for (int i = 0; i < winningCandidates.size(); i++) {
    EXPECT_EQ(opl->getWinners().at(i).getName(),
              winningCandidates.at(i)->getName())
        << "findPartyWinnersWinners: the winning candidate vector is incorrect";
    EXPECT_EQ(opl->getWinners().at(i).getNumBallots(),
              winningCandidates.at(i)->getNumBallots())
        << "findPartyWinnersWinners: the winning candidate vector is incorrect";
    EXPECT_EQ(opl->getWinners().at(i).getParty(),
              winningCandidates.at(i)->getParty())
        << "findPartyWinnersWinners: the winning candidate vector is incorrect";
  }
}

TEST_F(OPLTest, findPartyWinnersLosers) {
  std::vector<Candidate *> losingCandidates;
  opl->getParties()[0].setSeatsWon(2);  // D.setSeats(2);
  opl->getParties()[1].setSeatsWon(2);  // R.setSeats(2);
  opl->getParties()[2].setSeatsWon(0);  // I.setSeats(0);
  opl->findPartyWinners();
  losingCandidates.push_back(opl->getParties().at(0).getPartyMembers().at(2));
  losingCandidates.push_back(opl->getParties().at(2).getPartyMembers().at(0));
  for (int i = 0; i < losingCandidates.size(); i++) {
    EXPECT_EQ(opl->getLosers().at(i).getName(),
              losingCandidates.at(i)->getName())
        << "findPartyWinnersWinners: the losing candidate vector is incorrect";
    EXPECT_EQ(opl->getLosers().at(i).getNumBallots(),
              losingCandidates.at(i)->getNumBallots())
        << "findPartyWinnersWinners: the losing candidate vector is incorrect";
    EXPECT_EQ(opl->getLosers().at(i).getParty(),
              losingCandidates.at(i)->getParty())
        << "findPartyWinnersWinners: the losing candidate vector is incorrect";
  }
}

TEST_F(OPLTest, assignParty) {
  OPL opl2("OPL", 3, 4, 11);
  Candidate *Don;
  Candidate *Regina;
  Candidate *Issac;

  Don = new Candidate('D', "Don");
  Regina = new Candidate('R', "Regina");
  Issac = new Candidate('I', "Issac");

  Ballot b1(std::vector<int>{1, 0, 0});
  for (int i = 0; i < 5; i++) {  // give 5 ballots to Don
    Don->addBallot(b1);
  }
  for (int i = 0; i < 4; i++) {  // give 4 ballots to Regina
    Regina->addBallot(b1);
  }
  for (int i = 0; i < 2; i++) {  // give 2 ballots to Issac
    Issac->addBallot(b1);
  }

  Party D('D');
  Party R('R');
  Party I('I');

  std::vector<Party> parties{D, R, I};
  opl2.setParties(parties);

  opl2.addCandidate(*Don);
  opl2.addCandidate(*Regina);
  opl2.addCandidate(*Issac);

  opl2.assignParty();
  std::vector<Party> parties2 = opl2.getParties();
  EXPECT_EQ(parties2.at(0).getPartyMembers().at(0)->getName(), "Don")
      << "assignParty: Don was added to the wrong party";
  EXPECT_EQ(parties2.at(0).getPartyMembers().at(0)->getNumBallots(), 5)
      << "assignParty: Don was added to the wrong party";
  EXPECT_EQ(parties2.at(0).getPartyMembers().at(0)->getParty(), 'D')
      << "assignParty: Don was added to the wrong party";

  EXPECT_EQ(parties2.at(1).getPartyMembers().at(0)->getName(), "Regina")
      << "assignParty: Regina was added to the wrong party";
  EXPECT_EQ(parties2.at(1).getPartyMembers().at(0)->getNumBallots(), 4)
      << "assignParty: Regina was added to the wrong party";
  EXPECT_EQ(parties2.at(1).getPartyMembers().at(0)->getParty(), 'R')
      << "assignParty: Regina was added to the wrong party";

  EXPECT_EQ(parties2.at(2).getPartyMembers().at(0)->getName(), "Issac")
      << "assignParty: Issac was added to the wrong party";
  EXPECT_EQ(parties2.at(2).getPartyMembers().at(0)->getNumBallots(), 2)
      << "assignParty: Issac was added to the wrong party";
  EXPECT_EQ(parties2.at(2).getPartyMembers().at(0)->getParty(), 'I')
      << "assignParty: Issac was added to the wrong party";
}

TEST_F(OPLTest, partyExistsPartyDoesExist) {
  EXPECT_TRUE(opl->partyExists('D'))
      << "partyExistsPartyDoesExist: Party D should exist";
}

TEST_F(OPLTest, partyExistsPartyDoesNotExist) {
  EXPECT_FALSE(opl->partyExists('Q'))
      << "partyExistsPartyDoesNotExist: Party Q should not exist";
}