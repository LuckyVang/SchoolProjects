#include "../src/helpers.h"

int OPLBallotToIndex(std::string ballot) { return ballot.find('1'); }

int IRBallotToIndex(std::string ballot) {
  int index = 0;
  std::string number{};
  int length = ballot.find('1');
  std::string line = ballot.substr(0, length);
  std::stringstream strStream(line);

  while (std::getline(strStream, number, ',')) {
    index++;
  }

  return index;
}

std::vector<int> BallotToVec(int num, std::string ballot) {
  std::vector<int> result(num);
  std::stringstream strStream(ballot);
  std::string val;

  for (int i = 0; std::getline(strStream, val, ','); i++) {
    if (val.length() != 0) {
      result.at(i) = std::stoi(val);
    }
  }

  return result;
}

std::vector<int> IRBallotToVec(int num, std::string ballot) {
  std::vector<int> result(num);
  std::vector<int> ballotVec = BallotToVec(num, ballot);

  for (int i = 0; i < num; i++) {
    if (ballotVec.at(i) != 0) {
      result.at(ballotVec.at(i) - 1) = i + 1;
    }
  }

  return result;
}

std::string popItem(std::string &line, char l, char r) {
  std::size_t open, close, len;
  std::string name;
  open = line.find(l);
  close = line.find(r);
  len = close - open;

  name = line.substr(open + 1, (len)-1);
  line = line.substr(close + 1, line.length() - close - 1);

  return name;
}

std::vector<std::string> extractOPLNames(std::string line) {
  std::vector<std::string> names;
  std::string name;
  char open = '[';
  char close = ']';

  while ((name = popItem(line, open, close)) != "") {
    names.push_back(name);
  }

  return names;
}

std::vector<std::string> extractIRNames(std::string line) {
  std::vector<std::string> names;
  std::stringstream strStream(line);
  std::string name;

  while (std::getline(strStream, name, ',')) {
    names.push_back(name);
  }

  return names;
}

void printVec(std::vector<std::string> vec) {
  for (auto it = vec.begin(); it != vec.end(); it++) {
    std::cout << "\t" << *it << std::endl;
  }
}

void printVecI(std::vector<int> vec) {
  for (auto it = vec.begin(); it != vec.end(); it++) {
    std::cout << "\t" << *it << " ";
  }
  std::cout << std::endl;
}
