// Copyright 2020 Kornev Nikita

#include <iostream>
#include <vector>
#include <stack>
#include <string>
#include "include/converter.h"
using std::vector;

vector<int> converter::convert_dec_to_smaller(const vector<int>& value,
  const int& target_system) {
  int int_value;
  stack<int> temp_stack;
  vector<int> res;
  int remainder;

  int_value = parse(value);

  while (int_value > 0) {
    remainder = int_value % target_system;
    temp_stack.push(remainder);
    int_value /= target_system;
  }

  auto stack_size = temp_stack.size();

  for (size_t i = 0; i < stack_size; i++) {
    remainder = temp_stack.top();
    res.push_back(remainder);
    temp_stack.pop();
  }

  return res;
}

vector<int> converter::convert_smaller_to_dec(const vector<int>& value,
  const int& this_system) {
  int temp = 0;

  for (size_t i = 0; i < value.size(); i++) {
    temp += value[i] * static_cast<int>(pow(this_system, value.size() - i - 1));
  }

  vector<int> res = parse(temp);

  return res;
}

vector<char> converter::convert_dec_to_hex(const int& value) {
  int temp_value = value;
  stack<char> temp_stack;
  vector<char> res;
  char element;

  while (temp_value > 0) {
    auto remainder = temp_value % 16;

    if (remainder > 9) {
      /*if (remainder == 10)
        element = 'A';
      if (remainder == 11)
        element = 'B';
      if (remainder == 12)
        element = 'C';
      if (remainder == 13)
        element = 'D';
      if (remainder == 14)
        element = 'E';
      if (remainder == 15)
        element = 'F';*/
      switch (remainder) {
      case 10:
        element = 'A';
        break;
      case 11:
        element = 'B';
        break;
      case 12:
        element = 'C';
        break;
      case 13:
        element = 'D';
        break;
      case 14:
        element = 'E';
        break;
      case 15:
        element = 'F';
        break;
      }
    } else {
      element = remainder + '0';
    }

    temp_stack.push(element);
    temp_value /= 16;
  }

  auto stack_size = temp_stack.size();

  for (size_t i = 0; i < stack_size; i++) {
    element = temp_stack.top();
    res.push_back(element);
    temp_stack.pop();
  }
  return res;
}

int converter::convert_hex_to_dec(const vector<char>& value) {
  int res = 0;
  int temp = 0;

  for (size_t i = 0; i < value.size(); i++) {
    if (isdigit(value[i])) {
      temp = atoi(string({ static_cast<char>(value[i]) }).c_str());
    } else {
      switch (value[i]) {
        /*if (value[i] == 'A')
          temp = 10;
        if (value[i] == 'B')
          temp = 11;
        if (value[i] == 'C')
          temp = 12;
        if (value[i] == 'D')
          temp = 13;
        if (value[i] == 'E')
          temp = 14;
        if (value[i] == 'F')
          temp = 15;*/
      case 'A':
        temp = 10;
        break;
      case 'B':
        temp = 11;
        break;
      case 'C':
        temp = 12;
        break;
      case 'D':
        temp = 13;
        break;
      case 'E':
        temp = 14;
        break;
      case 'F':
        temp = 15;
        break;
      }
    }
    res += temp * static_cast<int>(pow(16, value.size() - i - 1));
  }

  return res;
}

vector<int> converter::convert(const vector<int>& value,
  const int& this_system, const int& target_system) {
  auto res = value;

  if (this_system != 10)
      res = convert_smaller_to_dec(value, this_system);

  if (target_system != 10)
      res = convert_dec_to_smaller(res, target_system);

  return res;
}

int converter::parse(const vector<int>& value) {
  string temp = "";
  int res;
  for (size_t i = 0; i < value.size(); i++)
    temp += value[i] + '0';
  res = atoi(temp.c_str());
  return res;
}

vector<int> converter::parse(const int& value) {
  string temp = std::to_string(value);
  vector<int> res;

  for (size_t i = 0; i < temp.size(); i++)
    res.push_back(temp[i] - 48);
  return res;
}

vector<char> converter::convert_to_16(const vector<int>& value,
  const int& this_system, const int& target_system) {
  vector<int> temp = convert_smaller_to_dec(value, this_system);
  int temp_int = parse(temp);

  auto res = convert_dec_to_hex(temp_int);
  return res;
}

vector<int> converter::convert_16_to(const vector<char>& value,
  const int& this_system, const int& target_system) {
  auto temp = convert_hex_to_dec(value);

  vector<int> temp_vector = parse(temp);

  if (target_system != 10)
      temp_vector = convert_dec_to_smaller(temp_vector, target_system);

  return temp_vector;
}
