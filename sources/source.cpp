// Copyright 2018 Your Name <your_email>

#include <header.hpp>
#include <iomanip>

bool operator<(const File& lhs, const File& rhs) {
  return std::make_tuple(lhs.date.year, lhs.date.month, lhs.date.day) <
         std::make_tuple(rhs.date.year, rhs.date.month, rhs.date.day);
}

std::ostream& operator<<(std::ostream& out, const Date& date) {
  out << date.year << "-" << date.month << "-" << date.day;
  return out;
}

Analys::Analys(const boost::filesystem::path& path) {
  if (path.empty()) {
    pathToFtp = boost::filesystem::path{".."};
  } else {
    pathToFtp = path;
  }
}
void Analys::start() { startAnalise(pathToFtp); }

void Analys::printAllFiles(std::ostream& out) {
  for (const auto& file : files) out << file.broker << " " << file.name << '\n';
}

void Analys::printAccountInfo(std::ostream& out) {
  for (const auto& acc : accounts) {
    out << "broker: " << acc.second[0].broker << " ";
    out << " account: ";
    out << std::setw(8) << std::setfill('0') << acc.first << " ";
    out << " files: " << acc.second.size() << " ";
    out << " lastdate: "
        << std::max_element(acc.second.begin(), acc.second.end())->date << " ";
    out << '\n';
  }
}

void Analys::startAnalise(const boost::filesystem::path& path) {
  for (const auto& iter : boost::filesystem::directory_iterator{path}) {
    if (boost::filesystem::is_regular_file(iter)) {
      anFile(iter);
    } else if (boost::filesystem::is_directory(iter)) {
      anDir(iter);
    }
  }
  if (!directories.empty()) {
    directories.pop_back();
  }
}

File Analys::parseFilename(std::string filename) {
  File file;
  file.name = filename;
  file.type = filename.substr(0, filename.find('_'));
  filename = filename.substr(filename.find('_') + 1);
  file.number =
      std::stoi(filename.substr(0, filename.find('_')));
  filename = filename.substr(filename.find('_') + 1);
  file.date.year = std::stoi(filename.substr(0, 4));
  file.date.month = std::stoi(filename.substr(4, 2));
  file.date.day = std::stoi(filename.substr(6, 2));
  filename = filename.substr(8);
  if (filename[0] != '.' || filename.substr(0, 4) == ".old") {
    throw std::exception();
  } else if (filename.substr(1).find('.') != std::string::npos) {
    throw std::exception();
  }
  if (filename != ".txt") {
    throw std::exception();
  }
  file.extension = filename;
  return file;
}

void Analys::anDir(const boost::filesystem::path& Path) {
  directories.push_back(Path.stem().string());
  startAnalise(Path);
}

void Analys::anFile(const boost::filesystem::path& Path) {
  try {
    File file = parseFilename(Path.filename().string());
    file.broker = directories.back();
    files.emplace_back(file);
    accounts[file.number].emplace_back(file);
  } catch (std::exception& ex) {
  }
}
const boost::filesystem::path& Analys::getPathToFtp() const {
  return pathToFtp;
}

/*int main(int argc, char* argv[]) {
  std::string str_Path;
  boost::filesystem::path Path;
  if (argc <= 1) {
    Path = "misc/ftp";
  } else {
    Path = argv[1];
    str_Path = argv[1];
  }
  if (!boost::filesystem::exists(Path)) {
    throw std::runtime_error{ "unable to open this Path " + str_Path };
  }
  Analys m(Path);
  m.start();
  return 0;
}*/
