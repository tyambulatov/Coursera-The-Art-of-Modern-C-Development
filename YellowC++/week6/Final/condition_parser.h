#pragma once

#include <iostream>
#include <memory>

#include "node.h"
#include "token.h"

using namespace std;

string ParseEvent(istream& is);

shared_ptr<Node> ParseCondition(istream& is);
