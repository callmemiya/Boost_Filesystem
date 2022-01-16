// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <boost/filesystem.hpp>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct Date {
  unsigned int year;
  unsigned int month;
  unsigned int day;
};

struct File {
  std::string name;
  std::string broker;
  std::string type;
  size_t number;
  Date date;
  std::string extension;
};

class Analys {
 public:
  explicit Analys(const boost::filesystem::path& pathToFtp);
  void start();
  void printAllFiles(std::ostream& out);
  void printAccountInfo(std::ostream& out);
  const boost::filesystem::path& getPathToFtp() const;

 private:
  boost::filesystem::path pathToFtp;
  std::vector<File> files;
  std::vector<std::string> directories;
  std::map<size_t, std::vector<File>> accounts;
  void startAnalise(const boost::filesystem::path& path);
  File parseFilename(std::string filename);
  void anDir(const boost::filesystem::path& path);
  void anFile(const boost::filesystem::path& path);
};

bool operator<(const File& lhs, const File& rhs);
std::ostream& operator<<(std::ostream& out, const Date& date);

#endif  // INCLUDE_HEADER_HPP_
