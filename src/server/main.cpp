// MIT License
//
// Copyright (c) 2022 Andrew SASSOYE, Constantin GUNDUZ, Gregory VAN DER PLUIJM,
// Thomas LEUTSCHER
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#include <QCoreApplication>
#include <QHostAddress>
#include <QString>
#include <regex>

#include "server/tetris_server.hpp"

int main(int argc, char *argv[]) {
  if (argc != 3 && argc != 1)
    throw std::invalid_argument("invalid input from the start");

  // Verify ip and port
  std::string regex = "^(?:[0-9]{1,3}.){3}[0-9]{1,3}$";
  if (!std::regex_match(argv[1], std::regex(regex)))
    throw std::invalid_argument("ip address is not valid");

  QString IP = argv[1];
  QHostAddress IPAddress = QHostAddress(IP);
  int port = 0;

  if (!std::isdigit(std::strtol(argv[2], nullptr, 10)) &&
      (port = std::strtol(argv[2], nullptr, 10)) <= 0 && port >= 65537)
    throw std::invalid_argument("port is not valid");

  QCoreApplication app(argc, argv);
  tetris::server::Tetris_Server server{&app, IPAddress, port};
  return QCoreApplication::exec();
}