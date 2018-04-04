/******************************************************************************
MIT License

Copyright (c) 2018 Rainerum Robotics Raspberry Pi Community

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************/
#include "agenda-server.hpp"

#include <sstream>
#include <cpprest/http_msg.h>

using namespace web;
using namespace http;

void Agenda_onGetPing(http_request message) {
  static const auto response = "version=0.1.0";
  message.reply(status_codes::OK, response);
}

void Agenda_onGetEntriesLength(http_request message) {
  static const auto param = "length=";
  std::ostringstream oss;
  uint32_t length = 0;
  // TODO: Set length to the number of entries found in the agenda.
  oss << param << length;
  message.reply(status_codes::OK, oss.str());
}

void Agenda_onGetEntries(web::http::http_request message) {
  message.reply(status_codes::OK, "NOT YET IMPLEMENTED!");
}

void Agenda_onGetEntryItem(web::http::http_request message, int position) {
  static const auto param = "position=";
  std::ostringstream oss;
  // TODO: Set length to the number of entries found in the agenda.
  oss << param << position;
  message.reply(status_codes::OK, oss.str());
}
