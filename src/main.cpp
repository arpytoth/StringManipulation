/*
 *  String Manipulatin by Arpad Toth
 *  Copyright (C) 2016  Arpad Toth
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Arpad Toth <arpytoth@live.com>
 */
#include "precise_timer.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

#define TEST_SIZE 1000000


void testStringCached() {
  toth::PreciseTimer timer;
  timer.start();

  std::string str;
  for (int i = 0; i < TEST_SIZE; ++i) {
    str += "Hello";
    str += std::to_string(i);
    str += "World";
    str = "";
  }
  timer.stop();

  std::cout << "Cached string operations took: " <<  timer.milliseconds() << "msecs" << std::endl;
}

void testString() {
  toth::PreciseTimer timer;
  timer.start();

  for (int i = 0; i < TEST_SIZE; ++i) {
    std::string str;
    str += "Hello";
    str += std::to_string(i);
    str += "World";
  }
  timer.stop();

  std::cout << "String operations took: " <<  timer.milliseconds() << "msecs" << std::endl;
}

void testCStringCached() {
  toth::PreciseTimer timer;
  timer.start();

  char buffer[40];
  for (int i = 0; i < TEST_SIZE; ++i) {
    sprintf(buffer, "Hello%dWorld", i);
    buffer[0] = '\0';
  }
  timer.stop();

  std::cout << "Cached C String operations took: " <<  timer.milliseconds() << "msecs" << std::endl;
}

void testCString() {
  toth::PreciseTimer timer;
  timer.start();

  for (int i = 0; i < TEST_SIZE; ++i) {
    char buffer[40];
    sprintf(buffer, "Hello%dWorld", i);
    buffer[0] = '\0';
  }
  timer.stop();

  std::cout << "C String operations took: " <<  timer.milliseconds() << "msecs" << std::endl;
}


void testStringStreamCached() {
  toth::PreciseTimer timer;
  timer.start();

  std::stringstream str;
  for (int i = 0; i < TEST_SIZE; ++i) {
    str << "Hello" << i << "World";
    str.str("");
  }
  timer.stop();

  std::cout << "Cached String Stream operations took: " <<  timer.milliseconds() << "msecs" << std::endl;
}

void testStringStream() {
  toth::PreciseTimer timer;
  timer.start();

  for (int i = 0; i < TEST_SIZE; ++i) {
    std::stringstream str;
    str << "Hello" << i << "World";
    str.str("");
  }
  timer.stop();

  std::cout << "String Stream operations took: " <<  timer.milliseconds() << "msecs" << std::endl;
}


int main() 
{
  std::cout << "No Caching: " << std::endl;
  std::cout << "------------" << std::endl;
  testString();
  testCString();
  testStringStream();

  std::cout << std::endl << "With Caching: " << std::endl;
  std::cout << "--------------" << std::endl;
  testStringCached();
  testCStringCached();
  testStringStreamCached();

  return 0;
}
